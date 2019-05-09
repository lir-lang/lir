CC=g++
STD=c++17


WFLAGS=-Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wundef -Wno-unused


CFLAGS=-Ofast -msse2 -march=native -finline-limit=100 -fipa-pta -m64 -fwhole-program -fsplit-loops -funswitch-loops --static



LFLAGS=-flto -Wl,--as-needed -lm -lc -lgcc -lc --static

INCLUDE=-I src -I .
LIBS=
BUILD_DIR=build
TARGET=lir


all:
	mkdir -p $(BUILD_DIR)
	$(CC) --std=$(STD) $(WFLAGS) $(CFLAGS) $(INCLUDE) -c main.cpp -o $(BUILD_DIR)/main.o

	$(CC) --std=$(STD) $(WFLAGS) $(LIBS) $(CFLAGS) $(LFLAGS) $(INCLUDE) build/*.o -o $(BUILD_DIR)/$(TARGET)


gen:
	mkdir -p $(BUILD_DIR)
	$(CC) --std=$(STD) $(WFLAGS) -fprofile-generate -fprofile-dir=build/ $(CFLAGS) $(INCLUDE) -c main.cpp -o $(BUILD_DIR)/main.o

	$(CC) --std=$(STD) $(WFLAGS) $(LIBS) -fprofile-generate -fprofile-dir=build/ $(CFLAGS) $(LFLAGS) $(INCLUDE) build/*.o -o $(BUILD_DIR)/$(TARGET)


use:
	mkdir -p $(BUILD_DIR)
	$(CC) --std=$(STD) $(WFLAGS) -fprofile-use $(CFLAGS) $(INCLUDE) -c main.cpp -o $(BUILD_DIR)/main.o

	$(CC) --std=$(STD) $(WFLAGS) $(LIBS) -fprofile-use $(CFLAGS) $(LFLAGS) $(INCLUDE) build/*.o -o $(BUILD_DIR)/$(TARGET)





prof:
	mkdir -p $(BUILD_DIR)
	$(CC) --std=$(STD) $(WFLAGS) -Og -g $(INCLUDE) -c main.cpp -o $(BUILD_DIR)/main.o

	$(CC) --std=$(STD) $(WFLAGS) $(LIBS) -Og -g $(LFLAGS) $(INCLUDE) build/*.o -o $(BUILD_DIR)/$(TARGET)

