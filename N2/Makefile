ifeq ($(OS),Windows_NT)
	GLFLAGS = -lglut32win -lopengl32 -lglu32
	EXT = .exe
else
	GLFLAGS = -lGL -lGLU -lglut
	EXT = 
endif

CFLAGS = -Wall

all: exec1 exec2 exec3 exec4 exec5 exec6 exec7

exec1:
	$(info Compilando exercicio 1...)
	g++ -o exec1$(EXT) exec1.cpp $< $(CFLAGS) $(GLFLAGS)

exec2:
	$(info Compilando exercicio 2...)
	g++ -o exec2$(EXT) exec2.cpp $< $(CFLAGS) $(GLFLAGS)

exec3:
	$(info Compilando exercicio 3...)
	g++ -o exec3$(EXT) exec3.cpp $< $(CFLAGS) $(GLFLAGS)

exec4:
	$(info Compilando exercicio 4...)
	g++ -o exec4$(EXT) exec4.cpp $< $(CFLAGS) $(GLFLAGS)

exec5:
	$(info Compilando exercicio 5...)
	g++ -o exec5$(EXT) exec5.cpp $< $(CFLAGS) $(GLFLAGS)

exec6:
	$(info Compilando exercicio 6...)
	g++ -o exec6$(EXT) exec6.cpp $< $(CFLAGS) $(GLFLAGS)

exec7:
	$(info Compilando exercicio 7...)
	g++ -o exec7$(EXT) exec7.cpp $< $(CFLAGS) $(GLFLAGS)

clean:
	rm -f exec1$(EXT)
	rm -f exec2$(EXT)
	rm -f exec3$(EXT)
	rm -f exec4$(EXT)
	rm -f exec5$(EXT)
	rm -f exec6$(EXT)
	rm -f exec7$(EXT)
	rm -f *.o