#ifndef UNITS_SI_PREFIX_IMP_H
#define UNITS_SI_PREFIX_IMP_H
#include "units_si_prefix.h"

struct UNITS_SI_Prefix
{
    const char* const magnitude;
    const char* prefix;
    const char* short_name;
};
const struct UNITS_SI_Prefix UNIT_YOTTA = {("1000000000000000000000000"), "Yotta", "Y"};
const struct UNITS_SI_Prefix UNIT_ZETTA = {("1000000000000000000000"), "Zetta", "Z"};
const struct UNITS_SI_Prefix UNIT_EXA = {("1000000000000000000"), "Exa", "E"};
const struct UNITS_SI_Prefix UNIT_PETA = {("1000000000000000"), "Peta", "P"};
const struct UNITS_SI_Prefix UNIT_TERA = {("1000000000000"), "Tera", "T"};
const struct UNITS_SI_Prefix UNIT_GIGA = {("1000000000"), "Giga", "G"};
const struct UNITS_SI_Prefix UNIT_MEGA = {("1000000"), "Mega", "M"};
const struct UNITS_SI_Prefix UNIT_KILO = {("1000"), "Kilo", "k"};
const struct UNITS_SI_Prefix UNIT_HECTO = {("100"), "Hecto", "h"};
const struct UNITS_SI_Prefix UNIT_DEKA = {("10"), "Deka", "da"};
const struct UNITS_SI_Prefix UNIT_SELF = {("1"), "", ""};
const struct UNITS_SI_Prefix UNIT_DECI = {("0.1"), "Deci", "d"};
const struct UNITS_SI_Prefix UNIT_CENTI = {("0.01"), "Centi", "c"};
const struct UNITS_SI_Prefix UNIT_MILLI = {("0.001"), "Milli", "m"};
const struct UNITS_SI_Prefix UNIT_MICRO = {("0.000001"), "Micro", "μ"};
const struct UNITS_SI_Prefix UNIT_NANO = {("0.000000001"), "Nano", "n"};
const struct UNITS_SI_Prefix UNIT_PICO = {("0.000000000001"), "Pico", "p"};
const struct UNITS_SI_Prefix UNIT_FEMTO = {("0.000000000000001"), "Femto", "f"};
const struct UNITS_SI_Prefix UNIT_ATTO = {("0.000000000000000001"), "Atto", "a"};
const struct UNITS_SI_Prefix UNIT_ZEPTO = {("0.000000000000000000001"), "Zepto", "z"};
const struct UNITS_SI_Prefix UNIT_YOCTO = {("0.000000000000000000000001"), "Yocto", "y"};

#endif