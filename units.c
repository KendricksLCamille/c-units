//
// Created by kendricks on 12/7/23.
//

#include "units.h"
#include "units_si_base_unit_type.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "units_dimmension.h"


struct UNITS_SI_Quantity
{
    const UNITS_MAGINITUDE_TYPE magnitude;
    const units_si_dimmension* const type;
};

const units_si_quantity INVALID_RESULT = { UNITS_MAGINITUDE_TYPE_ZERO, &INVALID};


units_si_quantity unit_add(const units_si_quantity a, const units_si_quantity b)
{
    if(a.type == NULL || b.type == NULL) return INVALID_RESULT;
    if(a.type != b.type) return INVALID_RESULT;
    
}



