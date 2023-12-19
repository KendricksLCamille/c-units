//
// Created by kendricks on 12/10/23.
//

/**
 * @file units_pointer_comparison.h
 *
 * @brief This file provides a structure definition used for maintaining a count of unique pointer occurrences.
 */

#ifndef CSI_POINTER_COMPARISON_H
#define CSI_POINTER_COMPARISON_H

#include <stddef.h>

/**
 * @brief Struct used for maintaining a count of unique pointer occurrences.
 *
 * @var const void* const data
 * Pointer to the data.
 *
 * @var const size_t number_of_occurrences
 * The number of occurrences for the particular data pointer.
 */
typedef struct pointer_counter
{
    const void* const data; /**< Data pointer */
    const size_t number_of_occurences; /**< The number of occurrences of the data pointer */
} pointer_counter_t;

/**
 * @brief This function counts the occurrence of each unique pointer in the given list of pointers.
 *
 * @param[in] list An array of pointers.
 * @param[in] size_of_list The number of elements in the list.
 * @param[out] output_size A pointer to a size_t variable where the size of the returned array will be stored.
 *
 * @return A pointer to an array of pointer_counter_t objects. Each object contains a pointer from the input list and 
 * the number of occurrences of this pointer in the list. The size of this array is stored in the output_size variable.
 * 
 * @note The returned pointer should be freed when no longer needed to avoid memory leaks.
 *
 * @note It is also assumed that the input pointer list does not contain any null pointers.
 *
 * @note If memory allocation fails, NULL is returned, the output_size variable is set to 0 and errno set to ENOMEM.
 */
pointer_counter_t* count_occurences_of_pointer(void** list, const size_t size_of_list, size_t* const output_size);

#endif //CSI_POINTER_COMPARISON_H
