//
// Created by kendricks on 12/7/23.
//

#include "units_quantity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct CSI_SI_Quantity
{
    CSI_MAGINITUDE_TYPE magnitude;
    const units_si_dimmension* type;
};

const units_si_quantity INVALID_RESULT = { CSI_MAGINITUDE_TYPE_ZERO, NULL};


char* unit_to_string_MALLOC(const units_si_quantity* unit){
    char* numericString = malloc(CSI_MAX_NUMBER_OF_CHARACTERS_IN_STRING * sizeof(char));
    CSI_MAGNITUDE_TYPE_TO_STRING(numericString, unit->magnitude);
    return numericString;   
}

#define ALLOCATE_AND_RETURN_UNIT(MAGNITUDE, TYPE) \
    units_si_quantity* result = malloc(sizeof(units_si_quantity)); \
    result->magnitude = MAGNITUDE; \
    result->type = TYPE; \
    return result

units_si_quantity* allocate_units_si_quantity(const units_si_quantity* const src)
{
    units_si_quantity* dest = malloc(sizeof(units_si_quantity));
    memcpy(dest, src, sizeof(units_si_quantity));
    return dest;
}
units_si_quantity* unit_add(const units_si_quantity* const a, const units_si_quantity* const b)
{
    CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_ADD(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

units_si_quantity* unit_subtract(const units_si_quantity* const a, const units_si_quantity* const b)
{
    CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_SUBTRACT(a->magnitude, b->magnitude);
        ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

units_si_quantity* unit_multiply(const units_si_quantity* const a, const units_si_quantity* const b)
{
    CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_MULTIPLY(a->magnitude, b->magnitude);
        ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

units_si_quantity* unit_divide(const units_si_quantity* const a, const units_si_quantity* const b)
{
    CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_DIVIDE(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

units_si_quantity* units_si_quantity_create(CSI_MAGINITUDE_TYPE mangitude, const units_si_dimmension* unit)
{
    ALLOCATE_AND_RETURN_UNIT(mangitude, unit);
}


