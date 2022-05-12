.PHONY: all clean

CC = g++
LD = ar

#
CXXFLAGS =-Wall\
			-O2

LDFLAGS =

# 文件名字
TARGET = slog

SRC_DIRS =./src

INCLUDES = -I ./ \
	-I /home/sirwang/workspace/code/SLOG/include \
	-I /home/sirwang/workspace/lib/spdlog/include

LIB_PATH = /home/sirwang/workspace/lib/spdlog/build/libspdlog.a

HEAD = $(wildcard $(SRC_DIRS)/*.h)
SRCS = $(wildcard $(SRC_DIRS)/*.cpp )
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

all: $(TARGET)

%.o: %.c %.cpp %.hpp %.hpp
	$(CC) -c $^

$(TARGET): $(OBJS)
	@mkdir bin
	@mkdir include
	$(LD) crv ./bin/lib$(TARGET).a $(OBJS)
	@cp -rp $(HEAD) ./include/

%.o: %.cpp %.h
	$(CC) -c $(INCLUDES) $(CXXFLAGS) $(LIB_PATH) $< -o $@ 

clean:
	-rm -rf ./bin ./include
	-rm -rf $(SRC_DIRS)/*.o
	-rm -rf $(SRC_DIRS)/*.gcf
	-rm -rf $(OBJS) $(TARGET) ./bin/lib$(TARGET).a