CC= g++

program_name= server

INC_FLAGS = -Iinclude -I../logger/include

CPP_FLAGS = $(INC_FLAGS) 

SRC_DIR=src
BUILD_DIR=build
OBJ_DIR=obj

SRC_LIST= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST= $(SRC_LIST:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
LOGGER_OBJ = ../logger/obj/my_logger.o


$(BUILD_DIR)/$(program_name): $(OBJ_LIST) $(LOGGER_OBJ) | $(BUILD_DIR)
	$(CC) -o $@ $^ $(CPP_FLAGS)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CPP_FLAGS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)