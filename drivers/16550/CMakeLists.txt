add_library(rmm-driver-16550)

target_link_libraries(rmm-driver-16550
    PRIVATE rmm-lib)

target_include_directories(rmm-driver-16550
    PUBLIC "include"
    PRIVATE "src/include")

target_sources(rmm-driver-16550
    PRIVATE "src/16550_console.S")
