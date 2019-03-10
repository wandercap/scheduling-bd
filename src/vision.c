#include "../lib/vision.h"
#include "../lib/transaction.h"
#include "../lib/conflict.h"
#include "../lib/graph.h"
#include "../lib/util.h"

/**
 * @brief Verifica se um conjunto de transações é equivalente por visão.
 * 
 * @param transactions 
 * @return int 
 */
int is_vision(transactions_p transactions) {
  graph_p g;
  transaction_p ta;
  int cyclic;

  g = create_graph();

  /**
   * @brief Para cada transação na lista de transações, crie um vertice no grafo.
   * 
   */
  add_list_node(g->vertex, create_list_node(create_vertex(0)));
  for(ta = transactions->first; ta != NULL; ta = ta->next) {
    if(get_vertex(ta->id, g)) {
      continue;
    } else {
      add_list_node(g->vertex, create_list_node(create_vertex(ta->id)));
    }
  }
  add_list_node(g->vertex, create_list_node(create_vertex(101)));

  // TO DO: Ligar as arestas do grafo...

  cyclic = is_cyclic(g);

  destroy_graph(g);

  return cyclic;
}