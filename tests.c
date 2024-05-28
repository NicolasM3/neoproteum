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

// -- When expand_capacity returns error
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

// Test adding elements to the array at specific index
// -- When add in the last index
bool should_add_at_last_index() {
    CC_Array* a;
    int tail_index = 2;

    ASSERT_CC_OK(cc_array_new(&a));

    cc_array_add(a, (void*) 1);
    cc_array_add(a, (void*) 2);
    cc_array_add_at(a, (void*) 100, tail_index);

    void* element;
    cc_array_get_at(a, 2, &element);

    for (size_t i = 0; i < cc_array_size(a); i++) {
        cc_array_get_at(a, i, &element);
        if (i == tail_index) {
            return element == (void*) 100;
        }
    }

    return true;
}

// -- When index is bigger then size
bool should_return_error_when_index_is_bigger() {
    CC_Array* a;
    int tail_index = 100;

    ASSERT_CC_OK(cc_array_new(&a));

    void* element;
    bool res = cc_array_get_at(a, tail_index, &element);

    if(res == CC_OK){
        return false;
    }
    
    return true;
}

// -- When index is equal than size but index is 0 too
bool should_return_error_when_index_is_bigger_and_index_is_0() {
    CC_Array* a;
    int tail_index = 0;

    ASSERT_CC_OK(cc_array_new(&a));

    void* element;
    bool res = cc_array_get_at(a, tail_index, &element);

    if(res != CC_OK){
        return false;
    }
    
    return true;
}

// -- When index array size is bigger or equal then capacity
bool should_expand_GROUPADDAT(){
    CC_Array* a;
    int tail_index = 0;

    ASSERT_CC_OK(cc_array_new(&a));

    a->capacity = CC_MAX_ELEMENTS;
    a->size = 10;

    bool res = cc_array_add_at(a, (void*) 1, tail_index);

    if(res != CC_OK){
        return false;
    }

    return true;
}


// -- When index array size is bigger or equal then capacity but can't expand
bool should_not_expand_GROUPADDAT() {
    CC_Array* a;
    int tail_index = 0;

    ASSERT_CC_OK(cc_array_new(&a));

    a->capacity = CC_MAX_ELEMENTS;
    a->size = CC_MAX_ELEMENTS;

    bool res = cc_array_add_at(a, (void*) 1, tail_index);

    if(res == CC_OK){
        return false;
    }

    return true;
}


test_t TESTS[] = {
    // arrya_add
    &should_not_expand,
    &should_expand_when_size_is_equal,
    &should_expand_when_size_is_bigger,
    &should_return_error_while_expand,
    // array_add_at
    &should_add_at_last_index,
    &should_return_error_when_index_is_bigger,
    &should_return_error_when_index_is_bigger_and_index_is_0,
    &should_expand_GROUPADDAT,
    &should_not_expand_GROUPADDAT,
    NULL
};