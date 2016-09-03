OBJ = SpaceInvaders.o gestione_impostazioni.o gestione_highscores.o gestione_partita.o gestione_menu.o
CXXFLAGS=$(DEBUG_FLAGS) -Wall -lallegro -lallegro_font -lallegro_ttf
LDFLAGS=-export-dynamic -lallegro -lallegro_font -lallegro_ttf

SpaceInvaders: $(OBJ)
	g++ -o SpaceInvaders $(OBJ) $(LDFLAGS)

-include dependencies

.PHONY: depend clean cleanall

depend:
	g++ -MM *.cc > dependencies
clean:
	rm -f *.o
cleanall:
	rm -f GSeq *.o *~
