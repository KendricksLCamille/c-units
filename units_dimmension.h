//
// Created by kendricks on 12/10/23.
//

#ifndef UNITS_DIMMENSION_H
#define UNITS_DIMMENSION_H

typedef struct UNITS_SI_Dimmension units_si_dimmension;
#define UNITS_CPC_U UNITS_CONST_POINTER_CONST(units_si_derived_units)
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


void units_get_metadata_of_unit(const units_si_dimmension* derived_units);
_Bool is_derived_types_the_same(const units_si_dimmension* a, const units_si_dimmension* b);


#endif //UNITS_DIMMENSION_H
