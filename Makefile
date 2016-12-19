#Makefile du tp2 par Yohan GRACIA et Zifan YAO

CC      = g++
CFLAGS  = -Wall -c
OFLAGS = -Wall -o
DEFFLAGS =
GFLAGS = -g -std=gnu++11



all: TP2Voyage clean

TP2Voyage: main.o Trajet.o TrajetSimple.o TrajetCompose.o Parcours.o Catalogue.o
    $(CC) $(OFLAGS) TP2Voyage main.o Trajet.o TrajetSimple.o TrajetCompose.o Parcours.o Catalogue.o

main.o: main.cpp
	$(CC) $(CFLAGS) $(GFLAGS) main.cpp

Trajet.o: Trajet.cpp Trajet.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) Trajet.cpp Trajet.h

TrajetSimple.o: TrajetSimple.cpp TrajetSimple.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) TrajetSimple.cpp TrajetSimple.h

TrajetCompose.o: TrajetCompose.cpp TrajetCompose.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) TrajetCompose.cpp TrajetCompose.h

Parcours.o: Parcours.cpp Parcours.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) Parcours.cpp Parcours.h

Catalogue.o: Catalogue.cpp Catalogue.h
	$(CC) $(CFLAGS) $(DEFFLAGS) $(GFLAGS) Catalogue.cpp Catalogue.h

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm TP2Voyage
