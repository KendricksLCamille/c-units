//
// Created by kendricks on 12/7/23.

#ifndef UNITS_H
#define UNITS_H


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
#define UNITS_TO_SIZE_T(A) (size_t)(A)
#define UNITS_TO_PTRDIFF_T(A) ((ptrdiff_t)(A))
#define UNITS_TO_LONG_DOUBLE(A) ((long double)(A))
#define UNITS_TO_STRING(A) UNITS_ERROR
#define UNITS_FREE_UNIT(UNIT)



typedef struct UNITS_SI_Quantity units_si_quantity;

// Returned when unsupported operations occurs. errono set to -1;
extern const units_si_quantity INVALID_RESULT;


char* unit_to_string_MALLOC(units_si_quantity unit);
units_si_quantity unit_add(units_si_quantity a, units_si_quantity b);
units_si_quantity unit_subtract(units_si_quantity a, units_si_quantity b);
units_si_quantity unit_scalar_multiply(units_si_quantity a, units_si_quantity b);
units_si_quantity unit_divide(units_si_quantity a, units_si_quantity b);
units_si_quantity unit_modulo(units_si_quantity a, units_si_quantity b);

#endif //UNITS_H