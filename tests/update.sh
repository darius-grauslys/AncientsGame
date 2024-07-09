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

gen_main() {
    find $2 -iname test_suite_main.c -exec sed -i "s/#include <main.c>//" {} \;
    output="$2/main.c"
    printf "#include <MAIN_TEST_SUITE_ANCIENTS_GAME.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    MunitSuite test_suite;

    include_test_suite__ANCIENTS_GAME(&test_suite);

    return munit_suite_main(&test_suite, (void*) \"µnit\", argc, argv);
}\n" > $output
    cp ./templates/test_util.h "$1/test_util.h"
    cp ./templates/munit.h "$1/munit.h"
    cp ./templates/munit.c "$2/munit.c"
    if ! test -f "$1/platform_defines.h"; then
        cp ./templates/platform_defines.h "$1/platform_defines.h"
    fi
    if ! test -f "$2/PLATFORM.c"; then
        cp ./templates/PLATFORM.c "$2/PLATFORM.c"
    fi
}

update () {
    core_include=$(realpath "./core/include")
    core_source=$(realpath "./core/source")
    ./update_recursive.sh \
        $ancientsgame_core_dir \
        "" \
        $core_include \
        $core_source
    gen_main $core_include $core_source
}

update 
