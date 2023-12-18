cmake_minimum_required(VERSION 3.27)
project(c_units C)
add_compile_options(-Wall -Wextra #[[-Werror]] -pedantic -Wshadow -Wconversion -Wcast-qual -Wformat=2 -ftrapv)

set(CMAKE_C_STANDARD 23)

# Enable testing for the project
add_executable(c_units main.c
        units_quantity.c
        units_si_prefix.h
        lib/sds-master/sds.c
        units_si_prefix.c
        units_si_base_unit_type.h
        units_si_base_unit_type.c
        units_dimmension.h
        units_dimmension.c
        units_pointer_support.h
        units_pointer_support.c
        units_configuration.h
)