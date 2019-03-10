#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct transaction {
    unsigned int order;
    unsigned int id;
    char operation;
    char data;
    int active;
    struct transaction *next;
} transaction_t, *transaction_p;

typedef struct transactions {
    unsigned int length;
    transaction_p first;
} transactions_t, *transactions_p;

transactions_p create_transactions_list(void);

int destroy_transactions_list(transactions_p transactions);

transaction_p create_transaction(char *transaction);

transaction_p create_trans(transaction_p t);

void add_transaction(transactions_p transactions, transaction_p transaction);

void inactive_transaction(transactions_p transactions, unsigned int id);

int exists_transaction(transactions_p transactions, unsigned int id);

int remove_transaction(transactions_p transactions, int id);

#endif