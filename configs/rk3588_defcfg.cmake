set(RMM_PLATFORM "rk3588" CACHE STRING "platform")
arm_config_option_override(NAME RMM_TOOLCHAIN DEFAULT "gnu")

arm_config_option_override(NAME RMM_MAX_SIZE DEFAULT 0x25ff000)

arm_config_option_override(NAME PLAT_CMN_CTX_MAX_XLAT_TABLES DEFAULT 80)

arm_config_option_override(NAME ENABLE_OPENCCA DEFAULT 1)

arm_config_option_override(NAME ENABLE_OPENCCA_PERF DEFAULT 0)

# XXX: We currently limit the RMM addressable memory to first 4GB
arm_config_option_override(NAME RMM_MAX_GRANULES DEFAULT 0x100000)

arm_config_option_override(NAME RMM_NUM_PAGES_PER_STACK DEFAULT 5)

arm_config_option_override(NAME RMM_FPU_USE_AT_REL2 DEFAULT OFF)

