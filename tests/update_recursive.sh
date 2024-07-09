#!/bin/bash

#
# 5 Arguments:
# 1) The path PREFIX for the search for core files.
# 2) The path SUFFIX for the search for core files,
# So, if we are outputting for core and we're looking
# in the directory ./core/source/world
# arg 2: world
# arg 3: (path_to_AncientsGame)/tests/core/include
# arg 4: (path_to_AncientsGame)/tests/core/source
# 3) The directory path output header files will go
# to.
# 4) The directory path output source files will go
# to.
#

search_base_dir=$1
search_suffix=$2
output_base_dir__include=$3
output_base_dir__source=$4

if [ "$search_suffix" == "" ]; then
    main_suite_dir__include="${output_base_dir__include}";
    main_suite_dir__source="${output_base_dir__source}";
else
    main_suite_dir__include="${output_base_dir__include}/${search_suffix}";
    main_suite_dir__source="${output_base_dir__source}/${search_suffix}";
fi

# make sure the output directories exist.
mkdir -p $main_suite_dir__include
mkdir -p $main_suite_dir__source

# the name of the test_suite dedicated for
# the entire directory
if [ "$search_suffix" == "" ]; then
    main_suite_name="ANCIENTS_GAME"
    main_suite_name__full="MAIN_TEST_SUITE_ANCIENTS_GAME"
else
    main_suite_name=$(realpath --relative-to=$search_base_dir $search_base_dir/$search_suffix | sed "s/\//_/g")
    main_suite_name="${main_suite_name~~}"
    main_suite_name__full="MAIN_TEST_SUITE_${main_suite_name}"
fi

# the output file paths for the main test_suite
main_test_suite__header="${main_suite_dir__include}/${main_suite_name__full}.h"
main_test_suite__source="${main_suite_dir__source}/${main_suite_name__full}.c"

# always remake these above mentioned files.
printf "" > $main_test_suite__header
if [[ -z $search_suffix ]]; then
    printf "#include <${main_suite_name__full}.h>" > $main_test_suite__source
else
    printf "#include <${search_suffix}/${main_suite_name__full}.h>" > $main_test_suite__source
fi
printf "\n\nINCLUDE_SUB_SUITES(${main_suite_name}, __COUNT," \
    >> $main_test_suite__source

# the path to search modules under
search_path="${search_base_dir}/${search_suffix}"

# find all modules in the search directory
# record them as paths relative to the 
# search_base_dir
modules=$(find $search_path -maxdepth 1 -type f -iname "*.c" -exec \
    realpath {} --relative-to=$search_base_dir \;)

# the number of modules found
module_count=1
for module in $modules; do
    module_count=$((module_count+1))
    test_suite__module_name="$(basename $module)"
    test_suite__module_name__full="test_suite_$(realpath --relative-to=$search_base_dir $search_base_dir/$module | sed "s/\//_/g")"
    test_sub_suite__header="${main_suite_dir__include}/\
${test_suite__module_name__full%.*}.h"
    test_sub_suite__source="${main_suite_dir__source}/\
${test_suite__module_name__full}"
    if [[ -z $search_suffix ]]; then
        test_sub_suite__header_include="\
$(basename $test_sub_suite__header)"
    else
        test_sub_suite__header_include="\
${search_suffix}/$(basename $test_sub_suite__header)"
    fi
    if ! test -f $test_sub_suite__header; then
        printf "#include <test_util.h>

DECLARE_SUITE(${test_suite__module_name%.*})\n" > $test_sub_suite__header
        printf "#include \"$(basename $test_sub_suite__header)\"\n" \
            >> $main_test_suite__header
    fi
    if ! test -f $test_sub_suite__source; then
        printf "#include <$test_sub_suite__header_include>\n
#include <${module}>

#warning Please make tests for: ${test_sub_suite__source}

// Before writing any tests, please see the README
// found in ./tests

DEFINE_SUITE(${test_suite__module_name%.*}, END_TESTS)\n" > $test_sub_suite__source
        printf "\nINCLUDE_SUITE(${test_suite__module_name%.*})," \
            >> $main_test_suite__source
    fi
done
# find $search_path -maxdepth 1 -type d -exec realpath {} \;
subdirs=$(find $search_path -mindepth 1 -maxdepth 1 -type d -exec realpath {} \;)
for dir in $subdirs; do
    module_count=$((module_count+1))
    dir_basename=$(basename $dir)
    dir_relative_name=$(realpath --relative-to=$search_base_dir $dir | sed "s/\//_/g")
    printf "#include \"${dir_basename}/MAIN_TEST_SUITE_${dir_relative_name~~}.h\"\n" \
        >> $main_test_suite__header
    printf "\nINCLUDE_SUITE(${dir_relative_name~~})," \
        >> $main_test_suite__source
done
printf "\n#include <test_util.h>

DECLARE_SUITE(${main_suite_name});\n\n" >> $main_test_suite__header
printf "NULL);

DEFINE_SUITE_WITH__SUB_SUITES(${main_suite_name}, END_TESTS);\n\n" \
    >> $main_test_suite__source
sed -i "s/__COUNT/${module_count}/" $main_test_suite__source
for dir in $subdirs; do
    dir_basename=$(basename $dir)
    if [[ -z $search_suffix ]]; then
        sh -c "./update_recursive.sh \
            $search_base_dir \
            \"${search_suffix}${dir_basename}\" \
            \"${output_base_dir__include}\" \
            \"${output_base_dir__source}\""
    else
        sh -c "./update_recursive.sh \
            $search_base_dir \
            \"${search_suffix}/${dir_basename}\" \
            \"${output_base_dir__include}\" \
            \"${output_base_dir__source}\""
    fi
done
