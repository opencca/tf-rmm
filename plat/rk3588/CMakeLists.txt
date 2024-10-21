#
# Additional config for maximum number of DRAM banks allowed to be managed
#
arm_config_option(
    NAME PLAT_ARM_MAX_DRAM_BANKS
    HELP "Maximum number of DRAM banks allowed in Arm platform layer"
    TYPE STRING
    DEFAULT 0x2)
    

add_library(rmm-plat-rk3588)

#
# Extra memory regions needed by this platform
#
arm_config_option_override(NAME PLAT_CMN_EXTRA_MMAP_REGIONS DEFAULT 1)

add_subdirectory("${RMM_SOURCE_DIR}/drivers/pl011" ${RMM_BINARY_DIR}/drivers/pl011)
add_subdirectory("${RMM_SOURCE_DIR}/plat/common" ${RMM_BINARY_DIR}/plat/common)

if(PLAT_ARM_MAX_DRAM_BANKS EQUAL 0x0)
    message(FATAL_ERROR "Invalid PLAT_ARM_MAX_DRAM_BANKS")
endif()

target_compile_definitions(rmm-plat-rk3588
    PRIVATE "PLAT_ARM_MAX_DRAM_BANKS=U(${PLAT_ARM_MAX_DRAM_BANKS})")

target_link_libraries(rmm-plat-rk3588
    PRIVATE rmm-driver-pl011
            rmm-lib
            rmm-plat-common)

target_sources(rmm-plat-rk3588
    PRIVATE "src/rk3588_setup.c"
            "src/rk3588_granule.c"
            "src/rk3588_memory.c")

target_include_directories(rmm-plat-rk3588
    PRIVATE "src/include")

add_library(rmm-platform ALIAS rmm-plat-rk3588)
