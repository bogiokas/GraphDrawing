Executable = test
SRC_DIR = src
BUILD_DIR = build
LOG_DIR = log

## logging flags - uncomment if terminal gets too crowded
makeLogDir = mkdir -p $(LOG_DIR)
LOGGING = 2> $(LOG_DIR)/make_$(notdir $@).log
LOGGING_RUN = > $(LOG_DIR)/run.log
rmLogFiles = rm -f ./log/*
rmEmptyLogFiles = find . -type f -empty -delete

SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

depFlags = -MMD -MP
INC_DIRS = $(shell find $(SRC_DIR) -type d)
incFlags = $(addprefix -I, $(INC_DIRS))

CXX = g++
versionFlags = -std=c++17
warningFlags = -Wall -Wextra -Wshadow -Weffc++
openGLFlags = -lglfw -lGL -lGLEW -lX11
allFlags = $(versionFlags) $(warningFlags) $(openGLFlags) $(depFlags) $(incFlags)

$(Executable): $(OBJS)
	$(rmLogFiles)
	$(makeLogDir)
	$(CXX) $(OBJS) $(allFlags) -o $@ $(LOGGING)
	$(rmEmptyLogFiles)
#	./$@ $(LOGGING_RUN)
#	$(rmEmptyLogFiles)
	

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(makeLogDir)
	mkdir -p $(dir $@)
	$(CXX) $(allFlags) -c $< -o $@ $(LOGGING)
	$(rmEmptyLogFiles)

-include $(DEPS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(Executable)

