//main.cpp

#include "Application.h"
#include "../Parser/Parser.h"

using namespace std;

int main(){

	int userInput = -1; // for the switch statement
	string input; // for the general user input
	string projectName; // holds the project name
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
				cin >> projectName;
				OpenProject(projectName);

			}
			else {

				cout << "incorrect input.";
				continue;

			}
		}
		else{

			cout << "That was not an option.\n";

		}
	}

	cout << "Your database currently looks like this: \n";
	ShowProject(projectName);
	bool breakvar = false; //to break from while and end program
	while(breakvar == false){

		cout << "\nMenu:\n To show your tables type 1\n to insert to a table type 2\n to Delete type 3\n to Update type 4\n to Save type 5\n to make a handwritten Query type 6\n to exit the program and save your progress type 0\n";
		//do we need anymore functions?
		cin >> userInput;
		cout << userInput;
		switch(userInput){
			case 1: // show
				ShowProject(projectName);
			break;
			case 2: // insert
				ProjectInsert(projectName);
			break;
			case 3: // delete
			break;
			case 4: // update
			break;
			case 5: // save
			break; 
			case 6: // handwritten query
				parser.Evaluate(input);
	 		break;
			case 0: // quit
				breakvar = true;
			break;
			default:
				cout << "That was not a choice";
			break;
		}
	}
}