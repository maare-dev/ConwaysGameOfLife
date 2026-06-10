#/bin/bash

src=(
    "src/main.cpp"
    "src/logic/logic.cpp"
    "src/res/res.cpp"
    "src/scene/scene.cpp"
    "src/scene/scenes/game/game.cpp"
    "src/scene/scenes/menu/menu.cpp"
    "src/shell/shell.cpp"
    "src/themes/themes.cpp"
    "src/ui/button/button.cpp"
    "src/ui/panel/panel.cpp"
)
flags=(
    "-std=c++20"
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Werror"
    "-g"
)
libs=(
    "-lraylib"
)
oname='life_0.0.1'

g++ "${flags[@]}" -o "$oname" "${src[@]}" "${libs[@]}" || exit 1

run=''
read -r -p "run? (Y/n)" run
case "$run" in
    ""|[Yy])
        clear
        "./$oname"
        ;;
    *)
        echo "cancelled"
        ;;
esac
