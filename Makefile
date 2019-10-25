Executable = test
SRC_DIR = src
BUILD_DIR = build
LOG_DIR = log

#makeLogDir = mkdir -p $(LOG_DIR)
#LOGGING = 2> $(LOG_DIR)/make_$(notdir $@).log
#LOGGING_RUN = > $(LOG_DIR)/run.log

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
	$(makeLogDir)
	$(CXX) $(OBJS) $(allFlags) -o $@ $(LOGGING)
	./$@ $(LOGGING_RUN)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(makeLogDir)
	mkdir -p $(dir $@)
	$(CXX) $(allFlags) -c $< -o $@ $(LOGGING)

-include $(DEPS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(Executable)

