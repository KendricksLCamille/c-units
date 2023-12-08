//
// Created by kendricks on 12/7/23.
//

#include "units.h"
#include "units_si_prefix.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const ushort MAX_NUMBER_OF_UNITS = 1000;

typedef struct UNITS_SI_Base_Units_Type
{
    const char* base_quantity;
    const char* name;
    const char* symbol;
} UNITS_SI_Base_Units_Type;
#define UNITS_CPC_UNIT_TYPE UNITS_CONST_POINTER_CONST(UNITS_SI_Base_Units_Type)
const UNITS_SI_Base_Units_Type LENGTH = {"Length", "meter", "m"};
const UNITS_SI_Base_Units_Type MASS = {"Mass", "kilogram", "kg"};
const UNITS_SI_Base_Units_Type TIME = {"Time", "second", "s"};
const UNITS_SI_Base_Units_Type ELECTRIC_CURRENT = {"Electric Current", "ampere", "A"};
const UNITS_SI_Base_Units_Type THERMODYNAIMC_TEMPATURE = {"Thermodynamic Temperature", "kelvin", "K"};
const UNITS_SI_Base_Units_Type AMOUNT_OF_SUBSTANCE = {"Amount of Substance", "mole", "mol"};
const UNITS_SI_Base_Units_Type LUMINOUS_INTENSITY = {"Luminous Intensity", "candela", "cd"};
const UNITS_SI_Base_Units_Type INVALID = {"Invalid", "Invalid", "Invalid"};
_Bool is_types_the_same(UNITS_CPC_UNIT_TYPE a, UNITS_CPC_UNIT_TYPE b)
{
    return a == b;
}


struct UNITS_SI_Prefix
{
    const char* const magnitude;
    const char* prefix;
    const char* short_name;
};
const struct UNITS_SI_Prefix UNIT_YOTTA = {("1000000000000000000000000"), "Yotta", "Y"};
const struct UNITS_SI_Prefix UNIT_ZETTA = {("1000000000000000000000"), "Zetta", "Z"};
const struct UNITS_SI_Prefix UNIT_EXA = {("1000000000000000000"), "Exa", "E"};
const struct UNITS_SI_Prefix UNIT_PETA = {("1000000000000000"), "Peta", "P"};
const struct UNITS_SI_Prefix UNIT_TERA = {("1000000000000"), "Tera", "T"};
const struct UNITS_SI_Prefix UNIT_GIGA = {("1000000000"), "Giga", "G"};
const struct UNITS_SI_Prefix UNIT_MEGA = {("1000000"), "Mega", "M"};
const struct UNITS_SI_Prefix UNIT_KILO = {("1000"), "Kilo", "k"};
const struct UNITS_SI_Prefix UNIT_HECTO = {("100"), "Hecto", "h"};
const struct UNITS_SI_Prefix UNIT_DEKA = {("10"), "Deka", "da"};
const struct UNITS_SI_Prefix UNIT_SELF = {("1"), "", ""};
const struct UNITS_SI_Prefix UNIT_DECI = {("0.1"), "Deci", "d"};
const struct UNITS_SI_Prefix UNIT_CENTI = {("0.01"), "Centi", "c"};
const struct UNITS_SI_Prefix UNIT_MILLI = {("0.001"), "Milli", "m"};
const struct UNITS_SI_Prefix UNIT_MICRO = {("0.000001"), "Micro", "μ"};
const struct UNITS_SI_Prefix UNIT_NANO = {("0.000000001"), "Nano", "n"};
const struct UNITS_SI_Prefix UNIT_PICO = {("0.000000000001"), "Pico", "p"};
const struct UNITS_SI_Prefix UNIT_FEMTO = {("0.000000000000001"), "Femto", "f"};
const struct UNITS_SI_Prefix UNIT_ATTO = {("0.000000000000000001"), "Atto", "a"};
const struct UNITS_SI_Prefix UNIT_ZEPTO = {("0.000000000000000000001"), "Zepto", "z"};
const struct UNITS_SI_Prefix UNIT_YOCTO = {("0.000000000000000000000001"), "Yocto", "y"};

UNITS_MAGINITUDE_TYPE array[20];


struct UNITS_SI_Derived_Units_Type
{
    const UNITS_SI_Base_Units_Type* const type; // For the majority of derived units, this is null

    // Nuerator and Denomiator are null if type is not null and vice versa usually.
    const units_si_derived_units* const numerator;
    size_t number_unit_in_numerator;

    const units_si_derived_units* const denominator;
    size_t number_unit_in_denominator;

    int exponent;
    const units_si_prefix* const prefix;
    const char* const derived_quantity;
    const char* const name;
    const char* const symbol;
};
_Bool is_derived_types_the_same(const units_si_derived_units* a, const units_si_derived_units* const b)
{
    if(a->type == b->type) return true;
    if(a->numerator == NULL || b->numerator == NULL || a->denominator == NULL || b->denominator == NULL) return false;
    if(a->number_unit_in_denominator != b->number_unit_in_denominator) return false;
    if(a->number_unit_in_numerator!= b->number_unit_in_numerator) return false;
    if(a->exponent!= b->exponent) return false;


    size_t max_a_numerator = a->number_unit_in_denominator;
    size_t max_a_denominator = a->number_unit_in_numerator;
    for(int a_numerator = 0; a_numerator < max_a_numerator; a_numerator++)
    {
        const units_si_derived_units a_numerator_unit = a->denominator[a_numerator];
        for(int b_numerator = 0; b_numerator < max_a_denominator; b_numerator++)
        {
            const units_si_derived_units b_numerator_unit = b->denominator[b_numerator];
            if(is_derived_types_the_same(&a_numerator_unit, &b_numerator_unit)) goto found;
        }
        not_found:
        return false;
        found:
    }
    
    return true;
}
const units_si_derived_units MAGINITUDE = {NULL, NULL, 0, NULL, 0, 0, NULL};
#define BASE_UNITS(unit_type, unit_name, unit_symbol, ...) {.type = &unit_type, .prefix = &UNIT_SELF,.derived_quantity = unit_type.name,.name = unit_name,.symbol = unit_symbol, .exponent = 1,  ##__VA_ARGS__}
const units_si_derived_units METER = BASE_UNITS(LENGTH, "meter", "m");
const units_si_derived_units KILO_GRAM = BASE_UNITS(MASS, "kilogram", "kg",  .prefix = &UNIT_KILO);
const units_si_derived_units SECOND = BASE_UNITS(TIME, "second", "s");
const units_si_derived_units AMPERE = BASE_UNITS(ELECTRIC_CURRENT, "ampere", "A");
const units_si_derived_units KELVIN = BASE_UNITS(THERMODYNAIMC_TEMPATURE, "kelvin", "K");
const units_si_derived_units MOLE = BASE_UNITS(AMOUNT_OF_SUBSTANCE, "mole", "mol");
const units_si_derived_units CANDELA = BASE_UNITS(LUMINOUS_INTENSITY, "candela", "cd");
const units_si_derived_units FREQUENCY = {.derived_quantity = "Frequency",.name = "hertz",.symbol = "Hz", .denominator = (const units_si_derived_units* const){&SECOND}, .prefix = &UNIT_SELF};



void units_si_derived_units_print(const units_si_derived_units* const derived_units)
{
    printf("Derived Units: %s\n", derived_units->derived_quantity);
    printf("Name: %s\n", derived_units->name);
    printf("Symbol: %s\n", derived_units->symbol);
}

