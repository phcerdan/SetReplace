import wolfram_model as wm
import networkx as nx

def graph_at_generation(wm_set, input_generation=-1 ):
   max_generation = wm_set.max_complete_generation()
   if input_generation == -1:
      input_generation = max_generation
   else:
      if input_generation > max_generation:
         raise ValueError(
            'input_generation: {} is greater than max_generation {}'.format(input_generation, max_generation))
      elif input_generation < 0:
         raise ValueError(
            'input_generation: {} cannot be negative'.format(input_generation))

   exps_all = wm_set.expressions()
   exps_at_gen = [e for e in exps_all if e.generation == input_generation ]
   edges_at_gen = [e.atoms for e in exps_at_gen]
   unique_nodes_at_gen = set([node for edge in edges_at_gen for node in edge])
   G = nx.DiGraph()
   for node in unique_nodes_at_gen:
      G.add_node(node, atom=node)
   for edge in edges_at_gen:
      G.add_edge(edge[0], edge[1])

   return G

