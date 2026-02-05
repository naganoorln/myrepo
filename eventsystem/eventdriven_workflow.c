#include <stdio.h>

/* States */
typedef enum {
    INITIATED,
    VALIDATED,
    DEBITED,
    CREDITED,
    COMPLETED,
    FAILED,
    REVERSED
} State;

/* Events */
typedef enum {
    EVT_INIT,
    EVT_VALID_OK,
    EVT_VALID_FAIL,
    EVT_DEBIT_OK,
    EVT_DEBIT_FAIL,
    EVT_CREDIT_OK,
    EVT_CREDIT_FAIL,
    EVT_COMPLETE,
    EVT_REVERSE
} Event;

/* Acount Information */
typedef struct {
    int id;
    double balance;
} Account;

/*Trannsactin */
typedef struct {
    int id;
    double amount;
    Account *from;
    Account *to;
    State state;

    /* simulate downstream failure */
    int force_credit_fail;
} Transaction;

/* Event Bus */
typedef void (*Handler)(Transaction *);

typedef struct {
    Event event;
    Handler handler;
} Subscription;

Subscription bus[32];
int busSize = 0;

void subscribe(Event e, Handler h) {
    bus[busSize++] = (Subscription){e, h};
}

void publish(Event e, Transaction *tx) {
    for (int i = 0; i < busSize; i++) {
        if (bus[i].event == e) {
            bus[i].handler(tx);
        }
    }
}

/* Core Oerations */

int validate(Transaction *tx) {
    return tx->amount > 0 && tx->from->balance >= tx->amount;
}

int debit(Transaction *tx) {
    if (tx->from->balance < tx->amount)
        return 0;

    tx->from->balance -= tx->amount;
    return 1;
}

int credit(Transaction *tx) {
    if (tx->force_credit_fail)
        return 0;

    tx->to->balance += tx->amount;
    return 1;
}

void reverse(Transaction *tx) {
    tx->from->balance += tx->amount;
}

/* Services */

void audit(Transaction *tx) {
    printf("[AUDIT] Tx %d | State = %d\n", tx->id, tx->state);
}

void validation_service(Transaction *tx) {
    if (validate(tx)) {
        tx->state = VALIDATED;
        publish(EVT_VALID_OK, tx);
    } else {
        tx->state = FAILED;
        publish(EVT_VALID_FAIL, tx);
    }
}

void debit_service(Transaction *tx) {
    if (debit(tx)) {
        tx->state = DEBITED;
        publish(EVT_DEBIT_OK, tx);
    } else {
        tx->state = FAILED;
        publish(EVT_DEBIT_FAIL, tx);
    }
}

void credit_service(Transaction *tx) {
    if (credit(tx)) {
        tx->state = CREDITED;
        publish(EVT_CREDIT_OK, tx);
    } else {
        publish(EVT_CREDIT_FAIL, tx);
    }
}

void completion_service(Transaction *tx) {
    tx->state = COMPLETED;
    publish(EVT_COMPLETE, tx);
}

void reversal_service(Transaction *tx) {
    reverse(tx);
    tx->state = REVERSED;
    publish(EVT_REVERSE, tx);
}

/* Subscribe/Register Events */

void setup() {
    subscribe(EVT_INIT, validation_service);
    subscribe(EVT_VALID_OK, debit_service);
    subscribe(EVT_DEBIT_OK, credit_service);
    subscribe(EVT_CREDIT_OK, completion_service);

    subscribe(EVT_CREDIT_FAIL, reversal_service);

    subscribe(EVT_VALID_FAIL, audit);
    subscribe(EVT_DEBIT_FAIL, audit);
    subscribe(EVT_COMPLETE, audit);
    subscribe(EVT_REVERSE, audit);
}

/* Run Case */

void run_case(const char *title, Transaction tx) {
    printf(" \n--- %s ---\n", title);
    publish(EVT_INIT, &tx);
    printf("Final State: %d\n", tx.state);
    printf("From Balance: %.2f | To Balance: %.2f\n",
           tx.from->balance, tx.to->balance);
}

int main() {
    setup();

    /* Case 1: Success */
    Account a1 = {1, 1000};
    Account b1 = {2, 200};
    run_case("Success",
        (Transaction){1, 300, &a1, &b1, INITIATED, 0});

    /* Case 2: Validation Fail */
    Account a2 = {3, 100};
    Account b2 = {4, 500};
    run_case("Validation Fail",
        (Transaction){2, 500, &a2, &b2, INITIATED, 0});

    /* Case 3: Debit Fail (balance changed after validation) */
    Account a3 = {5, 400};
    Account b3 = {6, 100};
    a3.balance = 200; /* simulate race condition */
    run_case("Debit Fail",
        (Transaction){3, 300, &a3, &b3, INITIATED, 0});

    /* Case 4: Credit → Reversal */
    Account a4 = {7, 800};
    Account b4 = {8, 100};
    run_case("Credit Fail → Reversal",
        (Transaction){4, 250, &a4, &b4, INITIATED, 1});

    return 0;
}

