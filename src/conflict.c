#include "../lib/conflict.h"
#include "../lib/graph.h"
#include "../lib/util.h"

/**
 * @brief Função que recebe um conjunto de transações e monta um grafo de precedência.
 * 
 * @param transactions 
 * @return int 
 */
int is_conflict(transactions_p transactions) {
  graph_p g;
  transaction_p ta, tb, ti, tj;
  vertex_p vi, vj;
  int cyclic;

  g = create_graph();

  /**
   * @brief Para cada transação na lista de transações, crie um vertice no grafo.
   * 
   */
  for(ta = transactions->first; ta != NULL; ta = ta->next) {
    if(get_vertex(ta->id, g)) {
      continue;
    } else {
      add_list_node(g->vertex, create_list_node(create_vertex(ta->id)));
    }
  }

  /**
   * @brief Para cada transação na lista de transações.
   * 
   */
  for(ta = transactions->first; ta != NULL; ta = ta->next) {
    ti = ta;

    /**
     * @brief Pegue as transações duas a duas.
     * 
     */
    for(tb = ta->next; tb != NULL; tb = tb->next) {
      tj = tb;
      
      /**
       * @brief Se as transações i e j forem sobre o mesmo item de dado, e forem transações diferentes.
       * 
       */
      if(ti->data == tj->data && ti->id != tj->id) {

        /**
         * @brief Se j é leitura e i é escrita, crie uma aresta de i para j.
         * 
         */
        if(tj->operation == 'r' && ti->operation == 'w') {
          vi = get_vertex(ti->id, g);
          vj = get_vertex(tj->id, g);

          if(!find_edge(g, create_edge(vi, vj))) {
            add_list_node(g->edges, create_list_node(create_edge(vi, vj)));
          }
        }

        /**
         * @brief Se j é escrita e i é leitura, crie uma aresta de i para j.
         * 
         */
        if(tj->operation == 'w' && ti->operation == 'r') {
          vi = get_vertex(ti->id, g);
          vj = get_vertex(tj->id, g);

          if(!find_edge(g, create_edge(vi, vj))) {
            add_list_node(g->edges, create_list_node(create_edge(vi, vj)));
          }
        }

        /**
         * @brief Se j é leitura e i é leitura, crie uma aresta de i para j.
         * 
         */
        if(tj->operation == 'w' && ti->operation == 'w') {
          vi = get_vertex(ti->id, g);
          vj = get_vertex(tj->id, g);

          if(!find_edge(g, create_edge(vi, vj))) {
            add_list_node(g->edges, create_list_node(create_edge(vi, vj)));
          }
        }
      }
    }
  }

  /**
   * @brief Busca cliclo no grafo gerado.
   * 
   */
  cyclic = is_cyclic(g);

  destroy_graph(g);

  return cyclic;
}