add_library(rmm-lib-opencca INTERFACE)

target_include_directories(rmm-lib-opencca
    INTERFACE "include" )


arm_config_option(
    NAME ENABLE_OPENCCA
    HELP "Enable OpenCCA"
    TYPE BOOL
    DEFAULT OFF)

arm_config_option(
    NAME ENABLE_OPENCCA_PERF
    HELP "Enable OpenCCA Performance Counter Measurements"
    TYPE BOOL
    DEFAULT OFF)

target_compile_definitions(rmm-lib-opencca
    INTERFACE "ENABLE_OPENCCA=${ENABLE_OPENCCA}"
    INTERFACE "ENABLE_OPENCCA_PERF=${ENABLE_OPENCCA_PERF}") 


if (ENABLE_OPENCCA EQUAL 0x1)
    message (INFO "Building for opencca")
endif()

if (ENABLE_OPENCCA_PERF EQUAL 0x1)
    message (INFO "Building for opencca_perf options")
endif()