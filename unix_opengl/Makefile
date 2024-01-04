
.PHONY: COPY_CFILES

ifneq ($(BUILD),$(CURDIR))

# I pulled the majority of the following from
# NDS Minicraft's makefile
export CC := gcc
export LD := $(CC)

include $(BASE_DIR)/core/Makefile.include
export SOURCE_UNIX_OPENGL := $(CURDIR)/source

export CFILES_UNIX_OPENGL != realpath --relative-to=$(SOURCE_UNIX_OPENGL) $$(find $(SOURCE_UNIX_OPENGL) -name *.c)
export OFILES_UNIX_OPENGL := $(CFILES_UNIX_OPENGL:.c=.o)
export OFILES := $(OFILES_CORE) $(OFILES_UNIX_OPENGL)

export INCLUDES := $(INCLUDE_CORE) $(CURDIR)/include
export LIBS		:= -lm -ldl -lGL -lGLU -lGLEW -lglfw

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
# we will probably just put this after SOURCE_UNIX_OPENGL above, and that will be
# where we add opengl libraries and etc.
export INCLUDE := \
  $(foreach dir,$(INCLUDES),-I$(dir)) \
  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
  -I$(ASSETS) \
  -I$(BUILD)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

ifneq ($(GENERATE_COMPILE_COMMANDS), 1)

$(BUILD):
	$(SILENTCMD)mkdir -p $(BUILD)
	$(SILENTCMD)make -C $(BUILD) -f $(CURDIR)/Makefile

else

$(BUILD):
	$(SILENTCMD)mkdir -p $(BUILD)
	$(SILENTCMD)make -C $(BUILD) -f $(CURDIR)/Makefile \
		-e GENERATE_COMPILE_COMMANDS=0 --always-make --dry-run \
		| grep -wE 'cc|gcc' \
		| grep -w '\-c' \
		| jq -nR '[inputs|{directory:".", command:., file: match("(?<=-c).*").string[1:-1]}]' \
		> $(BUILD)/compile_commands.json
endif 

else

# I made this going off of /opt/devkitpro/devkitARM/base_rules
ancients_game: $(OFILES) $(SPRITE_FILES)
	$(SILENT)$(LD) $(LDFLAGS) $(FLAGS_LINKER) $(OFILES) $(LIBPATHS) $(LIBS) -o $@

$(OFILES_UNIX_OPENGL):
	$(SILENTCMD)mkdir -p $(BUILD)/$$(dirname $@)
	$(SILENTCMD)$(CC) $(LIBS) $(INCLUDE) $(FLAGS) -o $(BUILD)/$@ -c $(SOURCE_UNIX_OPENGL)/$(@:.o=.c) 

include $(BASE_DIR)/core/Makefile.build

endif
