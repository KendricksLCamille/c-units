//
// Created by kendricks on 12/7/23.
//


#include <assert.h>
#include <stdio.h>

#include "csi_measurement.h"
#include "csi_unit.h"


int main()
{
    csi_measurment* one_meter = csi_measurment_create(1, &METER);
    csi_measurment* two_meter = unit_add(one_meter, one_meter);
    assert(csi_measurment_magnitude(two_meter) == 2);

    csi_measurment* one_kilometer = csi_measurment_create(1, csi_unit_with_prefix(&METER, &UNIT_KILO));
    csi_measurment* one_thousand_and_one_meter = unit_add(one_meter, one_kilometer);
    assert(csi_measurment_magnitude(one_thousand_and_one_meter) == 1001);
    return 0;
}
