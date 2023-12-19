//
// Created by kendricks on 12/7/23.

#ifndef CSI_QUANTITY_H
#define CSI_QUANTITY_H

#include <stddef.h>

#include "csi_unit.h"
#include <stdbool.h>

typedef struct CSI_Measurment csi_measurment;

// Returned when unsupported operations occurs such as (1K + c) or (Tempature + Velocity). errono set to -1;
extern const csi_measurment INVALID_RESULT;

char* unit_to_string_MALLOC(const csi_measurment* unit);
csi_measurment* unit_add(const csi_measurment* const a, const csi_measurment* const b);
csi_measurment* unit_subtract(const csi_measurment* const a, const csi_measurment* const b);
csi_measurment* unit_multiply(const csi_measurment* const a, const csi_measurment* const b);
csi_measurment* unit_divide(const csi_measurment* const a, const csi_measurment* const b);
csi_measurment* csi_measurment_create(CSI_MAGINITUDE_TYPE mangitude, const csi_unit* unit);

bool is_result_valid(const csi_measurment* result);
void csi_measurment_free_many(size_t num, ...);
void csi_measurment_free(csi_measurment* measurment);
CSI_MAGINITUDE_TYPE csi_measurment_magnitude(const csi_measurment* measurment);
char* csi_measurment_magnitude_string(const csi_measurment* measurment);
#endif //CSI_QUANTITY_H
