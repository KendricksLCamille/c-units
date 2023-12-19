cmake_minimum_required(VERSION 3.27)
project(c_units C)
add_compile_options(-Wall -Wextra #[[-Werror]] -pedantic -Wshadow -Wconversion -Wcast-qual -Wformat=2 -ftrapv)

set(CMAKE_C_STANDARD 23)

# Enable testing for the project
add_executable(csi main.c
        csi_prefix.h
        lib/sds-master/sds.c
        implementations/csi_prefix.c
        implementations/csi_quantity.c
        implementations/csi_unit.c
        csi_configuration.h
        implementations/csi_unit_implementation.h
        csi_unit.h
        csi_measurement.h
        implementations/csi_measurement.c
        csi_quantity.h
        macro_helper.h
)