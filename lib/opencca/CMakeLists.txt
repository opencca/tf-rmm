add_library(rmm-lib-opencca INTERFACE)

target_include_directories(rmm-lib-opencca
    INTERFACE "include" )


arm_config_option(
    NAME ENABLE_OPENCCA
    HELP "Enable OpenCCA"
    TYPE BOOL
    DEFAULT OFF)


target_compile_definitions(rmm-lib-opencca
    INTERFACE "ENABLE_OPENCCA=${ENABLE_OPENCCA}") 


if (ENABLE_OPENCCA EQUAL 0x1)
    message (INFO "Building for opencca")
endif()