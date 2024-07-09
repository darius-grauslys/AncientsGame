#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS := -Wall -O2
#    -march=armv5te -mtune=arm946e-s -fomit-frame-pointer\
#    -ffast-math

CFLAGS    += $(INCLUDE) #-DARM9

LDFLAGS  = 

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project (order is important)
#---------------------------------------------------------------------------------
LIBS := 

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS := 

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(CURDIR))
#---------------------------------------------------------------------------------

export CORE_OMIT := main.c
include $(DIR_CORE)/Makefile.include

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

export INCLUDES := $(SOURCE_CORE) $(INCLUDE_CORE) $(CURDIR)/include

export OUTPUT 	:= $(BUILD)/$(TARGET)

export DEPSDIR 	:= $(BUILD)

export CFILES_TEST_CORE	!= realpath --relative-to=$(SOURCE) $$(find $(SOURCE) -name *.c)
export CFILES 		:= $(CFILES_TEST_CORE)
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

export OFILES_TEST_CORE := \
  $(CFILES_TEST_CORE:.c=.o)

export OFILES := \
	$(addsuffix .o,$(BINFILES)) \
	$(OFILES_TEST_CORE)

export INCLUDE := \
  $(foreach dir,$(INCLUDES),-I$(dir)) \
  $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
  -I$(BUILD)/$(ASSETS)\
  -I$(BUILD)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	echo $(OFILES)
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

$(OUTPUT): $(OFILES)
	$(SILENT)$(LD) $(LDFLAGS) $(FLAGS_LINKER) $(OFILES) $(LIBPATHS) $(LIBS) -o $@

#---------------------------------------------------------------------------------
$(CFILES:.c=.o) : $(foreach file,$(CFILES),$(BASE_DIR)/tests/core/source/$(file))
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(FLAGS) -c $(BASE_DIR)/tests/core/source/$(basename $@).c -o $@
#---------------------------------------------------------------------------------

include $(DIR_CORE)/Makefile.build

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
