# Compiler
CC = cc
CFLAGS = -Wall -Wextra -pedantic

# Libraries
LIBS = -lGL -lm -lpthread -ldl -lrt -lX11

# Files
OBJ = main.o noise_utils.o gradient_noise.o

# Check for raylib
RAYLIB_DIR := raylib
RAYLIB_LIB := $(RAYLIB_DIR)/src/libraylib.a
# pkg config returns 0 if raylib is found so the conditional evaluates false
ifeq ($(shell pkg-config --exists raylib && echo yes),)
	# Second check: if the static library is found in the specified directory
	ifeq ($(shell test -e $(RAYLIB_LIB) && echo yes),yes)
		$(info Raylib static library found, using it...)
		LIBS += -L$(RAYLIB_DIR)/src -lraylib
		CFLAGS += -I$(RAYLIB_DIR)/src
	else
		# Clone and build raylib if it's not found
		raylib:
			git clone --depth=1 https://github.com/raysan5/raylib.git
			cd raylib/src && make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=STATIC
		LIBS += -L$(RAYLIB_DIR)/src -lraylib
		CFLAGS += -I$(RAYLIB_DIR)/src
	endif
else
	CFLAGS += -DRAYLIB_FOUND
	LIBS += -lraylib
endif

# Check for xxHash
XXHASH_DIR := xxHash
XXHASH_LIB := $(XXHASH_DIR)/libxxhash.a
# pkg config returns 0 if x is found so the conditional evaluates false
ifeq ($(shell pkg-config --exists xxHash && echo yes),)
	# Second check: if the static library is found in the specified directory
	ifeq ($(shell test -e $(XXHASH_LIB) && echo yes),yes)
		LIBS += -L$(XXHASH_DIR)/src -lxxhash
		CFLAGS += -I$(XXHASH_DIR)/src
	else
		# Clone and build raylib if it's not found
		xxHash:
			git clone --depth=1 https://github.com/raysan5/raylib.git
			cd raylib/src && make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=STATIC
		LIBS += -L$(XXHASH_DIR)/src -lxxhash
		CFLAGS += -I$(XXHASH_DIR)/src
	endif
else
	CFLAGS += -DXXHASH_FOUND
	LIBS += -lxxhash
endif

output: $(OBJ)
	$(CC) $(OBJ) -o output $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# main.o: main.c
# 	$(CC) -c main.c $(CFLAGS)
#
# gradient_noise.o: gradient_noise.c gradient_noise.h
# 	$(CC) -c gradient_noise.c $(CFLAGS)
#
# noise_utils.o: noise_utils.c noise_utils.h
# 	$(CC) -c noise_utils.c $(CFLAGS)

clean:
	rm *.o
	rm output
