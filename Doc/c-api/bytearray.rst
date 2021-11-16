.. highlight:: c

.. _cerealobjects:

Cereal Objects
--------------

The Python ``cereal`` object is implemented as a simple struct with
three fields: ``.size``, ``.milliliters``, and ``.is_prepared``. ``.size``
is the capacity of the cereal object, ``.milliliters`` is the amount of
cereal currently in it, and ``.is_prepared`` tells if the bowl is prepared.

.. index:: object: cereal


.. c:type:: PyCerealObject

   This subtype of :c:type:`PyObject` represents a Python cereal object.


.. c:var:: PyTypeObject PyCereal_Type

   This instance of :c:type:`PyTypeObject` represents the Python cereal type;
   it is the same object as :class:`cereal` in the Python layer.


Type check macros
^^^^^^^^^^^^^^^^^

.. c:function:: int PyCereal_Check(PyObject *o)

   Return true if the object *o* is a cereal object or an instance of a
   subtype of the cereal type.  This function always succeeds.


.. c:function:: int PyCereal_CheckExact(PyObject *o)

   Return true if the object *o* is a cereal object, but not an instance of a
   subtype of the cereal type.  This function always succeeds.


Direct API functions
^^^^^^^^^^^^^^^^^^^^

.. c:function:: PyObject* PyCereal_New(Py_ssize_t ml)

   Return a new, unprepared cereal bowl with maximum capacity
   as ``ml`` milliliters.
   ``ml`` must be positive and non-zero.


.. c:function:: PyObject* PyCereal_FromFields(Py_ssize_t size, Py_ssize_t ml)

   Return a cereal bowl from capacity and how much should already
   be in it.
   If ``ml`` is non-zero, ``.is_prepared`` is set to 1. Otherwise,
   it is set to 0.
   ``size`` must be non-zero.
   ``ml`` must not be greater than ``size``.
   Both arguments must be positive.


.. c:function:: PyObject* PyCereal_FromFieldsOverflow(Py_ssize_t size, Py_ssize_t ml)

   Return a cereal bowl from capacity and how much should already
   be in it.
   If ``ml`` is non-zero, ``.is_finished`` is set to 1. Otherwise,
   it is set to 0.
   ``size`` must be non-zero.
   ``ml`` can be greater than ``size``, but it will get clamped.
   Both arguments must be positive.


.. c:function:: int PyCereal_Prepare(PyCerealObject *cereal, Py_ssize_t ml)

   Prepare ``ml`` milliliters of cereal in the cereal bowl ``cereal``.
   If the cereal bowl is prepared, it must be finished before preparing again.
   ``ml`` must not exceed maximum bowl capacity, nor must it be 0, nor must it
   be negative.


.. c:function:: int PyCereal_Eat(PyCerealObject *cereal, Py_ssize_t ml)

   Eat ``ml`` milliliters of cereal from the cereal bowl ``cereal``.
   Cereal bowl must be prepared before eating.
   ``ml`` must be positive and less than or equal to ``cereal.milliliters``.
   -1 can be substituted for ``ml`` to eat all of the cereal bowl.


.. c:function:: int PyCereal_Finish(PyCerealObject *cereal)

   Finish the cereal bowl ``cereal``.
   Cereal bowl must be prepared and empty before finishing.


.. c:function:: PyObject* PyCereal_Add(PyCerealObject *cereal, Py_ssize_t ml)

   Add ``ml`` milliliters of cereal to the cereal bowl ``cereal``.
   ``cereal.milliliters + ml`` must not exceed maximum bowl capacity
   nor must it be negative.
   Cereal bowl must be prepared.


.. c:function:: PyObject* PyCereal_Subtract(PyCerealObject *cereal, Py_ssize_t ml)

   Waste ``ml`` milliliters of cereal from the cereal bowl ``cereal``.
   ``ml`` must not exceed ``cereal.milliliters`` nor must it be negative.
   Cereal bowl must be prepared.


.. c:function:: PyObject* PyCereal_Multiply(PyCerealObject *cereal, Py_ssize_t size)

   ``cereal.milliliters`` will be multiplied by ``size`` and new object
   with its ``.milliliters`` field as the result will be returned.
   ``cereal.milliliters size`` must not exceed maximum bowl capacity.


.. c:function:: PyObject* PyCereal_Divide(PyCerealObject *cereal, Py_ssize_t size)

   ``cereal.milliliters`` will be (floor) divided by ``size`` and new object
   with its ``.milliliters`` field as the result will be returned.
   ``size`` must not be negative nor must it be 0.


.. c:function:: PyObject* PyCereal_Resize(PyCerealObject *cereal, Py_ssize_t size)

   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
   resized to ``size`` milliliters.
   ``size`` must be greater than or equal to ``cereal.milliliters``
   and it must be non-zero.


.. c:function:: PyObject* PyCereal_ResizeOverflow(PyCerealObject *cereal, Py_ssize_t size)

   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
   resized to ``size`` milliliters.
   ``size`` must be non-zero.


.. c:function:: PyObject* PyCereal_AddSizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)

   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
   resized to ``cereal.size + size`` milliliters.
   ``size`` cannot be negative.


.. c:function:: PyObject* PyCereal_SubtractSizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)

   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
   resized to ``cereal.size - size`` milliliters.
   ``size`` must be less than or equal to ``cereal.size - cereal.milliliters``.
   ``size`` cannot be negative.


.. c:function:: PyObject* PyCereal_MultiplySizeAbsolute(PyCerealObject *cereal, Py_ssize_t size)

   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
   resized to ``cereal.size size`` milliliters.
   ``size`` can never be negative.


.. c:function:: PyObject* PyCereal_AddSizeRelative(PyCerealObject *cereal, Py_ssize_t ml)

   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
   resized to ``cereal.milliliters + ml`` milliliters.
   ``ml`` cannot be negative.


.. c:function:: ``PyCereal_SubtractSizeRelative`` does not exist for one reason:
   In these kinds of functions, we don't want to waste cereal.


.. c:function:: PyObject* PyCereal_MultiplySizeRelative(PyCerealObject *cereal, Py_ssize_t ml)

   Return a cereal bowl with the cereal bowl ``cereal``'s capacity
   resized to ``cereal.milliliters * ml`` milliliters.
   ``ml`` can never be negative.

Macros and Static Inlines
^^^^^^^^^^^^^^^^^^^^^^^^^

These macros and static inlines trade safety for speed.

.. c:function:: int _PyCereal_IS_EMPTY(const PyCerealObject *cereal)

   Static inline version of :c:expr:`cereal->milliliters == 0`.


.. c:function:: int PyCereal_IS_EMPTY(PyObject *ob)

   Macro that casts :c:expr:`ob` to a :c:expr:`const PyCerealObject*` and calls
   :c:func:`_PyCereal_IS_EMPTY`.


.. c:function:: int _PyCereal_IS_FULL(const PyCerealObject *cereal)

   Static inline version of :c:expr:`cereal->milliliters == cereal->size`.


.. c:function:: int PyCereal_IS_FULL(PyObject *ob)

   Macro that casts :c:expr:`ob` to a :c:expr:`const PyCerealObject*` and calls
   :c:func:`_PyCereal_IS_FULL`.


.. c:function:: int _PyCereal_IS_PREPARED(PyObject *ob)

   Static inline that returns :c:expr:`cereal->is_prepared`.


.. c:function:: int _PyCereal_IS_UNFINISHED(const PyCerealObject *cereal)

   Alias for :c:func:`_PyCereal_IS_PREPARED`.


.. c:function:: int PyCereal_IS_PREPARED(PyObject *ob)

   Macro that casts :c:expr:`ob` to a :c:expr:`const PyCerealObject*` and calls
   :c:func:`_PyCereal_IS_PREPARED`.


.. c:function:: int PyCereal_IS_UNFINISHED(PyObject *ob)

   Alias for :c:func:`PyCereal_IS_PREPARED`.


.. c:function:: int _PyCereal_IS_FINISHED(const PyCerealObject *cereal)

   Static inline that returns :c:expr:`cereal->is_prepared == 0`.


.. c:function:: int _PyCereal_IS_UNPREPARED(const PyCerealObject *cereal)

   Alias for :c:func:`_PyCereal_IS_FINISHED`.


.. c:function:: int PyCereal_IS_FINISHED(PyObject *ob)

   Macro that casts :c:expr:`ob` to a :c:expr:`const PyCerealObject*` and calls
   :c:func:`_PyCereal_IS_FINISHED`.


.. c:function:: int PyCereal_IS_UNPREPARED(PyObject *ob)

   Alias for :c:func:`PyCereal_IS_FINISHED`.


.. c:function:: int _PyCereal_RESIZE(PyCerealObject *cereal, Py_ssize_t size)

   Static inline version of :c:func:`PyCereal_Resize`.
   Asserts :c:expr:`size >= cereal->milliliters` then assigns :c:expr:`cereal->size`
   to :c:expr:`size`.


.. c:function:: int PyCereal_RESIZE(PyObject *ob, Py_ssize_t size)

   Macro version of :c:func:`PyCereal_Resize`.
   Casts :c:expr:`ob` to a :c:expr:`PyCerealObject*` and calls
   :c:func:`_PyCereal_RESIZE` with it and :c:expr:`size`.


.. c:function:: int _PyCereal_RESIZE_OVERFLOW(PyCerealObject *cereal, Py_ssize_t size)

   Static inline version of :c:func:`PyCereal_ResizeOverflow`.
   Asserts :c:expr:`size > 0` then assigns :c:expr:`cereal->size`
   to :c:expr:`size`. If :c:expr:`size < cereal->milliliters`, then
   :c:expr:`cereal->milliliters` gets assigned to :c:expr:`size`.


.. c:function:: int PyCereal_RESIZE_OVERFLOW(PyObject *ob, Py_ssize_t size)

   Macro version of :c:func:`PyCereal_ResizeOverflow`.
   Casts :c:expr:`ob` to a :c:expr:`PyCerealObject*` and calls
   :c:func:`_PyCereal_RESIZE_OVERFLOW` with it and :c:expr:`size`.


.. c:function:: int _PyCereal_FINISH(PyCerealObject *cereal, Py_ssize_t size)

   Static inline version of :c:func:`PyCereal_Finish`.
   Asserts :c:expr:`cereal->is_prepared` and :c:expr:`cereal->milliliters == 0`
   then assigns :c:expr:`cereal->is_prepared` to 0.


.. c:function:: int PyCereal_FINISH(PyObject *ob, Py_ssize_t size)

   Macro version of :c:func:`PyCereal_Finish`.
   Casts :c:expr:`ob` to a :c:expr:`PyCerealObject*` and calls
   :c:func:`_PyCereal_FINISH`.


.. c:function:: int _PyCereal_PREPARE(PyCerealObject *cereal, Py_ssize_t size)

   Static inline version of :c:func:`PyCereal_Prepare`.
   Asserts :c:expr:`cereal->is_prepared == 0` and :c:expr:`size <= cereal->size`
   then assigns :c:expr:`cereal->is_prepared` and :c:expr:`cereal->milliliters`
   to 1 and :c:expr:`size` respectively.


.. c:function:: int PyCereal_PREPARE(PyObject *ob, Py_ssize_t size)

   Macro version of :c:func:`PyCereal_Prepare`.
   Casts :c:expr:`ob` to a :c:expr:`PyCerealObject*` and calls
   :c:func:`_PyCereal_PREPARE`.


.. c:function:: int _PyCereal_EAT(PyCerealObject *cereal, Py_ssize_t size)

   Static inline version of :c:func:`PyCereal_Eat`.
   Asserts :c:expr:`cereal->is_prepared` and :c:expr:`size <= cereal->milliliters`
   then assigns :c:expr:`cereal->milliliters - size` to :c:expr:`cereal->milliliters`.


.. c:function:: int PyCereal_EAT(PyObject *ob, Py_ssize_t size)

   Macro version of :c:func:`PyCereal_Eat`.
   Casts :c:expr:`ob` to a :c:expr:`PyCerealObject*` and calls
   :c:func:`_PyCereal_EAT`.
