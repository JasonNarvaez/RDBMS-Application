//main.cpp

#include "Application.h"
#include "../Parser/Parser.h"

using namespace std;

int main(){

	string input;
	string projectName;
	while(input != "q"){
		cout << "Would you like to create a new Project?[y/n]\n";
		cin >> input;
		if(input == "y"){ 
			cout << "What would you like to name it?\n>";
			cin >> projectName;
			CreateNewProject(projectName);
			break;
		}
		else if(input == "n"){
			cout << "Would you like to open a past project?[y/n]\n";
			cin >> input;
			if(input == "n") {
				cout << "ok, Goodbye.\n";
				return 0;
			}
			else if(input == "y"){
				cout << "Please enter the name of the project you wish to open.\n";
				// open all files
			}
			else {
				cout << "incorrect input.";
				continue;
			}
		}
		else{
			cout << "That was not an option";
		}
	}

	cout << "Your database currently looks like this: \n";
	ShowProject(projectName);
	
}