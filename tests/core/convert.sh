export ancientsgame_base_dir=$(realpath "../../core/source")
export ancientsgame_files=$(sh -c 'cd ${ancientsgame_base_dir} && find . -iname "*.c"')

pushd "./source"

for file in $(echo $ancientsgame_files); do
    converted_name="test_$(basename $file)"
    copy_dir=$(dirname $file)
    src_file="${ancientsgame_base_dir}/${file}"
    dest_file="${copy_dir}/${converted_name}"
    mkdir -p $copy_dir
    if ! test -f $dest_file; then
        echo $dest_file
        echo "#include <$(echo $file | sed 's/\.\///')>" > $dest_file
    fi
done

popd

unset ancientsgame_base_dir
unset ancientsgame_files
