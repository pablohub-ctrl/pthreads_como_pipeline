
# Parte compilador
CC = gcc
P_DEF = -D DISABLE_SIMPLE_LOGGER
# flags
CFLAGS = -g -Wall
LPNG = `pkg-config libpng --libs`

# directorios
SRC = src/
# ejec
RUN = ./pipeline
PTHREAD = -lpthread

RM = rm

all: pipeline.o run

pipeline.o: 
	@$(CC) $(P_DEF) $(CFLAGS) pipeline.c -o pipeline $(LPNG) $(PTHREAD)
	
run:
	./pipeline -c 6 -m filtro.txt -n 3 -h 12 -t 20 -b


clean: clean1 clean2

clean1:
		@$(RM) pipeline

clean2:
		@$(RM) out*.png


