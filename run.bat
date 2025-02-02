:: filepath: /c:/Users/nearl/projects/sdl_test/build_and_run.bat
@echo off
gcc -o main main.c gestionGraphique.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
if %errorlevel% neq 0 exit /b %errorlevel%
main