#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "io.h"

#define FAIL 0
#define PASS 1

/**
 * Test reading account info
 */
int test1() {
    char buf[128];
    double val;
    char* input =   "Company1 10000\n"
                    "Company2 20000";
    /* Allows us to open a string as if it were a file */
    FILE* fd = fmemopen(input, strlen(input), "r");

    hashtable_t* accounts = read_accounts(fd);
    if (accounts == NULL) return FAIL;
    strcpy(buf, "Company1");
    if (get(accounts, buf, &val) != 0 || val != 10000.0) return FAIL;
    strcpy(buf, "Company2");
    if (get(accounts, buf, &val) != 0 || val != 20000.0) return FAIL;

    free_hashtable(accounts);
    fclose(fd);
    return PASS;
}

/**
 * Test reading transactions
 */
int test2() {
    char* input =   "100 ADD Facebook 200\n"
                    "101 ADD Google 300\n"
                    "102 TRANSFER Google Facebook 100\n"
                    "103 REMOVE Google";

    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    if (list == NULL) return FAIL;
    
    /* Start at the head of the list */
    node_t* curr = list->head;
    if (curr == NULL) return FAIL;
    
    /* 100 ADD Facebook 200 */
    if (curr->timestamp != 100 || curr->transaction_type != ADD
        || strcmp("Facebook", curr->company1) || curr->company2 != NULL
        || curr->value != 200) return FAIL;
    
    /* Move to the next in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;

    /* 101 ADD Google 300 */
    if (curr->timestamp != 101 || curr->transaction_type != ADD
        || strcmp("Google", curr->company1) || curr->company2 != NULL
        || curr->value != 300) return FAIL;

    /* Move to the next node in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;

    /* 102 TRANSFER Google Facebook 100 */
    if (curr->timestamp != 102 || curr->transaction_type != TRANSFER
        || strcmp("Google", curr->company1) || strcmp("Facebook", curr->company2)
        || curr->value != 100) return FAIL;

    /* Move to the next node in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;
    
    /* 103 REMOVE Google */
    if (curr->timestamp != 103 || curr->transaction_type != REMOVE
        || strcmp("Google", curr->company1) || curr->company2 != NULL)
        return FAIL;

    /* curr should be the last node in the list */
    if (curr->next != NULL)
        return FAIL;

    free_linkedlist(list);
    fclose(fd);
    return PASS;
}

/**
 * Test apply_transactions()
 */
int test3() {
    hashtable_t* accounts = create_hashtable(1024);
    linkedlist_t* transactions = create_linkedlist();

    if (add_node(transactions, create_node(1000, ADD, "Microsoft", NULL, 20000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1001, ADD, "Apple", NULL, 30000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1004, TRANSFER, "Apple", "Microsoft", 10000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1008, REMOVE, "Apple", NULL, 0.0)) < 0)
        return FAIL;

    if (apply_transactions(transactions, accounts) != 4) return FAIL;

    /* Microsoft should have an account balance of 30000 and Apple shouldn't exist */
    double val;
    if (key_exists(accounts, "Apple") != 0) return FAIL;
    if (get(accounts, "Microsoft", &val) < 0 || val != 30000.0) return FAIL;

    free_hashtable(accounts);
    free_linkedlist(transactions);
    return PASS;
}

/**
 * Test read_transactions() with leading and trailing space
 */
int test4() {
    char* input =   "\t100 ADD Facebook 200\n"
                    "101 ADD Google 300 \n"
                    " 102 TRANSFER Google Facebook 100   \n"
                    "103 REMOVE Google\n";

    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    if (list == NULL) return FAIL;
    
    /* Start at the head of the list */
    node_t* curr = list->head;
    if (curr == NULL) return FAIL;
    
    /* 100 ADD Facebook 200 */
    if (curr->timestamp != 100 || curr->transaction_type != ADD
        || strcmp("Facebook", curr->company1) || curr->company2 != NULL
        || curr->value != 200) return FAIL;
    
    /* Move to the next in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;

    /* 101 ADD Google 300 */
    if (curr->timestamp != 101 || curr->transaction_type != ADD
        || strcmp("Google", curr->company1) || curr->company2 != NULL
        || curr->value != 300) return FAIL;

    /* Move to the next node in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;

    /* 102 TRANSFER Google Facebook 100 */
    if (curr->timestamp != 102 || curr->transaction_type != TRANSFER
        || strcmp("Google", curr->company1) || strcmp("Facebook", curr->company2)
        || curr->value != 100) return FAIL;

    /* Move to the next node in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;
    
    /* 103 REMOVE Google */
    if (curr->timestamp != 103 || curr->transaction_type != REMOVE
        || strcmp("Google", curr->company1) || curr->company2 != NULL)
        return FAIL;

    /* curr should be the last node in the list */
    if (curr->next != NULL)
        return FAIL;

    free_linkedlist(list);
    fclose(fd);
    return PASS;
}

/**
 * Test read_accounts() with leading and trailing spaces
 */
int test5() {
    char buf[128];
    double val;
    char* input =   " Company1 10000\t\n"
                    "\tCompany2 20000 \n"
                    "  Company3 30000\n";
    /* Allows us to open a string as if it were a file */
    FILE* fd = fmemopen(input, strlen(input), "r");

    hashtable_t* accounts = read_accounts(fd);
    if (accounts == NULL) return FAIL;
    strcpy(buf, "Company1");
    if (get(accounts, buf, &val) != 0 || val != 10000.0) return FAIL;
    strcpy(buf, "Company2");
    if (get(accounts, buf, &val) != 0 || val != 20000.0) return FAIL;
    strcpy(buf, "Company3");
    if (get(accounts, buf, &val) != 0 || val != 30000.0) return FAIL;

    free_hashtable(accounts);
    fclose(fd);
    return PASS;
}

/**
 * Stress test for company name length
 */
int test6() {
    char* input =   "100 ADD AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 200\n";

    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    if (list == NULL) return FAIL;
    
    /* Start at the head of the list */
    node_t* curr = list->head;
    if (curr == NULL) return FAIL;
    
    if (curr->timestamp != 100 || curr->transaction_type != ADD
        || strcmp("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", curr->company1) || curr->company2 != NULL
        || curr->value != 200) return FAIL;
    
    free_linkedlist(list);
    fclose(fd);
    return PASS;
}

/**
 * Stress test for company name length
 */
int test7() {
    char buf[256];
    double val;
    char* input =   "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 10000\t\n";
    /* Allows us to open a string as if it were a file */
    FILE* fd = fmemopen(input, strlen(input), "r");

    hashtable_t* accounts = read_accounts(fd);
    if (accounts == NULL) return FAIL;
    strcpy(buf, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    if (get(accounts, buf, &val) != 0 || val != 10000.0) return FAIL;

    free_hashtable(accounts);
    fclose(fd);
    return PASS;
}

/**
 * Test error detection of out of order transactions
 */
int test8() {
    char* input =   "\t100 ADD Facebook 200\n"
                    "101 ADD Google 300\n"
                    "99 TRANSFER Google Facebook 100";

    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    fclose(fd);
    if (list != NULL) return FAIL;
    return PASS;
}

/**
 * Test bad input checking for apply_transactions()
 */
int test9() {
    if (apply_transactions(NULL, NULL) != -1) return FAIL;
    
    hashtable_t* accounts = create_hashtable(2048);
    if (apply_transactions(NULL, accounts) != -1) return FAIL;
    
    linkedlist_t* transactions = create_linkedlist();
    if (apply_transactions(transactions, NULL) != -1) return FAIL;

    if (apply_transactions(transactions, accounts) != 0) return FAIL;

    free_hashtable(accounts);
    free_linkedlist(transactions);
    return PASS;
}

/**
 * Test bad input checking for read_transactions()
 */
int test10() {
    if (read_transactions(NULL) != NULL) return FAIL;
    return PASS;
}

/**
 * Test bad input checking for read_accounts()
 */
int test11() {
    if (read_accounts(NULL) != NULL) return FAIL;
    return PASS;
}

/**
 * Test bad input checking for write_accounts()
 */
int test12() {
    write_accounts(NULL, NULL);
    return PASS;
}

/**
 * Test extra parameters for read_accounts()
 */
int test13() {
    char *input = "Microsoft 1000 1";
    FILE* fd = fmemopen(input, strlen(input), "r");
    hashtable_t* accounts = read_accounts(fd);
    if (accounts != NULL) return FAIL;
    fclose(fd);
    return PASS;
}

/**
 * Test extra parameters for read_transactions()
 */
int test14() {
    char *input = "1000 ADD Google 1000 r";
    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    fclose(fd);
    if (list != NULL) return FAIL;
    return PASS;
}

/**
 *  Test bad transaction type
 */
int test15() {
    char *input = "1000 BADTYPE";
    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    fclose(fd);
    if (list != NULL) return FAIL;
    return PASS;
}

/**
 * Test for preserving ordering with transactions with equal timestamps
 */
int test16() {
    char* input =   "\t100 ADD Facebook 200\n"
                    "101 ADD Google 300 \n"
                    " 101 TRANSFER Google Facebook 100   \n"
                    "101 REMOVE Google\n";

    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    fclose(fd);
    if (list == NULL) return FAIL;
    
    /* Start at the head of the list */
    node_t* curr = list->head;
    if (curr == NULL) return FAIL;
    
    /* 100 ADD Facebook 200 */
    if (curr->timestamp != 100 || curr->transaction_type != ADD
        || strcmp("Facebook", curr->company1) || curr->company2 != NULL
        || curr->value != 200) return FAIL;
    
    /* Move to the next in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;

    /* 101 ADD Google 300 */
    if (curr->timestamp != 101 || curr->transaction_type != ADD
        || strcmp("Google", curr->company1) || curr->company2 != NULL
        || curr->value != 300) return FAIL;

    /* Move to the next node in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;

    /* 101 TRANSFER Google Facebook 100 */
    if (curr->timestamp != 101 || curr->transaction_type != TRANSFER
        || strcmp("Google", curr->company1) || strcmp("Facebook", curr->company2)
        || curr->value != 100) return FAIL;

    /* Move to the next node in the linked list */
    curr = curr->next;
    if (curr == NULL) return FAIL;
    
    /* 101 REMOVE Google */
    if (curr->timestamp != 101 || curr->transaction_type != REMOVE
        || strcmp("Google", curr->company1) || curr->company2 != NULL)
        return FAIL;

    /* curr should be the last node in the list */
    if (curr->next != NULL)
        return FAIL;

    free_linkedlist(list);
    return PASS;
}

/**
 * Test for invalid value (negative) handling
 */
int test17() {
    char* input =   "\t100 ADD Facebook -1\n"
                    "101 TRANSFER Google Facebook 100\n"
                    "102 REMOVE Google\n";

    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    fclose(fd);
    if (list != NULL) return FAIL;
    
    return PASS;
}

/**
 * Test for invalid value (negative) handling
 */
int test18() {
    char* input =   "\t100 ADD Facebook 10\n"
                    "101 TRANSFER Google Facebook -2\n"
                    "102 REMOVE Google\n";

    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    fclose(fd);
    if (list != NULL) return FAIL;
    
    return PASS;
}

/**
 * Test that apply_transactions() is checking as well
 */
int test19() {
    hashtable_t* accounts = create_hashtable(1024);
    linkedlist_t* transactions = create_linkedlist();

    if (add_node(transactions, create_node(1000, ADD, "Microsoft", NULL, -1)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1001, ADD, "Apple", NULL, 30000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1004, TRANSFER, "Apple", "Microsoft", 10000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1008, REMOVE, "Apple", NULL, 0.0)) < 0)
        return FAIL;

    if (apply_transactions(transactions, accounts) != -1) return FAIL;

    free_hashtable(accounts);
    free_linkedlist(transactions);
    return PASS;
}

/**
 * Test that apply_transactions() is checking as well
 */
int test20() {
    hashtable_t* accounts = create_hashtable(1024);
    linkedlist_t* transactions = create_linkedlist();

    if (add_node(transactions, create_node(1000, ADD, "Microsoft", NULL, 2000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1001, ADD, "Apple", NULL, 30000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1004, TRANSFER, "Apple", "Microsoft", -1)) < 0)
        return FAIL;

    if (apply_transactions(transactions, accounts) != -1) return FAIL;

    free_hashtable(accounts);
    free_linkedlist(transactions);
    return PASS;
}

/**
 * Test that transfers from the same company to itself are handled properly and skipped
 */
int test21() {
    hashtable_t* accounts = create_hashtable(1024);
    linkedlist_t* transactions = create_linkedlist();

    if (add_node(transactions, create_node(1000, ADD, "Microsoft", NULL, 2000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1001, ADD, "Apple", NULL, 30000)) < 0)
        return FAIL;
    if (add_node(transactions, create_node(1004, TRANSFER, "Microsoft", "Microsoft", 3000)) < 0)
        return FAIL;

    if (apply_transactions(transactions, accounts) != 3) return FAIL;

    double value;
    if (get(accounts, "Microsoft", &value) != 0 || value != 2000) return FAIL;

    free_hashtable(accounts);
    free_linkedlist(transactions);
    return PASS;
}

/**
 * Test for reading a blank transaction file
 */
int test22() {
    char* input = "\n";

    FILE* fd = fmemopen(input, strlen(input), "r");
    linkedlist_t* list = read_transactions(fd);
    fclose(fd);
    if (list == NULL || list->head != NULL || list->tail != NULL) return FAIL;
    free_linkedlist(list);
    return PASS;
}

/**
 * Test for reading a blank transaction file
 */
int test23() {
    char* input = " ";

    FILE* fd = fmemopen(input, strlen(input), "r");
    fseek(fd, 1, SEEK_CUR);
    linkedlist_t* list = read_transactions(fd);
    fclose(fd);
    if (list == NULL || list->head != NULL || list->tail != NULL) return FAIL;
    free_linkedlist(list);
    return PASS;
}

/**
 * Test for reading a blank accounts file
 */
int test24() {
    char* input = "\n";
    FILE* fd = fmemopen(input, strlen(input), "r");
    hashtable_t* accounts = read_accounts(fd);
    fclose(fd);
    if (accounts == NULL) return FAIL;
    free_hashtable(accounts);
    return PASS;
}

/**
 * Test for reading a blank accounts file
 */
int test25() {
    char* input = " ";
    FILE* fd = fmemopen(input, strlen(input), "r");
    fseek(fd, 1, SEEK_CUR);
    hashtable_t* accounts = read_accounts(fd);
    fclose(fd);
    if (accounts == NULL) return FAIL;
    free_hashtable(accounts);
    return PASS;
}

int dispatch_test(int (*test)(), int idx) {
    int ret = test();
    if (ret == PASS) fprintf(stderr, "PASS: test%d\n", idx);
    else fprintf(stderr, "FAIL: test%d\n", idx);
    return ret;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <caseid>\n", argv[0]);
        return 1;
    }

    int (*tests[])() = {
        test1, test2, test3,
        test4, test5, test6,
        test7, test8, test9,
        test10, test11, test12,
        test13, test14, test15,
        test16, test17, test18,
        test19, test20, test21,
        test22, test23, test24,
        test25
    };
    const int testcount = sizeof(tests)/sizeof(int(*)());
    int testcase = atoi(argv[1]);
    if (testcase == 0) {
        int idx, ret = 1;
        for (idx = 1; idx <= testcount; idx++)
            ret = dispatch_test(tests[idx - 1], idx) && ret;
        return !ret;
    } else {
        return !dispatch_test(tests[testcase - 1], testcase);
    }
}
