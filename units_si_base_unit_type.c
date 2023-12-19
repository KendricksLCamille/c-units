//
// Created by kendricks on 12/10/23.
//

#include "units_si_base_unit_type.h"
#include "units_dimmension.h"

struct CSI_SI_Base_Unit_Type
{
    const char* base_quantity;
    const units_si_dimmension* base_dimmension;
};
const units_si_base_unit LENGTH = {"Length", &METER};
const units_si_base_unit MASS = {"Mass", &KILO_GRAM};
const units_si_base_unit TIME = {"Time", &SECOND};
const units_si_base_unit ELECTRIC_CURRENT = {"Electric Current", &AMPERE};
const units_si_base_unit THERMODYNAIMC_TEMPATURE = {"Thermodynamic Temperature", &KELVIN};
const units_si_base_unit AMOUNT_OF_SUBSTANCE = {"Amount of Substance",&MOLE};
const units_si_base_unit LUMINOUS_INTENSITY = {"Luminous Intensity", &CANDELA};
const units_si_base_unit INVALID = {"Invalid", NULL};
_Bool is_types_the_same(CONST_Base_Unit_Type a, CONST_Base_Unit_Type b)
{
    return a == b;
}

const units_si_dimmension* units_si_base_unit_to_dimmension(const units_si_base_unit* const a)
{
    return a->base_dimmension;
}
