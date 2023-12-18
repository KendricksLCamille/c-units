//
// Created by kendricks on 12/10/23.
//

#include "units_dimmension.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "units_pointer_support.h"
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

typedef struct dimmesnion_counter
{
    const units_si_dimmension* const dimmension;
    intmax_t counter;
} dimmesnion_counter;

_Bool find_in_units_si_dimmension_array(const dimmesnion_counter* array, const intmax_t size, const units_si_dimmension* const target, uintmax_t* index)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i].dimmension == target)
        {
            *index = i;
            return true;
        }
    }
    return false;
}

dimmesnion_counter* combine_dimmesnion_counters(const dimmesnion_counter* a, dimmesnion_counter* b)
{
    dimmesnion_counter* output = malloc(sizeof(dimmesnion_counter) * (a->counter + b->counter));
    if (output == NULL) return NULL;
    size_t used_index = a->counter;

    memcpy(output, a, sizeof(dimmesnion_counter) * used_index);

    for (size_t i = 0; i < b->counter; i++)
    {
        uintmax_t temp_index = 0;
        const dimmesnion_counter target = b[i];
        if (find_in_units_si_dimmension_array(output, used_index, target.dimmension, &temp_index))
        {
            output[temp_index].counter += b;
        }
        else
        {
            
            memcpy(&output[used_index++], &target, sizeof(dimmesnion_counter));
        }
    }

    output = realloc(output, used_index * sizeof(dimmesnion_counter));
    
    return output;
}

dimmesnion_counter* get_dimmensions_init(units_si_dimmension* dimmension)
{
    dimmesnion_counter *numerator, *denominator;
    // Get numerator portion of dimmension
    for(int i = 0; i < dimmension->number_unit_in_numerator; i++)
    {
        
    }
    

    return NULL;
}


sds get_data_from_list(const units_si_dimmension* const* const list, const size_t size_of_list)
{
    size_t data = 0;
    pointer_counter_t* simplified_list = count_occurences_of_pointer((void**)list, size_of_list, &data);
    if(simplified_list == NULL)
    {
        return NULL;
    }
    sds output = sdsempty();

    for (size_t i = 0; i < data; i++)
    {
        const pointer_counter_t tuple = simplified_list[i];
        const units_si_dimmension* unit = tuple.data;
        output = sdscatsds(output, sdsnew(unit->symbol));

        const size_t size = tuple.number_of_occurences;
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
sds get_dimmension(const units_si_dimmension* data2)
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

    const sds temp = get_dimmension(derived_units);
    printf("Dimmension: %s\n", temp);
    sdsfree(temp);
}

