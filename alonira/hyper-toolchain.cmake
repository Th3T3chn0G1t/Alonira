# Do this because cmake attempts to link against -lc and crt0
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if (HYPER_PLATFORM STREQUAL "uefi")
    set(HYPER_LD lld-link)
    set(HYPER_LLD_OUT_TARGET "/out:<TARGET>")
    set(HYPER_COMPILER_PREFIX x86_64-pc-win32-coff)
elseif (HYPER_PLATFORM STREQUAL "bios")
    set(HYPER_LD ld.lld)
    set(HYPER_LLD_OUT_TARGET "-o <TARGET>")
    set(HYPER_COMPILER_PREFIX i686-none-none)
else ()
    message(FATAL_ERROR "Platform ${HYPER_PLATFORM} is not supported")
endif ()

set(CMAKE_C_LINK_EXECUTABLE
    "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> \
     <LINK_FLAGS> <OBJECTS> ${HYPER_LLD_OUT_TARGET} <LINK_LIBRARIES>")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --target=${HYPER_COMPILER_PREFIX}")

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR ${HYPER_ARCH})
set(CMAKE_SYSROOT "")

set(CMAKE_C_COMPILER clang)
set(CMAKE_LINKER ${HYPER_LD})
