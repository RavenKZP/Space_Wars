CCOMP = g++
STD = -std=c++11
FILES = \
Space_Wars.cpp \
Algorithms/Algorithms.cpp \
Space_Functions.cpp

all:
	$(CCOMP) $(STD) $(FILES) -o Space_Wars

