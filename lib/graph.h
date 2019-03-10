#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
  void *content;
  struct list_node *next;
} list_node_t, *list_node_p;

typedef struct list {
  unsigned int length;
  list_node_p first; 
} list_t, *list_p;

typedef struct vertex {
  unsigned int id;
  unsigned int color;
  unsigned int visit;
  list_p in, out;
} vertex_t, *vertex_p;

typedef struct edge {
  vertex_p origin, destiny;
} edge_t, *edge_p;

typedef struct graph {
  list_p vertex, edges;
} graph_t, *graph_p;

list_p create_list(void);

int destroy_list(list_p list);

list_node_p create_list_node(void *content);

void add_list_node(list_p list, list_node_p node);

graph_p create_graph(void);

int destroy_graph(graph_p g);

vertex_p create_vertex(unsigned int id);

edge_p create_edge(vertex_p origin, vertex_p destiny);

vertex_p get_vertex(unsigned int id, graph_p g);

int find_edge(graph_p g, edge_p e);

int is_cyclic(graph_p g);

#endif
