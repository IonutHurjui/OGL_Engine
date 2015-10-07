#include "Errors.h"
#include <SDL\SDL.h>
#include <iostream>
#include <cstdlib>

using namespace std;


void fatalError(std::string errorString){

	cout << "#ERROR: " << errorString << endl;

}