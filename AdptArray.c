#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

// INITIAL CAPACITY STARTED WITH 10
#define INITIAL_CAPACITY 10

/**
 * The AdptArray_ struct represents a dynamic array with adaptive capacity.
 * It stores the array data, its size, capacity, and function pointers for copying, deleting, and printing elements.
 */

struct AdptArray_ {
    PElement *data;
    int size;
    int capacity;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
};

/**
 * CreateAdptArray Creates a new dynamic array with initial capacity of 10 and specified copy, delete,
 * and print functions.
 * @param copy_func The function used to copy elements added to the array.
 * @param del_func The function used to delete elements removed from the array.
 * @param print_func The function used to print the elements in the array.
 * @return A pointer to the newly created dynamic array, or NULL if memory allocation fails.
 */

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func) {
    PAdptArray arr = (PAdptArray) malloc(sizeof(struct AdptArray_));
    if (arr == NULL) {
        return NULL;
    }
    arr->data = (PElement *) malloc(sizeof(PElement) * INITIAL_CAPACITY);
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->copy_func = copy_func;
    arr->del_func = del_func;
    arr->print_func = print_func;
    return arr;
}

/**
 * DeleteAdptArray Deletes a dynamic array and its elements using the specified delete function.
 * @param arr A pointer to the dynamic array to delete.
 * @return void.
 */

void DeleteAdptArray(PAdptArray arr) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] != NULL) {
            arr->del_func(arr->data[i]);
        }
    }
    free(arr->data);
    free(arr);
}

/**
 * SetAdptArrayAt Sets the element at the specified index in a dynamic array.
 * If the index is greater than or equal to the current capacity of the array, the array's capacity is doubled.
 * The dynamic array's copy function is used to create a copy of the element and store it in the array.
 * If the copy function fails, the function returns FAIL and does not modify the array.
 * @param arr A pointer to the dynamic array to modify.
 * @param index The index of the element to set.
 * @param elem A pointer to the element to store in the array.
 * @return SUCCESS if the element was successfully set, or FAIL if there was an error.
 */

Result SetAdptArrayAt(PAdptArray arr, int index, PElement elem) {
    if (arr == NULL || index < 0) {
        return FAIL;
    }
    if (index >= arr->capacity) {
        int new_capacity = (index + 1) * 2;
        PElement *new_data = (PElement *) malloc(sizeof(PElement) * new_capacity);
        if (new_data == NULL) {
            return FAIL;
        }
        memcpy(new_data, arr->data, sizeof(PElement) * arr->size);
        free(arr->data);
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    if (arr->data[index] != NULL) {
        arr->del_func(arr->data[index]);
    }
    arr->data[index] = arr->copy_func(elem);
    if (arr->data[index] == NULL) {
        return FAIL;
    }
    if (index >= arr->size) {
        arr->size = index + 1;
    }
    return SUCCESS;
}

/**
 * GetAdptArrayAt retrieves the element at the specified index of the adaptive array.
 * If the index is out of bounds or the element at the index is NULL,
 * it returns NULL. Otherwise, it returns a copy of the element using the copy_func specified in CreateAdptArray().
 * @param arr A pointer to the adaptive array.
 * @param index The index of the element to retrieve.
 * @return
 * if the specified index is out of bounds or the element at the index is NULL, the function returns NULL.
 * Otherwise, it returns a copy of the element at the specified index.
 */

PElement GetAdptArrayAt(PAdptArray arr, int index) {
    if (arr == NULL || index < 0 || index >= arr->size || arr->data[index] == NULL) {
        return NULL;
    }
    return arr->copy_func(arr->data[index]);
}

/**
 * GetAdptArraySize retrieves the current size of the adaptive array.
 * @param arr A pointer to the adaptive array.
 * @return The current size of the adaptive array, or -1 if the array pointer is NULL.
 * The size of the adaptive array is defined as the number of elements it currently holds.
*/

int GetAdptArraySize(PAdptArray arr) {
    if (arr == NULL) {
        return -1;
    }
    return arr->size;
}

/**
 * PrintDB prints the elements in the adaptive array using the print_func specified in CreateAdptArray().
 * If the array is NULL or the print_func is NULL, it returns without printing anything.
 * @param arr A pointer to the adaptive array to print.
 * @return void
 */

void PrintDB(PAdptArray arr) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] != NULL) {
            arr->print_func(arr->data[i]);
        }
    }
}
