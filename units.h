//
// Created by kendricks on 12/7/23.

#ifndef UNITS_H
#define UNITS_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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


typedef struct UNITS_SI_Base_Units_Type UNITS_SI_Base_Units_Type;

extern const UNITS_SI_Base_Units_Type LENGTH;
extern const UNITS_SI_Base_Units_Type MASS;
extern const UNITS_SI_Base_Units_Type TIME;
extern const UNITS_SI_Base_Units_Type ELECTRIC_CURRENT;
extern const UNITS_SI_Base_Units_Type THERMODYNAIMC_TEMPATURE;
extern const UNITS_SI_Base_Units_Type AMOUNT_OF_SUBSTANCE;
extern const UNITS_SI_Base_Units_Type LUMINOUS_INTENSITY;
extern const UNITS_SI_Base_Units_Type INVALID;

typedef struct UNITS_SI_Prefix units_si_prefix;

extern units_si_prefix UNIT_YOTTA;
extern units_si_prefix UNIT_ZETTA;
extern units_si_prefix UNIT_EXA;
extern units_si_prefix UNIT_PETA;
extern units_si_prefix UNIT_TERA;
extern units_si_prefix UNIT_GIGA;
extern units_si_prefix UNIT_MEGA;
extern units_si_prefix UNIT_KILO;
extern units_si_prefix UNIT_HECTO;
extern units_si_prefix UNIT_DEKA;
extern units_si_prefix UNIT_DECI;
extern units_si_prefix UNIT_CENTI;
extern units_si_prefix UNIT_MILLI;
extern units_si_prefix UNIT_MICRO;
extern units_si_prefix UNIT_NANO;
extern units_si_prefix UNIT_PICO;
extern units_si_prefix UNIT_FEMTO;
extern units_si_prefix UNIT_ATTO;
extern units_si_prefix UNIT_ZEPTO;
extern units_si_prefix UNIT_YOCTO;

typedef struct UNITS_Unit UNITS_Unit;

#define UNITS_CONST_POINTER_CONST(TYPE) const TYPE* const
#define UNITS_CPC_USBUT UNITS_CONST_POINTER_CONST(UNITS_SI_Base_Units_Type)
#define UNITS_CPC_U UNITS_CONST_POINTER_CONST(Unit)


typedef struct UNITS_Numeric
{
    UNITS_MAGINITUDE_TYPE* real_value;
    UNITS_SI_Base_Units_Type* numerator_units;
    UNITS_SI_Base_Units_Type* denominator_units;
    ushort number_of_numerator_units;
    ushort number_of_denominator_units;
} Unit;


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
