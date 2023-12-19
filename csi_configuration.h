//
// Created by kendricks on 12/17/23.
//

#ifndef CSI_H
#define CSI_H

/*!
* @brief  The CSI_CPC macro is a preprocessor macro that defines a constant pointer to a constant value of a specific type.
* @param TYPE The type of the pointer to the constant value.
* 
* @code
* const int arr[] = {1, 2, 3};
* const int* const p = CSI_CPC(int)(arr);
* @endcode
*/
#define CSI_CPC(TYPE) const TYPE* const


#define CSI_MAGINITUDE_TYPE long double
#define CSI_MAGINITUDE_TYPE_ZERO 0.0L
#define CSI_MAGINITUDE_TYPE_ONE 1.0L
#define CSI_MAGINITUDE_TYPE_IS_ZERO(A) ((A) == 0)
#define CSI_MAGINITUDE_TYPE_ADD(A,B) ((A) + (B))
#define CSI_MAGINITUDE_TYPE_SUBTRACT(A,B) ((A) - (B))
#define CSI_MAGINITUDE_TYPE_MULTIPLY(A,B) ((A) * (B))
#define CSI_MAGINITUDE_TYPE_MODULO(A,B) ((A) % (B))
#define CSI_MAGINITUDE_TYPE_DIVIDE(A,B) ((A) / (B))
#define CSI_MAGNITUDE_TYPE_TO_STRING(STR,A) sprintf(STR,"%Lf", (A))
#define CSI_TO_LARGEST_UNSIGNED_INTEGER(A) (size_t)(A)
#define CSI_TO_LARGEST_SIGNED_INTEGER(A) ((ptrdiff_t)(A))
#define CSI_TO_LARGEST_REAL_NUMBER(A) ((long double)(A))
#define CSI_MAX_NUMBER_OF_CHARACTERS_IN_STRING 1000
#define CSI_STR_TO_MAGNITUDE_TYPE(STR) atof(STR)
#define CSI_FREE_CSI_MAGINITUDE_TYPE(UNIT)

/**
 * @brief The CSI_MALLOC macro is a preprocessor macro that allocates memory for an array of a specific size.
 *
 * @note Must return null if the allocation fails and returns a pointer to the allocated memory if the allocation succeeds.
 * @param SIZE_OF_TYPE The size of each element in the array.
 * @param NUM_OF_UNITS The number of elements in the array.
 *
 * @return A pointer to the allocated memory, or NULL if the allocation failed.
 *
 * @code
 * int* arr = CSI_MALLOC(int, 10);
 * if (arr == NULL) {
 *     printf("Failed to allocate memory\n");
 *     return 1;
 * }
 * for (int i = 0; i < 10; i++) {
 *     arr[i] = i;
 * }
 * CSI_FREE(arr);
 * @endcode
 */
#define CSI_MALLOC(SIZE_OF_TYPE, NUM_OF_UNITS) calloc(NUM_OF_UNITS, SIZE_OF_TYPE)

/**
 * @brief The CSI_REALLOC macro is a preprocessor macro that reallocates an array of a specific size.
 *
 * @note Must return null if the allocation fails and returns a pointer to the allocated memory if the allocation succeeds.
 * @param POINTER A pointer to the array to be reallocated.
 * @param SIZE_OF_TYPE The size of each element in the array.
 * @param NUM_OF_UNITS The new number of elements in the array.
 *
 * @return A pointer to the reallocated array, or NULL if the reallocation failed.
 *
 * @code
 * int* arr = CSI_MALLOC(int, 10);
 * if (arr == NULL) {
 *     printf("Failed to allocate memory\n");
 *     return 1;
 * }
 * for (int i = 0; i < 10; i++) {
 *     arr[i] = i;
 * }
 * arr = CSI_REALLOC(arr, int, 20);
 * if (arr == NULL) {
 *     printf("Failed to reallocate memory\n");
 *     return 1;
 * }
 * for (int i = 10; i < 20; i++) {
 *     arr[i] = i;
 * }
 * CSI_FREE(arr);
 * @endcode
 */
#define CSI_REALLOC(POINTER, SIZE_OF_TYPE, NUM_OF_UNITS) realloc(POINTER, NUM_OF_UNITS * SIZE_OF_TYPE)

/**
 * \brief Free memory allocated using CSI_MALLOC or CSI_REALLOC.
 * \note Must act like C's free function.
 * \note For example, CSI_FREE(NULL) does nothing.
 * \param POINTER The pointer to the memory to be freed.
 */
#define CSI_FREE(POINTER) free(POINTER)
#endif //CSI_H
