cmake_minimum_required(VERSION 3.27)
project(c_units C)

set(CMAKE_C_STANDARD 23)

add_executable(c_units main.c
        units.c
        units_si_prefix.h
        lib/sds-master/sds.c
        units_si_prefix_imp.h
        units_si_base_unit_type.h
        units_si_base_unit_type.c
        units_dimmension.h
        units_dimmension.c)
