ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

RESCOMP = windres
INCLUDES += -Isrc -I../CitrusEngine/src -I.. -I../libs/glm -I../libs -I../libs/spdlog/include
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug)
TARGETDIR = ../Build/CitrusPlayground/Debug/x86_64-linux/Binaries
TARGET = $(TARGETDIR)/CitrusPlayground
OBJDIR = ../Build/CitrusPlayground/Debug/x86_64-linux/CompilerData
DEFINES += -DCE_PLATFORM_LINUX -DCE_ENV_DEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -g -std=gnu17
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -g -std=gnu++20
LIBS += -lCitrusEngine
LDDEPS += ../Build/CitrusEngine/Debug/x86_64-linux/Binaries/libCitrusEngine.a
ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64 -L../Build/CitrusEngine/Debug/x86_64-linux/Binaries

else ifeq ($(config),release)
TARGETDIR = ../Build/CitrusPlayground/Release/x86_64-linux/Binaries
TARGET = $(TARGETDIR)/CitrusPlayground
OBJDIR = ../Build/CitrusPlayground/Release/x86_64-linux/CompilerData
DEFINES += -DCE_PLATFORM_LINUX -DCE_ENV_RELEASE
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -O2 -std=gnu17
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -O2 -std=gnu++20
LIBS += ../Build/CitrusEngine/Release/x86_64-linux/Binaries/libCitrusEngine.a
LDDEPS += ../Build/CitrusEngine/Release/x86_64-linux/Binaries/libCitrusEngine.a
ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64 -s

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/Playground.o
OBJECTS += $(OBJDIR)/Playground.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking CitrusPlayground...
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)...
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)...
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning CitrusPlayground
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) del /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/Playground.o: src/Playground.cpp
	@echo "Building C++ file $(notdir $<)..."
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) $(LIBS) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif