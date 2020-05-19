import wolfram_model as wm

def graph_at_generation(wm_set, input_generation=-1, method="networkx"):
   if method=="networkx":
      import wolfram_model.vis.networkx.vis as vis_nx
      return vis_nx.graph_at_generation(wm_set, input_generation)

def show(wm_set):
   exps = wm_set.expressions()
   return expr

