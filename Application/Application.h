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
	void OpenProject(string projectName);
	void ProjectInsert(string projectName);
	void LinkProject(string projectName);
};

// create a table warehouses
void CreateNewProject(string name){

	// create warehouse table
	parser.Evaluate("CREATE TABLE " + name + "Warehouse (Name VARCHAR(50), Location VARCHAR(200), IDNumber INTEGER) PRIMARY KEY (IDNumber)");

	// create a table stores
	parser.Evaluate("CREATE TABLE " + name + "Store (Name VARCHAR(100), Location VARCHAR(200), IDNumber INTEGER) PRIMARY KEY (IDNumber)");

	// create a table items
	parser.Evaluate("CREATE TABLE " + name + "Item (Name VARCHAR(100), Brand VARCHAR(50), Aisle VARCHAR(100), Barcode INTEGER) PRIMARY KEY (IDNumber)");

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
	
	//variables
	int input;
	string ID, barcode;
	char name[50], address[200], warehouse[50], brand[50], aisle[50];

	// cannot do the commas, does not keep spaces
	cout << "What would you like to add?\n Warehouse(0)\n Store(1)\n Item(2)\n Please note that you must create a warehouse before you can create the store that\n it links to and you must create a store before you can create the item it links to\n";
	cin >> input;
	switch(input){

		case 0: // Warehouse
			cout << "please enter the name\n>";
			cin.getline(name,sizeof(name));
			cin.getline(name,sizeof(name));//needed to fix input error

			cout << "please enter the address\n>";
			cin.getline(address,sizeof(address));

			cout << "please enter the ID#\n";
			cin >> ID;

			parser.Evaluate("INSERT INTO " + projectName + "Warehouse VALUES FROM (\"" + name + "\",\"" + address + "\"," + ID + ")");
			parser.Evaluate("SHOW" + projectName + "Warehouse");
			break;

		case 1: // store
			cout << "please enter the name\n>";
			cin.getline(name,sizeof(name));
			cin.getline(name,sizeof(name));//needed to fix input error

			cout << "please enter the address\n>";
			cin.getline(address,sizeof(address));

			cout << "please enter the ID#\n>";
			cin >> ID;

			parser.Evaluate("INSERT INTO " + projectName + "Store VALUES FROM (\"" + name + "\",\"" + address + "\"," + ID + ")");
			parser.Evaluate("SHOW" + projectName + "Store");
			break;

		case 2: //Item
			cout << "please enter the name\n>";
			cin.getline(name,sizeof(name));
			cin.getline(name,sizeof(name)); //needed to fix input error

			cout << "please enter the brand\n>";
			cin.getline(brand,sizeof(brand));
			cout << "please enter the aisle\n>";
			cin.getline(aisle,sizeof(aisle));

			cout << "please enter the barcode\n>";
			cin >> barcode;

			parser.Evaluate("INSERT INTO " + projectName + "Item VALUES FROM (\"" + name + "\",\"" + brand + "\",\"" + aisle + "\"," + barcode + ")");
			parser.Evaluate("SHOW" + projectName + "Item");
			break;

		default:
			cout << "That wasn't one of the acceptable choices";
		break;
	}

}

void LinkProject(string projectName){

	//variables
	string itemBarcode, storeID, warehouseID;
	int input;

	cout << "To add an item to a store's chart, type 0\nTo add a store to a warehouse's roster, type 1\n";
	cin >> input;
	switch(input){
		case 0: // add item to store
			cout << "Please enter the barcode of the Item you wish to add\n";
			parser.Evaluate("SHOW " + projectName + "Item");
			cin >> itemBarcode;

			cout << "Please enter the ID of the store.\n";
			parser.Evaluate("SHOW " + projectName + "Store");
			cin >> storeID;

			parser.Evaluate("INSERT INTO " + projectName + "StoreItemLink VALUES FROM (" + storeID + "," + itemBarcode + ")");
			parser.Evaluate("SHOW " + projectName + "StoreItemLink");

			break;
		case 1: // add store to warehouse
			cout << "Please enter the ID of the Warehouse\n";
			parser.Evaluate("SHOW " + projectName + "Warehouse");
			cin >> warehouseID;

			cout << "Please enter the ID of the store.\n";
			parser.Evaluate("SHOW " + projectName + "Store");
			cin >> storeID;

			parser.Evaluate("INSERT INTO " + projectName + "WarehouseStoreLink VALUES FROM (" + warehouseID + "," + storeID + ")");
			parser.Evaluate("SHOW " + projectName + "WarehouseStoreLink");

			break;
		default:
			cout << "That wasn't one of the acceptable choices";
			break;
	}
}









