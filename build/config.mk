# Set build host platform
# `DEFAULT`: Detect OS
# `LINUX`: Linux
# `OSX`: macOS
# `WINDOWS`: Windows
HOST ?= DEFAULT

# Set the build target architecture for Alonira
# `x86_64`: Target x86_64
ARCH ?= x86_64

# Sets the boot protocol to use
# `ULTRA`: Use the Ultra boot protocol and HyperLoader. Only compatible with `TARGET=x86_64`
BOOT_PROTOCOL ?= ULTRA

# Set build mode
# `DEBUG`: Includes debug symbols and disables optimizations
# `RELEASE`: Excludes debug symbols and enables optimizations
MODE ?= DEBUG

# The clang command to use
CLANG ?= clang

# The nasm command to use
NASM ?= nasm

# The lld command to use
LLD ?= lld

# The ar command to use
AR ?= ar

# The xorriso command to use
XORRISO ?= xorriso

# Extra compiler flags to apply to all host sources
HOST_EXTRA_CFLAGS ?=

# Extra linker flags to apply to all host binaries
HOST_EXTRA_LFLAGS ?=

# Extra compiler flags to apply to all target sources
TARGET_EXTRA_CFLAGS ?=

# Extra linker flags to apply to all target binaries
TARGET_EXTRA_LFLAGS ?=
