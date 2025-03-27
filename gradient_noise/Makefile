# Compiler
CC = cc
CFLAGS = -Wall -Wextra -pedantic

# Libraries
LIBS = -lGL -lm -lpthread -ldl -lrt -lX11

# Files
OBJ = main.o noise_utils.o gradient_noise.o

# Check for raylib
RAYLIB_EXISTS = 0
RAYLIB_DIR := raylib
RAYLIB_LIB := $(RAYLIB_DIR)/src/libraylib.a

# First, check if pkg-config can find raylib
ifeq ($(shell pkg-config --exists raylib && echo yes),yes)
	RAYLIB_EXISTS = 1
	CFLAGS += $(shell pkg-config --cflags raylib)
	LIBS += $(shell pkg-config --libs raylib)
else
	# Second check: check if the static library exists
	ifeq ($(shell test -e $(RAYLIB_LIB) && echo yes),yes)
		RAYLIB_EXISTS = 1
		CFLAGS += -I$(RAYLIB_DIR)/src
		LIBS += -L$(RAYLIB_DIR)/src -lraylib
	endif
endif

# Add a flag if raylib is found
ifeq ($(RAYLIB_EXISTS), 1)
	CFLAGS += -DRAYLIB_FOUND
endif

# Check for xxHash
XXHASH_EXISTS = 0
XXHASH_DIR := xxHash
XXHASH_LIB := $(XXHASH_DIR)/libxxhash.a

# First, check if pkg-config can find xxhash
ifeq ($(shell pkg-config --exists libxxhash && echo yes),yes)
	XXHASH_EXISTS = 1
	CFLAGS += $(shell pkg-config --cflags lxxhash)
	LIBS += $(shell pkg-config --libs lxxhash)
else
	# Second check: check if the static library exists
	ifeq ($(shell test -e $(XXHASH_LIB) && echo yes),yes)
		XXHASH_EXISTS = 1
		CFLAGS += -I$(XXHASH_DIR)
		LIBS += -L$(XXHASH_DIR) -lxxhash
	endif
endif

# Add a flag if xxhash is found
ifeq ($(XXHASH_EXISTS), 1)
	CFLAGS += -DXXHASH_FOUND
endif

output: $(OBJ) build_raylib build_xxhash
	$(CC) $(OBJ) -o output $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

build_raylib:
	@if [ $(RAYLIB_EXISTS) -eq 1 ]; then \
		echo "raylib is installed on the system"; \
	else \
		echo "raylib is not installed, building from source"; \
		git clone --depth=1 https://github.com/raysan5/raylib.git; \
		cd raylib/src && make PLATFORM=PLATFORM_DESKTOP XXHASH_LIBTYPE=STATIC; \
	fi


build_xxhash:
	@if [ $(XXHASH_EXISTS) -eq 1 ]; then \
		echo "xxhash is installed on the system"; \
	else \
		echo "xxhash is not installed, building from source"; \
		git clone --depth=1 https://github.com/Cyan4973/xxHash.git; \
		cd xxHash && make; \
	fi


clean:
	rm *.o
	rm output
