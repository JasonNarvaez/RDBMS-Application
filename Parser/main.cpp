#include <iostream>
#include <string>
#include "QueryNodes.h"
#include "../Engine/Engine.h"
#include "Parser.h"

using namespace std; 


int main () {

	//parser.openFile();
	while (cin.good()){
	string command;
	getline(cin, command);
	parser.Evaluate(command);
	
	}

}