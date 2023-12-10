//
// Created by kendricks on 12/7/23.
//

#include "units.h"
#include "units_si_prefix_imp.h"
#include "units_si_base_unit_type.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/sds-master/sds.h"







struct UNITS_SI_Quantity
{
    const UNITS_MAGINITUDE_TYPE magnitude;
    const units_si_dimmension* const type;
};

const units_si_quantity INVALID_RESULT = { UNITS_MAGINITUDE_TYPE_ZERO, &INVALID};


units_si_quantity unit_add(const units_si_quantity a, const units_si_quantity b)
{
    if(a.type == NULL || b.type == NULL) return INVALID_RESULT;
    if(a.type != b.type) return INVALID_RESULT;
    
}


/*units_si_derived_units* const unit_add2(
    const units_si_derived_units* const a,
    const units_si_derived_units* const b)
{
    if(!is_derived_types_the_same(a,b))
    {
        return &INVALID_UNIT;
    }

#define ALLOCATE_AND_COPY_DATA_TO_VARIABLE(src, dest, num_of_elements, type) \
    type dest;\
    {\
        size_t size_in_bytes = num_of_elements * sizeof(type); \
        dest = malloc(size_in_bytes); \
        memcpy(dest, src, size_in_bytes); \
    }0\

    const units_si_base_unit* type = a->type;
    ALLOCATE_AND_COPY_DATA_TO_VARIABLE(a->numerator, numerator, a->number_unit_in_numerator, units_si_derived_units*);
    size_t number_unit_in_numerator = a->number_unit_in_numerator;

    ALLOCATE_AND_COPY_DATA_TO_VARIABLE(a->denominator, denominator, a->number_unit_in_numerator, units_si_derived_units*);
    size_t number_unit_in_denominator = a->number_unit_in_denominator;

    units_si_derived_units new_derived_units = {
        .type = type,
        .numerator = numerator,
        .number_unit_in_numerator = number_unit_in_numerator,
        .denominator = denominator,
        .number_unit_in_denominator = number_unit_in_denominator,
        .power = a->power,
        .prefix = a->prefix,
        .derived_quantity = strdup(a->derived_quantity),
        .name = strdup(a->name),
        .symbol = strdup(a->symbol)
    };

#undef ALLOCATE_AND_COPY_DATA_TO_VARIABLE
    units_si_derived_units* const output = malloc(sizeof(units_si_derived_units));
    memcpy(output, &new_derived_units, sizeof(units_si_derived_units));
    return output;
}*/
