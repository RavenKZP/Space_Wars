CCOMP = g++
STD = -std=c++11
ALLEGRO = `pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0`
OUT = -o Space_Wars

FILES = \
Space_Wars.cpp \
Algorithms/Algorithms.cpp \
Space_Functions.cpp \
Space_Classes.cpp \
Space_Graphic.cpp

all:
	$(CCOMP) $(STD) $(FILES) $(OUT) $(ALLEGRO)


#allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0`
