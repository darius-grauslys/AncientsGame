
# I pulled the majority of the following from
# NDS Minicraft's makefile
CC := gcc
LD := $(CC)

SOURCE := $(CORE) $(BACKEND)

export CFILES        := $(shell find $(SOURCE) -name *.c)
export OFILES := \
  $(CFILES:.c=.o)

INCLUDES 	:= $(CORE)/include $(BACKEND)/include
LIBS		:= -lGL -lGLU

# Syntax highlighting suggests that we're using the Makefile dir builtin
# right here, but that's not the case. Notice, we have "foreach dir" so
# the variable dir shadows the builtin.
#
# TODO: currently, we don't establish the $(INCLUDES), which should be
# core/include and BACKEND/include - it should also be resolved with
# $(shell find ...) since we have subfolders in the includes.
#
# TODO: currently, we don't establish the $(LIBDIRS) either. For now
# we will probably just put this after SOURCE above, and that will be
# where we add opengl libraries and etc.
export INCLUDE := \
  $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
  -I$(CURDIR)/$(BUILD)/$(ASSETS)\
  -I$(CURDIR)/$(BUILD)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

# I made this going off of /opt/devkitpro/devkitARM/base_rules
ancients_game.exe: $(OBJS)/$(notdir $(OFILES))
	$(SILENT)$(LD)  $(LDFLAGS) $(OBJS)/$(notdir $(OFILES)) $(LIBPATHS) $(LIBS) -o $@

# I made this going off of /opt/devkitpro/devkitARM/base_rules
%.o: %.c
	$(SILENT)$(CC) -MMD -MP -MF $(OBJS)/$*.d $(CFLAGS) -c $< -o $@ $(ERROR_FILTER)
	# $(ADD_COMPILE_COMMAND) add $(CC) "$(CPPFLAGS) $(CFLAGS) -c $< -o $@" $<
