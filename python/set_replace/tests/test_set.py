import pytest
import numpy as np

import wolfram_model as wm

def test_step_specification():
    step_spec = wm.set.step_spec()
    print(step_spec)

def test_enum_termination_reason():
    a_termination_reason = wm.set.termination_reason.NotTerminated
    print(a_termination_reason)

@pytest.fixture
def set_inputs_0():
    rule = wm.rule(inputs=[[-1,-2], [-2, -3]], outputs=[[-1,-3], [-4, -2], [-1, -4]])
    initial_expressions = [[1,2], [2, 3]]
    order_function = wm.matcher.ordering_function.RuleID
    order_direction = wm.matcher.ordering_direction.Normal
    ordering = [[order_function, order_direction]]
    random_seed = 0
    return [rule, initial_expressions, ordering, random_seed]

def test_set_constructor(set_inputs_0):
    rule, initial_expressions, ordering, random_seed = set_inputs_0
    wm.set(
        rules=[rule], initial_expressions=initial_expressions,
        ordering=ordering, random_seed=random_seed)

def test_set_constructor_throws_if_negative_initial_expressions(set_inputs_0):
    rule, initial_expressions, ordering, random_seed = set_inputs_0
    initial_expressions = [[-1,-2], [-2, -3]]
    with  pytest.raises(ValueError) as excinfo:
        wm.set(
            rules=[rule], initial_expressions=initial_expressions,
            ordering=ordering, random_seed=random_seed)
    assert "initial_expressions must be" in str(excinfo.value)

@pytest.fixture
def step_spec0(set_inputs_0):
    step_spec = wm.set.step_spec()
    step_spec.max_events = 100;
    step_spec.max_generations_local = 100;
    step_spec.max_final_atoms = 100000;
    step_spec.max_final_atom_degree = 100000;
    step_spec.max_final_expressions = 100000;
    return step_spec

def test_set_replace(set_inputs_0, step_spec0):
    rule, initial_expressions, ordering, random_seed = set_inputs_0
    step_spec = step_spec0
    wms = wm.set(
        rules=[rule], initial_expressions=initial_expressions,
        ordering=ordering, random_seed=random_seed)
    substitutions_made = wms.replace(step_spec)
    termination_reason = wms.get_termination_reason()
    assert termination_reason == wm.set.termination_reason.MaxEvents
    assert substitutions_made == step_spec.max_events
    max_complete_generation = wms.max_complete_generation()
    assert max_complete_generation == step_spec.max_events

    substitution_made = wms.replaceOnce()
    assert not substitution_made, "Shouldn't advance when the termination_reason is MaxEvents"
    event_rule_ids = wms.event_rule_ids()
    assert event_rule_ids, "event_rule_ids is not empty"

