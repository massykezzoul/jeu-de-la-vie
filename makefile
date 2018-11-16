################################################################################################################
##
## Created By Massili Kezzoul to compile Code written in C++ on linux distribution
## 
## How to configure :
##		-Set the program name (EXEC variable)
## 		-Set the source code (SRC) and headers (HEADERS) if they are note in the same folder as this makefile
##   	-Set the archive name if needed $(ARCHIVE_NAME)
##  	-Happy Coding
##
## How to use :
## 		-make all      = Compilation
## 		-make exe      = executate the program (it will be compiled first)
## 		-make clean    = delete object files (*.o)
## 		-make mrproper = delete object files (*.o) and the executable that was created $(EXEC)
## 		-make tar      = create an archive .tar with all the source code, headers and this makefile
## 		-make zip 	   = create an archive .zip with all the source code, headers and this makefile
##
################################################################################################################
 
CC=g++
CFLAGS=-Wall -pedantic -ansi 
LDFLAGS=
EXEC=jeu_de_la_vie
SRC=population/population.cpp cellule/cellule.cpp configuration/configuration.cpp configuration/convert/convert.cpp main.cpp
OBJ= $(SRC:.cpp=.o)
HEADERS = population/population.h cellule/cellule.h configuration/configuration.h configuration/convert/convert.h
# The name of the archive
ARCHIVE_NAME=configuration_source

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

exe :
	@./$(EXEC) && echo '$(EXEC)' Done || echo Fail on running '$(EXEC)'

subl : 
	@subl $(SRC) $(HEADERS)

line :
	@wc -l $(SRC) $(HEADERS) makefile fichier_test/*

tar : 
	@tar -czvf $(ARCHIVE_NAME).tar.gz makefile $(SRC) $(HEADERS) && echo "'$(ARCHIVE_NAME).tar.gz' created" || echo "FAIL"
zip : 
	@zip -r $(ARCHIVE_NAME).zip makefile $(SRC) $(HEADERS) && echo "'$(ARCHIVE_NAME).zip' created" || echo "FAIL"