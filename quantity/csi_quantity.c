//
// Created by kendricks on 12/10/23.
//

#include "csi_quantity.h"
#include <stddef.h>

const csi_quantity LENGTH = {"Length", &METER};
const csi_quantity MASS = {"Mass", &KILO_GRAM};
const csi_quantity TIME = {"Time", &SECOND};
const csi_quantity ELECTRIC_CURRENT = {"Electric Current", &AMPERE};
const csi_quantity THERMODYNAIMC_TEMPATURE = {"Thermodynamic Temperature", &KELVIN};
const csi_quantity AMOUNT_OF_SUBSTANCE = {"Amount of Substance", &MOLE};
const csi_quantity LUMINOUS_INTENSITY = {"Luminous Intensity", &CANDELA};
const csi_quantity INVALID = {"Invalid", NULL};
