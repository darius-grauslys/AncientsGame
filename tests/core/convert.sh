export ancientsgame_base_dir=$(realpath "../../core/source")
export ancientsgame_files=$(sh -c 'cd ${ancientsgame_base_dir} && find . -iname "*.c" -type f')

pushd "./source"

for file in $(echo $ancientsgame_files); do
    converted_name="test_suite_$(basename $file)"
    copy_dir=$(dirname $file)
    src_file="${ancientsgame_base_dir}/${file}"
    dest_file="${copy_dir}/${converted_name}"
    mkdir -p $copy_dir
    if ! test -f $dest_file; then
        echo $dest_file
        echo "#include <$(echo $file | sed 's/\.\///')>" > $dest_file
    fi

    pushd "../include"

    suite_name=$(basename $copy_dir)
    if [ "$suite_name" != "." ]; then
        suite_name=$(echo $suite_name | sed "s/${suite_name}/test_suite_&.h/")
        suite_header="${copy_dir}/${suite_name}"
        mkdir -p $copy_dir
        touch $suite_header
    fi

    popd
done

popd

touch "./include/test_suite_ancient_game.h"

unset ancientsgame_base_dir
unset ancientsgame_files   
