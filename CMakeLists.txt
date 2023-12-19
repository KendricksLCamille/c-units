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
        quantity/csi_quantity.h
        quantity/csi_quantity.c
        unit/csi_unit.c
        units_pointer_support.h
        units_pointer_support.c
        csi_configuration.h
        unit/csi_unit_implementation.h
        unit/csi_unit.h
)