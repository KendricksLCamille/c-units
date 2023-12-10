//
// Created by kendricks on 12/7/23.
//

#include "units.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    units_get_metadata_of_unit(unit_add(&OHM, &SECOND));
    return 0;
}
