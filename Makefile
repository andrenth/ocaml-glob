SOURCES=glob_stubs.c glob.mli glob.ml
RESULT=glob

LIBINSTALL_FILES=$(wildcard *.mli *.cmi *.cma *.cmx *.cmxa *.a *.so)

all: byte-code-library
opt: native-code-library
reallyall: byte-code-library native-code-library
install: libinstall
uninstall: libuninstall
doc: htdoc

-include OCamlMakefile
