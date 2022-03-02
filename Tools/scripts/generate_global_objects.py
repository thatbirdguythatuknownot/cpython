import contextlib
import glob
import os.path
import re
import sys


__file__ = os.path.abspath(__file__)
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
INTERNAL = os.path.join(ROOT, 'Include', 'internal')


STRING_LITERALS = {
    'empty': '',
    'dot': '.',
}
IGNORED = {
    'ACTION',  # Python/_warnings.c
    'ATTR',  # Python/_warnings.c and Objects/funcobject.c
    'DUNDER',  # Objects/typeobject.c
    'RDUNDER',  # Objects/typeobject.c
    'SPECIAL',  # Objects/weakrefobject.c
}
IDENTIFIERS = [
    # from ADD() Python/_warnings.c
    'default',
    'ignore',

    # from GET_WARNINGS_ATTR() in Python/_warnings.c
    'WarningMessage',
    '_showwarnmsg',
    '_warn_unawaited_coroutine',
    'defaultaction',
    'filters',
    'onceregistry',

    # from WRAP_METHOD() in Objects/weakrefobject.c
    '__bytes__',
    '__reversed__',

    # from COPY_ATTR() in Objects/funcobject.c
    '__module__',
    '__name__',
    '__qualname__',
    '__doc__',
    '__annotations__',

    # from SLOT* in Objects/typeobject.c
    '__abs__',
    '__add__',
    '__and__',
    '__dec__',
    '__divmod__',
    '__float__',
    '__floordiv__',
    '__getitem__',
    '__iadd__',
    '__iand__',
    '__ifloordiv__',
    '__ilshift__',
    '__imatmul__',
    '__imod__',
    '__imul__',
    '__inc__',
    '__int__',
    '__invert__',
    '__ior__',
    '__irshift__',
    '__isub__',
    '__itruediv__',
    '__ixor__',
    '__lshift__',
    '__matmul__',
    '__mod__',
    '__mul__',
    '__neg__',
    '__or__',
    '__pos__',
    '__pow__',
    '__radd__',
    '__rand__',
    '__rdivmod__',
    '__rfloordiv__',
    '__rlshift__',
    '__rmatmul__',
    '__rmod__',
    '__rmul__',
    '__ror__',
    '__rpow__',
    '__rrshift__',
    '__rshift__',
    '__rsub__',
    '__rtruediv__',
    '__rxor__',
    '__str__',
    '__sub__',
    '__truediv__',
    '__xor__',
]


#######################################
# helpers

def iter_files():
    for name in ('Modules', 'Objects', 'Parser', 'PC', 'Programs', 'Python'):
        root = os.path.join(ROOT, name)
        for dirname, _, files in os.walk(root):
            for name in files:
                if not name.endswith(('.c', '.h')):
                    continue
                yield os.path.join(dirname, name)


def iter_global_strings():
    id_regex = re.compile(r'\b_Py_ID\((\w+)\)')
    str_regex = re.compile(r'\b_Py_DECLARE_STR\((\w+), "(.*?)"\)')
    for filename in iter_files():
        with open(filename, encoding='utf-8') as infile:
            for lno, line in enumerate(infile, 1):
                for m in id_regex.finditer(line):
                    identifier, = m.groups()
                    yield identifier, None, filename, lno, line
                for m in str_regex.finditer(line):
                    varname, string = m.groups()
                    yield varname, string, filename, lno, line

def iter_to_marker(lines, marker):
    for line in lines:
        if line.rstrip() == marker:
            break
        yield line


class Printer:

    def __init__(self, file):
        self.level = 0
        self.file = file
        self.continuation = [False]

    @contextlib.contextmanager
    def indent(self):
        save_level = self.level
        try:
            self.level += 1
            yield
        finally:
            self.level = save_level

    def write(self, arg):
        eol = '\n'
        if self.continuation[-1]:
            eol = f' \\{eol}' if arg else f'\\{eol}'
        self.file.writelines(("    "*self.level, arg, eol))

    @contextlib.contextmanager
    def block(self, prefix, suffix="", *, continuation=None):
        if continuation is None:
            continuation = self.continuation[-1]
        self.continuation.append(continuation)

        self.write(prefix + " {")
        with self.indent():
            yield
        self.continuation.pop()
        self.write("}" + suffix)


#######################################
# the global objects

START = '/* The following is auto-generated by Tools/scripts/generate_global_objects.py. */'
END = '/* End auto-generated code */'


def generate_global_strings(identifiers, strings):
    filename = os.path.join(INTERNAL, 'pycore_global_strings.h')

    # Read the non-generated part of the file.
    with open(filename) as infile:
        before = ''.join(iter_to_marker(infile, START))[:-1]
        for _ in iter_to_marker(infile, END):
            pass
        after = infile.read()[:-1]

    # Generate the file.
    with open(filename, 'w', encoding='utf-8') as outfile:
        printer = Printer(outfile)
        printer.write(before)
        printer.write(START)
        with printer.block('struct _Py_global_strings', ';'):
            with printer.block('struct', ' literals;'):
                for name, literal in sorted(strings.items()):
                    printer.write(f'STRUCT_FOR_STR({name}, "{literal}")')
            outfile.write('\n')
            with printer.block('struct', ' identifiers;'):
                for name in sorted(identifiers):
                    assert name.isidentifier(), name
                    printer.write(f'STRUCT_FOR_ID({name})')
        printer.write(END)
        printer.write(after)


def generate_runtime_init(identifiers, strings):
    # First get some info from the declarations.
    nsmallposints = None
    nsmallnegints = None
    with open(os.path.join(INTERNAL, 'pycore_global_objects.h')) as infile:
        for line in infile:
            if line.startswith('#define _PY_NSMALLPOSINTS'):
                nsmallposints = int(line.split()[-1])
            elif line.startswith('#define _PY_NSMALLNEGINTS'):
                nsmallnegints = int(line.split()[-1])
                break
        else:
            raise NotImplementedError
    assert nsmallposints and nsmallnegints

    # Then target the runtime initializer.
    filename = os.path.join(INTERNAL, 'pycore_runtime_init.h')

    # Read the non-generated part of the file.
    with open(filename) as infile:
        before = ''.join(iter_to_marker(infile, START))[:-1]
        for _ in iter_to_marker(infile, END):
            pass
        after = infile.read()[:-1]

    # Generate the file.
    with open(filename, 'w', encoding='utf-8') as outfile:
        printer = Printer(outfile)
        printer.write(before)
        printer.write(START)
        with printer.block('#define _Py_global_objects_INIT', continuation=True):
            with printer.block('.singletons =', ','):
                # Global int objects.
                with printer.block('.small_ints =', ','):
                    for i in range(-nsmallnegints, nsmallposints):
                        printer.write(f'_PyLong_DIGIT_INIT({i}),')
                printer.write('')
                # Global bytes objects.
                printer.write('.bytes_empty = _PyBytes_SIMPLE_INIT(0, 0),')
                with printer.block('.bytes_characters =', ','):
                    for i in range(256):
                        printer.write(f'_PyBytes_CHAR_INIT({i}),')
                printer.write('')
                # Global strings.
                with printer.block('.strings =', ','):
                    with printer.block('.literals =', ','):
                        for name, literal in sorted(strings.items()):
                            printer.write(f'INIT_STR({name}, "{literal}"),')
                    with printer.block('.identifiers =', ','):
                        for name in sorted(identifiers):
                            assert name.isidentifier(), name
                            printer.write(f'INIT_ID({name}),')
                printer.write('')
                with printer.block('.tuple_empty =', ','):
                    printer.write('.ob_base = _PyVarObject_IMMORTAL_INIT(&PyTuple_Type, 0)')
        printer.write(END)
        printer.write(after)


def get_identifiers_and_strings() -> 'tuple[set[str], dict[str, str]]':
    identifiers = set(IDENTIFIERS)
    strings = dict(STRING_LITERALS)
    for name, string, *_ in iter_global_strings():
        if string is None:
            if name not in IGNORED:
                identifiers.add(name)
        else:
            if name not in strings:
                strings[name] = string
            elif string != strings[name]:
                raise ValueError(f'string mismatch for {name!r} ({string!r} != {strings[name]!r}')
    return identifiers, strings

#######################################
# the script

def main() -> None:
    identifiers, strings = get_identifiers_and_strings()

    generate_global_strings(identifiers, strings)
    generate_runtime_init(identifiers, strings)


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()
    args = parser.parse_args()
    main(**vars(args))
