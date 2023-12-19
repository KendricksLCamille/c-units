#ifndef CSI_SI_PREFIX_H
#define CSI_SI_PREFIX_H

#include "csi_configuration.h"

typedef struct CSI_Prefix csi_prefix;
extern const csi_prefix UNIT_YOTTA;
extern const csi_prefix UNIT_ZETTA;
extern const csi_prefix UNIT_EXA;
extern const csi_prefix UNIT_PETA;
extern const csi_prefix UNIT_TERA;
extern const csi_prefix UNIT_GIGA;
extern const csi_prefix UNIT_MEGA;
extern const csi_prefix UNIT_KILO;
extern const csi_prefix UNIT_HECTO;
extern const csi_prefix UNIT_DEKA;
extern const csi_prefix UNIT_SELF;
extern const csi_prefix UNIT_DECI;
extern const csi_prefix UNIT_CENTI;
extern const csi_prefix UNIT_MILLI;
extern const csi_prefix UNIT_MICRO;
extern const csi_prefix UNIT_NANO;
extern const csi_prefix UNIT_PICO;
extern const csi_prefix UNIT_FEMTO;
extern const csi_prefix UNIT_ATTO;
extern const csi_prefix UNIT_ZEPTO;
extern const csi_prefix UNIT_YOCTO;

CSI_MAGINITUDE_TYPE csi_prefix_to_magnitude(const csi_prefix *prefix);
#endif
