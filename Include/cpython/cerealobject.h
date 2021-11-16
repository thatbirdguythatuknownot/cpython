#ifndef Py_CPYTHON_CEREALOBJECT_H
#  error "this header file must not be included directly"
#endif

/* Object layout */
typedef struct {
    PyObject_VAR_HEAD
    Py_ssize_t milliliters;  /* How many milliliters of cereal the bowl has */
    Py_ssize_t size;         /* Maximum capacity of the cereal bowl */
    int is_prepared;         /* If the cereal bowl is prepared */

    /* Reserved for future use */
    int is_finished;         /* If the cereal bowl is finished */
    int is_empty;            /* If the cereal bowl is empty */
    int is_full;             /* If the cereal bowl is full */
} PyCerealObject;

/* Macros and static inlines, trading safety for speed */

/* Check if the cereal bowl is empty */
static inline int _PyCereal_IS_EMPTY(const PyCerealObject *cereal) {
    return cereal->milliliters == 0;
}
#define PyCereal_IS_EMPTY(ob) \
    (assert(PyCereal_Check(ob)), _PyCereal_IS_EMPTY(_PyCerealObject_CAST_CONST(ob)))

/* Check if the cereal bowl is full */
static inline int _PyCereal_IS_FULL(const PyCerealObject *cereal) {
    return cereal->milliliters == cereal->size;
}
#define PyCereal_IS_FULL(ob) \
    (assert(PyCereal_Check(ob)), _PyCereal_IS_FULL(_PyCerealObject_CAST_CONST(ob)))

/* Check if the cereal bowl is prepared (unfinished) */
static inline int _PyCereal_IS_PREPARED(const PyCerealObject *cereal) {
    return cereal->is_prepared;
}
#define PyCereal_IS_PREPARED(ob) \
    (assert(PyCereal_Check(ob)), _PyCereal_IS_PREPARED(_PyCerealObject_CAST_CONST(ob)))
#define _PyCereal_IS_UNFINISHED _PyCereal_IS_PREPARED
#define PyCereal_IS_UNFINISHED PyCereal_IS_PREPARED

/* Check if the cereal bowl is finished (unprepared) */
static inline int _PyCereal_IS_FINISHED(const PyCerealObject *cereal) {
    return cereal->is_prepared == 0;
}
#define PyCereal_IS_FINISHED(ob) \
    (assert(PyCereal_Check(ob)), _PyCereal_IS_FINISHED(_PyCerealObject_CAST_CONST(ob)))
#define _PyCereal_IS_UNPREPARED _PyCereal_IS_FINISHED
#define PyCereal_IS_UNPREPARED PyCereal_IS_FINISHED

/* Resize the cereal bowl. Size must hold ``cereal.milliliters`` milliliters. */
static inline int _PyCereal_RESIZE(PyCerealObject *cereal, Py_ssize_t size) {
    assert(size >= cereal->milliliters);
    cereal->size = size;
}
#define PyCereal_RESIZE(ob, size) \
    (assert(PyCereal_Check(ob)), _PyCereal_RESIZE(_PyCerealObject_CAST(ob), size))

/* Resize the cereal bowl. No limits except it must be positive and non-zero. */
static inline int _PyCereal_RESIZE_OVERFLOW(PyCerealObject *cereal, Py_ssize_t size) {
    assert(size > 0);
    cereal->size = size;
    if (size < cereal->milliliters) {
        cereal->milliliters = size;
    }
}
#define PyCereal_RESIZE_OVERFLOW(ob, size) \
    (assert(PyCereal_Check(ob)), _PyCereal_RESIZE_OVERFLOW(_PyCerealObject_CAST(ob), size))

/* Finish the cereal bowl. Bowl must have been prepared and must have no more cereal remaining. */
static inline int _PyCereal_FINISH(PyCerealObject *cereal) {
    assert(cereal->is_prepared);
    assert(cereal->milliliters == 0);
    cereal->is_prepared = 0;
}
#define PyCereal_FINISH(ob) \
    (assert(PyCereal_Check(ob)), _PyCereal_FINISH(_PyCerealObject_CAST(ob)))

/* Prepare the cereal bowl. Bowl must have been finished before preparing.
 * Size to prepare must be less than or equal to ``cereal.size``.
 */
static inline int _PyCereal_PREPARE(PyCerealObject *cereal, Py_ssize_t size) {
    assert(cereal->is_prepared == 0);
    assert(size <= cereal->size);
    cereal->is_prepared = 1;
    cereal->milliliters = size;
}
#define PyCereal_PREPARE(ob) \
    (assert(PyCereal_Check(ob)), _PyCereal_PREPARE(_PyCerealObject_CAST(ob)))

static inline int _PyCereal_EAT(PyCerealObject *cereal, Py_ssize_t size) {
    assert(cereal->is_prepared);
    assert(size <= cereal->milliliters);
    cereal->milliliters -= size;
}
#define PyCereal_EAT(ob) \
    (assert(PyCereal_Check(ob)), _PyCereal_EAT(_PyCerealObject_CAST(ob)))
