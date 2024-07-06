
print_usage() {
    printf \
    "Usage: run_ui_builder.sh <-b BACKEND> [-f UI_FILE_NAME]
        run_ui_builder.sh will use tools/ui_builder.py to generate .c and .h
        files based on the [-f UI_FILE_NAME].xml configuration.

            -b\ttarget backend
            -f\tspecific ui file to generate from
            -d\tflags to pass into ./tools/ui_builder.py\n"
}

BACKEND='NDS'
FILE_SEARCH='*'
ARGS=""

while getopts 'b:f:d:c' flag; do
    case "$flag" in
        f) FILE_SEARCH="$OPTARG" ;;
        b) BACKEND="$OPTARG" ;;
        d) ARGS="$OPTARG" ;;
        \?) ;;
        *) print_usage
            exit 1 ;;
    esac
done

if [ "$FILE_SEARCH" = "*" ]; then
    print_usage
    printf "\n\tREQUIRED: -f\n"
    exit 1
fi

if [ "$(echo $FILE_SEARCH | sed 's/[^\*]//g' | sed 's/(\*)*/\*/')" = "*" ]; then
    print_usage
    printf "\n\tERROR: cannot use wild characters in -f\n"
    exit 1
fi

BASENAME=$(basename $FILE_SEARCH)

BACKEND=$(echo $BACKEND | tr '[:upper:]' '[:lower:]')

XML=$(find ./$BACKEND -iname $BASENAME.xml)

if [ -z "$XML" ]; then
    echo Could not find $BASENAME.xml
    exit 1
fi

python ./tools/ui_builder.py $XML $ARGS &
VISUALIZER_PID=$!
if [ -z "$(echo $ARGS | grep "is_visualizing false")" ]; then
    nvim $XML &
    NVIM_PID=$!
    wait $NVIM_PID
    kill $VISUALIZER_PID
else
    wait $VISUALIZER_PID
fi
