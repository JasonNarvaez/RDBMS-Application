/*
Main:
	Gives user option to create or upload a project

	When starting the program:
		Commands:
		'q' exits the program
			if user chooses not to open or create a project
			program will quit
		'y' yes
		'n' no

	When creating/updating a project:
		Commands:
		0 - save and quit
		1 - show tables
		2 - add object (warehouse, store, item)
		3 - link (item with store, store to warehouse)
		4 - delete
		5 - update
		6 - save
		7 - make custom query
		8 - check stock
		9 - product location
	   10 - check store warehouse relations

*/
//main.cpp
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Application.h"
#include "../Parser/Parser.h"

using namespace std;

int main(){

	int userInput = -1; // for the switch statement
	string input; // for the general user input
	string projectName; // holds the project name

	system("clear");

	while(input != "q"){

		cout << "Would you like to create a new Project?[y/n]\n";
		cin >> input;

		if(input == "y" || input == "Y"){ 

			cout << "What would you like to name it?\n>";
			cin >> projectName;
			CreateNewProject(projectName);
			break;

		}
		else if(input == "n" || input == "N"){

			cout << "Would you like to open a past project?[y/n]\n";
			cin >> input;

			if(input == "n" || input == "N") {

				cout << "ok, Goodbye.\n";
				return 0;

			}
			else if(input == "y" || input == "Y"){

				cout << "Please enter the name of the project you wish to open.\n";
				cin >> projectName;
				int worked = OpenProject(projectName);
				system ("clear");
				
				if (worked == 0){
					cout << "DATABASE LOADED" << endl;
					break;
				}
				else{
					continue;
				}
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

		cout << "\nMenu:\n To show your tables, type 1\n to add a warehouse, store, or item, type 2\n to link an item to a store or link a store to a warehouse,type 3\n to Delete, type 4\n to Update a table, type 5\n to Save a table, type 6\n to make a handwritten Query, type 7\n to check what is in stock at a store, type 8\n to check which stores a product is located, type 9\n to see check which stores a particular warehouse stocks, type 10\n to exit the program and save your progress, type 0\n";
		//do we need any more functions?
		cin >> userInput;
	 			string input;

		switch(userInput){ 
			case 1: // show
				system("clear");
				ShowProject(projectName);
				break;
			case 2: // insert
				system("clear");
				ProjectInsert(projectName);
				break;
			case 3: // link
				system("clear");
				LinkProject(projectName);
				break;
			case 4: // delete
				system("clear");
				TableDelete(projectName); //throwing an error when more than one thing is 
				break;
			case 5: // update

				break; 
			case 6: // save
				system("clear");
				SingleTableSave(projectName);
	 			break;
	 		case 7: // handwritten query
				system("clear");
				cin >> input;
	 			parser.Evaluate(input);
	 			break;
	 		case 8:
	 			system("clear");
	 			cout << "Enter Store Number: ";
	 			cin >> input;
	 			InStock(input, projectName);
	 			break;
	 		case 9:
	 			system("clear");
	 			cout << "Enter Barcode Number: ";
	 			cin >> input;
	 			ItemLocated(input, projectName);
	 			break;
 			case 10:
	 			system("clear");
	 			cout << "Enter Warehouse Number: ";
	 			cin >> input;
	 			WarehouseSupplies(input, projectName);
	 			break;
			case 0: // quit
				system("clear");
				parser.Evaluate("EXIT");
				breakvar = true;
				break;
			default:
				system("clear");
				cout << "That was not a choice";
				break;
		}
	}
}