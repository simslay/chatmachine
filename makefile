CC = g++
CFLAGS = -Wall -std=c++11
EXEC_NAME = chatmachine9
INCLUDES =
LIBS =
DEPS = $(wildcard src/*.h)
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
INSTALL_DIR = /usr/bin

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

install :
	cp $(EXEC_NAME) $(INSTALL_DIR)
