import pytest
import numpy as np

import wolfram_model as wm

def test_match_enums():
    order_function = wm.matcher.ordering_function.RuleIndex
    print(order_function)
    order_direction = wm.matcher.ordering_direction.Normal
    print(order_direction)
    ordering_spec = [[order_function, order_direction]]

def a_dummy_get_atoms_vector_func(long_):
    return [long_, long_]

def test_matcher_constructor():
    rule = wm.rule(inputs=[[-1,-2], [-2, -3]], outputs=[[-1,-3], [-4, -2], [-1, -4]])
    atoms_index = wm.atoms_index(a_dummy_get_atoms_vector_func)
    ordering_spec = [[wm.matcher.ordering_function.RuleIndex,
                      wm.matcher.ordering_direction.Normal]]
    matcher = wm.matcher(
        rules=[rule],
        atoms_index=atoms_index,
        get_atoms_vector=a_dummy_get_atoms_vector_func,
        ordering=ordering_spec
    )
    print(matcher.all_matches())

