OBJ = ./bin/main.o
BIN = ./bin/main
SRC = ./src/main.c

all: build clean

run: 
	 	$(BIN)

build:	$(BIN)
		gcc $(SRC) -o $(BIN)

clean:
		rm -f $(OBJ)

help:
		@echo ---- make        -- run build clean
		@echo ---- make build  -- build ./bin/main
		@echo ---- make clean  -- clean .o files
		@echo ---- make run    -- run ./bin/main