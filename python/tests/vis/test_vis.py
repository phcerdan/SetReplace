import wolfram_model as wm
import wolfram_model.vis.fixture as fixture
import wolfram_model.vis as vis
import pytest
try:
   import networkx as nx
   from matplotlib import pyplot as plt
except ImportError as e:
   raise e


@pytest.fixture
def wms0():
    return fixture.wm0()[0]

def test_graph_at_generation(wms0):
   wms = wms0
   method = "networkx"
   G = vis.graph_at_generation(wms, input_generation=-1, method=method)
   print(G.nodes)
   print(G.edges)
   assert G.nodes, "G has nodes"

def test_show_at_generation_with_nx_draw(wms0):
   wms = wms0
   method = "networkx"
   G = vis.graph_at_generation(wms, input_generation=-1, method=method)
   pos = nx.nx_agraph.graphviz_layout(G, prog='neato')
   nx.draw(G,
           pos,
           node_size=100)
   plt.show(block=False)
   plt.pause(2)
   plt.close()

def test_show_at_generation_multiple_plt(wms0):
   wms = wms0
   method = "networkx"
   max_gen = wms.max_complete_generation() + 1
   fig, axs = plt.subplots(max_gen)
   for gen in range(max_gen):
       G = vis.graph_at_generation(wms, input_generation=gen, method=method)
       num_nodes = G.number_of_nodes()
       pos = nx.nx_agraph.graphviz_layout(G, prog='dot')
       nx.draw(G,
               pos,
               node_size=100,
               ax=axs[gen],
               with_labels=True,
               node_color=range(num_nodes),
               # vmin=0.0,
               # vmax=123,
               cmap=plt.get_cmap('Accent')
               )
   plt.show(block=False)
   plt.pause(2)
   plt.close()
