//
// Created by kendricks on 12/7/23.

#ifndef UNITS_QUANTITY_H
#define UNITS_QUANTITY_H

#include "units_configuration.h"
#include "units_dimmension.h"



typedef struct UNITS_SI_Quantity units_si_quantity;

// Returned when unsupported operations occurs. errono set to -1;
extern const units_si_quantity INVALID_RESULT;

char* unit_to_string_MALLOC(const units_si_quantity* unit);
units_si_quantity* unit_add(const units_si_quantity* const a, const units_si_quantity* const b);
units_si_quantity* unit_subtract(const units_si_quantity* const a, const units_si_quantity* const b);
units_si_quantity* unit_multiply(const units_si_quantity* const a, const units_si_quantity* const b);
units_si_quantity* unit_divide(const units_si_quantity* const a, const units_si_quantity* const b);
units_si_quantity* units_si_quantity_create(UNITS_MAGINITUDE_TYPE mangitude, const units_si_dimmension* unit);

#endif //UNITS_H