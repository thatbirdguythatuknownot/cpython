#ifndef Py_CEREALOBJECT_H
#define Py_CEREALOBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

/* PyCereal object internals */

/* PyCerealObject represents a cereal bowl.
 * Contrary to popular opinion, PyCerealObject DOES NOT
 : represent cereal itself.
 * PyCerealObject inspired by <@235904856106336257> (Cypheriel#3463)
 */

#ifndef Py_LIMITED_API
#  define Py_CPYTHON_CEREALOBJECT_H
#  include "cpython/cerealobject.h"
#  undef Py_CPYTHON_CEREALOBJECT_H
#endif

/* Type object */
PyAPI_DATA(PyTypeObject) PyCereal_Type;

/* Type check macros */
#define PyCereal_Check(self) PyObject_TypeCheck(self, &PyCereal_Type)
#define PyCereal_CheckExact(self) Py_IS_TYPE(self, &PyCereal_Type)

/* Cast argument to PyCerealObject * type. */
#define _PyCerealObject_CAST(op) ((PyCerealObject *)(op))
#define _PyCerealObject_CAST_CONST(op) ((const PyCerealObject *)(op))

/* Direct API functions */

/* PyObject *PyCereal_New(Py_ssize_t ml)
 *   Return a new, unprepared cereal bowl with maximum capacity
 :   as ``ml`` milliliters.
 *   ``ml`` must be positive and non-zero.
 */
PyAPI_FUNC(PyObject *) PyCereal_New(Py_ssize_t ml);

/* PyObject *PyCereal_FromFields(Py_ssize_t size, Py_ssize_t ml)
 *   Return a cereal bowl from capacity and how much should already
 :   be in it.
 *   If ``ml`` is non-zero, ``.is_prepared`` is set to 1. Otherwise,
 :   it is set to 0.
 *   ``size`` must be non-zero.
 *   ``ml`` must not be greater than ``size``.
 *   Both arguments must be positive.
 */
PyAPI_FUNC(PyObject *) PyCereal_FromFields(Py_ssize_t size, Py_ssize_t ml);

/* PyObject *PyCereal_FromFieldsOverflow(Py_ssize_t size, Py_ssize_t ml)
 *   Return a cereal bowl from capacity and how much should already
 :   be in it.
 *   If ``ml`` is non-zero, ``.is_finished`` is set to 1. Otherwise,
 :   it is set to 0.
 *   ``size`` must be non-zero.
 *   ``ml`` can be greater than ``size``, but it will get clamped.
 *   Both arguments must be positive.
 */
PyAPI_FUNC(PyObject *) PyCereal_FromFieldsOverflow(Py_ssize_t size, Py_ssize_t ml);

/* int PyCereal_Prepare(PyCerealObject *cereal, Py_ssize_t ml)
 *   Prepare ``ml`` milliliters of cereal in the cereal bowl ``cereal``.
 *   If the cereal bowl is prepared, it must be finished before preparing again.
 *   ``ml`` must not exceed maximum bowl capacity, nor must it be 0, nor must it
 :   be negative.
 */
PyAPI_FUNC(int) PyCereal_Prepare(PyCerealObject *cereal, Py_ssize_t ml);

/* int PyCereal_Eat(PyCerealObject *cereal, Py_ssize_t ml)
 *   Eat ``ml`` milliliters of cereal from the cereal bowl ``cereal``.
 *   Cereal bowl must be prepared before eating.
 *   ``ml`` must be positive and less than or equal to ``cereal.milliliters``.
 *   -1 can be substituted for ``ml`` to eat all of the cereal bowl.
 */
PyAPI_FUNC(int) PyCereal_Eat(PyCerealObject *cereal, Py_ssize_t ml);

/* int PyCereal_Finish(PyCerealObject *cereal)
 *   Finish the cereal bowl ``cereal``.
 *   Cereal bowl must be prepared and empty before finishing.
 */
PyAPI_FUNC(int) PyCereal_Finish(PyCerealObject *cereal);

/* PyObject *PyCereal_Add(PyCerealObject *cereal, Py_ssize_t ml)
 *   Add ``ml`` milliliters of cereal to the cereal bowl ``cereal``.
 *   ``cereal.milliliters + ml`` must not exceed maximum bowl capacity
 :   nor must it be negative.
 *   Cereal bowl must be prepared.
 */
PyAPI_FUNC(PyObject *) PyCereal_Add(PyCerealObject *cereal, Py_ssize_t ml);

/* PyObject *PyCereal_Subtract(PyCerealObject *cereal, Py_ssize_t ml)
 *   Waste ``ml`` milliliters of cereal from the cereal bowl ``cereal``.
 *   ``ml`` must not exceed ``cereal.milliliters`` nor must it be negative.
 *   Cereal bowl must be prepared.
 */
PyAPI_FUNC(PyObject *) PyCereal_Subtract(PyCerealObject *cereal, Py_ssize_t ml);

/* PyObject *PyCereal_Multiply(PyCerealObject *cereal, Py_ssize_t size)
 *   ``cereal.milliliters`` will be multiplied by ``size`` and new object
 :   with its ``.milliliters`` field as the result will be returned.
 *   ``cereal.milliliters * size`` must not exceed maximum bowl capacity.
 */
PyAPI_FUNC(PyObject *) PyCereal_Multiply(PyCerealObject *cereal, Py_ssize_t size);

/* PyObject *PyCereal_Divide(PyCerealObject *cereal, Py_ssize_t size)
 *   ``cereal.milliliters`` will be (floor) divided by ``size`` and new object
 :   with its ``.milliliters`` field as the result will be returned.
 *   ``size`` must not be negative nor must it be 0.
 */
PyAPI_FUNC(PyObject *) PyCereal_Divide(PyCerealObject *cereal, Py_ssize_t size);

/* PyObject *PyCereal_Resize(PyCerealObject *cereal, Py_ssize_t size)
 *   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
 :   resized to ``size`` milliliters.
 *   ``size`` must be greater than or equal to ``cereal.milliliters``
 :   and it must be non-zero.
 */
PyAPI_FUNC(PyObject *) PyCereal_Resize(PyCerealObject *cereal, Py_ssize_t size);

/* PyObject *PyCereal_ResizeOverflow(PyCerealObject *cereal, Py_ssize_t size)
 *   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
 :   resized to ``size`` milliliters.
 *   ``size`` must be non-zero.
 */
PyAPI_FUNC(PyObject *) PyCereal_ResizeOverflow(PyCerealObject *cereal, Py_ssize_t size);

/* PyObject *PyCereal_AddSizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)
 *   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
 :   resized to ``cereal.size + size`` milliliters.
 *   ``size`` cannot be negative.
 */
PyAPI_FUNC(PyObject *) PyCereal_AddSizeAbsolute(PyCerealObject *cereal, Py_ssize_t size);

/* PyObject *PyCereal_SubtractSizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)
 *   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
 :   resized to ``cereal.size - size`` milliliters.
 *   ``size`` must be less than or equal to ``cereal.size - cereal.milliliters``.
 *   ``size`` cannot be negative.
 */
PyAPI_FUNC(PyObject *) PyCereal_SubtractSizeAbsolute(PyCerealObject *cereal, Py_ssize_t size);

/* PyObject *PyCereal_MultiplySizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)
 *   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
 :   resized to ``cereal.size * size`` milliliters.
 *   ``size`` can never be negative.
 */
PyAPI_FUNC(PyObject *) PyCereal_MultiplySizeAbsolute(PyCerealObject *cereal, Py_ssize_t size);

/* PyObject *PyCereal_AddSizeRelative(PyCerealObject *cereal, Py_ssize_t ml)
 *   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
 :   resized to ``cereal.milliliters + ml`` milliliters.
 *   ``ml`` cannot be negative.
 */
PyAPI_FUNC(PyObject *) PyCereal_AddSizeRelative(PyCerealObject *cereal, Py_ssize_t ml);

/* ``PyCereal_SubtractSizeRelative`` does not exist for one reason:
 *   In these kinds of functions, we don't want to waste cereal.
 */

/* PyObject *PyCereal_MultiplySizeRelative(PyCerealObject *cereal, Py_ssize_t ml)
 *   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
 :   resized to ``cereal.milliliters * ml`` milliliters.
 *   ``ml`` can never be negative.
 */
PyAPI_FUNC(PyObject *) PyCereal_MultiplySizeRelative(PyCerealObject *cereal, Py_ssize_t ml);

#ifdef __cplusplus
}
#endif
#endif /* !Py_CEREALOBJECT_H */
