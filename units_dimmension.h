//
// Created by kendricks on 12/10/23.
//

#ifndef CSI_DIMMENSION_H
#define CSI_DIMMENSION_H

#include <stddef.h>

#include "csi_configuration.h"

typedef struct CSI_SI_Dimmension units_si_dimmension;
#define CSI_CPC_U CSI_CONST_POINTER_CONST(units_si_derived_units)
extern const units_si_dimmension METER;
extern const units_si_dimmension KILO_GRAM;
extern const units_si_dimmension SECOND;
extern const units_si_dimmension AMPERE;
extern const units_si_dimmension KELVIN;
extern const units_si_dimmension MOLE;
extern const units_si_dimmension CANDELA;
extern const units_si_dimmension HERTZ;
extern const units_si_dimmension NEWTON;
extern const units_si_dimmension PASCAL;
extern const units_si_dimmension JOULE;
extern const units_si_dimmension WATT;
extern const units_si_dimmension COULOMB;
extern const units_si_dimmension VOLT;
extern const units_si_dimmension OHM;

char* get_dimmensions_string(const units_si_dimmension* dimmensions);
void print_dimmensions(const units_si_dimmension* dimmensions);
#endif //CSI_DIMMENSION_H
