//Application.h
#include <vector>
#include <iostream>
#include "../Parser/Parser.h"
#include "../Engine/Engine.h"

using namespace std;

class Application {
public:
	void CreateNewProject(string name);  //creates a new project	
	void ShowProject(string projectName);
};

// create a table warehouses
void CreateNewProject(string name){

	// create warehouse table
	parser.Evaluate("CREATE TABLE " + name + "Warehouse (Name VARCHAR(50), Location VARCHAR(100), IDNumber INTEGER) PRIMARY KEY (IDNumber)");

	// create a table stores
	parser.Evaluate("CREATE TABLE " + name + "Store (Name VARCHAR(50), Location VARCHAR(100), IDNumber INTEGER) PRIMARY KEY (IDNumber)");

	// create a table items
	parser.Evaluate("CREATE TABLE " + name + "Item (Name VARCHAR(50), Brand VARCHAR(50), Aisle VARCHAR(100), Barcode INTEGER) PRIMARY KEY (IDNumber)");

	// create a Table link the store with the warehouse
	parser.Evaluate("CREATE TABLE " + name + "WarehouseStoreLink (StoreID INTEGER, WarehouseID INTEGER) PRIMARY KEY (IDNumber)");

	// create a Table to link the item to the store
	parser.Evaluate("CREATE TABLE " + name + "StoreItemLink (StoreID INTEGER, ItemID INTEGER) PRIMARY KEY (IDNumber)");

	cout << "\nNew Project for " + name + " Created!\n\n";
}

void ShowProject(string projectName){ //shows all tables in the current project

	parser.Evaluate("SHOW " + projectName + "Warehouse");
	parser.Evaluate("SHOW " + projectName + "Store");
	parser.Evaluate("SHOW " + projectName + "Item");
	parser.Evaluate("SHOW " + projectName + "WarehouseStoreLink ");
	parser.Evaluate("SHOW " + projectName + "StoreItemLink");
}

void OpenProject(string projectName){ //opens a previous project
	engine.Open(projectName + "Warehouse");
	engine.Open(projectName + "Store");
	engine.Open(projectName + "Item");
	engine.Open(projectName + "WarehouseStoreLink ");
	engine.Open(projectName + "StoreItemLink");
}

void ProjectInsert(string projectName){
	int input;
	string name, address, ID, warehouse;
	cout << "What would you like to add?\n Warehouse(0)\n Store(1)\n Item(2)\n Please note that you must create a warehouse before you can create the store that\n it links to and you must create a store before you can create the item it links to";
	cin >> input;
	switch(input){
		case '0': // Warehouse
			cout << "please enter the name\n>";
			cin >> name;
			cout << "please enter the address\n>";
			cin >> address;
			cout << "please enter the ID#\n";
			cin >> ID;
			parser.Evaluate("INSERT INTO " + projectName + "Warehouse VALUES FROM (\"" + name + "\",\"" + address + "\"," + ID + ")");
		break;
		case '1': // store
			cout << "please enter the name\n>";
			cin >> name;
			cout << "please enter the address\n>";
			cin >> address;
			cout << "please enter the ID#\n";
			cin >> ID;
			parser.Evaluate("INSERT INTO " + projectName + "Warehouse VALUES FROM (\"" + name + "\",\"" + address + "\"," + ID + ")");
			cout << "please enter the warehouse that caters to this store";
			cin >> warehouse;
			// parser.Evaluate("INSERT INTO " + + " VALUES FROM ") //search through warehouse table and find the correct id number
		break;
		case '2': //Item
			cout << "please enter the name\n>";
			cout << "please enter the brand\n>";
			cout << "please enter the aisle\n";
			cout << "please enter the barcode\n";
		break;
	}

	//key will be item key and store key/ store key and warehouse key

}









