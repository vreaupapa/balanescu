compile: build run

build:
	gcc ./src/main.c -o ./out/sdl_game.exe -lSDL3 -lSDL3_image

run:
	cmd /c out\sdl_game.exe