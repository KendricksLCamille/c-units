cmake_minimum_required(VERSION 3.27)
project(c_units C)
add_compile_options(-Wall -Wextra #[[-Werror]] -pedantic -Wshadow -Wconversion -Wcast-qual -Wformat=2 -ftrapv)

set(CMAKE_C_STANDARD 23)

# Enable testing for the project
add_executable(csi main.c
        units_quantity.c
        prefix/csi_prefix.h
        lib/sds-master/sds.c
        prefix/csi_prefix.c
        units_si_base_unit_type.h
        units_si_base_unit_type.c
        units_dimmension.h
        units_dimmension.c
        units_pointer_support.h
        units_pointer_support.c
        csi_configuration.h
)