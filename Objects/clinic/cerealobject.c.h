/*[clinic input]
preserve
[clinic start generated code]*/

static int
cereal___init___impl(PyCerealObject *self, Py_ssize_t capacity,
                     Py_ssize_t milliliters);

static int
cereal___init__(PyObject *self, PyObject *args, PyObject *kwargs)
{
    int return_value = -1;
    static const char * const _keywords[] = {"capacity", "milliliters", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "cereal", 0};
    PyObject *argsbuf[2];
    PyObject * const *fastargs;
    Py_ssize_t nargs = PyTuple_GET_SIZE(args);
    Py_ssize_t noptargs = nargs + (kwargs ? PyDict_GET_SIZE(kwargs) : 0) - 1;
    Py_ssize_t capacity;
    Py_ssize_t milliliters = 0;

    fastargs = _PyArg_UnpackKeywords(_PyTuple_CAST(args)->ob_item, nargs, kwargs, NULL, &_parser, 1, 2, 0, argsbuf);
    if (!fastargs) {
        goto exit;
    }
    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(fastargs[0]);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        capacity = ival;
    }
    if (!noptargs) {
        goto skip_optional_pos;
    }
    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(fastargs[1]);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        milliliters = ival;
    }
skip_optional_pos:
    return_value = cereal___init___impl((PyCerealObject *)self, capacity, milliliters);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_prepare__doc__,
"prepare($self, milliliters, /, brand=\'\')\n"
"--\n"
"\n"
"Prepare `milliliters` milliliters of cereal. `milliliters` must not exceed cereal bowl size.\n"
"\n"
"  milliliters\n"
"    How much milliliters of cereal to prepare. Must not exceed bowl capacity\n"
"  brand\n"
"    The brand of cereal");

#define CEREAL_PREPARE_METHODDEF    \
    {"prepare", (PyCFunction)(void(*)(void))cereal_prepare, METH_FASTCALL|METH_KEYWORDS, cereal_prepare__doc__},

static PyObject *
cereal_prepare_impl(PyCerealObject *self, Py_ssize_t milliliters,
                    const char *brand);

static PyObject *
cereal_prepare(PyCerealObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"", "brand", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "prepare", 0};
    PyObject *argsbuf[2];
    Py_ssize_t noptargs = nargs + (kwnames ? PyTuple_GET_SIZE(kwnames) : 0) - 1;
    Py_ssize_t milliliters;
    const char *brand = "";

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 2, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(args[0]);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        milliliters = ival;
    }
    if (!noptargs) {
        goto skip_optional_pos;
    }
    if (!PyUnicode_Check(args[1])) {
        _PyArg_BadArgument("prepare", "argument 'brand'", "str", args[1]);
        goto exit;
    }
    Py_ssize_t brand_length;
    brand = PyUnicode_AsUTF8AndSize(args[1], &brand_length);
    if (brand == NULL) {
        goto exit;
    }
    if (strlen(brand) != (size_t)brand_length) {
        PyErr_SetString(PyExc_ValueError, "embedded null character");
        goto exit;
    }
skip_optional_pos:
    return_value = cereal_prepare_impl(self, milliliters, brand);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_eat__doc__,
"eat($self, milliliters=-1, /)\n"
"--\n"
"\n"
"Eat `milliliters` milliliters of cereal. `milliliters` must not exceed the amount of cereal in the bowl.\n"
"\n"
"  milliliters\n"
"    How much milliliters of cereal to eat. Must not exceed amount of cereal in the bowl\n"
"    -1 means eat all the cereal");

#define CEREAL_EAT_METHODDEF    \
    {"eat", (PyCFunction)(void(*)(void))cereal_eat, METH_FASTCALL, cereal_eat__doc__},

static PyObject *
cereal_eat_impl(PyCerealObject *self, Py_ssize_t milliliters);

static PyObject *
cereal_eat(PyCerealObject *self, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    Py_ssize_t milliliters = -1;

    if (!_PyArg_CheckPositional("eat", nargs, 0, 1)) {
        goto exit;
    }
    if (nargs < 1) {
        goto skip_optional;
    }
    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(args[0]);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        milliliters = ival;
    }
skip_optional:
    return_value = cereal_eat_impl(self, milliliters);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_finish__doc__,
"finish($self, /)\n"
"--\n"
"\n"
"Finish the cereal in the cereal bowl.");

#define CEREAL_FINISH_METHODDEF    \
    {"finish", (PyCFunction)cereal_finish, METH_NOARGS, cereal_finish__doc__},

static PyObject *
cereal_finish_impl(PyCerealObject *self);

static PyObject *
cereal_finish(PyCerealObject *self, PyObject *Py_UNUSED(ignored))
{
    return cereal_finish_impl(self);
}

PyDoc_STRVAR(cereal_add__doc__,
"add($self, milliliters, /)\n"
"--\n"
"\n"
"Add `milliliters` milliliters of cereal to the bowl. Result must not exceed bowl capacity.\n"
"\n"
"  milliliters\n"
"    How much milliliters of cereal to add\n"
"    Combined with the amount of cereal in the bowl, it must not exceed bowl capacity");

#define CEREAL_ADD_METHODDEF    \
    {"add", (PyCFunction)cereal_add, METH_O, cereal_add__doc__},

static PyObject *
cereal_add_impl(PyCerealObject *self, Py_ssize_t milliliters);

static PyObject *
cereal_add(PyCerealObject *self, PyObject *arg)
{
    PyObject *return_value = NULL;
    Py_ssize_t milliliters;

    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(arg);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        milliliters = ival;
    }
    return_value = cereal_add_impl(self, milliliters);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_subtract__doc__,
"subtract($self, milliliters, /)\n"
"--\n"
"\n"
"Subtract `milliliters` milliliters of cereal from the bowl. `milliliters` must be less than or equal to the amount of cereal in the bowl.\n"
"\n"
"  milliliters\n"
"    How much milliliters of cereal to subtract\n"
"    It must be less than or equal to the amount of cereal in the bowl");

#define CEREAL_SUBTRACT_METHODDEF    \
    {"subtract", (PyCFunction)cereal_subtract, METH_O, cereal_subtract__doc__},

static PyObject *
cereal_subtract_impl(PyCerealObject *self, Py_ssize_t milliliters);

static PyObject *
cereal_subtract(PyCerealObject *self, PyObject *arg)
{
    PyObject *return_value = NULL;
    Py_ssize_t milliliters;

    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(arg);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        milliliters = ival;
    }
    return_value = cereal_subtract_impl(self, milliliters);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_multiply__doc__,
"multiply($self, num, /)\n"
"--\n"
"\n"
"Multiply the amount of cereal in the bowl by `num`. Results must not exceed bowl capacity.\n"
"\n"
"  num\n"
"    How much to multiply the amount of cereal in the bowl by\n"
"    Result must not exceed bowl capacity.");

#define CEREAL_MULTIPLY_METHODDEF    \
    {"multiply", (PyCFunction)cereal_multiply, METH_O, cereal_multiply__doc__},

static PyObject *
cereal_multiply_impl(PyCerealObject *self, Py_ssize_t num);

static PyObject *
cereal_multiply(PyCerealObject *self, PyObject *arg)
{
    PyObject *return_value = NULL;
    Py_ssize_t num;

    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(arg);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        num = ival;
    }
    return_value = cereal_multiply_impl(self, num);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_divide__doc__,
"divide($self, num, /)\n"
"--\n"
"\n"
"Divide the amount of cereal in the bowl by `num`. `num` must not be 0.\n"
"\n"
"  num\n"
"    How much to divide the amount of cereal in the bowl by\n"
"    This argument cannot be 0.");

#define CEREAL_DIVIDE_METHODDEF    \
    {"divide", (PyCFunction)cereal_divide, METH_O, cereal_divide__doc__},

static PyObject *
cereal_divide_impl(PyCerealObject *self, Py_ssize_t num);

static PyObject *
cereal_divide(PyCerealObject *self, PyObject *arg)
{
    PyObject *return_value = NULL;
    Py_ssize_t num;

    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(arg);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        num = ival;
    }
    return_value = cereal_divide_impl(self, num);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_resize__doc__,
"resize($self, size, /)\n"
"--\n"
"\n"
"Return a resized cereal bowl with capacity `size` milliliters. `size` must be greater than or equal to the amount of cereal in the bowl.\n"
"\n"
"  size\n"
"    The capacity of the cereal bowl in milliliters\n"
"    Must not be less than the amount of cereal in the bowl");

#define CEREAL_RESIZE_METHODDEF    \
    {"resize", (PyCFunction)cereal_resize, METH_O, cereal_resize__doc__},

static PyObject *
cereal_resize_impl(PyCerealObject *self, Py_ssize_t size);

static PyObject *
cereal_resize(PyCerealObject *self, PyObject *arg)
{
    PyObject *return_value = NULL;
    Py_ssize_t size;

    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(arg);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        size = ival;
    }
    return_value = cereal_resize_impl(self, size);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_resize_overflow__doc__,
"resize_overflow($self, size, /)\n"
"--\n"
"\n"
"Return a resized cereal bowl with capacity `size` milliliters.\n"
"\n"
"  size\n"
"    The capacity of the cereal bowl in milliliters");

#define CEREAL_RESIZE_OVERFLOW_METHODDEF    \
    {"resize_overflow", (PyCFunction)cereal_resize_overflow, METH_O, cereal_resize_overflow__doc__},

static PyObject *
cereal_resize_overflow_impl(PyCerealObject *self, Py_ssize_t size);

static PyObject *
cereal_resize_overflow(PyCerealObject *self, PyObject *arg)
{
    PyObject *return_value = NULL;
    Py_ssize_t size;

    {
        Py_ssize_t ival = -1;
        PyObject *iobj = _PyNumber_Index(arg);
        if (iobj != NULL) {
            ival = PyLong_AsSsize_t(iobj);
            Py_DECREF(iobj);
        }
        if (ival == -1 && PyErr_Occurred()) {
            goto exit;
        }
        size = ival;
    }
    return_value = cereal_resize_overflow_impl(self, size);

exit:
    return return_value;
}

PyDoc_STRVAR(cereal_replace_brand__doc__,
"replace_brand($self, /, brand=\'\')\n"
"--\n"
"\n"
"Return a cereal bowl with a different brand named `brand`.\n"
"\n"
"  brand\n"
"    The brand of cereal");

#define CEREAL_REPLACE_BRAND_METHODDEF    \
    {"replace_brand", (PyCFunction)(void(*)(void))cereal_replace_brand, METH_FASTCALL|METH_KEYWORDS, cereal_replace_brand__doc__},

static PyObject *
cereal_replace_brand_impl(PyCerealObject *self, const char *brand);

static PyObject *
cereal_replace_brand(PyCerealObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"brand", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "replace_brand", 0};
    PyObject *argsbuf[1];
    Py_ssize_t noptargs = nargs + (kwnames ? PyTuple_GET_SIZE(kwnames) : 0) - 0;
    const char *brand = "";

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 0, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    if (!noptargs) {
        goto skip_optional_pos;
    }
    if (!PyUnicode_Check(args[0])) {
        _PyArg_BadArgument("replace_brand", "argument 'brand'", "str", args[0]);
        goto exit;
    }
    Py_ssize_t brand_length;
    brand = PyUnicode_AsUTF8AndSize(args[0], &brand_length);
    if (brand == NULL) {
        goto exit;
    }
    if (strlen(brand) != (size_t)brand_length) {
        PyErr_SetString(PyExc_ValueError, "embedded null character");
        goto exit;
    }
skip_optional_pos:
    return_value = cereal_replace_brand_impl(self, brand);

exit:
    return return_value;
}
/*[clinic end generated code: output=86649a2019304f62 input=a9049054013a1b77]*/
