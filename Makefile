OBJ=SpaceInvaders.o gestione_impostazioni.o gestione_classifica.o gestione_partita.o gestione_menu.o gestione_grafica.o gestione_audio.o gestione_timer.o
LIBS=allegro-5 allegro_acodec-5 allegro_audio-5 allegro_font-5 allegro_image-5 allegro_ttf-5
CXXFLAGS=$(DEBUG_FLAGS) -Wall `pkg-config --cflags $(LIBS)`
LDFLAGS=-export-dynamic `pkg-config --libs $(LIBS)`
DEBUG_LEVEL=1

SpaceInvaders: $(OBJ)
	g++ -o SpaceInvaders $(OBJ) $(LDFLAGS)

-include dependencies

.PHONY: clean cleanall debug debug-level-2 depend dependall

debug: DEBUG_FLAGS = -g -D DEBUG_MODE -D DEBUG_LEVEL=$(DEBUG_LEVEL)
debug: SpaceInvaders
debug-level-2: DEBUG_LEVEL=2
debug-level-2: debug
clean:
	rm -f SpaceInvaders *.o
cleanall:
	rm -f SpaceInvaders *.o *~ dependencies highscores partita.sav SpaceInvaders.config
depend:
	g++ -MM *.cc > dependencies
dependall:
	g++ -M *.cc > dependencies