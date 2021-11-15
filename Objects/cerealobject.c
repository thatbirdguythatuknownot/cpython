/* PyCereal (cereal) object implementation */

#define PY_SSIZE_T_CLEAN
#include "Python.h"

/*[clinic input]
class cereal "PyCerealObject *" "&PyCereal_Type"
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=fd0585a7bbe1becb]*/

#include "clinic/cerealobject.c.h"

/* Direct API functions */

PyObject *
PyCereal_New(Py_ssize_t ml)
{
    PyCerealObject *new;

    if (ml < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 1 to PyCereal_New(): %zd",
                     ml);
        return NULL;
    }
    else if (ml == 0) {
        PyErr_Format(PyExc_ValueError,
                     "cereal bowl cannot have a capacity of 0");
        return NULL;
    }

    new = PyObject_New(PyCerealObject, &PyCereal_Type);
    if (new == NULL) {
        return NULL;
    }

    Py_SET_SIZE(new, ml);
    new->size = ml;
    new->milliliters = 0;
    new->is_prepared = 0;

    return (PyObject *)new;
}

PyObject *
PyCereal_FromFields(Py_ssize_t size, Py_ssize_t ml)
{
    PyCerealObject *new;

    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 1 to PyCereal_FromFields(): %zd",
                     size);
        return NULL;
    }
    else if (size == 0) {
        PyErr_SetString(PyExc_ValueError,
                        "cereal bowl cannot have a capacity of 0");
        return NULL;
    }

    if (ml < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_FromFields(): %zd",
                     ml);
        return NULL;
    }
    else if (ml > size) {
        PyErr_SetString(PyExc_ValueError,
                        "cannot overflow cereal bowl");
    }

    new = PyObject_New(PyCerealObject, &PyCereal_Type);
    if (new == NULL) {
        return NULL;
    }

    Py_SET_SIZE(new, size);
    new->size = size;
    new->milliliters = ml;
    new->is_prepared = ml ? 1 : 0;

    return (PyObject *)new;
}

PyObject *
PyCereal_FromFieldsOverflow(Py_ssize_t size, Py_ssize_t ml)
{
    PyCerealObject *new;

    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 1 to PyCereal_FromFieldsOverflow(): %zd",
                     size);
        return NULL;
    }
    else if (size == 0) {
        PyErr_Format(PyExc_ValueError,
                     "cereal bowl cannot have a capacity of 0");
        return NULL;
    }

    if (ml < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_FromFieldsOverflow(): %zd",
                     ml);
        return NULL;
    }

    new = PyObject_New(PyCerealObject, &PyCereal_Type);
    if (new == NULL) {
        return NULL;
    }

    Py_SET_SIZE(new, size);
    new->size = size;
    new->milliliters = ml > size ? size : ml;
    new->is_prepared = ml ? 1 : 0;

    return (PyObject *)new;
}

int
PyCereal_Prepare(PyCerealObject *cereal, Py_ssize_t ml)
{
    if (cereal->is_prepared) {
        PyErr_SetString(PyExc_TypeError,
                        "cannot prepare an already prepared cereal bowl");
        return NULL;
    }

    if (ml < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_Prepare(): %zd",
                     size);
        return -1;
    }
    else if (ml == 0) {
        PyErr_SetString(PyExc_ValueError,
                        "cannot prepare 0 milliliters of cereal");
        return -1;
    }
    else if (ml > cereal->size) {
        PyErr_Format(PyExc_ValueError,
                     "cereal bowl cannot hold %zd milliliters of cereal, "
                     "it can only hold %zd milliliters",
                     ml, cereal->size);
        return -1;
    }

    cereal->is_prepared = 1;
    cereal->milliliters = ml;
    return 0;
}

int
PyCereal_Eat(PyCerealObject *cereal, Py_ssize_t ml)
{
    if (cereal->is_prepared == 0) {
        PyErr_SetString(PyExc_TypeError,
                        "cannot eat from unprepared cereal bowl");
        return NULL;
    }

    if (ml == 0) {
        return 0;
    }
    else if (ml == -1) {
        ml = cereal->milliliters;
    }
    else if (ml < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_Eat(): %zd",
                     size);
        return -1;
    }
    else if (ml > cereal->milliliters) {
        PyErr_Format(PyExc_ValueError,
                     "cannot eat %zd milliliters of cereal, "
                     "cereal bowl only has %zd milliliters",
                     ml, cereal->milliliters);
        return -1;
    }

    cereal->is_prepared = 1;
    cereal->milliliters -= ml;
    return 0;
}

int
PyCereal_Finish(PyCerealObject *cereal)
{
    if (cereal->is_prepared == 0) {
        PyErr_SetString(PyExc_TypeError,
                        "cannot finish an unprepared cereal bowl");
        return NULL;
    }
    if (cereal->milliliters > 0) {
        PyErr_Format(PyExc_TypeError,
                     "cannot finish a non-empty cereal bowl with "
                     "%zd milliliters of cereal still in it",
                     cereal->milliliters);
        return -1;
    }

    cereal->is_prepared = 0;
    return 0;
}

PyObject *
PyCereal_Add(PyCerealObject *cereal, Py_ssize_t ml)
{
    Py_ssize_t size, milliliters;

    if (cereal->is_prepared == 0) {
        PyErr_SetString(PyExc_TypeError,
                        "cannot add to unprepared cereal bowl");
        return NULL;
    }

    if (ml < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_Add(): %zd",
                     ml);
        return NULL;
    }
    if ((milliliters = cereal->milliliters + ml) >
        (size = cereal->size))
    {
        PyErr_Format(PyExc_TypeError,
                     "cannot add %zd milliliters of cereal to "
                     "cereal bowl with %zd milliliters already "
                     "in it (max capacity %zd milliliters)",
                     ml, cereal->milliliters, size);
        return NULL;
    }

    return PyCereal_FromFields(milliliters, size);
}

PyObject *
PyCereal_Subtract(PyCerealObject *cereal, Py_ssize_t ml)
{
    if (cereal->is_prepared == 0) {
        PyErr_SetString(PyExc_TypeError,
                        "cannot subtract from unprepared cereal bowl");
        return NULL;
    }

    if (ml < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_Subtract(): %zd",
                     ml);
        return NULL;
    }
    if (ml > cereal->milliliters)
    {
        PyErr_Format(PyExc_TypeError,
                     "cannot subtract %zd milliliters of cereal "
                     "from cereal bowl with %zd milliliters in it",
                     ml, cereal->milliliters);
        return NULL;
    }

    return PyCereal_FromFields(cereal->milliliters - ml, cereal->size);
}

PyObject *
PyCereal_Multiply(PyCerealObject *cereal, Py_ssize_t size)
{
    Py_ssize_t size_bowl, milliliters;

    if (cereal->is_prepared == 0) {
        PyErr_SetString(PyExc_TypeError,
                        "cannot multiply with unprepared cereal bowl");
        return NULL;
    }

    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_Multiply(): %zd",
                     size);
        return NULL;
    }
    if ((milliliters = cereal->milliliters * size) >
        (size_bowl = cereal->size))
    {
        PyErr_Format(PyExc_TypeError,
                     "cannot multiply %zd milliliters of cereal "
                     "with %zd (max capacity %zd milliliters)",
                     cereal->milliliters, ml, size_bowl);
        return NULL;
    }

    return PyCereal_FromFields(milliliters, size_bowl);
}

PyObject *
PyCereal_Divide(PyCerealObject *cereal, Py_ssize_t size)
{
    Py_ssize_t milliliters;

    if (cereal->is_prepared == 0) {
        PyErr_SetString(PyExc_TypeError,
                        "cannot divide unprepared cereal bowl");
        return NULL;
    }

    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_Divide(): %zd",
                     size);
        return NULL;
    }
    else if (size == 0) {
        PyErr_SetString(PyExc_ZeroDivisionError,
                        "division by 0");
        return NULL;
    }

    return PyCereal_FromFields(cereal->milliliters / size, cereal->size);
}

PyObject *
PyCereal_Resize(PyCerealObject *cereal, Py_ssize_t size)
{
    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_Resize(): %zd",
                     size);
        return NULL;
    }
    if (size < cereal->milliliters) {
        PyErr_SetString(PyExc_ValueError,
                        "cannot overflow cereal bowl");
        return NULL;
    }

    return PyCereal_FromFields(size, cereal->milliliters);
}

PyObject *
PyCereal_ResizeOverflow(PyCerealObject *cereal, Py_ssize_t size)
{
    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_ResizeOverflow(): %zd",
                     size);
        return NULL;
    }

    return PyCereal_FromFieldsOverflow(size, cereal->milliliters);
}

PyObject *
PyCereal_AddSizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)
{
    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_AddSizeAbsolute(): %zd",
                     size);
        return NULL;
    }

    return PyCereal_FromFields(cereal->size+size, cereal->milliliters);
}

PyObject *
PyCereal_SubtractSizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)
{
    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_SubtractSizeAbsolute(): %zd",
                     size);
        return NULL;
    }

    size = cereal->size - size;
    if (size < cereal->milliliters) {
        PyErr_SetString(PyExc_ValueError,
                        "cannot overflow cereal bowl");
        return NULL;
    }

    return PyCereal_FromFields(size, cereal->milliliters);
}

PyObject *
PyCereal_MultiplySizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)
{
    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_MultiplySizeAbsolute(): %zd",
                     size);
        return NULL;
    }

    return PyCereal_FromFields(cereal->size*size, cereal->milliliters);
}

PyObject *
PyCereal_AddSizeRelative(PyCerealObject *cereal, Py_ssize_t size)
{
    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_AddSizeRelative(): %zd",
                     size);
        return NULL;
    }

    return PyCereal_FromFields(cereal->milliliters+size, cereal->milliliters);
}

PyObject *
PyCereal_MultiplySizeRelative(PyCerealObject *cereal, Py_ssize_t size)
{
    if (size < 0) {
        PyErr_Format(PyExc_TypeError,
                     "invalid argument 2 to PyCereal_MultiplySizeRelative(): %zd",
                     size);
        return NULL;
    }

    return PyCereal_FromFields(cereal->milliliters*size, cereal->milliliters);
}

/* ------------------------------------------------------------------------ */
/* Type slots */

/*[clinic input]
cereal.__init__

    capacity: Py_ssize_t
        The capacity of the cereal bowl
    milliliters: Py_ssize_t = 0
        The initial amount of cereal (in milliliters) in the bowl

[clinic start generated code]*/

static int
cereal___init___impl(PyCerealObject *self, Py_ssize_t capacity,
                     Py_ssize_t milliliters)
/*[clinic end generated code: output=0f3b87a8fbc62644 input=b53d6e062e3f81ae]*/
{
    Py_SET_SIZE(cereal, capacity);
    cereal->size = capacity;
    cereal->milliliters = milliliters > capacity ? capacity : milliliters;
    cereal->is_prepared = milliliters ? 1 : 0;
    return 0;
}

static PyObject *
cereal_repr(PyCerealObject *cereal)
{
    return PyUnicode_FromFormat("%s(capacity=%zd, milliliters=%zd)",
                                Py_TYPE(cereal)->tp_name, cereal->size,
                                cereal->milliliters);
}

static PyObject *
cereal_str(PyCerealObject *cereal)
{
    return PyUnicode_FromFormat("Cereal bowl that can hold %zd milliliters "
                                "with %zd milliliters of cereal in it",
                                cereal->size, cereal->milliliters);
}

static PyObject *
cereal_richcompare(PyObject *self, PyObject *other, int op)
{
    PyCerealObject *v, *w;

    if (!PyCereal_Check(self) || !PyCereal_Check(other)) {
        Py_RETURN_NOTIMPLEMENTED;
    }

    v = (PyCerealObject *)self;
    w = (PyCerealObject *)other;
    Py_RETURN_RICHCOMPARE(v->size, w->size, op);
}

static void
cereal_dealloc(PyCerealObject *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

/* ------------------------------------------------------------------------ */
/* Methods */

/*[clinic input]
cereal.prepare

    milliliters: Py_ssize_t
        How much milliliters of cereal to prepare. Must not exceed bowl capacity
    /

Prepare `milliliters` milliliters of cereal. `milliliters` must not exceed cereal bowl size.
[clinic start generated code]*/

static PyObject *
cereal_prepare_impl(PyCerealObject *self, Py_ssize_t milliliters)
/*[clinic end generated code: output=ad92a05b88f5445a input=e8e7a926f5b9ebdd]*/
{
    int status;
    status = PyCereal_Prepare(self, milliliters);
    if (status == -1) {
        return NULL;
    }
    Py_RETURN_NONE;
}

/*[clinic input]
cereal.eat

    milliliters: Py_ssize_t = -1
        How much milliliters of cereal to eat. Must not exceed amount of cereal in the bowl
        -1 means eat all the cereal
    /

Eat `milliliters` milliliters of cereal. `milliliters` must not exceed the amount of cereal in the bowl.
[clinic start generated code]*/

static PyObject *
cereal_eat_impl(PyCerealObject *self, Py_ssize_t milliliters)
/*[clinic end generated code: output=1c05e21cf6361b45 input=c523f7db8bd75812]*/
{
    int status;
    status = PyCereal_Eat(self, milliliters);
    if (status == -1) {
        return NULL;
    }
    Py_RETURN_NONE;
}

/*[clinic input]
cereal.finish

Finish the cereal in the cereal bowl.
[clinic start generated code]*/

static PyObject *
cereal_finish_impl(PyCerealObject *self)
/*[clinic end generated code: output=5bb510ac53e65f97 input=67321439ec3d3027]*/
{
    int status;
    status = PyCereal_Finish(self);
    if (status == -1) {
        return NULL;
    }
    Py_RETURN_NONE;
}

/*[clinic input]
cereal.add

    milliliters: Py_ssize_t
        How much milliliters of cereal to add
        Combined with the amount of cereal in the bowl, it must not exceed bowl capacity
    /

Add `milliliters` milliliters of cereal to the bowl. Result must not exceed bowl capacity.
[clinic start generated code]*/

static PyObject *
cereal_add_impl(PyCerealObject *self, Py_ssize_t milliliters)
/*[clinic end generated code: output=898eeec572cf21e2 input=f888aff99e790f55]*/
{
    PyObject *res;
    res = PyCereal_Add(self, milliliters);
    return res;
}

/*[clinic input]
cereal.subtract

    milliliters: Py_ssize_t
        How much milliliters of cereal to subtract
        It must be less than or equal to the amount of cereal in the bowl
    /

Subtract `milliliters` milliliters of cereal from the bowl. `milliliters` must be less than or equal to the amount of cereal in the bowl.
[clinic start generated code]*/

static PyObject *
cereal_subtract_impl(PyCerealObject *self, Py_ssize_t milliliters)
/*[clinic end generated code: output=958be41cb8f665bf input=8230388ccc49c6b9]*/
{
    PyObject *res;
    res = PyCereal_Subtract(self, milliliters);
    return res;
}

/*[clinic input]
cereal.multiply

    num: Py_ssize_t
        How much to multiply the amount of cereal in the bowl by
        Result must not exceed bowl capacity.
    /

Multiply the amount of cereal in the bowl by `num`. Results must not exceed bowl capacity.
[clinic start generated code]*/

static PyObject *
cereal_multiply_impl(PyCerealObject *self, Py_ssize_t num)
/*[clinic end generated code: output=ce73db43e4fc1ee2 input=a48a6814b973b588]*/
{
    PyObject *res;
    res = PyCereal_Multiply(self, num);
    return res;
}

/*[clinic input]
cereal.divide

    num: Py_ssize_t
        How much to divide the amount of cereal in the bowl by
        This argument cannot be 0.
    /

Divide the amount of cereal in the bowl by `num`. `num` must not be 0.
[clinic start generated code]*/

static PyObject *
cereal_divide_impl(PyCerealObject *self, Py_ssize_t num)
/*[clinic end generated code: output=344f7077fc5191ae input=5d67df1ef7d49693]*/
{
    PyObject *res;
    res = PyCereal_Divide(self, num);
    return res;
}

/*[clinic input]
cereal.resize

    size: Py_ssize_t
        The capacity of the cereal bowl in milliliters
        Must not be less than the amount of cereal in the bowl
    /

Return a resized cereal bowl with capacity `size` milliliters. `size` must be greater than or equal to the amount of cereal in the bowl.
[clinic start generated code]*/

static PyObject *
cereal_resize_impl(PyCerealObject *self, Py_ssize_t size)
/*[clinic end generated code: output=18bddfe74a44bbb5 input=b34b2a64f9cffb4e]*/
{
    PyObject *res;
    res = PyCereal_Resize(self, size);
    return res;
}

/*[clinic input]
cereal.resize_overflow

    size: Py_ssize_t
        The capacity of the cereal bowl in milliliters
    /

Return a resized cereal bowl with capacity `size` milliliters.
[clinic start generated code]*/

static PyObject *
cereal_resize_overflow_impl(PyCerealObject *self, Py_ssize_t size)
/*[clinic end generated code: output=b88688c03373346d input=c62c66fe7a1797c8]*/
{
    PyObject *res;
    res = PyCereal_ResizeOverflow(self, size);
    return res;
}

static PyMethodDef cereal_methods[] = {
    CEREAL_PREPARE_METHODDEF
    CEREAL_EAT_METHODDEF
    CEREAL_FINISH_METHODDEF
    CEREAL_ADD_METHODDEF
    CEREAL_SUBTRACT_METHODDEF
    CEREAL_MULTIPLY_METHODDEF
    CEREAL_DIVIDE_METHODDEF
    CEREAL_RESIZE_METHODDEF
    CEREAL_RESIZE_OVERFLOW_METHODDEF
    {NULL}
};

static PyMemberDef cereal_members[] = {
    {"capacity", T_PYSSIZET, offsetof(PyCerealObject, size), READONLY},
    {"size", T_PYSSIZET, offsetof(PyCerealObject, size), READONLY},
    {"milliliters", T_PYSSIZET, offsetof(PyCerealObject, milliliters), READONLY},
    {"is_prepared", T_INT, offsetof(PyCerealObject, is_prepared), READONLY},
    {NULL}
};

PyDoc_STRVAR(cereal_doc,
"cereal(int, int) -> cereal"
"\n\n"
"Construct a cereal bowl from capacity and prepared cereal.");

PyTypeObject PyCereal_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "cereal",
    sizeof(PyCerealObject),
    0,
    (destructor)cereal_dealloc,         /* tp_dealloc */
    0,                                  /* tp_vectorcall_offset */
    0,                                  /* tp_getattr */
    0,                                  /* tp_setattr */
    0,                                  /* tp_as_async */
    (reprfunc)cereal_repr,              /* tp_repr */
    0,                                  /* tp_as_number */
    0,                                  /* tp_as_sequence */
    0,                                  /* tp_as_mapping */
    0,                                  /* tp_hash */
    0,                                  /* tp_call */
    cereal_str,                         /* tp_str */
    PyObject_GenericGetAttr,            /* tp_getattro */
    0,                                  /* tp_setattro */
    0,                                  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE |
        _Py_TPFLAGS_MATCH_SELF,         /* tp_flags */
    cereal_doc,                         /* tp_doc */
    0,                                  /* tp_traverse */
    0,                                  /* tp_clear */
    (richcmpfunc)cereal_richcompare,    /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    0,                                  /* tp_iter */
    0,                                  /* tp_iternext */
    cereal_methods,                     /* tp_methods */
    cereal_members,                     /* tp_members */
    0,                                  /* tp_getset */
    0,                                  /* tp_base */
    0,                                  /* tp_dict */
    0,                                  /* tp_descr_get */
    0,                                  /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc)cereal___init__,          /* tp_init */
    PyType_GenericAlloc,                /* tp_alloc */
    PyType_GenericNew,                  /* tp_new */
    PyObject_Del,                       /* tp_free */
};
