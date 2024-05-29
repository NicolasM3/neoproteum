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

    cc_array_add(a, (void*) 1);

    if(cc_array_capacity(a) != DEFAULT_CAPACITY){
        return false;
    }
    if(cc_array_size(a) == array_elements_ammout){
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
    
    cc_array_add(a, (void*) 1);

    if(cc_array_capacity(a) == DEFAULT_CAPACITY){
        return false;
    }
    if(cc_array_size(a) == array_elements_ammout){
        return false;
    }

    return true;
}

// -- When array is equal to DEFAULT_CAPACITY
bool should_expand_when_size_is_equal() {
    array_elements_ammout = DEFAULT_CAPACITY;
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));
    a->size = array_elements_ammout;

    cc_array_add(a, (void*) 1);

    if(cc_array_capacity(a) == DEFAULT_CAPACITY){
        return false;
    }
    if(cc_array_size(a) == array_elements_ammout){
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

    int res = cc_array_add(a, (void*) 1);
   
    if(res != CC_ERR_MAX_CAPACITY){
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

    if(a->size != 3){
        return false;
    }

    void* element;
    for (size_t i = 0; i < cc_array_size(a); i++) {
        cc_array_get_at(a, i, &element);
        if (i == tail_index) {
            return element == (void*) 100;
        }
    }

    return true;
}


// -- When index is bigger then size - 1
bool should_return_error_when_index_is_bigger() {
    CC_Array* a;
    int index = 100;

    ASSERT_CC_OK(cc_array_new(&a));

    void* element;
    bool res = cc_array_add_at(a, &element, index);

    if(res == CC_OK){
        return false;
    }
    
    return true;
}


// -- When size is equal to 0 but index is not 0
bool should_return_error_when_index_is_bigger_and_index_is_0() {
    CC_Array* a;
    int tail_index = 2;

    ASSERT_CC_OK(cc_array_new(&a));

    void* element;
    int res = cc_array_add_at(a, &element, tail_index);

    if(res != CC_ERR_OUT_OF_RANGE){
        return false;
    }
    
    return true;
}

// -- When index array size is bigger or equal then capacity
bool should_expand_GROUPADDAT(){
    CC_Array* a;
    int tail_index = 0;
    int array_size = 10;

    ASSERT_CC_OK(cc_array_new(&a));

    a->capacity = CC_MAX_ELEMENTS;
    a->size = array_size;

    int res = cc_array_add_at(a, (void*) 1, tail_index);

    if(res != CC_ERR_OUT_OF_RANGE){
        return false;
    }

    if(a->size != array_size+1){
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

    int res = cc_array_add_at(a, (void*) 1, tail_index);

    if(res != CC_ERR_MAX_CAPACITY){
        return false;
    }

    return true;
}

// -- General cases that should return ok
bool cc_array_add_at_general_tests() {
    CC_Array* a;
    int tail_index = 0;

    ASSERT_CC_OK(cc_array_new(&a));

    bool res = cc_array_add_at(a, (void*) 100, 0);     // Should add at first index
    ASSERT_CC_OK(res);
    if(res != CC_OK){return false;}

    res = cc_array_add_at(a, (void*) 200, 0);          // Should add at second index
    ASSERT_CC_OK(res);
    if(res != CC_OK){return false;}

    res = cc_array_add_at(a, (void*) 200, 2);          // Should add at second index
    ASSERT_CC_OK(res);
    if(res != CC_OK){return false;}

    return true;
}

// Test swapping elements in the array
// -- When index is bigger or equal then size 
bool should_return_a_error_GROUPARRAYSWAPAT() {
    CC_Array* a;
    int indexBigger = 100;
    int index2 = 0;
    int array_size = 10;

    a->size = array_size;

    ASSERT_CC_OK(cc_array_new(&a));

    // One index is bigger then size
    int res = cc_array_swap_at(a, indexBigger, index2);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    res = cc_array_swap_at(a, index2, indexBigger);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    // index is equal to size
    res = cc_array_swap_at(a, array_size, indexBigger);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    res = cc_array_swap_at(a, indexBigger, array_size);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    // Both index are bigger the size
    res = cc_array_swap_at(a, indexBigger, indexBigger);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    // Both index are equal to size
    res = cc_array_swap_at(a, array_size, array_size);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}

    return true;
}

// Test filtering elements in the array
// -- When size is not equal 0
bool should_return_CC_OK_GROUPARRAYFILTERMUT() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    // size is bigger than 0
    a->size = 10;
    int res = cc_array_filter_mut(a, (bool (*)(const void *)) 1);
    if(res == CC_ERR_OUT_OF_RANGE){ return false; }

    // size i lower than 0
    a->size = -1;
    res = cc_array_filter_mut(a, (bool (*)(const void *)) 1);
    if(res == CC_ERR_OUT_OF_RANGE){ return false; }

    // size is equal to 0
    a->size = 0;
    res = cc_array_filter_mut(a, (bool (*)(const void *)) 1);
    if(res == CC_ERR_OUT_OF_RANGE){ return false; }

    return true;
} 

// Test reducing elements in the array
// -- When size is 1 
bool should_return_the_value_of_first_element_GROUPARRAYREDUCE() {
    void *first_element = (void*) 10;
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));
    cc_array_add(a, (void*) first_element);

    void *result = 0;
    cc_array_reduce(a, (void (*)(void *, void *, void *)) 1, &result);
    if(result != first_element){return false;}

    return true;
}

// When size is not 1 
bool should_not_return_the_value_of_first_element_GROUPARRAYREDUCE() {
    void *first_element = (void*) 10;
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));
    cc_array_add(a, (void*) first_element);

    // size is bigger than 1
    a->size = 10;
    void *result = 0;
    cc_array_reduce(a, (void (*)(void *, void *, void *)) 1, &result);
    if(result == first_element){return false;}

    // size is lower than 1
    a->size = -1;
    result = 0;
    cc_array_reduce(a, (void (*)(void *, void *, void *)) 1, &result);
    if(result == first_element){return false;}

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
    &cc_array_add_at_general_tests,
    // cc_array_swap_at
    &should_return_a_error_GROUPARRAYSWAPAT,
    // cc_array_filter_mut
    &should_return_CC_OK_GROUPARRAYFILTERMUT,
    // cc_array_reduce
    NULL
};