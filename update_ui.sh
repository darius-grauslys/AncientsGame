print_usage() {
    printf \
    "Usage: update_ui.sh [-b BACKEND]

            -b\ttarget backend\n"
}

BACKEND=''

while getopts 'b:f' flag; do
    case "$flag" in
        b) BACKEND="$OPTARG" ;;
        \?) ;;
        *) print_usage
            exit 1 ;;
    esac
done

if [ "$BACKEND" = "" ]; then
    print_usage
    printf "\n\tREQUIRED: -b\n"
    exit 1
fi

BACKEND=$(echo $BACKEND | tr '[:upper:]' '[:lower:]')

./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__game__equip
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__game__hud
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__game__idle
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__game__labor
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__game__settings
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__game__station
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__game__trade
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__game__typer

./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__menu__main
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__menu__multiplayer
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__menu__singleplayer
./run_ui_builder.sh -d "is_visualizing false" -b ${BACKEND} -f ui_window__menu__settings
