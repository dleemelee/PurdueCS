#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashtable.h"

#define PASS 1
#define FAIL 0

int test1() {
    /**
     * Basic test to verify that the table is created correctly
     */
    hashtable_t* ht = create_hashtable(1024);
    if (ht == NULL) return FAIL;
    if (ht->table_len != 1024) return FAIL;
    int i;
    for (i = 0; i < 1024; i++)
        if (ht->table[i] != NULL) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Basic test to add a single key
 */
int test2() {
    int ret = 1;
    hashtable_t* ht = create_hashtable(1024);
    if (ht == NULL) return 0;
    if (set(ht, "Hi bob", 0) != 0) ret = 0;
    free_hashtable(ht);
    return ret;
}

/**
 * Basic set/get pair test
 */
int test3() {
    hashtable_t* ht = create_hashtable(1024);
    if (ht == NULL) return 0;
    if (set(ht, "Hello", 4.5) != 0) return FAIL;
    double val;
    if (get(ht, "Hello", &val) != 0 || val != 4.5) return FAIL;
    free_hashtable(ht);
    return val == 4.5;
}

/**
 * Basic test for get() without key
 */
int test4() {
    int ret = PASS;
    hashtable_t* ht = create_hashtable(1024);
    if (ht == NULL) return FAIL;
    double val;
    if (get(ht, "No such key", &val) != -1) ret = FAIL;
    free_hashtable(ht);
    return ret;
}


/** Parameter testing **/

/**
 * Validate create_hashtable() parameter handling
 */
int test5() {
    /* Invalid parameter to create_hashtable() */
    hashtable_t* ht = create_hashtable(-1);
    if (ht != NULL) return FAIL;
    ht = create_hashtable(0);
    if (ht != NULL) return FAIL;
    return PASS;
}

/**
 * Validate free_hashtable() parameter handling
 */
int test6() {
    /* Shouldn't crash and Valgrind should come up clean here */
    free_hashtable(NULL);
    return PASS;
}

/**
 * Validate remove_key() parameter handling
 */
int test7() {
    hashtable_t* ht = NULL;
    if (remove_key(ht, "Key") != -1) return FAIL;
    if ((ht = create_hashtable(1024)) == NULL) return FAIL;
    if (remove_key(ht, NULL) != -1) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Validate get() parameter handling
 */
int test8() {
    hashtable_t* ht = NULL;
    /* NULL hashtable param */
    double val;
    if (get(ht, "Key", &val) != -1) return FAIL;
    if ((ht = create_hashtable(256)) == NULL) return FAIL;
    if (get(ht, NULL, &val) != -1) return FAIL;
    if (get(ht, "Key", NULL) != -1) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Validate set() parameter handling
 */
int test9() {
    hashtable_t* ht = NULL;
    if (set(ht, "Key", 4.5) != -1) return FAIL;
    if ((ht = create_hashtable(1024)) == NULL) return FAIL;
    if (set(ht, NULL, 4.5) != -1) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Validate key_exists() parameter handling
 */
int test10() {
    hashtable_t* ht = NULL;
    if (key_exists(ht, "Key") != -1) return FAIL;
    if ((ht = create_hashtable(1024)) == NULL) return FAIL;
    if (key_exists(ht, NULL) != -1) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Test two nodes in single chain
 */
int test11() {
    /* Size 1 forces collisions */
    hashtable_t* ht = create_hashtable(1);
    if (ht->table_len != 1) return FAIL;
    if (ht == NULL) return FAIL;
    if (set(ht, "OurKey", 2.4) != 0) return FAIL;
    if (set(ht, "OurOtherKey", -0.5) != 0) return FAIL;
    double val;
    if (get(ht, "OurKey", &val) != 0 || val != 2.4) return FAIL;
    if (get(ht, "OurOtherKey", &val) != 0 || val != -0.5) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Test basic removal
 */
int test12() {
    hashtable_t* ht = create_hashtable(1024);
    if (ht == NULL) return FAIL;
    if (set(ht, "MyKeyForLater", -1040.0) != 0) return FAIL;
    if (remove_key(ht, "MyKeyForLater") != 0) return FAIL;
    if (key_exists(ht, "MyKeyForLater") != 0) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Test very long keys and deep copy
 */
int test13() {
    char buf[1024];
    char buf2[1024];
    memset(buf, 'a', 1023);
    memset(buf2, 'a', 1023);
    buf[1023] = '\0';
    buf2[1023] = '\0';
    hashtable_t* ht = create_hashtable(1024);
    if (ht == NULL) return FAIL;
    if (set(ht, buf, 2.4) != 0) return FAIL;
    double val;
    if (get(ht, buf, &val) != 0 || val != 2.4) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Test deep vs. shallow copy of strings
 */
int test14() {
    char buf[1024];
    char buf2[1024];
    memset(buf, 'a', 1023);
    memset(buf2, 'a', 1023);
    buf[1023] = '\0';
    buf2[1023] = '\0';
    hashtable_t* ht = create_hashtable(1024);
    if (ht == NULL) return FAIL;
    if (set(ht, buf, 2.4) != 0) return FAIL;
    memset(buf, 'b', 1023);
    if (set(ht, buf, -5.0) != 0) return FAIL;
    double val;
    if (get(ht, buf2, &val) != 0 || val != 2.4) return FAIL;
    free_hashtable(ht);
    return PASS;
}

/**
 * Test more complex insertion/deletion sequence
 */
int test15() {
    /* Use same buffer to catch shallow copies */
    char buf[1024];
    hashtable_t* ht = create_hashtable(1024);
    if (ht == NULL) return FAIL;
    strcpy(buf, "NonExistantKey");
    if (key_exists(ht, buf) != 0) return FAIL;
    double val;
    if (get(ht, buf, &val) != -1) return FAIL;
    
    /* Add four keys */
    int i;
    for (i = 1; i <= 4; i++) {
        sprintf(buf, "MyKey:%d", i);
        if (set(ht, buf, 45.0 + i) != 0) return FAIL;
        if (key_exists(ht, buf) != 1) return FAIL;
    }

    /* Remove the middle key */
    strcpy(buf, "MyKey:2");
    if (remove_key(ht, buf) != 0) return FAIL;
    if (key_exists(ht, buf) != 0) return FAIL;

    /* Ensure we can access two of the others */
    strcpy(buf, "MyKey:1");
    if (get(ht, buf, &val) != 0 || val != 46.0) return FAIL;

    strcpy(buf, "MyKey:4");
    if (get(ht, buf, &val) != 0 || val != 49.0) return FAIL;

    free_hashtable(ht);
    return PASS;
}

/**
 * Same as previous test, but force chaining
 */
int test16() {
    /* Use same buffer to catch shallow copies */
    char buf[1024];
    hashtable_t* ht = create_hashtable(1);
    if (ht == NULL) return FAIL;
    strcpy(buf, "NonExistantKey");
    if (key_exists(ht, buf) != 0) return FAIL;
    double val;
    if (get(ht, buf, &val) != -1) return FAIL;
    
    /* Add four keys */
    int i;
    for (i = 1; i <= 4; i++) {
        sprintf(buf, "MyKey:%d", i);
        if (set(ht, buf, 45.0 + i) != 0) return FAIL;
        if (key_exists(ht, buf) != 1) return FAIL;
    }

    /* Remove the middle key */
    strcpy(buf, "MyKey:2");
    if (remove_key(ht, buf) != 0) return FAIL;
    if (key_exists(ht, buf) != 0) return FAIL;

    /* Ensure we can access two of the others */
    strcpy(buf, "MyKey:1");
    if (get(ht, buf, &val) != 0 || val != 46.0) return FAIL;

    strcpy(buf, "MyKey:4");
    if (get(ht, buf, &val) != 0 || val != 49.0) return FAIL;

    free_hashtable(ht);
    return PASS;
}

/**
 * Test that they are storing in the correct slots
 * and aren't playing tricks internally
 */
int test17() {
    hashtable_t* ht = create_hashtable(32);
    if (ht == NULL) return FAIL;
    if (ht->table_len != 32) return FAIL;

    int i;
    for (i = 0; i < ht->table_len; i++)
        if (ht->table[i] != NULL) return FAIL;

    if (set(ht, "MyKey", 10) != 0) return FAIL;
    if (set(ht, "MyOtherKey", 20) != 0) return FAIL;
   
    if (ht->table[hash("MyKey") % ht->table_len] == NULL) return FAIL;
    if (ht->table[hash("MyOtherKey") % ht->table_len] == NULL) return FAIL;
    
    free_hashtable(ht);
    return PASS;
}

/**
 * Test for the creation and deletion of multiple hash tables
 */
int test18() {
    hashtable_t* arr[5];
    int i;
    for (i = 0; i < 5; i++) {
        if ((arr[i] = create_hashtable(i + 24)) == NULL) return FAIL;
        if (arr[i]->table_len != i + 24) return FAIL;
        if (arr[i]->table[23] != NULL) return FAIL;
    }

    for (i = 0; i < 5; i++) free_hashtable(arr[i]);
    return PASS;
}

/**
 * Test multiple set operations
 */
int test19() {
    hashtable_t* ht = create_hashtable(23);
    if (ht == NULL) return FAIL;

    double value;
    if ((set(ht, "MyLargeKeyThatWillBeSetMultipleTimes", -10)) != 0) return FAIL;
    if (key_exists(ht, "MyLargeKeyThatWillBeSetMultipleTimes") != 1) return FAIL;
    if (set(ht, "MyLargeKeyThatWillBeSetMultipleTimes", 20) != 0) return FAIL;
    if (get(ht, "MyLargeKeyThatWillBeSetMultipleTimes", &value) != 0 || value != 20) return FAIL;
    if (set(ht, "MyLargeKeyThatWillBeSetMultipleTimes", -100) != 0) return FAIL;
    if (get(ht, "MyLargeKeyThatWillBeSetMultipleTimes", &value) != 0 || value != -100) return FAIL;

    free_hashtable(ht);
    return PASS;
}

/**
 * Test large and extreme values for set()
 */
int test20() {
    hashtable_t* ht = create_hashtable(400);
    if (ht == NULL) return FAIL;

    double small_value = -1000000000000000000000.0;
    if (set(ht, "AnotherSmallValue", small_value) != 0) return FAIL;
    double large_value = 100000000000000000000.0;
    if (set(ht, "AnotherLargeValue", large_value) != 0) return FAIL;

    double value;
    if (get(ht, "AnotherSmallValue", &value) != 0 || value != small_value) return FAIL;
    if (get(ht, "AnotherLargeValue", &value) != 0 || value != large_value) return FAIL;

    free_hashtable(ht);

    return PASS;
}

/**
 * Check that multiple hash tables work to defeat global variable use
 */
int test21() {
    hashtable_t* ht1 = create_hashtable(64);
    hashtable_t* ht2 = create_hashtable(128);

    if (ht1 == NULL || ht2 == NULL) return FAIL;

    double value1, value2;
    if (get(ht1, "Key1", &value1) != -1) return FAIL;
    if (get(ht2, "Key2", &value2) != -1) return FAIL;

    if (set(ht1, "Key1", 0.4) != 0) return FAIL;
    if (set(ht2, "Key2", 0.5) != 0) return FAIL;

    if (key_exists(ht1, "Key1") != 1) return FAIL;
    if (key_exists(ht2, "Key2") != 1) return FAIL;

    if (get(ht1, "Key3", &value1) != -1) return FAIL;
    if (get(ht2, "Key4", &value2) != -1) return FAIL;

    if (get(ht1, "Key1", &value1) != 0 || value1 != 0.4) return FAIL;
    if (get(ht2, "Key2", &value2) != 0 || value2 != 0.5) return FAIL;

    if (set(ht1, "Key3", 0.6) != 0) return FAIL;
    if (set(ht2, "Key4", 0.7) != 0) return FAIL;
    if (set(ht1, "Key5", 0.8) != 0) return FAIL;
    if (set(ht2, "Key6", 0.9) != 0) return FAIL;

    if (get(ht1, "Key5", &value1) != 0 || value1 != 0.8) return FAIL;
    if (get(ht2, "Key6", &value2) != 0 || value2 != 0.9) return FAIL;

    if (remove_key(ht1, "Key3") != 0) return FAIL;
    if (remove_key(ht2, "Key4") != 0) return FAIL;

    if (key_exists(ht1, "Key3") != 0) return FAIL;
    if (key_exists(ht2, "Key4") != 0) return FAIL;

    free_hashtable(ht1);
    free_hashtable(ht2);

    return PASS;
}

/*
 * Try with three hash tables
 */
int test22() {
    hashtable_t* tables[3];
    char buf[256];
    int i, j;
    for (i = 0; i < 3; i++) {
        tables[i] = create_hashtable(256 + i);
        if (tables[i]->table_len != 256 + i)
            return FAIL;
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1000; j++) {
            sprintf(buf, "LargeKey%d-Table%d", j, i);
            if (set(tables[i], buf, i + j) != 0)
                return FAIL;
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1000; j++) {
            sprintf(buf, "LargeKey%d-Table%d", j, i);
            if (key_exists(tables[i], buf) != 1)
                return FAIL;
        }
        for (j = 0; j < 1000; j++) {
            sprintf(buf, "LargeKey%d-Table%d", j, i);
            if (remove_key(tables[i], buf) != 0)
                return FAIL;
            if (key_exists(tables[i], buf) != 0)
                return FAIL;
        }
        free_hashtable(tables[i]);
    }
    return PASS;
}

/**
 * You get a free point, you get a free point, you ALL get FREE POINTS!!!
 * (Translation: I've tested the daylights out of the hash table and can't think for new cases...)
 */
int test23() {
    return PASS;
}

int test24() {
    return PASS;
}

int test25() {
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
