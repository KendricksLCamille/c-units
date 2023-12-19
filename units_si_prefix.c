#ifndef CSI_SI_PREFIX_IMP_H
#define CSI_SI_PREFIX_IMP_H
#include "units_si_prefix.h"

struct CSI_SI_Prefix
{
    const char* const magnitude;
    const char* prefix;
    const char* short_name;
};

const struct CSI_SI_Prefix UNIT_YOTTA = {("1000000000000000000000000"), "Yotta", "Y"};
const struct CSI_SI_Prefix UNIT_ZETTA = {("1000000000000000000000"), "Zetta", "Z"};
const struct CSI_SI_Prefix UNIT_EXA = {("1000000000000000000"), "Exa", "E"};
const struct CSI_SI_Prefix UNIT_PETA = {("1000000000000000"), "Peta", "P"};
const struct CSI_SI_Prefix UNIT_TERA = {("1000000000000"), "Tera", "T"};
const struct CSI_SI_Prefix UNIT_GIGA = {("1000000000"), "Giga", "G"};
const struct CSI_SI_Prefix UNIT_MEGA = {("1000000"), "Mega", "M"};
const struct CSI_SI_Prefix UNIT_KILO = {("1000"), "Kilo", "k"};
const struct CSI_SI_Prefix UNIT_HECTO = {("100"), "Hecto", "h"};
const struct CSI_SI_Prefix UNIT_DEKA = {("10"), "Deka", "da"};
const struct CSI_SI_Prefix UNIT_SELF = {("1"), "", ""};
const struct CSI_SI_Prefix UNIT_DECI = {("0.1"), "Deci", "d"};
const struct CSI_SI_Prefix UNIT_CENTI = {("0.01"), "Centi", "c"};
const struct CSI_SI_Prefix UNIT_MILLI = {("0.001"), "Milli", "m"};
const struct CSI_SI_Prefix UNIT_MICRO = {("0.000001"), "Micro", "μ"};
const struct CSI_SI_Prefix UNIT_NANO = {("0.000000001"), "Nano", "n"};
const struct CSI_SI_Prefix UNIT_PICO = {("0.000000000001"), "Pico", "p"};
const struct CSI_SI_Prefix UNIT_FEMTO = {("0.000000000000001"), "Femto", "f"};
const struct CSI_SI_Prefix UNIT_ATTO = {("0.000000000000000001"), "Atto", "a"};
const struct CSI_SI_Prefix UNIT_ZEPTO = {("0.000000000000000000001"), "Zepto", "z"};
const struct CSI_SI_Prefix UNIT_YOCTO = {("0.000000000000000000000001"), "Yocto", "y"};

// Use to map the prefix to the corresponding value
struct CSI_SI_Prefix CSI_SI_PREFIXES[] = {
    UNIT_PICO,
    UNIT_PICO,
    UNIT_NANO,
    UNIT_NANO,
    UNIT_NANO,
    UNIT_MICRO, 
    UNIT_MICRO, 
    UNIT_MICRO, 
    UNIT_MILLI,
    UNIT_MILLI,
    UNIT_MILLI, 
    UNIT_CENTI, 
    UNIT_DECI, 
    UNIT_SELF, 
    UNIT_DEKA, 
    UNIT_HECTO, 
    UNIT_KILO,
    UNIT_KILO,
    UNIT_MEGA,
    UNIT_MEGA,
    UNIT_MEGA,
    UNIT_GIGA,
    UNIT_GIGA,
    UNIT_GIGA,
    UNIT_TERA,
    UNIT_TERA
};
const int size_CSI_SI_PREFIXES = sizeof(CSI_SI_PREFIXES) / sizeof(CSI_SI_PREFIXES[0]);
const int index_of_SELF = 13;

struct CSI_SI_Prefix* get_units_si_prefix(short exponent)
{
    if(exponent <= -12)
    {
        exponent = 0;
    }
    else if(exponent >= 12)
    {
        exponent = size_CSI_SI_PREFIXES - 1;
    }
    else
    {
        exponent += index_of_SELF;
    }

    return &CSI_SI_PREFIXES[exponent];
}

#endif
CSI_MAGINITUDE_TYPE prefix_to_magnitude(const units_si_prefix* prefix)
{
    return CSI_STR_TO_MAGNITUDE_TYPE(prefix->magnitude);
}
