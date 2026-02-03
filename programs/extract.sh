#!/bin/bash

for z in *.zip; do
    zipname="${z%.zip}"     # remove .zip
    base="${zipname%.c}"    # remove trailing .c if present

    # Try extracting main.cpp
    if unzip -o -j "$z" "main.cpp" >/dev/null 2>&1; then
        mv -f main.cpp "$base.cpp"

    # Else try extracting main.c
    elif unzip -o -j "$z" "main.c" >/dev/null 2>&1; then
        mv -f main.c "$base.c"
    fi
done

