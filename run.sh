#!/bin/bash
gcc -o main main.c gestionGraphique.c -Iinclude -Llib -lSDL2 -lSDL2_ttf
if [ $? -ne 0 ]; then
    exit $?
fi
./main


# chmod +x run_mac.sh
# ./run.sh