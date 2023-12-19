#ifndef CSI_DIMMENSION_IMPL_H
#define CSI_DIMMENSION_IMPL_H

#include <stddef.h>

#include "csi_unit.h"
#include "prefix/csi_prefix.h"
#include "quantity/csi_quantity.h"


struct CSI_Unit
{
    const csi_quantity* type; // For the majority of derived units, this is null

    // Nuerator and Denomiator are null if type is not null and vice versa usually.
    const csi_unit* const * const numerator;
    const size_t number_unit_in_numerator;

    const csi_unit* const * const denominator;
    const size_t number_unit_in_denominator;

    int power;
    const csi_prefix* const prefix;
    const char* const derived_quantity;
    const char* const name;
    const char* const symbol;
};


const csi_unit MAGINITUDE = {NULL, NULL, 0, NULL, 0, 0, NULL, NULL, NULL, NULL};

#define BASE_CSI_UNIT(unit_type, unit_name, unit_symbol, ...) {.type = &unit_type, .prefix = &UNIT_SELF,.derived_quantity = unit_name,.name = unit_name,.symbol = unit_symbol, .power = 1,  ##__VA_ARGS__}

const csi_unit METER = BASE_CSI_UNIT(LENGTH, "meter", "m");
const csi_unit KILO_GRAM = BASE_CSI_UNIT(MASS, "kilogram", "kg", .prefix = &UNIT_KILO);
const csi_unit SECOND = BASE_CSI_UNIT(TIME, "second", "s");
const csi_unit AMPERE = BASE_CSI_UNIT(ELECTRIC_CURRENT, "ampere", "A");
const csi_unit KELVIN = BASE_CSI_UNIT(THERMODYNAIMC_TEMPATURE, "kelvin", "K");
const csi_unit MOLE = BASE_CSI_UNIT(AMOUNT_OF_SUBSTANCE, "mole", "mol");
const csi_unit CANDELA = BASE_CSI_UNIT(LUMINOUS_INTENSITY, "candela", "cd");

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define CSI_DERIVED_UNIT(var_name, u_quat, u_name, u_symbol, u_denominator, u_numerator) \
const csi_unit var_name = { \
.derived_quantity = u_quat, \
.name = u_name, \
.symbol = u_symbol, \
.prefix = &UNIT_SELF, \
.denominator = u_denominator, \
.number_unit_in_denominator = ARRAY_SIZE(u_denominator),\
.numerator = u_numerator, \
.number_unit_in_numerator = ARRAY_SIZE(u_numerator)\
}

#define CAST(name, array) const csi_unit* const name = (const csi_unit* const[])array
CSI_DERIVED_UNIT(INVALID_UNIT, "invalid_unit", "invalid_unit", "invalid_unit", NULL, NULL);

CAST(hertz_denominator, {&SECOND});
CSI_DERIVED_UNIT(HERTZ, "frequency", "hertz", "Hz", hertz_denominator, NULL);

const struct CSI_Unit* denominator_FORCE[] = {&SECOND, &SECOND};
const struct CSI_Unit* numerator_FORCE[] = {&KILO_GRAM, &METER};
CSI_DERIVED_UNIT(NEWTON, "Force", "Newton", "N", numerator_FORCE, denominator_FORCE);

const struct CSI_Unit* denominator_PRESSURE[] = {&METER, &METER};
const struct CSI_Unit* numerator_PRESSURE[] = {&NEWTON};
CSI_DERIVED_UNIT(PASCAL, "Pressure", "Pascal", "Pa", numerator_PRESSURE, denominator_PRESSURE);
#endif
