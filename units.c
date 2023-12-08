//
// Created by kendricks on 12/7/23.
//

#include "units.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct UNITS_SI_Base_Units_Type
{
    const char* base_quantity;
    const char* name;
    const char* symbol;
};

const UNITS_SI_Base_Units_Type LENGTH = {"Length", "meter", "m"};
const UNITS_SI_Base_Units_Type MASS = {"Mass", "kilogram", "kg"};
const UNITS_SI_Base_Units_Type TIME = {"Time", "second", "s"};
const UNITS_SI_Base_Units_Type ELECTRIC_CURRENT = {"Electric Current", "ampere", "A"};
const UNITS_SI_Base_Units_Type THERMODYNAIMC_TEMPATURE = {"Thermodynamic Temperature", "kelvin", "K"};
const UNITS_SI_Base_Units_Type AMOUNT_OF_SUBSTANCE = {"Amount of Substance", "mole", "mol"};
const UNITS_SI_Base_Units_Type LUMINOUS_INTENSITY = {"Luminous Intensity", "candela", "cd"};
const UNITS_SI_Base_Units_Type INVALID = {"Invalid", "Invalid", "Invalid"};

_Bool is_types_the_same(UNITS_CPC_USBUT a, UNITS_CPC_USBUT b)
{
    return a == b;
}

#define CPC_UMT UNITS_CONST_POINTER_CONST(UNITS_MAGINITUDE_TYPE)

struct UNITS_SI_Prefix
{
    CPC_UMT magnitude;
    const char* prefix;
    const char* short_name;
};

struct UNITS_SI_Prefix UNIT_YOTTA = {("1000000000000000000000000"), "Yotta", "Y"};
struct UNITS_SI_Prefix UNIT_ZETTA = {("1000000000000000000000"), "Zetta", "Z"};
struct UNITS_SI_Prefix UNIT_EXA = {("1000000000000000000"), "Exa", "E"};
struct UNITS_SI_Prefix UNIT_PETA = {("1000000000000000"), "Peta", "P"};
struct UNITS_SI_Prefix UNIT_TERA = {("1000000000000"), "Tera", "T"};
struct UNITS_SI_Prefix UNIT_GIGA = {("1000000000"), "Giga", "G"};
struct UNITS_SI_Prefix UNIT_MEGA = {("1000000"), "Mega", "M"};
struct UNITS_SI_Prefix UNIT_KILO = {("1000"), "Kilo", "k"};
struct UNITS_SI_Prefix UNIT_HECTO = {("100"), "Hecto", "h"};
struct UNITS_SI_Prefix UNIT_DEKA = {("10"), "Deka", "da"};
struct UNITS_SI_Prefix UNIT_DECI = {("0.1"), "Deci", "d"};
struct UNITS_SI_Prefix UNIT_CENTI = {("0.01"), "Centi", "c"};
struct UNITS_SI_Prefix UNIT_MILLI = {("0.001"), "Milli", "m"};
struct UNITS_SI_Prefix UNIT_MICRO = {("0.000001"), "Micro", "μ"};
struct UNITS_SI_Prefix UNIT_NANO = {("0.000000001"), "Nano", "n"};
struct UNITS_SI_Prefix UNIT_PICO = {("0.000000000001"), "Pico", "p"};
struct UNITS_SI_Prefix UNIT_FEMTO = {("0.000000000000001"), "Femto", "f"};
struct UNITS_SI_Prefix UNIT_ATTO = {("0.000000000000000001"), "Atto", "a"};
struct UNITS_SI_Prefix UNIT_ZEPTO = {("0.000000000000000000001"), "Zepto", "z"};
struct UNITS_SI_Prefix UNIT_YOCTO = {("0.000000000000000000000001"), "Yocto", "y"};

UNITS_MAGINITUDE_TYPE array[20];

struct UNITS_Unit
{
    UNITS_CPC_USBUT numerator;
    int* power_of_numerator;
    ushort number_unit_in_numerator;

    UNITS_CPC_USBUT denominator;
    int* power_of_denominator;
    ushort number_unit_in_denominator;

    const char* name;
    long double to_base_type;
};


/*
int logBase10(int number) {
    int count = 0;
    while (number != 0) {
        number /= 10;
        ++count;
    }
    return count-1;
}

char* intToStr(const int number) {
    const _Bool is_negative = number < 0;
    const int number_abs = is_negative ? -number : number;
    const int number_of_digits = logBase10(number_abs) + is_negative ? 2 : 1;
    
    char* numStr = malloc(number_of_digits * sizeof(char));
    if (is_negative) {
        numStr[0] = '-';
        numStr++;
    }
    
    if(numStr == NULL) {
        printf("Failed to allocate memory.\n");
        return NULL;
    }

    sprintf(numStr, "%d", number);

    return numStr;
}

char* unit_to_string_MALLOC(const Unit* unit)
{
    const UNITS_MAGINITUDE_TYPE value = *unit->real_value;
#if UNITS_TO_STRING(1) == UNITS_ERROR
    return intToStr(value);
#else
    return UNITS_TO_STRING(value);
#endif
}

struct UnitsAndNumberOfElements
{
    UNITS_SI_Base_Units_Type* units;
    ushort number_of_elements;
};

Unit* unit_scalar_multiply(UNITS_CUCP a, UNITS_CUCP b)
{
    auto a_value = *a->real_value;
    auto b_value = *b->real_value;
    auto result = UNITS_MAGINITUDE_TYPE_MULTIPLY(a_value, b_value);
    return NULL;
}

UNITS_SI_Base_Units_Type* units_the_same(UNITS_CUCP a, UNITS_CUCP b)
{
    if(a->number_of_numerator_units != b->number_of_numerator_units || a->number_of_denominator_units != b->number_of_denominator_units)
    {
        return false;
    }

    // Ensure that units are the same for the numberator
    for(int num = 0; num < a->number_of_numerator_units; num++)
    {
        UNITS_SI_Base_Units_Type unit = a->numerator_units[num];
        for(int num2 = 0; num2 < b->number_of_denominator_units; num2++)
        {
            if(&unit == &b->numerator_units[num2]) goto found;
        }
        not_found:
        return false;
        found:
    }
    
    // Ensure that units are the same for the denominator
    for(int num = 0; num < a->number_of_denominator_units; num++)
    {
        UNITS_SI_Base_Units_Type unit = a->denominator_units[num];
        for(int num2 = 0; num2 < b->number_of_numerator_units; num2++)
        {
            if(&unit == &b->denominator_units[num2]) goto found;
        }
        not_found:
        return false;
        found:
    }
    
    return true;
}*/
long double* UNITS_str_to_long_double(const char* const str)
{
    char* endptr;
    long double* malloc_value = malloc(sizeof(long double));
    *malloc_value = strtold(str, &endptr);

    if (*endptr != '\0')
    {
        // In this case, there are additional characters in the string which couldn't be converted.
        printf("Warning: Couldn't fully convert the string to long double.\n");
    }

    return malloc_value;
}
