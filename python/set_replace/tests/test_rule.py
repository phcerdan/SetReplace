import pytest
import numpy as np

import wolfram_model as wm

def test_rule():
    rule = wm.rule(inputs=[[1,2]], outputs=[[1,3]])
    assert rule.inputs[0][1] == 2, "Rule is populated with non-default constructor, using lists"

    rule = wm.rule(inputs=np.array([[1,2]]), outputs=np.array([[1,3]]))
    assert rule.outputs[0][1] == 3, "Rule is populated with non-default constructor, using np.arrays"
    print(rule)

