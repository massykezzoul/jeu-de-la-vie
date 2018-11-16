#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream> // for istringstream
#include "convert.h"

using namespace std;


int convert(string non_convertie){
	int i = non_convertie.size() -1;
	unsigned int j = 0;
	int r = 0;
	int tmp;

	while (j < non_convertie.size()){
		tmp = convert_char(non_convertie[j]);
		if (tmp == -1)
			return -1;
		else
			r = r + dix_puiss(i) * tmp;
		j++;
		i--;
	}
	return r;

}


int nbr_char(size_t n) {
	if (n < 10)
		return 1;
	else 
		return nbr_char(n / 10) + 1 ;
}


int convert_char(char c) {
	switch (c) {
		case '0' : return 0;
		break;
		case '1' : return 1;
		break;
		case '2' : return 2;
		break;
		case '3' : return 3;
		break;
		case '4' : return 4;
		break;
		case '5' : return 5;
		break;
		case '6' : return 6;
		break;
		case '7' : return 7;
		break;
		case '8' : return 8;
		break;
		case '9' : return 9;
		break;
		default : return -1;
		break;
		
	}
}

size_t dix_puiss(int n) {
	if(n<0)
		return -1; /* ERREUR */
	else {
		if (n == 0)
			return 1;
		else 
			return 10*dix_puiss(n-1);
	}
}

/* thanks Stackoverflow */
bool isFloat( string myString ) {
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail(); 
}