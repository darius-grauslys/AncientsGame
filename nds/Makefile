#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/ds_rules

GAME_TITLE := Minicraft DS Edition
GAME_ICON := ../icon.bmp

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS := -Wall -O2\
    -march=armv5te -mtune=arm946e-s -fomit-frame-pointer\
    -ffast-math

CFLAGS    += $(INCLUDE) -DARM9
CXXFLAGS  := $(CFLAGS) -fno-exceptions

LDFLAGS  = -specs=ds_arm9.specs -Wl,-Map,$(notdir $*.map)

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project (order is important)
#---------------------------------------------------------------------------------
LIBS := -lmm9 -lfilesystem -lfat -lnds9

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS := $(LIBNDS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(CURDIR))
#---------------------------------------------------------------------------------

include $(BASE_DIR)/core/Makefile.include

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCE is the directory containing source code
# INCLUDES is a list of directories containing extra header files
# ASSETS is the directory of assets
#---------------------------------------------------------------------------------
export TARGET  	:= $(shell basename $(BASE_DIR))
export SOURCE   := source
export DATA     := data

export INCLUDES := $(INCLUDES) $(BASE_DIR)/nds/include

export OUTPUT 	:= $(BUILD)/$(TARGET)

export DEPSDIR 	:= $(BUILD)

export CFILES_NDS	!= realpath --relative-to=$(SOURCE) $$(find $(SOURCE) -name *.c)
export CFILES 		:= $(CFILES_NDS) $(CFILES_CORE)
export SFILES       := $(shell find $(SOURCE) -name *.s)

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
  export LD := $(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
  export LD := $(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES_NDS := \
  $(CFILES_NDS:.c=.o)

export OFILES := \
	$(SPRITE_FILES:.png=.o) \
	$(addsuffix .o,$(BINFILES)) \
	$(OFILES_NDS) $(OFILES_CORE)

export INCLUDE := \
  $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
  -I$(CURDIR)/$(BUILD)/$(ASSETS)\
  -I$(CURDIR)/$(BUILD)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds

#---------------------------------------------------------------------------------
else

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

$(OUTPUT).nds : $(OUTPUT).elf
	ndstool -c $@ -9 $<

$(OUTPUT).elf : $(OFILES)

#---------------------------------------------------------------------------------
$(CFILES_NDS:.c=.o) : $(foreach file,$(CFILES_NDS),$(BASE_DIR)/nds/source/$(file))
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $(BASE_DIR)/nds/source/$(basename $@).c -o $@
#---------------------------------------------------------------------------------

include $(BASE_DIR)/core/Makefile.build

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
