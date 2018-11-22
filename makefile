################################################################################################################
##
## How to use :
## 		-make all      = Compilation
## 		-make exe      = Execution du program sans aucun paramètre
## 		-make clean    = delete object files (*.o)
## 		-make mrproper = delete object files (*.o) and the executable that was created $(EXEC)
## 		-make tar      = create an archive .tar with all the source code, headers and this makefile
## 		-make zip 	   = create an archive .zip with all the source code, headers and this makefile
##
################################################################################################################
 
CC=g++
CFLAGS=-Wall -pedantic -ansi 
LDFLAGS=
EXEC=jeu
SRC=population/population.cpp cellule/cellule.cpp configuration/configuration.cpp configuration/convert/convert.cpp option/option.cpp main.cpp
OBJ= $(SRC:.cpp=.o)
HEADERS = population/population.h cellule/cellule.h configuration/configuration.h configuration/convert/convert.h option/option.h
# The name of the archive
ARCHIVE_NAME=code_source_v0.1

## Compilation

all: $(EXEC)

$(EXEC) : $(OBJ) $(HEADERS)
	@$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS) -g && echo	"'$(EXEC)' created"

%.o: %.cpp 
	@$(CC) -o $@ -c $< $(CFLAGS) 


## clean and all that shit

.PHONY : clean mrproper

clean :
	@rm $(OBJ) -rvf

mrproper :	clean
	@rm $(EXEC) -rvf

# Affiche le nombre de ligne de code total
line :
	@wc -l $(SRC) $(HEADERS) makefile

# Compression en .tar.gz
tar : 
	@tar -czvf $(ARCHIVE_NAME).tar.gz makefile $(SRC) $(HEADERS) && echo "'$(ARCHIVE_NAME).tar.gz' created" || echo "FAIL"

# Compression en .zip
zip : 
	@zip -r $(ARCHIVE_NAME).zip makefile $(SRC) $(HEADERS) && echo "'$(ARCHIVE_NAME).zip' created" || echo "FAIL"
