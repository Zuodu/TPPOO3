#Makefile du tp3 par Yohan GRACIA et Zifan YAO
#
CC      = g++
CFLAGS  = -Wall -c
OFLAGS = -Wall -o
DEFFLAGS = 
CXX = -std=gnu++11
GFLAGS = -g
#Conditions par rapport a l'environnement
ifdef SYSTEMROOT
	DEFFLAGS += -DWINDOWS
	RM = del /Q
else
	ifeq ($(shell uname), Linux)
		DEFFLAGS += -DLINUX
		RM = rm
	endif
endif
#Debut des regles
all: TP2Voyage clean

TP2Voyage: main.o Trajet.o TrajetSimple.o TrajetCompose.o Parcours.o Catalogue.o
	$(CC) $(OFLAGS) TP2Voyage main.o Trajet.o TrajetSimple.o TrajetCompose.o Parcours.o Catalogue.o

main.o: main.cpp
	$(CC) $(CFLAGS) $(GFLAGS) $(CXX) main.cpp

Trajet.o: Trajet.cpp Trajet.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) $(CXX) Trajet.cpp Trajet.h

TrajetSimple.o: TrajetSimple.cpp TrajetSimple.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) $(CXX) TrajetSimple.cpp TrajetSimple.h

TrajetCompose.o: TrajetCompose.cpp TrajetCompose.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) $(CXX) TrajetCompose.cpp TrajetCompose.h

Parcours.o: Parcours.cpp Parcours.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) $(CXX) Parcours.cpp Parcours.h

Catalogue.o: Catalogue.cpp Catalogue.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) $(CXX) Catalogue.cpp Catalogue.h

.PHONY: clean cleanest

clean:
	$(RM) *.o

cleanest: clean
	$(RM) TP2Voyage
### FIN DU MAKEFILE ###