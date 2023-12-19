#ifndef CSI_SI_BASE_UNIT_TYPE_IMP_H
#define CSI_SI_BASE_UNIT_TYPE_IMP_H
//
// Created by kendricks on 12/8/23.
//

#include "units_quantity.h"

typedef struct CSI_SI_Base_Unit_Type units_si_base_unit;
#define CONST_Base_Unit_Type CSI_CPC(units_si_base_unit)

extern const units_si_base_unit LENGTH;
extern const units_si_base_unit MASS;
extern const units_si_base_unit TIME;
extern const units_si_base_unit ELECTRIC_CURRENT;
extern const units_si_base_unit THERMODYNAIMC_TEMPATURE;
extern const units_si_base_unit AMOUNT_OF_SUBSTANCE;
extern const units_si_base_unit LUMINOUS_INTENSITY;
extern const units_si_base_unit INVALID;

_Bool is_types_the_same(CONST_Base_Unit_Type a, CONST_Base_Unit_Type b);
const units_si_dimmension* units_si_base_unit_to_dimmension(const units_si_base_unit* const a);
#endif
