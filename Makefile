
# Assignment operators in Makefile:
# 	Note: all variables work as inline subsitution.
# "=" 	- 	Recursive assignment. If there are variables referenced in the RValue
# 			then when the assigned variable is used, it will recursively evaluate
# 			the RValue at the time of inlining.
#
# ":="	-	Literal assignment. Any and all variables in the RValue is subsituted
# 			at the time of assignment. No recurison will happen when inlining this
# 			assigned variable.
#
# "!="	-	Shell assignment. This will treat the RValue is a shell command and run it.
# 			The output then becomes the RValue.

.PHONY: nds test_nds unix_opengl test_unix_opengl clean

export BASE_DIR := $(CURDIR)

export SILENT := @

export BUILD_NDS := $(CURDIR)/build/nds
export BUILD_UNIX_OPENGL := $(CURDIR)/build/unix_opengl

default:
	echo 'I deleted the Makefile. TODO: make default target print a target specification menu.'

nds:
	$(SILENT)mkdir -p ./build && make -C $(CURDIR)/nds -f $(CURDIR)/nds/Makefile -e BUILD=$(BUILD_NDS)

test_nds:
	$(SILENT)mkdir -p ./build && make -C $(CURDIR)/nds -f $(CURDIR)/nds/Makefile -e BUILD=$(CURDIR)/build/test_nds

unix_opengl:
	$(SILENT)mkdir -p ./build && make -C $(CURDIR)/unix_opengl -f $(CURDIR)/unix_opengl/Makefile -e BUILD=$(BUILD_UNIX_OPENGL)

test_unix_opengl:
	$(SILENT)mkdir -p ./build && make -C $(CURDIR)/unix_opengl -f $(CURDIR)/unix_opengl/Makefile -e BUILD=$(CURDIR)/build/test_unix_opengl

clean:
	rm -r ./build/*
