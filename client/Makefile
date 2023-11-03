CC= g++

program_name= client

INC_FLAGS = -Iinclude

CPP_FLAGS = $(INC_FLAGS) -MMD -MP

SRC_DIR=src
BUILD_DIR=build
OBJ_DIR=obj

SRC_LIST= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST= $(SRC_LIST:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


$(BUILD_DIR)/$(program_name): $(OBJ_LIST)
	$(CC) -o $@ $^ $(CPP_FLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	$(CC) -c -o $@ $< $(CPP_FLAGS)

clean:
	rm -f $(OBJ_DIR)/* $(BUILD_DIR)/*