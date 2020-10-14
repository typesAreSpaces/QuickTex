SRC=$(wildcard *.tex)
PAPER=main.tex
OUTPUT=$(PAPER:.tex=.pdf)
FILES=$(wildcard ./*.tex)
SHELL=/bin/zsh
all: $(FILES)
	echo $(SRC)
	rubber --pdf $(PAPER)
.PHONY: clean
	clean:
	rubber --clean $(PAPER)
	rm -rf $(OUTPUT)
watch:
	@while [ 1 ]; do; inotifywait $(SRC); sleep 0.01; make all; done

