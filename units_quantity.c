//
// Created by kendricks on 12/7/23.
//

#include "units_quantity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct CSI_Measurment
{
    CSI_MAGINITUDE_TYPE magnitude;
    const csi_unit* type;
};

const csi_measurment INVALID_RESULT = {CSI_MAGINITUDE_TYPE_ZERO, NULL};


char* unit_to_string_MALLOC(const csi_measurment* unit)
{
    char* numericString = malloc(CSI_MAX_NUMBER_OF_CHARACTERS_IN_STRING * sizeof(char));
    CSI_MAGNITUDE_TYPE_TO_STRING(numericString, unit->magnitude);
    return numericString;
}

#define ALLOCATE_AND_RETURN_UNIT(MAGNITUDE, TYPE) \
    csi_measurment* result = malloc(sizeof(csi_measurment)); \
    result->magnitude = MAGNITUDE; \
    result->type = TYPE; \
    return result

csi_measurment* allocate_units_si_quantity(const csi_measurment* const src)
{
    csi_measurment* dest = malloc(sizeof(csi_measurment));
    memcpy(dest, src, sizeof(csi_measurment));
    return dest;
}

csi_measurment* unit_add(const csi_measurment* const a, const csi_measurment* const b)
{
    CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_ADD(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

csi_measurment* unit_subtract(const csi_measurment* const a, const csi_measurment* const b)
{
    CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_SUBTRACT(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

csi_measurment* unit_multiply(const csi_measurment* const a, const csi_measurment* const b)
{
    CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_MULTIPLY(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

csi_measurment* unit_divide(const csi_measurment* const a, const csi_measurment* const b)
{
    CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_DIVIDE(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

csi_measurment* units_si_quantity_create(const CSI_MAGINITUDE_TYPE mangitude, const csi_unit* unit)
{
    ALLOCATE_AND_RETURN_UNIT(mangitude, unit);
}