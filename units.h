//
// Created by kendricks on 12/7/23.

#ifndef UNITS_H
#define UNITS_H

#include <stdlib.h>

#include "units_dimmension.h"


#define UNITS_CONST_POINTER_CONST(TYPE) const TYPE* const


#define UNITS_MAGINITUDE_TYPE long double
#define UNITS_MAGINITUDE_TYPE_ZERO 0.0L
#define UNITS_STR_TO_MAGNITUDE_TYPE_POINTER(STR) UNITS_str_to_long_double(STR)
#define UNITS_MAGINITUDE_TYPE_IS_ZERO(A) ((A) == 0)
#define UNITS_MAGINITUDE_TYPE_ADD(A,B) ((A) + (B))
#define UNITS_MAGINITUDE_TYPE_SUBTRACT(A,B) ((A) - (B))
#define UNITS_MAGINITUDE_TYPE_MULTIPLY(A,B) ((A) * (B))
#define UNITS_MAGINITUDE_TYPE_MODULO(A,B) ((A) % (B))
#define UNITS_MAGINITUDE_TYPE_DIVIDE(A,B) ((A) / (B))
#define UNITS_MAGNITUDE_TYPE_TO_STRING(STR,A) sprintf(STR,"%Lf", (A))
#define UNITS_TO_LARGEST_UNSIGNED_INTEGER(A) (size_t)(A)
#define UNITS_TO_LARGEST_SIGNED_INTEGER(A) ((ptrdiff_t)(A))
#define UNITS_MAX_NUMBER_OF_CHARACTERS_IN_STRING 100
#define UNITS_TO_LARGEST_REAL_NUMBER(A) ((long double)(A))
#define UNITS_FREE_UNITS_MAGINITUDE_TYPE(UNIT)



typedef struct UNITS_SI_Quantity units_si_quantity;

// Returned when unsupported operations occurs. errono set to -1;
extern const units_si_quantity INVALID_RESULT;

char* unit_to_string_MALLOC(const units_si_quantity* unit);
units_si_quantity* unit_add(const units_si_quantity* const a, const units_si_quantity* const b);
units_si_quantity* unit_subtract(const units_si_quantity* const a, const units_si_quantity* const b);
units_si_quantity* unit_multiply(const units_si_quantity* const a, const units_si_quantity* const b);
units_si_quantity* unit_divide(const units_si_quantity* const a, const units_si_quantity* const b);
units_si_quantity* units_si_quantity_create(UNITS_MAGINITUDE_TYPE mangitude, const units_si_dimmension* unit);

#endif //UNITS_H