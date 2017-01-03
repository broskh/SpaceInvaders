CXXFLAGS=$(DEBUG_FLAGS) $(NOASS) -Wall `pkg-config --cflags $(LIBS)`
DEBUG_LEVEL=1
LDFLAGS=-export-dynamic `pkg-config --libs $(LIBS)`
LIBS=allegro-5 allegro_acodec-5 allegro_audio-5 allegro_font-5 allegro_image-5 allegro_ttf-5
OBJ=SpaceInvaders.o gestione_impostazioni.o gestione_classifica.o gestione_partita.o gestione_menu.o gestione_grafica.o gestione_audio.o gestione_timer.o

SpaceInvaders: $(OBJ)
	g++ -o SpaceInvaders $(OBJ) $(LDFLAGS)

-include dependencies

.PHONY: clean cleanAll debug debugExtended depend dependAll noAsserts

clean:
	rm -f SpaceInvaders *.o
cleanAll:
	rm -f SpaceInvaders *.o *~ dependencies ../highscores ../partita.sav ../SpaceInvaders.config
debug: DEBUG_FLAGS = -g -D DEBUG_MODE -D DEBUG_LEVEL=$(DEBUG_LEVEL)
debug: SpaceInvaders
debugExtended: DEBUG_LEVEL=2
debugExtended: debug
depend:
	g++ -MM *.cc > dependencies
noAsserts: NOASS=-D NDEBUG
noAsserts: SpaceInvaders
	