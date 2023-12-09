#ifndef UNITS_SI_BASE_UNIT_TYPE_IMP_H
#define UNITS_SI_BASE_UNIT_TYPE_IMP_H
  //
// Created by kendricks on 12/8/23.
//

#include "units_si_base_unit_type.h"

struct UNITS_SI_Base_Unit_Type
{
    const char* base_quantity;
    const char* name;
    const char* symbol;
};
const units_si_base_unit LENGTH = {"Length", "meter", "m"};
const units_si_base_unit MASS = {"Mass", "kilogram", "kg"};
const units_si_base_unit TIME = {"Time", "second", "s"};
const units_si_base_unit ELECTRIC_CURRENT = {"Electric Current", "ampere", "A"};
const units_si_base_unit THERMODYNAIMC_TEMPATURE = {"Thermodynamic Temperature", "kelvin", "K"};
const units_si_base_unit AMOUNT_OF_SUBSTANCE = {"Amount of Substance", "mole", "mol"};
const units_si_base_unit LUMINOUS_INTENSITY = {"Luminous Intensity", "candela", "cd"};
const units_si_base_unit INVALID = {"Invalid", "Invalid", "Invalid"};
_Bool is_types_the_same(CONST_Base_Unit_Type a, CONST_Base_Unit_Type b)
{
    return a == b;
}
#endif
