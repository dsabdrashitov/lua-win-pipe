OUTPUT_NAME := lua-win-pipe
DLL_NAME := winpipe

CC := g++
LIBS := lua53

BUILD_DIR := ./build
SRC_PREFIX := ./src
SRC_DIRS := $(SRC_PREFIX)
INC_DIRS := ./include
LIB_DIRS := ./lib

OUTPUT_DIR := $(BUILD_DIR)/$(OUTPUT_NAME)
OUTPUT_DLL := $(OUTPUT_DIR)/$(DLL_NAME).dll

SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
HEADERS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.h))
OBJ_PREFIX := $(BUILD_DIR)/obj
OBJS := $(patsubst $(SRC_PREFIX)/%.cpp,$(OBJ_PREFIX)/%.o,$(SRCS))

LUAS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.lua))
LUAB := $(patsubst $(SRC_PREFIX)/%.lua,$(OUTPUT_DIR)/%.lua,$(LUAS))

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
LIB_FLAGS := $(addprefix -L,$(LIB_DIRS)) $(addprefix -l,$(LIBS))
LDFLAGS := $(LIB_FLAGS)
CFLAGS := $(INC_FLAGS)

all: $(OUTPUT_DLL) $(LUAB)

just_dll: $(OUTPUT_DLL)

$(OUTPUT_DLL): $(OBJS)
	-mkdir $(subst /,\,$(dir $@))
	$(CC) -shared $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_PREFIX)/%.o: $(SRC_PREFIX)/%.cpp $(HEADERS)
	-mkdir $(subst /,\,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT_DIR)/%.lua: $(SRC_PREFIX)/%.lua
	-mkdir $(subst /,\,$(dir $@))
	copy /Y $(subst /,\,$< $@)

clean:
	-rd /s /q $(subst /,\,$(BUILD_DIR))
