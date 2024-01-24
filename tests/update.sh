#!/bin/bash

# this script will update the test_suite to include any
# newly added modules and directories.
# For each directory, there will be a corresponding header
# and source file of the name: test_suite_(DIRNAME)
# This header will have an include_test_suite__(DIRNAME)
# function that takes an MunitSuite pointer, and establishes
# the MunitSuite fields to correspond to the dirname test_suite.
#
# Each source file will have its own test_suite which is
# a sub_suite automatically added to the dirname test suite.
# If a test_suite source file for the original source file
# is generated, it will include a #warning to inform the
# source maintainer to write tests for their newly added module.
#
# For every bash function call to update(...) there should be
# a directory in ./tests/ with an ./include and ./source

export ancientsgame_base_dir=$(realpath "../")
export ancientsgame_core_dir=$(realpath "../core/source")
export ancientsgame_nds_dir=$(realpath "../nds/source")
export ancientsgame_unix_opengl_dir=$(realpath "../unix_opengl/source")

update () {
    ./update_recursive.sh \
        $ancientsgame_core_dir \
        "" \
        $(realpath "./core/include") \
        $(realpath "./core/source")
}

update 
