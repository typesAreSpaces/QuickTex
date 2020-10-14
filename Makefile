IDIR = include
ODIR = obj
SDIR = src
CC = g++
FLAGS = -I$(IDIR) -std=c++11 -Wall

SRC = $(wildcard $(SDIR)/*.cpp)
OBJS = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC))
DEPS = $(wildcard $(IDIR)/*.h)

quicktex: $(OBJS) bin
	$(CC) -g -o bin/$@ $(OBJS) $(FLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) obj
	$(CC) -g -c -o $@ $< $(FLAGS) 

obj:
	@mkdir -p obj

bin:
	@mkdir -p bin

.PHONY: clean
clean:
	rm -rf obj/* bin
