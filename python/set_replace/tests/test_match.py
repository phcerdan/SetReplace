import pytest
import numpy as np

import wolfram_model as wm

def test_match_enums():
    order_function = wm.matcher.ordering_function.RuleID
    print(order_function)
    order_direction = wm.matcher.ordering_direction.Normal
    print(order_direction)
    ordering_spec = [[order_function, order_direction]]


