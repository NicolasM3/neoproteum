#include "lib.h"
#include "tests.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define DEFAULT_CAPACITY 8
#define DEFAULT_EXPANSION_FACTOR 2
#define CC_MAX_ELEMENTS ((size_t) - 2)

// Test adding elements to the array
// -- When array is smaller then DEFAULT_CAPACITY
int array_elements_ammout = DEFAULT_CAPACITY - 2;
bool should_not_expand() {
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    a->size = array_elements_ammout;

    if(cc_array_capacity(a) != DEFAULT_CAPACITY){
        return false;
    }
    if(cc_array_size(a) != array_elements_ammout){
        return false;
    }

    return true;
}

// -- When array is bigger then DEFAULT_CAPACITY
bool should_expand_when_size_is_bigger() {
    array_elements_ammout = DEFAULT_CAPACITY + 1;
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    a->size = array_elements_ammout;

    if(cc_array_capacity(a) == DEFAULT_CAPACITY){
        return false;
    }
    if(cc_array_size(a) != array_elements_ammout){
        return false;
    }

    return true;
}

// -- When array is equal then DEFAULT_CAPACITY
bool should_expand_when_size_is_equal() {
    array_elements_ammout = DEFAULT_CAPACITY;
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    a->size = array_elements_ammout;

    if(cc_array_capacity(a) == DEFAULT_CAPACITY){
        return false;
    }
    if(cc_array_size(a) != array_elements_ammout){
        return false;
    }

    return true;
}

bool should_return_error_while_expand() {
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    a->capacity = CC_MAX_ELEMENTS;
    a->size = CC_MAX_ELEMENTS;

    bool res = cc_array_add(a, (void*) 1);

    if(res == CC_OK){
        return false;
    }

    return true;

}

test_t TESTS[] = {
    &should_not_expand,
    &should_expand_when_size_is_equal,
    &should_expand_when_size_is_bigger,
    &should_return_error_while_expand,
    NULL
};