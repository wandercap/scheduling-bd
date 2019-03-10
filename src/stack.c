#include "../lib/stack.h"
#include "../lib/util.h"

/**
 * @brief Cria uma pilha.
 * 
 * @return stack_p 
 */
stack_p create_stack(void) {

  stack_p stack = (stack_p)malloc(sizeof(stack_t));
  if(!stack)
    err_exit("Erro ao criar pilha!");

  stack->first = NULL;
  stack->length = 0;

  return stack;

}

/**
 * @brief Destroi uma pilha.
 * 
 * @param stack 
 * @return int 
 */
int destroy_stack(stack_p stack) {
  if(!stack)
    return 0;

  stack_node_p node;

  while(stack->first) {
    node = stack->first;
    stack->first = stack->first->next;

    free(node->content);
    free(node);
  }

  free(stack);

  return 1;
}

/**
 * @brief Cria um nodo de pilha.
 * 
 * @param content 
 * @return stack_node_p 
 */
stack_node_p create_stack_node(void *content) {
  if(!content)
    err_exit("Não é possível criar um nodo sem conteúdo.");

  stack_node_p node = (stack_node_p)malloc(sizeof(stack_node_t));
  if(!node)
    err_exit("Erro ao criar nodo!");

  node->content = content;
  node->next = NULL;

  return node;
}

/**
 * @brief Adiciona um nodo no topo da pilha.
 * 
 * @param stack 
 * @param node 
 */
void push(stack_p stack, stack_node_p node) {
  if(!stack)
    err_exit("A pilha não existe!");

  if(!node)
    err_exit("Não é possível adicionar um nodo nulo.");

  stack_node_p first = stack->first;

  if(first != NULL) {
    node->next = first;
    stack->first = node;
  } else {
    stack->first = node;
  }

  stack->length++;
}

/**
 * @brief Retira um nodo do topo da pilha.
 * 
 * @param stack 
 * @return stack_node_p 
 */
stack_node_p pop(stack_p stack) {
  stack_node_p first = (stack_node_p)malloc(sizeof(stack_node_t));

  first = stack->first;
  stack->first = first->next;

  stack->length --;
  return first;
}