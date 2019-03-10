#include "../lib/transaction.h"
#include "../lib/util.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Cria uma lista de transações.
 * 
 * @return transactions_p 
 */
transactions_p create_transactions_list(void) {
  transactions_p transactions = (transactions_p)malloc(sizeof(transactions_t));
  if(!transactions)
    err_exit("Erro ao criar lista de transações!");

  transactions->first = NULL;
  transactions->length = 0;

  return transactions;
}

/**
 * @brief Destroi uma lista de transações.
 * 
 * @param transactions 
 * @return int 
 */
int destroy_transactions_list(transactions_p transactions) {
  if(!transactions)
    return 0;

  transaction_p transaction, ts;

  for (transaction = transactions->first; transaction != NULL; transaction = transaction->next) {
    ts = transaction;
    free(ts);
  }

  transactions->first = NULL;
  transactions->length = 0;

  //free(transactions);

  return 1;
}

/**
 * @brief Cria uma transação a parti de uma string.
 * 
 * @param trstr 
 * @return transaction_p 
 */
transaction_p create_transaction(char *trstr) {
  if(!trstr)
    err_exit("Não é possível criar uma transação nula.");

  transaction_p transaction = (transaction_p)malloc(sizeof(transaction_t));
  if(!transaction)
    err_exit("Erro ao criar nodo!");

  sscanf(trstr, "%d %d %c  %c", &transaction->order, &transaction->id, &transaction->operation, &transaction->data);

  transaction->active = 0;
  transaction->next = NULL;

  return transaction;
}

/**
 * @brief Cria uma transação a partir de outra transação.
 * 
 * @param t 
 * @return transaction_p 
 */
transaction_p create_trans(transaction_p t) {
  if(!t)
    err_exit("Não é possível criar uma transação nula.");

  transaction_p ts = NULL;
  ts = (transaction_p)malloc(sizeof(transaction_t));
  if(!ts)
    err_exit("Erro ao criar nodo!");

  ts->order = t->order;
  ts->id = t->id;
  ts->operation = t->operation;
  ts->data = t->data;
  ts->active = 0;
  ts->next = NULL;

  return ts;
}

/**
 * @brief Adiciona uma transação à lista de transações.
 * 
 * @param transactions 
 * @param transaction 
 */
void add_transaction(transactions_p transactions, transaction_p transaction) {
  if(!transactions)
    err_exit("A lista de transações não existe!");

  if(!transaction)
    err_exit("Não é possível adicionar uma transação nula.");

  transaction_p first = transactions->first;

  if(first != NULL) {
    while(first->next != NULL) {
      first = first->next;
    }

    first->next = transaction;
    transaction->next = NULL;
  } else {
    transactions->first = transaction;
  }

  transactions->length++;
}

/**
 * @brief Remove uma transação da lista de transações.
 * 
 * @param transactions 
 * @param id 
 * @return int 
 */
int remove_transaction(transactions_p transactions, int id) {
  if(!transactions)
    err_exit("A lista de transações não existe!");

  transaction_p transaction, aux_trans;

  for(transaction = transactions->first; transaction != NULL; transaction = transaction->next) {
    if(transaction->id == id) {
      aux_trans->next = transaction->next;

      //free(transaction);

      transactions->length--;

      return 1;
    }

    aux_trans = transaction;
  }

  return 0;
}

/**
 * @brief Inativa uma transação.
 * 
 * @param transactions 
 * @param id 
 */
void inactive_transaction(transactions_p transactions, unsigned int id) {
  if(!transactions)
    err_exit("A lista de transações não existe!");
  
  transaction_p transaction;

  for(transaction = transactions->first; transaction != NULL; transaction = transaction->next) {
    if(transaction->id == id) {
      transaction->active = 1;
    }
  }
}

/**
 * @brief Procura uma transação na lista de transações.
 * 
 * @param transactions 
 * @param id 
 * @return int 
 */
int exists_transaction(transactions_p transactions, unsigned int id) {
  if(!transactions)
    err_exit("A lista de transações não existe!");
  
  transaction_p transaction;

  for(transaction = transactions->first; transaction != NULL; transaction = transaction->next) {
    if(transaction->id == id) {
      return 1;
    }
  }

  return 0;
}