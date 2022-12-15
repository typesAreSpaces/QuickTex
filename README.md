# QuickTex

This tool automatically generates a minimal 
setup to quickly start working on a TeX project.

## Requirements

- latexmk
- inotify-tools

## Build instructions

```
git clone https://github.com/typesAreSpaces/QuickTex.git
cd QuickTex
make
```

The binary `quicktex` will appear inside the bin folder
generated by the previous commands.

## Worflow

Execute `quicktex <project-name>`. The latter will generate
a directory named `<project-name>` including a main.tex
file, a figure folder, a Makefile containing rules to compile
the tex file main and editable tex files.

Execute `make` to compile the main.tex file.

Execute `make watch` to call a infinity while loop that
constanly updates the output whenever a change is produced
in any of the tex files in the project.
 

