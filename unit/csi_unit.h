//
// Created by kendricks on 12/10/23.
//

#ifndef CSI_DIMMENSION_H
#define CSI_DIMMENSION_H

#include "../csi_configuration.h"

typedef struct CSI_Unit csi_unit;
#define CSI_CPC_UNIT CSI_CPC(csi_unit)
extern const csi_unit METER;

extern const csi_unit KILO_GRAM;
extern const csi_unit SECOND;
extern const csi_unit AMPERE;
extern const csi_unit KELVIN;
extern const csi_unit MOLE;
extern const csi_unit CANDELA;
extern const csi_unit HERTZ;
extern const csi_unit NEWTON;
extern const csi_unit PASCAL;
extern const csi_unit JOULE;
extern const csi_unit WATT;
extern const csi_unit COULOMB;
extern const csi_unit VOLT;
extern const csi_unit OHM;


extern const csi_unit Squared(CSI_CPC_UNIT unit);
char* get_dimmensions_string(CSI_CPC_UNIT dimmensions);
void print_dimmensions(CSI_CPC_UNIT dimmensions);
#endif //CSI_DIMMENSION_H
