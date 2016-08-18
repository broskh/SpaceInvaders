OBJ = SpaceInvaders.o
CXXFLAGS=$(DEBUG_FLAGS) -Wall -lallegro
LDFLAGS=-export-dynamic -lallegro

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
