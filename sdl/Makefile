
.PHONY: $(BUILD) COPY_CFILES

ifneq ($(BUILD),$(CURDIR))

# I pulled the majority of the following from
# NDS Minicraft's makefile
export CC := gcc
export LD := $(CC)

include $(BASE_DIR)/core/Makefile.include
export SOURCE_SDL := $(CURDIR)/source

export CFILES_SDL != realpath --relative-to=$(SOURCE_SDL) $$(find $(SOURCE_SDL) -name *.c)
export OFILES_SDL := $(CFILES_SDL:.c=.o)
export OFILES := $(OFILES_CORE) $(OFILES_SDL)

export INCLUDES := $(INCLUDE_CORE) $(BASE_DIR)/sdl/include
export LIBS		:= -lm -ldl -lGL -lGLEW -lSDL2 -lcglm

export DEPSDIR := $(BUILD)

# Syntax highlighting suggests that we're using the Makefile dir builtin
# right here, but that's not the case. Notice, we have "foreach dir" so
# the variable dir shadows the builtin.
#
# TODO: currently, we don't establish the $(INCLUDES), which should be
# core/include and BACKEND/include - it should also be resolved with
# $(shell find ...) since we have subfolders in the includes.
#
# TODO: currently, we don't establish the $(LIBDIRS) either. For now
# we will probably just put this after SOURCE_SDL above, and that will be
# where we add opengl libraries and etc.
export INCLUDE := \
  $(foreach dir,$(INCLUDES),-I$(dir)) \
  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
  -I$(ASSETS) \
  -I$(BUILD)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

$(BUILD):
	$(SILENTCMD)mkdir -p $(BUILD)
	$(SILENTCMD)make -C $(BUILD) -f $(CURDIR)/Makefile

else

# I made this going off of /opt/devkitpro/devkitARM/base_rules
ancients_game: $(OFILES) $(SPRITE_FILES)
	$(SILENT)$(LD) $(LDFLAGS) $(FLAGS_LINKER) $(OFILES) $(LIBPATHS) $(LIBS) -o $@
	@$(ADD_COMPILE_COMMAND) end

$(OFILES_SDL):
	$(SILENTCMD)mkdir -p $(BUILD)/$$(dirname $@)
	$(SILENTCMD)$(CC) $(LIBS) $(INCLUDE) $(FLAGS) -o $(BUILD)/$@ -c $(SOURCE_SDL)/$(@:.o=.c) 
	@$(ADD_COMPILE_COMMAND) add $(CC) "$(CFLAGS) $(LIBS) $(INCLUDE) $(FLAGS) \
		-o $(BUILD)/$@ -c $(SOURCE_CORE)/$(@:.o=.c)" $(BUILD)/$@

include $(BASE_DIR)/core/Makefile.build

endif
