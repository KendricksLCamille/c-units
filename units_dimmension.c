//
// Created by kendricks on 12/10/23.
//

#include "units_dimmension.h"

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "units_si_base_unit_type.h"
#include "units_si_prefix.h"
#include "lib/sds-master/sds.h"

struct UNITS_SI_Dimmension
{
    const units_si_base_unit* type; // For the majority of derived units, this is null

    // Nuerator and Denomiator are null if type is not null and vice versa usually.
    const units_si_dimmension* const * const numerator;
    size_t number_unit_in_numerator;

    const units_si_dimmension* const * const denominator;
    size_t number_unit_in_denominator;

    int power;
    const units_si_prefix* const prefix;
    const char* const derived_quantity;
    const char* const name;
    const char* const symbol;
};

typedef struct list
{
    units_si_dimmension* list;
    size_t size;
    UNITS_MAGINITUDE_TYPE multiplier;
} list_t;

void find_and_increment_else_multiply(struct list* list, const units_si_dimmension* dimmension, const _Bool negative)
{
    for (size_t i = 0; i < list->size; i++)
    {
        const units_si_dimmension dimmension2 = *list->list[i];
        const units_si_prefix* prefix2 = dimmension2.prefix;
        const units_si_prefix* prefix1 = dimmension->prefix;
        
        if (dimmension2.type == dimmension->type)
        {
            if(prefix1 != prefix2)
            {
                const UNITS_MAGINITUDE_TYPE val1 = prefix_to_magnitude(prefix1);
                const UNITS_MAGINITUDE_TYPE val2 = prefix_to_magnitude(prefix2);
                list->multiplier = UNITS_MAGINITUDE_TYPE_MULTIPLY(val1, val2);
            }
            const int power2 = list->list[i]->power + (negative? -1 : 1) * dimmension->power;
            (list->list[i]->power) = power2;
            return;
        }
    }
    list->list = realloc(list->list, (list->size + 1) * sizeof(units_si_dimmension));
    if(list->list == NULL)
    {
        errno = ENOMEM;
        return;
    }
    list->list[list->size] = dimmension;
    list->size++;
}
const list_t* collapse_multiply(const units_si_dimmension* dimmensions, list_t* list)
{
    if(list == NULL)
    {
        list = malloc(sizeof(list_t));
        list->multiplier = UNITS_MAGINITUDE_TYPE_ZERO;
    }
    
    for (size_t i = 0; i < dimmensions->number_unit_in_numerator; i++)
    {
        const units_si_dimmension* dimmension = dimmensions->numerator[i];
        if(dimmension->type == NULL) collapse_multiply(dimmensions, list);
        find_and_increment_else_multiply(list, dimmension, false);
        if(errno == ENOMEM) return NULL;
    }
    
    for (size_t i = 0; i < dimmensions->number_unit_in_denominator; i++)
    {
        const units_si_dimmension* dimmension = dimmensions->denominator[i];
        if(dimmension->type == NULL) collapse_multiply(dimmensions, list);
        find_and_increment_else_multiply(list, dimmension, true);
        if(errno == ENOMEM) return NULL;
    }
    
    return list;
}

void find_and_increment_else_add(struct list* list, const units_si_dimmension* dimmension)
{
    for (size_t i = 0; i < list->size; i++)
    {
        const units_si_dimmension dimmension2 = *list->list[i];
        const units_si_prefix* prefix2 = dimmension2.prefix;
        const units_si_prefix* prefix1 = dimmension->prefix;
        
        if (dimmension2.type == dimmension->type)
        {
            if(prefix1 != prefix2)
            {
                const UNITS_MAGINITUDE_TYPE val1 = prefix_to_magnitude(prefix1);
                const UNITS_MAGINITUDE_TYPE val2 = prefix_to_magnitude(prefix2);
                list->multiplier = UNITS_MAGINITUDE_TYPE_MULTIPLY(val1, val2);
            }   
            return;
        }
    }
    list->list = realloc(list->list, (list->size + 1) * sizeof(units_si_dimmension));
    if(list->list == NULL)
    {
        errno = ENOMEM;
        return;
    }
    list->list[list->size] = dimmension;
    list->size++;
}
list_t* collapse_add(const units_si_dimmension* dimmensions, list_t* list)
{
    if(list == NULL)
    {
        list = malloc(sizeof(list_t));
        list->multiplier = UNITS_MAGINITUDE_TYPE_ZERO;
        list->size = 0;
    }
    
    for (size_t i = 0; i < dimmensions->number_unit_in_numerator; i++)
    {
        const units_si_dimmension* dimmension = dimmensions->numerator[i];
        if(dimmension->type == NULL) collapse_add(dimmensions, list);
        find_and_increment_else_add(list, dimmension);
        if(errno == ENOMEM) return NULL;
    }
    
    for (size_t i = 0; i < dimmensions->number_unit_in_denominator; i++)
    {
        const units_si_dimmension* dimmension = dimmensions->denominator[i];
        if(dimmension->type == NULL) collapse_add(dimmensions, list);
        find_and_increment_else_add(list, dimmension);
        if(errno == ENOMEM) return NULL;
    }
    
    return list;
}


_Bool is_lists_equal(const list_t* list1, const list_t* list2)
{
    if(list1->size!= list2->size) return false;
    for (size_t i = 0; i < list1->size; i++)
    {
        const units_si_dimmension l1 = *list1->list[i];
        for (size_t j = 0; j < list2->size; j++)
        {
            const units_si_dimmension l2 = *list2->list[j];
            if(l1.type == l2.type && l1.power == l2.power) goto success;
        }
        return false; // If not a single match is found, return false.
        success:
    }
    return true;
}
char* list_to_string(const list_t* list)
{
    sds str = sdsempty();
    for (size_t i = 0; i < list->size; i++)
    {
        const units_si_dimmension dimmension = *list->list[i];
        if(i > 0) str = sdscat(str, " * ");
        str = sdscat(str, dimmension.name);
        if(dimmension.power!= 1)
        {
            str = sdscat(str, "^");
            str = sdscatfmt(str, "%d", dimmension.power);
        }
    }

    char* result = strdup(str);
    sdsfree(str);
    return result;
}

char* get_dimmensions_string(const units_si_dimmension* dimmensions)
{
    list_t* list = collapse_multiply(dimmensions, NULL);
    char* result = list_to_string(list);
    free(list);
    return result;
}


const units_si_dimmension MAGINITUDE = {NULL, NULL, 0, NULL, 0, 0, NULL};

#define BASE_UNITS(unit_type, unit_name, unit_symbol, ...) {.type = &unit_type, .prefix = &UNIT_SELF,.derived_quantity = unit_name,.name = unit_name,.symbol = unit_symbol, .power = 1,  ##__VA_ARGS__}

const units_si_dimmension METER = BASE_UNITS(LENGTH, "meter", "m");
const units_si_dimmension KILO_GRAM = BASE_UNITS(MASS, "kilogram", "kg", .prefix = &UNIT_KILO);
const units_si_dimmension SECOND = BASE_UNITS(TIME, "second", "s");
const units_si_dimmension AMPERE = BASE_UNITS(ELECTRIC_CURRENT, "ampere", "A");
const units_si_dimmension KELVIN = BASE_UNITS(THERMODYNAIMC_TEMPATURE, "kelvin", "K");
const units_si_dimmension MOLE = BASE_UNITS(AMOUNT_OF_SUBSTANCE, "mole", "mol");
const units_si_dimmension CANDELA = BASE_UNITS(LUMINOUS_INTENSITY, "candela", "cd");


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define UNITS_SI_DERIVED_UNIT_TYPE2(var_name, u_quat, u_name, u_symbol, u_denominator, u_numerator) \
const units_si_dimmension var_name = { \
        .derived_quantity = u_quat, \
        .name = u_name, \
        .symbol = u_symbol, \
        .prefix = &UNIT_SELF, \
        .denominator = u_denominator, \
        .number_unit_in_denominator = ARRAY_SIZE(u_denominator),\
        .numerator = u_numerator, \
        .number_unit_in_numerator = ARRAY_SIZE(u_numerator)\
    }


UNITS_SI_DERIVED_UNIT_TYPE2(INVALID_UNIT, "invalid_unit", "invalid_unit", "invalid_unit", NULL, NULL);

const units_si_dimmension HERTZ = {
    .derived_quantity = "frequency", .name = "hertz", .symbol = "Hz", .prefix = &UNIT_SELF, .power = 1,
    .denominator = (const struct UNITS_SI_Dimmension* const[]){&SECOND}, .number_unit_in_denominator = 1,
    .numerator = (const struct UNITS_SI_Dimmension* const[]){}, .number_unit_in_numerator = 0,
};

const struct UNITS_SI_Dimmension* denominator_FORCE[] = {&SECOND, &SECOND};
const struct UNITS_SI_Dimmension* numerator_FORCE[] = {&KILO_GRAM, &METER};
const units_si_dimmension NEWTON = {
    .derived_quantity = "Force", .name = "Newton", .symbol = "N", .prefix = &UNIT_SELF,
    .denominator = denominator_FORCE, .number_unit_in_denominator = ARRAY_SIZE(denominator_FORCE),
    .numerator = numerator_FORCE, .number_unit_in_numerator = ARRAY_SIZE(numerator_FORCE)
};

const struct UNITS_SI_Dimmension* denominator_POWER[] = {&METER, &METER};
const struct UNITS_SI_Dimmension* numerator_POWER[] = {&NEWTON};
const units_si_dimmension WATT = {
    .derived_quantity = "Power", .name = "Watt", .symbol = "W", .prefix = &UNIT_SELF, .denominator = denominator_POWER,
    .number_unit_in_denominator = ARRAY_SIZE(denominator_POWER), .numerator = numerator_POWER,
    .number_unit_in_numerator = ARRAY_SIZE(numerator_POWER)
};

const struct UNITS_SI_Dimmension* denominator_PRESSURE[] = {&METER, &METER, &SECOND};
// e.g. (M L^-2 T^-2), Please define according to your need
const struct UNITS_SI_Dimmension* numerator_PRESSURE[] = {&KILO_GRAM};
// e.g. (M L^-2 T^-2), Please define according to your need
const units_si_dimmension PASCAL = {
    .derived_quantity = "Pressure", .name = "Pascal", .symbol = "Pa", .prefix = &UNIT_SELF,
    .denominator = denominator_PRESSURE, .number_unit_in_denominator = ARRAY_SIZE(denominator_PRESSURE),
    .numerator = numerator_PRESSURE, .number_unit_in_numerator = ARRAY_SIZE(numerator_PRESSURE)
};

const struct UNITS_SI_Dimmension* denominator_ENERGY[] = {&METER, &SECOND};
// e.g. (M L^2 T^-2), Please define according to your need
const struct UNITS_SI_Dimmension* numerator_ENERGY[] = {&KILO_GRAM, &METER};
// e.g. (M L^2 T^-2), Please define according to your need
const units_si_dimmension JOULE = {
    .derived_quantity = "Energy", .name = "Joule", .symbol = "J", .prefix = &UNIT_SELF,
    .denominator = denominator_ENERGY, .number_unit_in_denominator = ARRAY_SIZE(denominator_ENERGY),
    .numerator = numerator_ENERGY, .number_unit_in_numerator = ARRAY_SIZE(numerator_ENERGY)
};

const struct UNITS_SI_Dimmension* denominator_ELECTRIC_CHARGE[] = {&SECOND};
// e.g. (I T), Please define according to your need
const struct UNITS_SI_Dimmension* numerator_ELECTRIC_CHARGE[] = {&AMPERE};
// e.g. (I T), Please define according to your need
const units_si_dimmension COULOMB = {
    .derived_quantity = "Electric Charge", .name = "Coulomb", .symbol = "C", .prefix = &UNIT_SELF,
    .denominator = denominator_ELECTRIC_CHARGE, .number_unit_in_denominator = ARRAY_SIZE(denominator_ELECTRIC_CHARGE),
    .numerator = numerator_ELECTRIC_CHARGE, .number_unit_in_numerator = ARRAY_SIZE(numerator_ELECTRIC_CHARGE)
};

const struct UNITS_SI_Dimmension* denominator_ELECTRIC_POTENTIAL[] = {&METER, &METER, &SECOND};
// e.g. (M L^2 T^-3 I^-1), Please define according to your need
const struct UNITS_SI_Dimmension* numerator_ELECTRIC_POTENTIAL[] = {&KILO_GRAM, &AMPERE};
// e.g. (M L^2 T^-3 I^-1), Please define according to your need
const units_si_dimmension VOLT = {
    .derived_quantity = "Electric Potential", .name = "Volt", .symbol = "V", .prefix = &UNIT_SELF,
    .denominator = denominator_ELECTRIC_POTENTIAL,
    .number_unit_in_denominator = ARRAY_SIZE(denominator_ELECTRIC_POTENTIAL), .numerator = numerator_ELECTRIC_POTENTIAL,
    .number_unit_in_numerator = ARRAY_SIZE(numerator_ELECTRIC_POTENTIAL)
};

const struct UNITS_SI_Dimmension* denominator_ELECTRICAL_RESISTANCE[] = {&METER, &METER, &SECOND};
// e.g. (M L^2 T^-3 I^-2), Please define according to your need
const struct UNITS_SI_Dimmension* numerator_ELECTRICAL_RESISTANCE[] = {&KILO_GRAM, &AMPERE, &AMPERE};
// e.g. (M L^2 T^-3 I^-2), Please define according to your need
const units_si_dimmension OHM = {
    .derived_quantity = "Electrical Resistance", .name = "Ohm", .symbol = "Ω", .prefix = &UNIT_SELF,
    .denominator = denominator_ELECTRICAL_RESISTANCE,
    .number_unit_in_denominator = ARRAY_SIZE(denominator_ELECTRICAL_RESISTANCE),
    .numerator = numerator_ELECTRICAL_RESISTANCE,
    .number_unit_in_numerator = ARRAY_SIZE(numerator_ELECTRICAL_RESISTANCE)
};

