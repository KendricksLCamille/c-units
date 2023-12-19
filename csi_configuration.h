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
#define CSI_STR_TO_MAGNITUDE_TYPE(STR) atof(STR)
#define CSI_MAGINITUDE_TYPE_IS_ZERO(A) ((A) == 0)
#define CSI_MAGINITUDE_TYPE_ADD(A,B) ((A) + (B))
#define CSI_MAGINITUDE_TYPE_SUBTRACT(A,B) ((A) - (B))
#define CSI_MAGINITUDE_TYPE_MULTIPLY(A,B) ((A) * (B))
#define CSI_MAGINITUDE_TYPE_MODULO(A,B) ((A) % (B))
#define CSI_MAGINITUDE_TYPE_DIVIDE(A,B) ((A) / (B))
#define CSI_MAGNITUDE_TYPE_TO_STRING(STR,A) sprintf(STR,"%Lf", (A))
#define CSI_TO_LARGEST_UNSIGNED_INTEGER(A) (size_t)(A)
#define CSI_TO_LARGEST_SIGNED_INTEGER(A) ((ptrdiff_t)(A))
#define CSI_MAX_NUMBER_OF_CHARACTERS_IN_STRING 1000
#define CSI_TO_LARGEST_REAL_NUMBER(A) ((long double)(A))
#define CSI_FREE_CSI_MAGINITUDE_TYPE(UNIT)

#endif //CSI_H
