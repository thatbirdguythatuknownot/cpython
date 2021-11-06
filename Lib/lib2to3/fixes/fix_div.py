"""Fixer that turns / into //.

First checks for left operand and right operand integerness. If the
integerness is not determined (e.g. saw number 5.0) or unable to be
determined (e.g. saw a trailer) the operation is left alone. Otherwise,
the division operator is changed into a floor division operator.
Examples:

* Change

    class foo(object):
        bar = 50

    a = 20 ** 5 / 3
    b = foo.bar / 7

into

    class foo(object):
        bar = 50

    a = 20 ** 5 // 3
    b = foo.bar / 7
"""
# Author: Jeremiah Vivian

# Local imports
from ..pytree import Node, Leaf
from ..pgen2 import token
from .. import fixer_base


def contains_no_float(node):
    if isinstance(node, Node):
        if node.type == 336:
            return False
        children = node.children
        length = len(children)
        if length == 2:
            operand = children[1]
            return contains_no_float(operand)
        elif length == 3:
            left = children[0]
            right = children[2]
            return (contains_no_float(left)
                    and contains_no_float(right))
    elif isinstance(node, Leaf):
        if node.type == 2:
            return '.' not in node.value
    return False


class FixDiv(fixer_base.BaseFix):
    # There must be a better way to fix a division operation.
    _accept_type = token.SLASH

    def match(self, node):
        if node.value == '/':
            left = node.prev_sibling
            right = node.next_sibling
            return (contains_no_float(left)
                    and contains_no_float(right))
        return False

    def transform(self, node, results):
        new = Leaf(token.DOUBLESLASH, "//", prefix=node.prefix)
        return new
