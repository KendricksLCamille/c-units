//
// Created by kendricks on 12/10/23.
//

#include "units_dimmension.h"

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

_Bool is_derived_types_the_same(const units_si_dimmension* a, const units_si_dimmension* const b)
{
    if (a->type == b->type) return true;
    if (a->numerator == NULL || b->numerator == NULL || a->denominator == NULL || b->denominator == NULL) return false;
    if (a->number_unit_in_denominator != b->number_unit_in_denominator) return false;
    if (a->number_unit_in_numerator != b->number_unit_in_numerator) return false;
    if (a->power != b->power) return false;


    size_t max_a_numerator = a->number_unit_in_denominator;
    size_t max_a_denominator = a->number_unit_in_numerator;
    for (int a_numerator = 0; a_numerator < max_a_numerator; a_numerator++)
    {
        const units_si_dimmension a_numerator_unit = *a->denominator[a_numerator];
        for (int b_numerator = 0; b_numerator < max_a_denominator; b_numerator++)
        {
            const units_si_dimmension b_numerator_unit = *b->denominator[b_numerator];
            if (is_derived_types_the_same(&a_numerator_unit, &b_numerator_unit)) goto found;
        }
    not_found:
        return false;
    found:
    
    }

    return true;
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



typedef struct Tuple
{
    void* data;
    size_t size;
} tuple_t;

tuple_t* simplify_list(void** list, const size_t size_of_list, size_t* output_size)
{
    tuple_t* simplified_list = malloc(size_of_list * sizeof(tuple_t));
    if (simplified_list == NULL) exit(EXIT_FAILURE);

    for (size_t i = 0; i < size_of_list; i++)
    {
        _Bool already_in_list = false;
        for (size_t k = 0; k < *output_size; k++)
        {
            tuple_t data = simplified_list[k];
            if (data.data == list[i])
            {
                already_in_list = true;
                break;
            }
        }
        if (already_in_list) continue;


        size_t count = 1;
        for (size_t j = i + 1; j < size_of_list; j++)
        {
            if (list[i] == list[j])
            {
                count++;
            }
        }

        simplified_list[(*output_size)++] = (tuple_t){list[i], count};
    }
    return simplified_list;
}

sds get_data_from_list(const units_si_dimmension* const* const list, const size_t size_of_list)
{
    size_t data = 0;
    tuple_t* simplified_list = simplify_list((void**)list, size_of_list, &data);
    sds output = sdsempty();

    for (size_t i = 0; i < data; i++)
    {
        tuple_t tuple = simplified_list[i];
        const units_si_dimmension* unit = simplified_list[i].data;
        output = sdscatsds(output, sdsnew(unit->symbol));

        const size_t size = simplified_list[i].size;
        if (size != 1) output = sdscatfmt(output, "%U", size);
        if (i != data - 1) output = sdscatsds(output, sdsnew(" * "));
    }

    if (data > 1)
    {
        sds temp = sdscatsds(sdsnew("( "), output);
        sdsfree(output);
        temp = sdscatsds(temp, sdsnew(" )"));
        output = temp;
    }
    free(simplified_list);
    return output;
}

sds simplify_list_to_string(const units_si_dimmension* data2)
{
    sds numerator = get_data_from_list(data2->numerator, data2->number_unit_in_numerator);
    sds denominator = get_data_from_list(data2->denominator, data2->number_unit_in_denominator);

    if (sdslen(numerator) == 0) numerator = sdscat(numerator, sdsnew("1"));
    if (sdslen(denominator) >= 1) denominator = sdscat(sdsnew("/"), denominator);
    return sdscatsds(numerator, denominator);
}

// max_depth = 0 means it will go through the intmax_t maximum value interations which is platform dependant
sds get_data_from_list_rec(const units_si_dimmension* const* const list, const size_t size_of_list,
                           const intmax_t max_depth)
{
    if (max_depth == 0)
    {
        return sdsempty();
    }

    return sdsempty();
}

sds units_si_derived_units_to_str(const units_si_dimmension* const type)
{
    sds numerator = sdsempty();
    sds denomator = sdsempty();

    units_si_dimmension unit = *type;
    for (int i = 0; i < type->number_unit_in_numerator; i++)
    {
        if (unit.type != NULL)
        {
            numerator = sdscatsds(numerator, sdsnew(unit.symbol));
        }
        else
        {
            const sds another = units_si_derived_units_to_str(unit.numerator[i]);
            numerator = sdscatsds(numerator, another);
        }
        if (type->number_unit_in_numerator > 1 && i < type->number_unit_in_numerator - 1)
        {
            numerator = sdscatsds(numerator, sdsnew(" * "));
        }
    }

    for (int i = 0; i < type->number_unit_in_denominator; i++)
    {
        sds temp = sdscatsds(denomator, sdsempty());
        denomator = temp;

        if (unit.type != NULL)
        {
            denomator = sdscatsds(denomator, sdsnew(unit.symbol));
        }
        else
        {
            const sds another = units_si_derived_units_to_str(unit.denominator[i]);
            if (unit.denominator[i]->type != NULL)
            {
                denomator = sdscatsds(denomator, another);
            }
            else
            {
                denomator = sdscat(denomator, sdsnew("("));
                denomator = sdscatsds(denomator, another);
                denomator = sdscat(denomator, sdsnew(")"));
            }
        }
    }

    if (sdslen(numerator) == 0)
    {
        numerator = sdscat(numerator, sdsnew("1"));
    }
    if (sdslen(denomator) != 0)
    {
        denomator = sdscatsds(sdsnew(" / "), denomator);
    }
    sds output = sdscatsds(numerator, denomator);
    return output;
}

void units_get_metadata_of_unit(const units_si_dimmension* const derived_units)
{
    printf("Derived Units: %s\n", derived_units->derived_quantity);
    printf("Name: %s\n", derived_units->name);
    printf("Symbol: %s\n", derived_units->symbol);
}