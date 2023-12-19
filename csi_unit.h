//
// Created by kendricks on 12/10/23.
//

#ifndef CSI_DIMMENSION_H
#define CSI_DIMMENSION_H

#include <stddef.h>
#include "csi_configuration.h"
#include "csi_prefix.h"

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


char* get_dimmensions_string(CSI_CPC_UNIT dimmensions);
void print_dimmensions(CSI_CPC_UNIT dimmensions);

struct csi_unit_and_magnitude
{
    csi_unit* unit;
    CSI_MAGINITUDE_TYPE manigitude;
};

struct csi_unit_and_magnitude* get_base_dimmension(CSI_CPC_UNIT d1, CSI_CPC_UNIT d2);

_Bool is_dimmensions_eqiuvalent(const csi_unit* dimm, const csi_unit* dimm2);
csi_unit* csi_unit_with_prefix(const csi_unit* dimm, const csi_prefix* prefix);
#endif //CSI_DIMMENSION_H
