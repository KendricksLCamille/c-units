//
// Created by kendricks on 12/7/23.
//

#include "units.h"
#include "units_si_prefix.h"
#include "units_si_base_unit_type_imp.h"
#include "units_si_prefix_imp.h"

#include <stdbool.h>
#include <stdio.h>




struct UNITS_SI_Derived_Units_Type
{
    const units_si_base_unit* type; // For the majority of derived units, this is null

    // Nuerator and Denomiator are null if type is not null and vice versa usually.
    const units_si_derived_units* const * const numerator;
    size_t number_unit_in_numerator;

    const units_si_derived_units* const * const denominator;
    size_t number_unit_in_denominator;

    int power;
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
    if(a->power!= b->power) return false;


    size_t max_a_numerator = a->number_unit_in_denominator;
    size_t max_a_denominator = a->number_unit_in_numerator;
    for(int a_numerator = 0; a_numerator < max_a_numerator; a_numerator++)
    {
        const units_si_derived_units a_numerator_unit = *a->denominator[a_numerator];
        for(int b_numerator = 0; b_numerator < max_a_denominator; b_numerator++)
        {
            const units_si_derived_units b_numerator_unit = *b->denominator[b_numerator];
            if(is_derived_types_the_same(&a_numerator_unit, &b_numerator_unit)) goto found;
        }
        not_found:
        return false;
        found:
    }
    
    return true;
}
const units_si_derived_units MAGINITUDE = {NULL, NULL, 0, NULL, 0, 0, NULL};
#define BASE_UNITS(unit_type, unit_name, unit_symbol, ...) {.type = &unit_type, .prefix = &UNIT_SELF,.derived_quantity = unit_type.name,.name = unit_name,.symbol = unit_symbol, .power = 1,  ##__VA_ARGS__}
const units_si_derived_units METER = BASE_UNITS(LENGTH, "meter", "m");
const units_si_derived_units KILO_GRAM = BASE_UNITS(MASS, "kilogram", "kg",  .prefix = &UNIT_KILO);
const units_si_derived_units SECOND = BASE_UNITS(TIME, "second", "s");
const units_si_derived_units AMPERE = BASE_UNITS(ELECTRIC_CURRENT, "ampere", "A");
const units_si_derived_units KELVIN = BASE_UNITS(THERMODYNAIMC_TEMPATURE, "kelvin", "K");
const units_si_derived_units MOLE = BASE_UNITS(AMOUNT_OF_SUBSTANCE, "mole", "mol");
const units_si_derived_units CANDELA = BASE_UNITS(LUMINOUS_INTENSITY, "candela", "cd");

typedef struct Tuple {void* data; size_t size;} tuple_t;
tuple_t* simplify_list(void** list, const size_t size_of_list, size_t* output_size)
{
    tuple_t* simplified_list = malloc(size_of_list * sizeof(tuple_t));
    if(simplified_list == NULL) exit(EXIT_FAILURE);
    
    for(size_t i = 0; i < size_of_list; i++)
    {
        _Bool already_in_list = false;
        for(size_t k = 0; k < *output_size; k++)
        {
            tuple_t data = simplified_list[k];
            if(data.data == list[i])
            {
                already_in_list = true;
                break;
            }
        }
        if(already_in_list) continue;

        
        size_t count = 1;
        for(size_t j = i + 1; j < size_of_list; j++)
        {
            if(list[i] == list[j])
            {
                count++;
            }
        }
        
        simplified_list[(*output_size)++] = (tuple_t){list[i], count};
    }
    return simplified_list;
}

sds get_data_from_list(const units_si_derived_units* const* const list, const size_t size_of_list)
{
    size_t data = 0;
    tuple_t* simplified_list = simplify_list((void**)list, size_of_list, &data);
    sds output = sdsempty();

    for(size_t i = 0; i < data; i++)
    {
        tuple_t tuple = simplified_list[i];
        const units_si_derived_units* unit = simplified_list[i].data;
        output = sdscatsds(output, sdsnew(unit->symbol));

        const size_t size = simplified_list[i].size;
        if(size != 1) output = sdscatfmt(output, "%U", size);
        if(i != data - 1) output = sdscatsds(output, sdsnew(" * "));
    }

    if(data > 1)
    {
        sds temp = sdscatsds( sdsnew("( "), output);
        sdsfree(output);
        temp = sdscatsds( temp, sdsnew(" )"));
        output = temp;
    }
    free(simplified_list);
    return output;
}
void simplify_list_to_string(const units_si_derived_units* data2)
{
    sds numerator = get_data_from_list(data2->numerator, data2->number_unit_in_numerator);
    sds denominator = get_data_from_list(data2->denominator,  data2->number_unit_in_denominator);

    if(sdslen(numerator) == 0) numerator = sdscat(numerator, sdsnew("1"));
    if(sdslen(denominator) >= 1) denominator = sdscat(sdsnew("/"), denominator);
    const sds output = sdscatsds(numerator, denominator);
    sdsfree(denominator);
    printf("%s\n", output);
    sdsfree(output);
}

#define UNITS_SI_DERIVED_UNIT_TYPE(var_name, u_quat, u_name, u_symbol, u_denominator, u_den_size, u_numerator, u_num_size) \
const units_si_derived_units var_name = { \
        .derived_quantity = u_quat, .name = u_name, .symbol = u_symbol, .prefix = &UNIT_SELF, .power = 1, \
        .denominator = (const struct UNITS_SI_Derived_Units_Type* const[])u_denominator, \
        .number_unit_in_denominator = u_den_size,\
        .numerator = (const struct UNITS_SI_Derived_Units_Type* const[])u_numerator, \
        .number_unit_in_numerator = u_num_size,\
        \
    }\



const struct UNITS_SI_Derived_Units_Type* const derived_units_arr1[] = { &SECOND, };

UNITS_SI_DERIVED_UNIT_TYPE(FREQUENCY, "frequency", "hertz", "Hz", {&SECOND}, 1, {}, 0);
const units_si_derived_units FORCE = {
    .derived_quantity = "Force",
    .name = "Newton",
    .symbol = "N", .prefix = &UNIT_SELF,
    .denominator = (const struct UNITS_SI_Derived_Units_Type* const[]){&SECOND, &SECOND}, .number_unit_in_denominator = 2,
    .numerator = (const struct UNITS_SI_Derived_Units_Type* const[]){&KILO_GRAM, &METER}, .number_unit_in_numerator = 2
};
const units_si_derived_units POWER = {
    .derived_quantity = "Power",
    .name = "Watt",
    .symbol = "W", .prefix = &UNIT_SELF,
    .denominator = (const struct UNITS_SI_Derived_Units_Type* const[]){&METER, &METER}, .number_unit_in_denominator = 2,
    .numerator = (const struct UNITS_SI_Derived_Units_Type* const[]){&FORCE}, .number_unit_in_numerator = 1
}; 

sds units_si_derived_units_to_str(const units_si_derived_units* const type)
{
    sds numerator = sdsempty();
    sds denomator = sdsempty();

    units_si_derived_units unit = *type;
    for(int i = 0; i < type->number_unit_in_numerator; i++)
    {
        if(unit.type != NULL)
        {
            numerator = sdscatsds(numerator, sdsnew(unit.symbol));
        }
        else
        {
            const sds another = units_si_derived_units_to_str(unit.numerator[i]);
            numerator = sdscatsds(numerator, another);
        }
        if(type->number_unit_in_numerator > 1 && i < type->number_unit_in_numerator - 1)
        {
            numerator =  sdscatsds(numerator, sdsnew(" * "));
        }
    }

    for(int i = 0; i < type->number_unit_in_denominator; i++)
    {

        sds temp = sdscatsds(denomator, sdsempty());
        denomator = temp;
        
        if(unit.type != NULL)
        {
            denomator = sdscatsds(denomator, sdsnew(unit.symbol));
        }
        else
        {
            const sds another = units_si_derived_units_to_str(unit.denominator[i]);
            if(unit.denominator[i]->type != NULL)
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

    if(sdslen(numerator) == 0)
    {
        numerator = sdscat(numerator, sdsnew("1"));
    }
    if(sdslen(denomator) != 0)
    {
        denomator = sdscatsds(sdsnew(" / "), denomator);
    }
    sds output = sdscatsds(numerator, denomator);
    return output;
}
void units_get_metadata_of_unit(const units_si_derived_units* const derived_units)
{
    printf("Derived Units: %s\n", derived_units->derived_quantity);
    printf("Name: %s\n", derived_units->name);
    printf("Symbol: %s\n", derived_units->symbol);
}

