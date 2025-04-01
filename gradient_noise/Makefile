# Compiler
CC = cc
CFLAGS = -Wall -Wextra -pedantic

# Libraries
LIBS = -lGL -lm -lpthread -ldl -lrt -lX11

# Files
OBJ = main.o noise_utils.o gradient_noise.o

# Checking for xxHash
XXHASH_DIR := xxHash

ifeq ($(shell pkg-config --exists libxxhash && echo yes),yes)
# xxhash is installed system-wide
XXHASH_EXISTS := 1
CFLAGS += -DXXHASH_FOUND
LIBS += -lxxhash

else ifeq ($(shell test -e $(XXHASH_DIR)/libxxhash.a && echo yes),yes)
# xxhash is statically built
XXHASH_EXISTS := 2
CFLAGS += -I $(XXHASH_DIR)
LIBS += -L $(XXHASH_DIR) -lxxhash

else
# xxHash isn't found
XXHASH_EXISTS := 0
CFLAGS += -I $(XXHASH_DIR)
LIBS += -L $(XXHASH_DIR) -lxxhash

endif

# Checking for raylib
RAYLIB_DIR := raylib

ifeq ($(shell pkg-config --exists raylib && echo yes),yes)
# raylib is installed system-wide
RAYLIB_EXISTS := 1
CFLAGS += -DRAYLIB_FOUND
LIBS += -lraylib

else ifeq ($(shell test -e $(RAYLIB_DIR)/src/libraylib.a && echo yes),yes)
# raylib is statically built
RAYLIB_EXISTS := 2
CFLAGS += -I $(RAYLIB_DIR)/src
LIBS += -L $(RAYLIB_DIR)/src -lraylib

else
# raylib isn't found
RAYLIB_EXISTS := 0
CFLAGS += -I $(RAYLIB_DIR)/src
LIBS += -L $(RAYLIB_DIR)/src -lraylib

endif

output: build_xxhash build_raylib $(OBJ)
	$(CC) $(OBJ) -o output $(LIBS)
	@echo "Succesfully built. To execute run ./output"

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

build_xxhash:
	@echo checking for xxHash...
ifeq ($(XXHASH_EXISTS), 1)
	@echo xxHash installed on the system
else ifeq ($(XXHASH_EXISTS), 2)
	@echo xxHash statically built
else ifeq ($(XXHASH_EXISTS), 0)
	@read -p "xxHash not found, do you want to build it from source? (Y/n) " choice; \
	if [ "$$choice" == "y" ] || [ "$$choice" == "" ]; then \
		git clone --depth=1 https://github.com/Cyan4973/xxHash.git; \
		cd xxHash && make; \
	else \
		echo "Aborting build"; \
		exit 1; \
	fi
endif

build_raylib:
	@echo checking for raylib...
ifeq ($(RAYLIB_EXISTS), 1)
	@echo raylib installed on the system
else ifeq ($(RAYLIB_EXISTS), 2)
	@echo raylib statically built
else ifeq ($(RAYLIB_EXISTS), 0)
	@read -p "raylib not found, do you want to build it from source? (Y/n) " choice; \
	if [ "$$choice" == "y" ] || [ "$$choice" == "" ]; then \
		git clone --depth=1 https://github.com/raysan5/raylib.git; \
		cd raylib/src && make PLATFORM=PLATFORM_DESKTOP XXHASH_LIBTYPE=STATIC; \
	else \
		echo "Aborting build"; \
		exit 1; \
	fi
endif

clean:
	@if ls *.o 1> /dev/null 2>&1; then \
		echo "Removing binary and object files..."; \
		rm output; \
		rm *.o; \
	fi
	@read -p "Do you also want to remove the statically built libraries? (y/N) " choice; \
	if [ "$$choice" == "y" ]; then \
		rm -fr xxHash; \
		rm -fr raylib; \
	fi
