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
"prepare($self, milliliters, /)\n"
"--\n"
"\n"
"Prepare `milliliters` milliliters of cereal. `milliliters` must not exceed cereal bowl size.\n"
"\n"
"  milliliters\n"
"    How much milliliters of cereal to prepare. Must not exceed bowl capacity");

#define CEREAL_PREPARE_METHODDEF    \
    {"prepare", (PyCFunction)cereal_prepare, METH_O, cereal_prepare__doc__},

static PyObject *
cereal_prepare_impl(PyCerealObject *self, Py_ssize_t milliliters);

static PyObject *
cereal_prepare(PyCerealObject *self, PyObject *arg)
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
    return_value = cereal_prepare_impl(self, milliliters);

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
/*[clinic end generated code: output=3f427c6575920a90 input=a9049054013a1b77]*/
