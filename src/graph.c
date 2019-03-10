#include "../lib/graph.h"
#include "../lib/stack.h"
#include "../lib/util.h"

/**
 * @brief Cria uma lista.
 * 
 * @return list_p 
 */
list_p create_list(void) {
  list_p list = (list_p)malloc(sizeof(list_t));
  if(!list)
    err_exit("Erro ao criar lista!");

  list->first = NULL;
  list->length = 0;

  return list;
}

/**
 * @brief Destroi uma lista.
 * 
 * @param list 
 * @return int 
 */
int destroy_list(list_p list) {
  if(!list)
    return 0;

  list_node_p node;

  while(list->first) {
    node = list->first;
    list->first = list->first->next;

    free(node->content);
    free(node);
  }

  free(list);

  return 1;
}

/**
 * @brief Cria um nodo de ponteito genérico da lista.
 * 
 * @param content 
 * @return list_node_p 
 */
list_node_p create_list_node(void *content) {
  if(!content)
    err_exit("Não é possível criar um nodo sem conteúdo.");

  list_node_p node = (list_node_p)malloc(sizeof(list_node_t));
  if(!node)
    err_exit("Erro ao criar nodo!");

  node->content = content;
  node->next = NULL;

  return node;
}

/**
 * @brief Adiciona um nodo a lista.
 * 
 * @param list 
 * @param node 
 */
void add_list_node(list_p list, list_node_p node) {
  if(!list)
    err_exit("A lista não existe!");

  if(!node)
    err_exit("Não é possível adicionar um nodo nulo.");

  list_node_p first = list->first;

  if(first != NULL) {
    while(first->next != NULL) {
      first = first->next;
    }

    first->next = node;
    node->next = NULL;
  } else {
    list->first = node;
  }

  list->length++;
}

/**
 * @brief Cria um grafo.
 * 
 * @return graph_p 
 */
graph_p create_graph(void) {
  graph_p g = (graph_p)malloc(sizeof(graph_t));
  if(!g)
    err_exit("Erro ao criar novo grafo!");

  g->vertex = create_list();
  g->edges = create_list();

  return g;
}

/**
 * @brief Destroi um grafo.
 * 
 * @param g 
 * @return int 
 */
int destroy_graph(graph_p g) {
  if(!g)
    return 0;

  if((destroy_list(g->edges) & destroy_list(g->vertex)) == 1) {
    free(g);

    return 1;
  }
  
  return 0;
}

/**
 * @brief Cria um vértice.
 * 
 * @param id 
 * @return vertex_p 
 */
vertex_p create_vertex(unsigned int id) {

  vertex_p v = (vertex_p)malloc(sizeof(vertex_t));
  if(!v)
    err_exit("Erro ao criar novo vertice!");

  v->id = id;

  v->color = 0;
  v->visit = 0;

  v->in = create_list();
  v->out = create_list();

  return v;
}

/**
 * @brief Cria uma aresta.
 * 
 * @param origin 
 * @param destiny 
 * @return edge_p 
 */
edge_p create_edge(vertex_p origin, vertex_p destiny) {
  if(!origin)
    err_exit("Não é possível criar um vértice origem.");

  if(!destiny)
    err_exit("Não é possível criar um vértice sem destino.");

  edge_p e = (edge_p)malloc(sizeof(edge_t));
  if(!e)
    err_exit("Erro ao criar aresta!");

  e->origin = origin;
  e->destiny = destiny;

  add_list_node(origin->out, create_list_node(e));
  add_list_node(destiny->in, create_list_node(e));

  return e;
}

/**
 * @brief Procura o vértice "id" no grafo "g".
 * 
 * @param id 
 * @param g 
 * @return vertex_p 
 */
vertex_p get_vertex(unsigned int id, graph_p g) {
  if(!g)
    err_exit("Erro ao carregar o grafo!");

  list_node_p node;
  vertex_p v;

  for(node = g->vertex->first; node != NULL; node = node->next) {
    v = node->content;

    if(id == v->id) {
      return v;
    }
  }

  return NULL;
}

/**
 * @brief Procura a aresta "e" no grafo "g".
 * 
 * @param g 
 * @param e 
 * @return int 
 */
int find_edge(graph_p g, edge_p e) {
  if(!g)
    err_exit("Erro ao carregar o grafo!");
  
  if(!e)
    err_exit("Erro ao carregar a aresta!");

  list_node_p node;
  edge_p ed;

  for (node = g->edges->first; node != NULL; node = node->next) {
    ed = node->content;

    if ((e->origin == ed->origin) && (e->destiny == ed->destiny))
      return 1;
  }

  return 0;
}

/**
 * @brief Faz uma busca em largura no grafo "g", para encontrar ciclos.
 * 
 * @param g 
 * @return int 
 */
int is_cyclic(graph_p g) {
  if(!g)
    err_exit("Erro ao carregar o grafo!");

  vertex_p v;
  edge_p e;
  list_node_p node_l;
  stack_node_p node_s;
  stack_p stack = create_stack();
  int i = 0;

  /**
   * @brief Se existe um vertice apenas com arestas de saída, pegue-o como inicial.
   * 
   */
  for(node_l = g->vertex->first; node_l != NULL; node_l = node_l->next) {
    v = node_l->content;

    if(v->in->length == 0 && v->out->length != 0) {
      break;
    }
  }

  /**
   * @brief Se não achou nenhum vértice e existe um vértice com arestas de saída, pegue-o como inicial.
   * 
   */
  if(v->in->length != 0 ) {
    for(node_l = g->vertex->first; node_l != NULL; node_l = node_l->next) {
      v = node_l->content;

      if(v->out->length != 0) {
        break;
      }
    }
  }

  /**
   * @brief Empilha o vértice escolhido como inicial.
   * 
   */
  push(stack,  create_stack_node(v));
  i++;

  /**
   * @brief Enquanto a pilha não estiver vazia.
   * 
   */
  while(stack->length > 0) {
    /**
     * @brief Retiro o vértice do topo da pilha.
     * 
     */
    node_s = pop(stack);
    v = (vertex_p)node_s->content;

    /**
     * @brief Se o vértice ainda não foi visitado.
     * 
     */
    if(!v->visit) {
      v->visit = 1;

      /**
       * @brief Para cada aresta de saída do vertice(origem), empilha o vértice destino.
       * 
       */
      for(node_l = v->out->first; node_l != NULL; node_l = node_l->next) {
        e = (edge_p)node_l->content;
        if(e->destiny) {
          if(e->destiny->color == 0) {
            e->destiny->color = 1;
            push(stack, create_stack_node(e->destiny));
            i++;
          }
        }
      }
      
      /**
       * @brief Se ainda não visitei todos os vétices, empilha um vértice ainda não visitado.
       * 
       */
      if (i < g->vertex->length) {
        for(node_l = g->vertex->first; node_l != NULL; node_l = node_l->next) {
          v = node_l->content;

          if(v->visit == 0) {
            push(stack,  create_stack_node(v));
            break;
          }
        }
      }
    } else {
      /**
       * @brief Se o vértice já foi visitado antes, achou um ciclo.
       * 
       */
      return 1;
    }
  }

  return 0;
}

