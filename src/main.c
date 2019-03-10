#include <stdlib.h>
#include <stdio.h>
#include "../lib/transaction.h"
#include "../lib/conflict.h"
#include "../lib/scheduling.h"
#include "../lib/util.h"

#define STR 256

int main(int argc, char **argv) {
	FILE *input;
	char *trstr;
	transactions_p transactions;
	unsigned int order, id;
    char operation, data;

	input = stdin;
	if(!input) {
		err_exit("Erro ao ler o arquivo!");
	}

	trstr = (char *)malloc(STR*sizeof(char));

	transactions = create_transactions_list();

	while(fgets(trstr, STR, input)!=NULL) {
		sscanf(trstr, "%d %d %c %c", &order, &id, &operation, &data);
		if(operation == 'c')
			inactive_transaction(transactions, id);
		add_transaction(transactions, create_transaction(trstr));
	}

	do_scheduling(transactions);

	return 0;
}
