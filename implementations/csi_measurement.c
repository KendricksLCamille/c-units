//
// Created by kendricks on 12/7/23.
//

#include "../csi_measurement.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../csi_unit.h"
#include "../lib/sds-master/sds.h"


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
    size_t size;
    const CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_ADD(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

csi_measurment* unit_subtract(const csi_measurment* const a, const csi_measurment* const b)
{
    const CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_SUBTRACT(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

csi_measurment* unit_multiply(const csi_measurment* const a, const csi_measurment* const b)
{
    const CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_MULTIPLY(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

csi_measurment* unit_divide(const csi_measurment* const a, const csi_measurment* const b)
{
    const CSI_MAGINITUDE_TYPE magnitude = CSI_MAGINITUDE_TYPE_DIVIDE(a->magnitude, b->magnitude);
    ALLOCATE_AND_RETURN_UNIT(magnitude, a->type);
}

csi_measurment* csi_measurment_create(CSI_MAGINITUDE_TYPE mangitude, const csi_unit* unit)
{
    csi_measurment* result = malloc(sizeof(csi_measurment));
    result->magnitude = mangitude;
    result->type = unit;
    return result;
}

bool is_result_valid(const csi_measurment* result)
{
    return result != &INVALID_RESULT;
}

void csi_measurment_free_many(size_t num, ...)
{
    va_list args;
    va_start(args, num);
    for (size_t i = 0; i < num; i++)
        free(va_arg(args, csi_measurment*));
    va_end(args);
}

void csi_measurment_free(csi_measurment* measurment)
{
    free(measurment);
}

CSI_MAGINITUDE_TYPE csi_measurment_magnitude(const csi_measurment* measurment)
{
    return measurment->magnitude;
}

char* csi_measurment_magnitude_string(const csi_measurment* measurment)
{
    char* numeric_str = malloc(CSI_MAX_NUMBER_OF_CHARACTERS_IN_STRING * sizeof(char));
    CSI_MAGNITUDE_TYPE_TO_STRING(numeric_str, measurment->magnitude);
    sds output = sdsnew(numeric_str);
    output = sdscat(output, " "); // Add a space between the magnitude and the unit.
    char* unit_str = get_dimmensions_string(measurment->type);
    output = sdscat(output, unit_str);
    free(unit_str);
    char* output2 = strdup(output);
    sdsfree(output);
    return output2;
}

csi_measurment* units_si_quantity_create(const CSI_MAGINITUDE_TYPE mangitude, const csi_unit* unit)
{
    ALLOCATE_AND_RETURN_UNIT(mangitude, unit);
}
