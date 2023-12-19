#ifndef CSI_SI_PREFIX_H
#define CSI_SI_PREFIX_H

#include "csi_configuration.h"

typedef struct CSI_SI_Prefix units_si_prefix;
extern const units_si_prefix UNIT_YOTTA;
extern const units_si_prefix UNIT_ZETTA;
extern const units_si_prefix UNIT_EXA;
extern const units_si_prefix UNIT_PETA;
extern const units_si_prefix UNIT_TERA;
extern const units_si_prefix UNIT_GIGA;
extern const units_si_prefix UNIT_MEGA;
extern const units_si_prefix UNIT_KILO;
extern const units_si_prefix UNIT_HECTO;
extern const units_si_prefix UNIT_DEKA;
extern const units_si_prefix UNIT_SELF;
extern const units_si_prefix UNIT_DECI;
extern const units_si_prefix UNIT_CENTI;
extern const units_si_prefix UNIT_MILLI;
extern const units_si_prefix UNIT_MICRO;
extern const units_si_prefix UNIT_NANO;
extern const units_si_prefix UNIT_PICO;
extern const units_si_prefix UNIT_FEMTO;
extern const units_si_prefix UNIT_ATTO;
extern const units_si_prefix UNIT_ZEPTO;
extern const units_si_prefix UNIT_YOCTO;

CSI_MAGINITUDE_TYPE prefix_to_magnitude(const units_si_prefix *prefix);
#endif
