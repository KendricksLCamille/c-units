#ifndef CSI_SI_BASE_UNIT_TYPE_IMP_H
#define CSI_SI_BASE_UNIT_TYPE_IMP_H
//
// Created by kendricks on 12/8/23.
//

#include "csi_quantity.h"
#include "csi_configuration.h"
#include "csi_unit.h"

typedef struct CSI_Measurement
{
    CSI_CPC(char) name;
    CSI_CPC(csi_unit) base_unit;
} csi_quantity;

extern const csi_quantity LENGTH;
extern const csi_quantity MASS;
extern const csi_quantity TIME;
extern const csi_quantity ELECTRIC_CURRENT;
extern const csi_quantity THERMODYNAIMC_TEMPATURE;
extern const csi_quantity AMOUNT_OF_SUBSTANCE;
extern const csi_quantity LUMINOUS_INTENSITY;
extern const csi_quantity INVALID;

#endif
