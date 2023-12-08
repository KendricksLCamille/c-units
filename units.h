//
// Created by kendricks on 12/7/23.

#ifndef UNITS_H
#define UNITS_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define UNITS_CONST_POINTER_CONST(TYPE) const TYPE* const


#define UNITS_MAGINITUDE_TYPE long double
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




typedef struct UNITS_SI_Derived_Units_Type units_si_derived_units;
#define UNITS_CPC_U UNITS_CONST_POINTER_CONST(units_si_derived_units)
extern const units_si_derived_units METER;
extern const units_si_derived_units KILO_GRAM;
extern const units_si_derived_units SECOND;
extern const units_si_derived_units AMPERE;
extern const units_si_derived_units KELVIN;
extern const units_si_derived_units MOLE;
extern const units_si_derived_units CANDELA;
extern const units_si_derived_units FREQUENCY;

void units_si_derived_units_print(const units_si_derived_units* const derived_units);

typedef struct UNITS_Numeric UNITS_Numeric;


char* unit_to_string_MALLOC(UNITS_CPC_U unit);

UNITS_CPC_U unit_scalar_multiply(UNITS_CPC_U a, UNITS_CPC_U b);
UNITS_CPC_U unit_divide(UNITS_CPC_U a, UNITS_CPC_U b);
UNITS_CPC_U unit_modulo(UNITS_CPC_U a, UNITS_CPC_U b);
UNITS_CPC_U unit_add(UNITS_CPC_U a, UNITS_CPC_U b);
UNITS_CPC_U unit_subtract(UNITS_CPC_U a, UNITS_CPC_U b);


#endif //UNITS_H
/*
typedef struct UNITS_SI_Prefixes
{
    short factor;
    const char *symbol;
    const char *name;
    UNITS_MAGINITUDE_TYPE* ;
};
*/
