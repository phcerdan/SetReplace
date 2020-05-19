import wolfram_model as wm

def wm0():
   # Rule: {{x, y}, {x, z}} -> {{x, y}, {x, w}, {y, w}, {z, w}}
    rule = wm.rule(
       inputs=[[-1,-2], [-1, -3]],
       outputs=[[-1,-2], [-1, -4], [-2, -4], [-3, -4]])
    initial_expressions = [[1,2], [1, 3]]
    order_function = wm.matcher.ordering_function.RuleIndex
    order_direction = wm.matcher.ordering_direction.Normal
    ordering = [[order_function, order_direction]]
    random_seed = 0

    step_spec = wm.set.step_spec()
    step_spec.max_events = 100;
    step_spec.max_generations_local = 100;
    step_spec.max_final_atoms = 100000;
    step_spec.max_final_atom_degree = 100000;
    step_spec.max_final_expressions = 100000;

    rules = [rule]
    wms = wm.set(
        rules=rules, initial_expressions=initial_expressions,
        ordering=ordering, random_seed=random_seed)
    substitutions_made = wms.replace(step_spec)

    return [wms, rules, step_spec, [initial_expressions, ordering, random_seed]]

