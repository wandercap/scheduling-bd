#include "../lib/scheduling.h"
#include "../lib/transaction.h"
#include "../lib/conflict.h"
#include "../lib/vision.h"
#include "../lib/util.h"

/**
 * @brief Verifica o escalonamento das transações.
 * 
 * @param transactions 
 */
void do_scheduling(transactions_p transactions) {
  transactions_p trans, actives;
  transaction_p t, ta;
  int i = 1;

  /**
   * @brief Cria uma lista de transações lidas e transações ativas.
   * 
   */
  trans = create_transactions_list();
  actives = create_transactions_list();

  /**
   * @brief Processa cada uma das transações.
   * 
   */
  for(t = transactions->first; t != NULL; t = t->next) {

    /**
     * @brief Se não é uma operação de commit, adiciona à lista de transações ativas e lidas.
     * 
     */
    if(t->operation != 'c') {
      if(!exists_transaction(actives, t->id)) {
        add_transaction(actives, create_trans(t));
      }
      add_transaction(trans, create_trans(t));
    } else {
      /**
       * @brief Se é commit, subtraio as transações ativas.
       * 
       */
      actives->length--;

      /**
       * @brief Se não há mais transações ativas, processe as transações.
       * 
       */
      if(actives->length == 0) {
        char *str = (char *)malloc(256*sizeof(char));
        char *act = (char *)malloc(256*sizeof(char));

        for(ta = actives->first; ta != NULL; ta = ta->next) {
          sprintf(act, "%s,%d", act, ta->id);
        }

        act++;
        sprintf(str, "%d %s", i, act);

        /**
         * @brief Verifico se as transações são serializaveis por conflito.
         * 
         */
        if(is_conflict(trans)) {
          sprintf(str, "%s NS", str);
        } else {
          sprintf(str, "%s SS", str);
        }

        /**
         * @brief Verifico se as transações são equivalentes por visão.
         * 
         */
        if(is_vision(trans)) {
          sprintf(str, "%s NV", str);
        } else {
          sprintf(str, "%s SV", str);
        }

        printf("%s\n", str);

        destroy_transactions_list(trans);
        destroy_transactions_list(actives);

        // trans = create_transactions_list();
        // actives = create_transactions_list();
        i++;
      }
    }
  }
}