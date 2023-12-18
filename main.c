//
// Created by kendricks on 12/7/23.
//


#include <stdio.h>

#include "units.h"
int main()
{
    units_si_quantity* created = units_si_quantity_create(1, &METER);
    units_si_quantity* added = unit_add(created, created);
    printf("%s\n", unit_to_string_MALLOC(added));
    return 0;
}
