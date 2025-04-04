compile: build run

build:
	gcc $(wildcard src/*.c)  -o ./out/sdl_game.exe -lSDL3 -lSDL3_image -lSDL3_ttf

run:
	cmd /c out\sdl_game.exe