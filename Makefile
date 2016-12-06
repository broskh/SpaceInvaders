OBJ = SpaceInvaders.o gestione_impostazioni.o gestione_classifica.o gestione_partita.o gestione_menu.o gestione_grafica.o gestione_audio.o
CXXFLAGS=$(DEBUG_FLAGS) -Wall -L/usr/local/lib -lallegro -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image
LDFLAGS=-export-dynamic -L/usr/local/lib -lallegro -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image

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
