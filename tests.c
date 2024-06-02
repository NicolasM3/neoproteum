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

    ASSERT_CC_OK(cc_array_new(&a));

    cc_array_add(a, (void*) 1);

    void* element;
    int res = cc_array_add_at(a, &element, 2);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}

    res = cc_array_add_at(a, &element, 0);
    if(res != CC_OK){return false;}

    cc_array_add(a, (void*) 2);
    res = cc_array_add_at(a, &element, 1);
    if(res != CC_OK){return false;}
    
    return true;
}

bool should_throw_error_when_size_equals_0_and_index_is_not_0() {
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    void* element;
    int res = cc_array_add_at(a, &element, 2);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}

    res = cc_array_add_at(a, &element, 0);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}

    /* res = cc_array_add_at(a, &element, 1);
    if(res != CC_OK){return false;} */

    return true;
}

// -- When index array size is bigger or equal then capacity
bool should_expand_GROUPADDAT(){
    CC_Array* a;
    int tail_index = 0;

    ASSERT_CC_OK(cc_array_new(&a));
    cc_array_add(a, (void*) 1);
    a->capacity = 1;
    int res = cc_array_add_at(a, (void*) 3, tail_index);
    if(a->capacity == 1){return false;}

    ASSERT_CC_OK(cc_array_new(&a));
    cc_array_add(a, (void*) 1);
    cc_array_add(a, (void*) 2);
    a->capacity = 1;
    res = cc_array_add_at(a, (void*) 3, tail_index);
    if(a->capacity == 1){return false;}

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

    ASSERT_CC_OK(cc_array_new(&a));

    a->size = array_size;

    // One index is bigger then size
    int res = cc_array_swap_at(a, indexBigger, index2);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    res = cc_array_swap_at(a, index2, indexBigger);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    // index is equal to size
    res = cc_array_swap_at(a, array_size, index2);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    res = cc_array_swap_at(a, index2, array_size);
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
    /* ASSERT_CC_OK(cc_array_add(a, (void*) 1));
    ASSERT_CC_OK(cc_array_add(a, (void*) 2));
    int res = cc_array_filter_mut(a, is_positive);
    if(res == CC_ERR_OUT_OF_RANGE){ return false; } */

    // size is equal to 0
    ASSERT_CC_OK(cc_array_new(&a));
    a->size = 0;
    int res = cc_array_filter_mut(a, (bool (*)(const void *)) 1);
    if(res != CC_ERR_OUT_OF_RANGE){ return false; }

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

bool should_return_ok_when_array_is_not_empty() {
    CC_Array* a;
    void* element;
    int value = 22;

    ASSERT_CC_OK(cc_array_new(&a));
    ASSERT_CC_OK(cc_array_add(a, &value));

    int res = cc_array_get_last(a, &element);

    if (res != CC_OK || element != &value) {
        return false;
    }

    return true;
}

bool should_return_last_element_when_array_has_multiple_elements() {
    CC_Array* a;
    int values[] = {1, 2, 3};
    void* element;

    ASSERT_CC_OK(cc_array_new(&a));
    for (int i = 0; i < 3; i++) {
        ASSERT_CC_OK(cc_array_add(a, &values[i]));
    }

    int res = cc_array_get_last(a, &element);

    if (res != CC_OK || element != &values[2]) {
        return false;
    }

    return true;
}

bool should_replace_elements_when_iter_index_valid() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    int val1 = 1, val2 = 2;
    void *e1 = (void *)3, *e2 = (void *)4;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    // Adiciona elementos para configurar os tamanhos dos arrays
    ASSERT_CC_OK(cc_array_add(ar1, &val1));
    ASSERT_CC_OK(cc_array_add(ar2, &val2));

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 1; // iter->index - 1 será 0, que é um índice válido

    int res = cc_array_zip_iter_replace(&iter, e1, e2, &out1, &out2);

    if (res != CC_OK || out1 != &val1 || out2 != &val2) {
        return false;
    }

    return true;
}

bool should_replace_elements_at_specific_index() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    int vals1[] = {1, 2, 3};
    int vals2[] = {4, 5, 6};
    void *e1 = (void *)7, *e2 = (void *)8;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    // Adiciona elementos em ar1 e ar2
    for (int i = 0; i < 3; ++i) {
        ASSERT_CC_OK(cc_array_add(ar1, &vals1[i]));
        ASSERT_CC_OK(cc_array_add(ar2, &vals2[i]));
    }

    iter.ar1 = ar1;
    iter.ar2 = ar2;

    // Verifica substituições em índices 1, 2 e 3
    for (int i = 1; i <= 3; ++i) {
        iter.index = i;
        int res = cc_array_zip_iter_replace(&iter, e1, e2, &out1, &out2);

        if (res != CC_OK || out1 != &vals1[i - 1] || out2 != &vals2[i - 1] || 
            cc_array_get_at(ar1, i - 1, &out1) != CC_OK || out1 != e1 || 
            cc_array_get_at(ar2, i - 1, &out2) != CC_OK || out2 != e2) {
            return false;
        }
    }

    return true;
}

bool should_replace_elementes_when_iter_index_minus_one_exceeds_just_one_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e1));

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 2; 

    return cc_array_zip_iter_replace(&iter, e1, e2, &out1, &out2) == CC_OK;
}

bool should_replace_elementes_when_iter_index_minus_one_greater_ar1_size_and_less_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 3; 

    return cc_array_zip_iter_replace(&iter, e1, e2, &out1, &out2) == CC_OK;
}

bool should_replace_elementes_when_iter_index_minus_one_less_ar1_size_and_greater_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 3; 

    return cc_array_zip_iter_replace(&iter, e1, e2, &out1, &out2) == CC_OK;
}

bool should_replace_elementes_when_iter_index_minus_one_equals_ar1_size_and_less_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 2; 

    return cc_array_zip_iter_replace(&iter, e1, e2, &out1, &out2) == CC_OK;
}

bool should_remove_elements_when_iter_index_valid() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    int val1 = 1, val2 = 2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    // Adiciona elementos para configurar os tamanhos dos arrays
    ASSERT_CC_OK(cc_array_add(ar1, &val1));
    ASSERT_CC_OK(cc_array_add(ar2, &val2));

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 1; // iter->index - 1 será 0, que é um índice válido

    int res = cc_array_zip_iter_remove(&iter, &out1, &out2);

    if (res != CC_OK || out1 != &val1 || out2 != &val2) {
        return false;
    }

    return true;
}

bool should_remove_elements_at_specific_index() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    int vals1[] = {1, 2, 3};
    int vals2[] = {4, 5, 6};
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    // Adiciona elementos em ar1 e ar2
    for (int i = 0; i < 3; ++i) {
        ASSERT_CC_OK(cc_array_add(ar1, &vals1[i]));
        ASSERT_CC_OK(cc_array_add(ar2, &vals2[i]));
    }

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.last_removed = false;

    // Tenta remover o elemento na posição 1
    iter.index = 1;
    int res = cc_array_zip_iter_remove(&iter, &out1, &out2);

    // Verifica se a remoção foi bem-sucedida e se os elementos corretos foram removidos
    if (res != CC_OK ||
        *((int *)out1) != 1 || *((int *)out2) != 4 ||
        ar1->size != 2 || ar2->size != 2 ||
        cc_array_get_at(ar1, 0, &out1) != CC_OK || *((int *)out1) != 2 ||
        cc_array_get_at(ar2, 0, &out2) != CC_OK || *((int *)out2) != 5) {
        return false;
    }

    // Tenta remover o mesmo elemento novamente, deve falhar
    res = cc_array_zip_iter_remove(&iter, &out1, &out2);
    if (res != CC_ERR_VALUE_NOT_FOUND) {
        return false;
    }

    // Tenta remover um elemento com índice fora do intervalo
    iter.index = 5;
    iter.last_removed = false;
    res = cc_array_zip_iter_remove(&iter, &out1, &out2);
    if (res != CC_ERR_OUT_OF_RANGE) {
        return false;
    }

    // Verifica se o mutante está ativo: tenta remover com índice % 1 (sempre 0)
    iter.index = 1;
    iter.last_removed = false;
    cc_array_zip_iter_remove(&iter, &out1, &out2);
    if (*((int *)out2) == 4) {
        return false;
    }

    return true;
}


bool should_remove_elementes_when_iter_index_minus_one_exceeds_just_one_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e1));

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 2;
    iter.last_removed = false;

    return cc_array_zip_iter_remove(&iter, &out1, &out2) == CC_OK;
}

bool should_remove_elementes_when_iter_index_minus_one_greater_ar1_size_and_less_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 3; 

    return cc_array_zip_iter_remove(&iter, &out1, &out2) == CC_OK;
}

bool should_remove_elementes_when_iter_index_minus_one_equals_ar1_size_and_less_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 2; 

    return cc_array_zip_iter_remove(&iter, &out1, &out2) == CC_OK;
}

bool should_remove_elementes_when_iter_index_minus_one_less_ar1_size_and_greater_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 3; 

    return cc_array_zip_iter_remove(&iter, &out1, &out2) == CC_OK;
}

// cc_array_zip_iter_add
// -- When size and capacity from arrays are not equal
bool should_do_not_throw_CC_ERR_ALLOC(){
    CC_ArrayZipIter* iter;
    CC_Array* a;
    CC_Array* b;

    // size is smaller than capacity and capacity is the maxx
    cc_array_new(&a);
    cc_array_new(&b);
    a->size = 0;
    a->capacity = CC_MAX_ELEMENTS;
    cc_array_zip_iter_init(iter, a, b);
    int res = cc_array_zip_iter_add(iter, (void*) 2, (void*) 1);
    if(res != CC_OK){return false;} 

    cc_array_new(&a);
    cc_array_new(&b);
    a->size = 0;
    a->capacity = CC_MAX_ELEMENTS;
    cc_array_zip_iter_init(iter, b, a);
    res = cc_array_zip_iter_add(iter, (void*) 2, (void*) 1);
    if(res != CC_OK){return false;} 

    return true;
}

// -- when size and capacity are equal but can expand
bool should_return_ok_GROUPZIPITERADD(){
    CC_ArrayZipIter* iter;
    CC_Array* a;
    CC_Array* b;

    cc_array_new(&a);
    cc_array_new(&b);

    // size is equal than capacity
    a->size = DEFAULT_CAPACITY;
    a->capacity = DEFAULT_CAPACITY;
    cc_array_zip_iter_init(iter, a, b);
    int res = cc_array_zip_iter_add(iter, (void*) 2, (void*) 1);
    if(res == CC_ERR_ALLOC){return false;}

    cc_array_new(&a);
    cc_array_new(&b);
    a->size = DEFAULT_CAPACITY;
    a->capacity = DEFAULT_CAPACITY;
    cc_array_zip_iter_init(iter, b, a);
    res = cc_array_zip_iter_add(iter, (void*) 2, (void*) 1);
    if(res == CC_ERR_ALLOC){return false;}

    return true;
}

// -- when size and capacity are equal but cant expand
bool should_return_error_GROUPZIPITERADD(){
    CC_ArrayZipIter* iter;
    CC_Array* a;
    CC_Array* b;

    // size is equal than capacity
    cc_array_new(&a);
    cc_array_new(&b);
    a->size = CC_MAX_ELEMENTS;
    a->capacity = CC_MAX_ELEMENTS;
    cc_array_zip_iter_init(iter, a, b);
    int res = cc_array_zip_iter_add(iter, (void*) 2, (void*) 1);
    if(res != CC_ERR_ALLOC){return false;}

    cc_array_new(&a);
    cc_array_new(&b);
    a->size = CC_MAX_ELEMENTS;
    a->capacity = CC_MAX_ELEMENTS;
    cc_array_zip_iter_init(iter, a, b);
    res = cc_array_zip_iter_add(iter, (void*) 2, (void*) 1);
    if(res != CC_ERR_ALLOC){return false;}

    return true;
}

bool should_return_index_plus_1() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter *iter;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    cc_array_zip_iter_init(iter, ar1, ar2);
    iter->index = 2;

    return cc_array_zip_iter_index(iter) == 3;
}

bool should_return_index_times_1() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter *iter;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    cc_array_zip_iter_init(iter, ar1, ar2);
    iter->index = 1;

    return cc_array_zip_iter_index(iter) == 1;
}

bool should_return_index_module_1() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter *iter;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    cc_array_zip_iter_init(iter, ar1, ar2);
    iter->index = 6;

    return cc_array_zip_iter_index(iter) == 0;
}

// cc_array_remove
// -- When element does not exist
bool should_return_error_GROUPARRAYREMOVE(){
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    cc_array_add(a, (void*) 1);
    cc_array_add(a, (void*) 2);

    void* element;
    int res = cc_array_remove(a, (void*) 100, element);
    if (res != CC_ERR_OUT_OF_RANGE) {return false;}

    return true;
}

// -- When element exists and should not be the last
bool should_return_ok_and_move_array_GROUPARRAYREMOVE(){
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    cc_array_add(a, (void*) 1);
    cc_array_add(a, (void*) 2);

    void* element;
    int res = cc_array_remove(a, (void*) 1, element);
    if (res != CC_OK) {return false;}
    if (a->size != 1) {return false;}
    if (cc_array_index_of(a, (void*) 1, element) != CC_ERR_OUT_OF_RANGE){return false;}
    if (cc_array_index_of(a, (void*) 2, element) != CC_OK){return false;}

    return true;
}

// --When element is the last
bool should_return_just_reduce_array_size() {
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    cc_array_add(a, (void*) 1);
    cc_array_add(a, (void*) 2);

    void* element;
    int res = cc_array_remove(a, (void*) 2, element);
    if (res != CC_OK) {return false;}
    if (a->size != 1) {return false;}
    if (cc_array_index_of(a, (void*) 1, element) != CC_OK){return false;}
    if (cc_array_index_of(a, (void*) 2, element) != CC_ERR_VALUE_NOT_FOUND){return false;}

    return true;
}

// cc_array_reverse
// -- When array is not empty
bool should_reverse() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    cc_array_add(a, (void*) 1);
    cc_array_add(a, (void*) 2);

    cc_array_reverse(a);
    if(a->buffer[0] != (void*) 2 || a->buffer[1] != (void*) 1){
        return false;
    }

    return true;
}

// cc_array_filter
// -- When array is empty
bool should_return_a_erro_GROUPFILTER() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));
    CC_Array* element;

    // size is 0
    a->size = 0;
    int res = cc_array_filter(a, (bool (*)(const void *)) 1, &element);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}

    return true;
}

// -- When array is not empty
bool should_return_a_filtered_array_GROUPFILTER(){
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));
    CC_Array** element;

    ASSERT_CC_OK(cc_array_add(a, (void*) 1));
    ASSERT_CC_OK(cc_array_add(a, (void*) 2));
    ASSERT_CC_OK(cc_array_add(a, (void*) 3));
    int res = cc_array_filter(a, (bool (*)(const void *)) 1, element);
    if(res == CC_ERR_OUT_OF_RANGE){return false;}
    
    //if(element->size != 2){return false;}

    return true;
}

// cc_array_remove_at
// -- When index is bigger or equal to siz
bool should_return_a_error_GROUPARRAYREMOVEAT() {
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    ASSERT_CC_OK(cc_array_add(a, (void*) 1))

    CC_Array* out;
    // One index is bigger then size
    int res = cc_array_remove_at(a, 100, out);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}
    // index is equal to size
    res = cc_array_remove_at(a, a->size, out);
    if(res != CC_ERR_OUT_OF_RANGE){return false;}

    ASSERT_CC_OK(cc_array_add(a, (void*) 2))
    // index is smaller than size
    res = cc_array_remove_at(a, 1, out);
    if(res != CC_OK){return false;}

    return true;
}

// -- When element exists and should not be the last
bool should_return_ok_and_move_array_GROUPARRAYREMOVEAT(){
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    cc_array_add(a, (void*) 1);
    cc_array_add(a, (void*) 2);

    CC_Array* element;
    int res = cc_array_remove_at(a, 0, element);
    if (res != CC_OK) {return false;}
    if (a->size != 1) {return false;}
    if (cc_array_index_of(a, (void*) 1, element) != CC_ERR_OUT_OF_RANGE){return false;}
    if (cc_array_index_of(a, (void*) 2, element) != CC_OK){return false;}

    return true;
}

// --When element is the last
bool should_return_just_reduce_array_size_GROUPARRAYREMOVEAT() {
    CC_Array* a;

    ASSERT_CC_OK(cc_array_new(&a));

    cc_array_add(a, (void*) 1);
    cc_array_add(a, (void*) 2);

    CC_Array* element;
    int res = cc_array_remove_at(a,  1, element);
    if (res != CC_OK) {return false;}
    if (a->size != 1) {return false;}
    if (cc_array_index_of(a, (void*) 1, element) != CC_OK){return false;}
    if (cc_array_index_of(a, (void*) 2, element) != CC_ERR_VALUE_NOT_FOUND){return false;}

    return true;
}

// cc_array_zip_iter_next
bool should_go_to_next_index_when_iter_index_valid() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    int val1 = 1, val2 = 2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    // Adiciona elementos para configurar os tamanhos dos arrays
    ASSERT_CC_OK(cc_array_add(ar1, &val1));
    ASSERT_CC_OK(cc_array_add(ar2, &val2));

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 0; // iter->index será 0, que é um índice válido

    int res = cc_array_zip_iter_next(&iter, &out1, &out2);

    if (res != CC_OK || out1 != &val1 || out2 != &val2  || iter.index != 1) {
        return false;
    }

    return true;
}

bool should_go_to_next_index_when_iter_index_less_ar1_and_equals_ar2() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e1));

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 1; 

    return cc_array_zip_iter_next(&iter, &out1, &out2) == CC_OK;
}

bool should_go_to_next_index_when_iter_index_greater_ar1_size_and_less_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 2; 

    return cc_array_zip_iter_next(&iter, &out1, &out2) == CC_OK;
}

bool should_go_to_next_index_when_iter_index_less_ar1_size_and_greater_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar1, e2));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 2; 

    return cc_array_zip_iter_next(&iter, &out1, &out2) == CC_OK;
}

bool should_go_to_next_index_when_iter_index_equals_ar1_size_and_less_ar2_size() {
    CC_Array *ar1, *ar2;
    CC_ArrayZipIter iter;
    void *e1 = (void *)1, *e2 = (void *)2;
    void *out1, *out2;

    ASSERT_CC_OK(cc_array_new(&ar1));
    ASSERT_CC_OK(cc_array_new(&ar2));

    ASSERT_CC_OK(cc_array_add(ar1, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e1));
    ASSERT_CC_OK(cc_array_add(ar2, e2));
    

    iter.ar1 = ar1;
    iter.ar2 = ar2;
    iter.index = 1; 

    return cc_array_zip_iter_next(&iter, &out1, &out2) == CC_OK;
}

// cc_array_trim_capacity
// -- When array is not equal to capacity
bool should_return_trim() {
    CC_Array* a;
    ASSERT_CC_OK(cc_array_new(&a));

    a->capacity = 10;

    ASSERT_CC_OK(cc_array_add(a, (void*) 1));
    ASSERT_CC_OK(cc_array_add(a, (void*) 2));

    int res = cc_array_trim_capacity(a);
    if(a->capacity != a->size){return false;}
    if(res == CC_ERR_ALLOC){return false;}

    cc_array_trim_capacity(a);
    if(a->capacity != a->size){return false;}
    if(res == CC_ERR_ALLOC){return false;}

    return true;
}

// cc_array_iter_next
// -- When iter index is bigget than array size
bool should_throw_iter_end_error() {
    CC_Array* a;
    CC_ArrayIter iter;

    ASSERT_CC_OK(cc_array_add(a, (void*) 1));

    ASSERT_CC_OK(cc_array_new(&a));
    cc_array_iter_init(&iter, a);

    void* element;
    int res = cc_array_iter_next(&iter, &element);
    if(res != CC_OK){return false;}
    if(element != (void*) 1){return false;}
    if(iter.index != 1){return false;}

    res = cc_array_iter_next(&iter, &element);
    if(res != CC_ITER_END){return false;}

    iter.index = 10;
    res = cc_array_iter_next(&iter, &element);
    if(res != CC_ITER_END){return false;}

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
     //&should_throw_error_when_size_equals_0_and_index_is_not_0,
     &cc_array_add_at_general_tests,
    // cc_array_filter_mut
     &should_return_CC_OK_GROUPARRAYFILTERMUT,
    // cc_array_reduce

    //cc_array_get_last
    &should_return_ok_when_array_is_not_empty,
    &should_return_last_element_when_array_has_multiple_elements,

    //cc_array_zip_iter_replace
    &should_replace_elements_when_iter_index_valid,
    &should_replace_elements_at_specific_index,
    &should_replace_elementes_when_iter_index_minus_one_exceeds_just_one_size,
    &should_replace_elementes_when_iter_index_minus_one_greater_ar1_size_and_less_ar2_size,
    &should_replace_elementes_when_iter_index_minus_one_equals_ar1_size_and_less_ar2_size,
    &should_replace_elementes_when_iter_index_minus_one_less_ar1_size_and_greater_ar2_size,

    //cc_array_zip_iter_remove
    &should_remove_elements_when_iter_index_valid,
    // &should_remove_elements_at_specific_index,
    &should_remove_elementes_when_iter_index_minus_one_exceeds_just_one_size,
    &should_remove_elementes_when_iter_index_minus_one_greater_ar1_size_and_less_ar2_size,
    &should_remove_elementes_when_iter_index_minus_one_equals_ar1_size_and_less_ar2_size,
    &should_remove_elementes_when_iter_index_minus_one_less_ar1_size_and_greater_ar2_size,

    //cc_array_zip_iter_add
    &should_do_not_throw_CC_ERR_ALLOC,
    &should_return_ok_GROUPZIPITERADD,
    &should_return_error_GROUPZIPITERADD,

    //cc_array_zip_iter_index
    &should_return_index_plus_1,
    &should_return_index_times_1,
    &should_return_index_module_1,

    // cc_array_remove
    &should_return_error_GROUPARRAYREMOVE,
    &should_return_ok_and_move_array_GROUPARRAYREMOVE,
    //&should_return_just_reduce_array_size,

    // cc_array_reverse
    &should_reverse,

    // cc_array_filter
    &should_return_a_erro_GROUPFILTER,
    //&should_return_a_filtered_array_GROUPFILTER,

    // cc_array_zip_iter_next
    &should_go_to_next_index_when_iter_index_valid,
    &should_go_to_next_index_when_iter_index_less_ar1_and_equals_ar2,
    &should_go_to_next_index_when_iter_index_greater_ar1_size_and_less_ar2_size,
    &should_go_to_next_index_when_iter_index_less_ar1_size_and_greater_ar2_size,
    &should_go_to_next_index_when_iter_index_equals_ar1_size_and_less_ar2_size,


    // cc_array_remove_at
    // &should_return_a_error_GROUPARRAYREMOVEAT,
    // &should_return_ok_and_move_array_GROUPARRAYREMOVEAT,
    // &should_return_just_reduce_array_size_GROUPARRAYREMOVEAT,

    // cc_array_trim_capacity
    &should_return_trim,

    // cc_array_swap_at
    &should_return_a_error_GROUPARRAYSWAPAT,
    NULL
};
