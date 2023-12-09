//
// Created by kendricks on 12/8/23.
//

#ifndef UNITS_SI_BASE_UNIT_TYPE_H
#define UNITS_SI_BASE_UNIT_TYPE_H
#include "units.h"


typedef struct UNITS_SI_Base_Unit_Type units_si_base_unit;
#define CONST_Base_Unit_Type UNITS_CONST_POINTER_CONST(units_si_base_unit)
extern const units_si_base_unit LENGTH;
extern const units_si_base_unit MASS;
extern const units_si_base_unit TIME;
extern const units_si_base_unit ELECTRIC_CURRENT;
extern const units_si_base_unit THERMODYNAIMC_TEMPATURE;
extern const units_si_base_unit AMOUNT_OF_SUBSTANCE;
extern const units_si_base_unit LUMINOUS_INTENSITY;
extern const units_si_base_unit INVALID;


#endif //UNITS_SI_BASE_UNIT_TYPE_H
