OBJS = Basic.o Main.o Validplaywall.o Playwall.o Playmove.o Genmove.o 
SOURCE = Basic.c Main.c Validplaywall.c Playwall.c Playmove.c Genmove.c
OUT = quoridor
CC = gcc
FLAGS = -g -Wall

$(OUT): $(OBJS)
	$(CC) -o $(OUT) $(FLAGS) $(OBJS)

Main.o: Main.c
	$(CC) -c $(FLAGS) Main.c
	
Validplaywall.o: Validplaywall.c
	$(CC) -c $(FLAGS) Validplaywall.c
	
Playwall.o: Playwall.c
	$(CC) -c $(FLAGS) Playwall.c

Playmove.o: Playmove.c
	$(CC) -c $(FLAGS) Playmove.c

Genmove.o: Genmove.c
	$(CC) -c $(FLAGS) Genmove.c

.PHONY: 
	clean

clean:
	rm -f $(OBJS) $(OUT)

# Sdi1500129
# Petropoulakis Panagiotis
