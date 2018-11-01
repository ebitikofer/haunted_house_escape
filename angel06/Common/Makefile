# Simple makefile to just get it to work in Stocker 307 machines.
# Written by dmc
# last-modified: Mon Sep 17 13:43:38 2012
#commented out next line for new linux machines
#CC = /opt/csw/bin/g++
GCC_OPTIONS= -pedantic -I ../../include -g
LDLIBS = -L/usr/local/lib/ -L/usr/X11R6/lib -lX11 -lXi -lXmu  -lGLEW -lGL -lGLU  -lglut -lm
INCS = -I/usr/local/include/ -I/home/e/School/cs4250/code-egs/ -I../include/
OPTIONS=$(GCC_OPTIONS) $(INCS)

InitShader.o: InitShader.cpp
	$(CC) InitShader.cpp $(OPTIONS) -c -o $@
