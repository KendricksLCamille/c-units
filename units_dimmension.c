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
#include "prefix/csi_prefix.h"
#include "lib/sds-master/sds.h"

struct CSI_SI_Dimmension
{
    const units_si_base_unit* type; // For the majority of derived units, this is null

    // Nuerator and Denomiator are null if type is not null and vice versa usually.
    const units_si_dimmension* const * const numerator;
    size_t number_unit_in_numerator;

    const units_si_dimmension* const * const denominator;
    size_t number_unit_in_denominator;

    int power;
    const csi_prefix* const prefix;
    const char* const derived_quantity;
    const char* const name;
    const char* const symbol;
};

typedef struct list
{
    units_si_dimmension* list;
    size_t size;
    CSI_MAGINITUDE_TYPE multiplier;
} list_t;

CSI_MAGINITUDE_TYPE get_base_unit_multiplier(const units_si_dimmension* dimmension)
{
    CSI_MAGINITUDE_TYPE denominator_multiplier = csi_prefix_to_magnitude(
        units_si_base_unit_to_dimmension(dimmension->type)->prefix);
    CSI_MAGINITUDE_TYPE numerator_multiplier = csi_prefix_to_magnitude(dimmension->prefix);
    return CSI_MAGINITUDE_TYPE_DIVIDE(numerator_multiplier, denominator_multiplier);
}
void find_and_increment_then_multiple(struct list* list, const units_si_dimmension* dimmension, const _Bool negative)
{
    for (size_t i = 0; i < list->size; i++)
    {
        const units_si_dimmension dimmension2 = list->list[i];
        
        if (dimmension2.type == dimmension->type)
        {
            list->multiplier = CSI_MAGINITUDE_TYPE_MULTIPLY(get_base_unit_multiplier(dimmension),
                                                            get_base_unit_multiplier(&dimmension2));
            const int power2 = dimmension2.power + (negative? -1 : 1) * dimmension->power;
            list->list[i].power = power2;
            return;
        }
    }
    list->list = realloc(list->list, (list->size + 1) * sizeof(units_si_dimmension));
    if(list->list == NULL)
    {
        errno = ENOMEM;
        return;
    }
    memcpy(&list->list[list->size], units_si_base_unit_to_dimmension(dimmension->type), sizeof(units_si_dimmension));
    list->list[list->size].power *= negative? -1 : 1;
    list->size++;
}
list_t* collapse(const units_si_dimmension* dimmensions, list_t* list)
{
    if (list == NULL)
    {
        list = malloc(sizeof(list_t));
        list->multiplier = CSI_MAGINITUDE_TYPE_ZERO;
    }
    
    for (size_t i = 0; i < dimmensions->number_unit_in_numerator; i++)
    {
        const units_si_dimmension* dimmension = dimmensions->numerator[i];
        if(dimmension->type == NULL)
        {
            collapse(dimmension, list);
        }
        else
        {
            find_and_increment_then_multiple(list, dimmension, false);
        }
        if(errno == ENOMEM) return NULL;
    }
    
    for (size_t i = 0; i < dimmensions->number_unit_in_denominator; i++)
    {
        const units_si_dimmension* dimmension = dimmensions->denominator[i];
        if(dimmension->type == NULL)
        {
            collapse(dimmensions, list);
        }
        else
        {
            find_and_increment_then_multiple(list, dimmension, true);
        }
        if(errno == ENOMEM) return NULL;
    }
    
    return list;
}

_Bool is_lists_equal(const list_t* list1, const list_t* list2)
{
    if(list1->size!= list2->size) return false;
    for (size_t i = 0; i < list1->size; i++)
    {
        const units_si_dimmension l1 = list1->list[i];
        for (size_t j = 0; j < list2->size; j++)
        {
            const units_si_dimmension l2 = list2->list[j];
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
        const units_si_dimmension dimmension = list->list[i];
        if(i > 0) str = sdscat(str, " * ");
        str = sdscat(str, dimmension.symbol);
        if(dimmension.power!= 1)
        {
            str = sdscat(str, "^");
            str = sdscatfmt(str, "%i", dimmension.power);
        }
    }

    char* result = strdup(str);
    sdsfree(str);
    return result;
}

char* get_dimmensions_string(const units_si_dimmension* dimmensions)
{
    list_t* list = collapse(dimmensions, NULL);
    if(errno == ENOMEM) return NULL;
    char* result = list_to_string(list);
    if(errno == ENOMEM) return NULL;
    free(list);
    return result;
}

void print_dimmensions(const units_si_dimmension* dimmensions)
{
    printf("Quntity: %s\n", dimmensions->derived_quantity);
    printf("Name: %s\n", dimmensions->name);
    printf("Symbol: %s\n", dimmensions->symbol);
    printf("Breakdown: %s\n", get_dimmensions_string(dimmensions));
}


const units_si_dimmension MAGINITUDE = {NULL, NULL, 0, NULL, 0, 0, NULL};

#define BASE_CSI(unit_type, unit_name, unit_symbol, ...) {.type = &unit_type, .prefix = &UNIT_SELF,.derived_quantity = unit_name,.name = unit_name,.symbol = unit_symbol, .power = 1,  ##__VA_ARGS__}

const units_si_dimmension METER = BASE_CSI(LENGTH, "meter", "m");
const units_si_dimmension KILO_GRAM = BASE_CSI(MASS, "kilogram", "kg", .prefix = &UNIT_KILO);
const units_si_dimmension SECOND = BASE_CSI(TIME, "second", "s");
const units_si_dimmension AMPERE = BASE_CSI(ELECTRIC_CURRENT, "ampere", "A");
const units_si_dimmension KELVIN = BASE_CSI(THERMODYNAIMC_TEMPATURE, "kelvin", "K");
const units_si_dimmension MOLE = BASE_CSI(AMOUNT_OF_SUBSTANCE, "mole", "mol");
const units_si_dimmension CANDELA = BASE_CSI(LUMINOUS_INTENSITY, "candela", "cd");

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define CSI_SI_DERIVED_UNIT_TYPE2(var_name, u_quat, u_name, u_symbol, u_denominator, u_numerator) \
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


CSI_SI_DERIVED_UNIT_TYPE2(INVALID_UNIT, "invalid_unit", "invalid_unit", "invalid_unit", NULL, NULL);

const units_si_dimmension HERTZ = {
    .derived_quantity = "frequency", .name = "hertz", .symbol = "Hz", .prefix = &UNIT_SELF, .power = 1,
    .denominator = (const struct CSI_SI_Dimmension* const[]){&SECOND}, .number_unit_in_denominator = 1,
    .numerator = NULL, .number_unit_in_numerator = 0,
};

const struct CSI_SI_Dimmension* denominator_FORCE[] = {&SECOND, &SECOND};
const struct CSI_SI_Dimmension* numerator_FORCE[] = {&KILO_GRAM, &METER};
const units_si_dimmension NEWTON = {
    .derived_quantity = "Force", .name = "Newton", .symbol = "N", .prefix = &UNIT_SELF,
    .denominator = denominator_FORCE, .number_unit_in_denominator = ARRAY_SIZE(denominator_FORCE),
    .numerator = numerator_FORCE, .number_unit_in_numerator = ARRAY_SIZE(numerator_FORCE)
};

const struct CSI_SI_Dimmension* denominator_PRESSURE[] = {&METER, &METER};
// e.g. (M L^-2 T^-2), Please define according to your need
const struct CSI_SI_Dimmension* numerator_PRESSURE[] = {&NEWTON};
// e.g. (M L^-2 T^-2), Please define according to your need
const units_si_dimmension PASCAL = {
    .derived_quantity = "Pressure", .name = "Pascal", .symbol = "Pa", .prefix = &UNIT_SELF,
    .denominator = denominator_PRESSURE, .number_unit_in_denominator = ARRAY_SIZE(denominator_PRESSURE),
    .numerator = numerator_PRESSURE, .number_unit_in_numerator = ARRAY_SIZE(numerator_PRESSURE)
};

// e.g. (M L^2 T^-2), Please define according to your need
const struct CSI_SI_Dimmension* numerator_ENERGY[] = {&NEWTON, &METER};
// e.g. (M L^2 T^-2), Please define according to your need
const units_si_dimmension JOULE = {
    .derived_quantity = "Energy", .name = "Joule", .symbol = "J", .prefix = &UNIT_SELF,
    .denominator = NULL, .number_unit_in_denominator = 0,
    .numerator = numerator_ENERGY, .number_unit_in_numerator = ARRAY_SIZE(numerator_ENERGY)
};

const struct CSI_SI_Dimmension* numerator_POWER[] = {&JOULE};
const struct CSI_SI_Dimmension* denominator_POWER[] = {&SECOND};
const units_si_dimmension WATT = {
    .derived_quantity = "Power", .name = "Watt", .symbol = "W", .prefix = &UNIT_SELF, .denominator = denominator_POWER,
    .number_unit_in_denominator = ARRAY_SIZE(denominator_POWER), .numerator = numerator_POWER,
    .number_unit_in_numerator = ARRAY_SIZE(numerator_POWER)
};

const struct CSI_SI_Dimmension* numerator_ELECTRIC_CHARGE[] = {&AMPERE, &SECOND};
const units_si_dimmension COULOMB = {
    .derived_quantity = "Electric Charge", .name = "Coulomb", .symbol = "C", .prefix = &UNIT_SELF,
    .denominator = NULL, .number_unit_in_denominator = 0,
    .numerator = numerator_ELECTRIC_CHARGE, .number_unit_in_numerator = ARRAY_SIZE(numerator_ELECTRIC_CHARGE)
};

const struct CSI_SI_Dimmension* numerator_ELECTRIC_POTENTIAL[] = {&WATT};
const struct CSI_SI_Dimmension* denominator_ELECTRIC_POTENTIAL[] = {&AMPERE};
const units_si_dimmension VOLT = {
    .derived_quantity = "Electric Potential", .name = "Volt", .symbol = "V", .prefix = &UNIT_SELF,
    .denominator = denominator_ELECTRIC_POTENTIAL,
    .number_unit_in_denominator = ARRAY_SIZE(denominator_ELECTRIC_POTENTIAL), .numerator = numerator_ELECTRIC_POTENTIAL,
    .number_unit_in_numerator = ARRAY_SIZE(numerator_ELECTRIC_POTENTIAL)
};

const struct CSI_SI_Dimmension* numerator_ELECTRICAL_RESISTANCE[] = {&VOLT};
const struct CSI_SI_Dimmension* denominator_ELECTRICAL_RESISTANCE[] = {&AMPERE};
const units_si_dimmension OHM = {
    .derived_quantity = "Electrical Resistance", .name = "Ohm", .symbol = "Ω", .prefix = &UNIT_SELF,
    .denominator = denominator_ELECTRICAL_RESISTANCE,
    .number_unit_in_denominator = ARRAY_SIZE(denominator_ELECTRICAL_RESISTANCE),
    .numerator = numerator_ELECTRICAL_RESISTANCE,
    .number_unit_in_numerator = ARRAY_SIZE(numerator_ELECTRICAL_RESISTANCE)
};

