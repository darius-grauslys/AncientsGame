#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/ds_rules

GAME_TITLE := AncientsGame 
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

export INCLUDES := $(INCLUDE_CORE) $(BASE_DIR)/nds/include

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

export SHARED_SPRITE_FILES := $(foreach sprite_dir,$(SPRITE_DIRS),$(sprite_dir)/GFX_$(shell basename $(sprite_dir)).o)

export OFILES := \
	$(PALETTE_FILES:.grit=.o) \
	$(SPRITE_FILES:.png=.o) \
	$(SHARED_SPRITE_FILES) \
	$(addsuffix .o,$(BINFILES)) \
	$(OFILES_CORE) $(OFILES_NDS)

export INCLUDE := \
  $(foreach dir,$(INCLUDES),-I$(dir)) \
  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
  -I$(BUILD)/$(ASSETS)\
  -I$(BUILD)

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
	$(CC) $(CFLAGS) $(INCLUDE) $(FLAGS) \
		-o $@ -c $(BASE_DIR)/nds/source/$(basename $@).c
	$(ADD_COMPILE_COMMAND) add $(CC) "$(CFLAGS) $(INCLUDE) $(FLAGS) \
		-o $@ -c $(BASE_DIR)/nds/source/$(basename $@).c" $@
#---------------------------------------------------------------------------------

include $(BASE_DIR)/core/Makefile.build

$(SPRITE_DIRS): 
	@mkdir -p $@
	cd $@ && grit $(shell find $(BASE_DIR)/core/$@ -iname *.png) \
		-ff$(BASE_DIR)/nds/$@/$(shell basename $@).grit
$(SHARED_SPRITE_FILES):
	cd $(shell dirname $@) && $(CC) $(CFLAGS) -c $(shell basename $(basename $@)).s -o $(shell basename $(basename $@)).o

#---------------------------------------------------------------------------------
$(SPRITE_FILES:.png=.o) : $(SPRITE_DIRS) $(foreach file,$(SPRITE_FILES),$(BASE_DIR)/core/$(file)) 
	$(CC) $(CFLAGS) -c $(basename $@).s -o $(basename $@).o
	$(ADD_COMPILE_COMMAND) add $(CC) "$(CFLAGS) -x assembler-with-cpp $(ASFLAGS) \
		-c $(basename $@).s -o $@" $(basename $@).s
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
soundbank.bin soundbank.h : $(foreach file,$(AUDIO_FILES),../$(file))
	@mmutil $^ -d -osoundbank.bin -hsoundbank.h
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
%.bin.o %_bin.h : %.bin
	@echo $(notdir $<)
	@$(bin2o)
#---------------------------------------------------------------------------------

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
