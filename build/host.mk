ifeq ($(HOST), DEFAULT)
	ifeq ($(OS), Windows_NT)
		HOST = WINDOWS
	else
		ifeq ($(shell uname -s), Linux)
			HOST = LINUX
		endif
		ifeq ($(shell uname -s), Darwin)
			HOST = OSX
		endif
	endif
endif

ifeq ($(HOST), LINUX)
	RM = rm
	RMDIR = rm -rf
	ECHO = echo -e
	CD = cd
	AND = &&
	MKDIR = mkdir
	
	HOST_LIB_PREFIX = lib
	HOST_STATIC_LIB_SUFFIX = .host.a
	HOST_DYNAMIC_LIB_SUFFIX = .host.so
	HOST_EXECUTABLE_SUFFIX = .host.out
	HOST_OBJECT_SUFFIX = .host.o

	HOST_GLOBAL_CFLAGS += -fPIC

	HOST_DYNAMIC_LIB_TOOL = $(HOST_CLINKER) -shared $(HOST_GLOBAL_LFLAGS) $(addprefix -L,$(HOST_LIBDIRS)) $(HOST_LFLAGS) -o $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
	HOST_STATIC_LIB_TOOL = $(AR) -r -c $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
	HOST_INTERNAL_EXECUTABLE_TOOL_LFLAG := -Wl,-rpath,
	HOST_EXECUTABLE_TOOL = $(HOST_CLINKER) -fPIE $(HOST_GLOBAL_LFLAGS) $(addprefix -L,$(HOST_LIBDIRS)) $(addprefix $(HOST_INTERNAL_EXECUTABLE_TOOL_LFLAG),$(HOST_LIBDIRS)) $(HOST_LFLAGS) -o $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
endif

ifeq ($(HOST),OSX)
	RM = rm
	RMDIR = rm -rf
	ECHO = echo
	CD = cd
	AND = &&
	MKDIR = mkdir

	HOST_LIB_PREFIX = lib
	HOST_STATIC_LIB_SUFFIX = .host.a
	HOST_DYNAMIC_LIB_SUFFIX = .dylib
	HOST_EXECUTABLE_SUFFIX = .host.out
	HOST_OBJECT_SUFFIX = .host.o

	HOST_GLOBAL_CFLAGS += -fPIC

	HOST_DYNAMIC_LIB_TOOL = $(HOST_CLINKER) -dynamiclib $(HOST_GLOBAL_LFLAGS) $(addprefix -L,$(HOST_LIBDIRS)) $(HOST_LFLAGS) -install_name "@rpath/$(notdir $@)" -o $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
	HOST_STATIC_LIB_TOOL = $(AR) -r -c $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
	HOST_INTERNAL_EXECUTABLE_TOOL_LFLAG := -Wl,-rpath,
	HOST_EXECUTABLE_TOOL = $(HOST_CLINKER) -fPIE $(HOST_GLOBAL_LFLAGS) $(addprefix -L,$(HOST_LIBDIRS)) $(addprefix $(HOST_INTERNAL_EXECUTABLE_TOOL_LFLAG),$(HOST_LIBDIRS)) $(HOST_LFLAGS) -o $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
endif

ifeq ($(HOST), WINDOWS)
	RM = del
	RMDIR = rmdir
	ECHO = echo
	CD = cd
	AND = &&
	MKDIR = mkdir

	HOST_LIB_PREFIX =
	HOST_STATIC_LIB_SUFFIX = .lib
	HOST_DYNAMIC_LIB_SUFFIX = .dll
	HOST_EXECUTABLE_SUFFIX = .exe
	HOST_OBJECT_SUFFIX = .host.obj

	HOST_DYNAMIC_LIB_TOOL = $(HOST_CLINKER) -shared $(HOST_GLOBAL_LFLAGS) $(addprefix -L,$(HOST_LIBDIRS)) $(HOST_LFLAGS) -o $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
	HOST_STATIC_LIB_TOOL = $(AR) -r -c $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
	HOST_EXECUTABLE_TOOL = $(HOST_CLINKER) -fPIE $(HOST_GLOBAL_LFLAGS) $(addprefix -L,$(HOST_LIBDIRS)) $(HOST_LFLAGS) -o $@ $(filter %$(HOST_OBJECT_SUFFIX),$^)
endif
