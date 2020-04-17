import pytest
import numpy as np

import wolfram_model as wm

def test_constructor():
    expr = wm.expression()
    assert not expr.atoms, "Atoms is empty in default constructor"

    expr.atoms = [3,3]
    assert expr.atoms, "Atoms not empty after initializing them with a list (stl.h)"
    assert expr.atoms[1] == 3

    expr.atoms = np.array([1,1])
    assert expr.atoms, "Atoms not empty after initializing them with a numpy array (numpy.h)"
    assert expr.atoms[1] == 1

    # Workaround: Copy the complete array to another variable in python, modify it, and copy it back. Expensive.
    # Solution: Use OPAQUE types with stl_bind.h. Some niceties are lost (maybe solvable, need more research).
    expr.atoms.append(5)
    assert len(expr.atoms) == 2, "Append does not work (passing a reference) (stl.h)"

    print(expr)




