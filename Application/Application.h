//Application.h
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "../Parser/Parser.h"
#include "../Engine/Engine.h"

using namespace std;

class Application {

public:
	void CreateNewProject(string name);  //creates a new project	
	void ShowProject(string projectName);
	int OpenProject(string projectName);
	void ProjectInsert(string projectName);
	void LinkProject(string projectName);
	void SingleTableSave(string projectName);
	void TableUpdate(string projectName);
	void TableDelete(string projectName);
	void InStock(string storeNumber, string projectName);
	void ItemLocated(string barcode, string projectName);
};

// create a table warehouses
void CreateNewProject(string name){

	// create warehouse table
	parser.Evaluate("CREATE TABLE " + name + "Warehouse (Name VARCHAR(50), Location VARCHAR(200), IDNumber INTEGER) PRIMARY KEY (IDNumber)");

	// create a table stores
	parser.Evaluate("CREATE TABLE " + name + "Store (Name VARCHAR(100), Location VARCHAR(200), StoreID INTEGER) PRIMARY KEY (IDNumber)");

	// create a table items
	parser.Evaluate("CREATE TABLE " + name + "Item (Name VARCHAR(100), Brand VARCHAR(50), Aisle VARCHAR(100), Barcode INTEGER) PRIMARY KEY (Barcode)");

	// create a Table link the store with the warehouse
	parser.Evaluate("CREATE TABLE " + name + "WarehouseStoreLink (StoreID INTEGER, WarehouseID INTEGER) PRIMARY KEY (StoreID, WarehouseID)");

	// create a Table to link the item to the store
	parser.Evaluate("CREATE TABLE " + name + "StoreItemLink (StoreID INTEGER, Barcode INTEGER) PRIMARY KEY (StoreID, Barcode)");

	cout << "\nNew Project for " + name + " Created!\n\n";
}

void ShowProject(string projectName){ //shows all tables in the current project

	parser.Evaluate("SHOW " + projectName + "Warehouse");
	parser.Evaluate("SHOW " + projectName + "Store");
	parser.Evaluate("SHOW " + projectName + "Item");
	parser.Evaluate("SHOW " + projectName + "WarehouseStoreLink ");
	parser.Evaluate("SHOW " + projectName + "StoreItemLink");
}

int OpenProject(string projectName){ //opens a previous project
	vector<int> worked;
	worked.push_back(parser.openFile(projectName + "Warehouse")); //error checking for corrupt or non-existant files
	worked.push_back(parser.openFile(projectName + "Store"));
	worked.push_back(parser.openFile(projectName + "Item"));
	worked.push_back(parser.openFile(projectName + "WarehouseStoreLink"));
	worked.push_back(parser.openFile(projectName + "StoreItemLink"));

	for(int i = 0; i < worked.size(); i++){ // to determine if any of the files can't be opened
		if(worked[i] == 1){ // if even one file is corrupt, do not continue
			return 1;
		}
	}
	return 0; // if all the files are there, proceed
}

void ProjectInsert(string projectName){
	
	//variables
	int input;
	string ID, barcode;
	char name[50], address[200], warehouse[50], brand[50], aisle[50];

	// cannot do the commas, does not keep spaces
	cout << "What would you like to add?\n Warehouse(0)\n Store(1)\n Item(2)\n";
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

	cout << "To add an item to a store's inventory, type 0\nTo add a store to a warehouse's roster, type 1\n";
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

void SingleTableSave(string projectName){

	int input;
	cout << "What would you like to save?\n for the Warehouse table, type 0\n for the Store table, type 1\n for the Item table, type 2\n for the Warehouse roster, type 3\n for the store inventory, type 4\n";
	switch(input){
		case 0: // saves warehouse table
			parser.Evaluate("WRITE " + projectName + "Warehouse");
			break;
		case 1: // saves store table
			parser.Evaluate("WRITE " + projectName + "Store");
			break;
		case 2: // saves item table
			parser.Evaluate("WRITE " + projectName + "Item");
			break;
		case 3: // saves warehouse roster
			parser.Evaluate("WRITE " + projectName + "WarehouseStoreLink");
			break;
		case 4: // saves store inventory
			parser.Evaluate("WRITE " + projectName + "StoreItemLink");
			break;
		default:
			cout << "Incorrect input";
			break;
	}
}

void TableUpdate(string projectName){

	int input;
	string id;
	cout << "Which file would you like to delete from?\n for the Warehouse table, type 0\n for the Store table, type 1\n for the Item table, type 2\n";
	cin >> input;
	switch(input){
		case 0: // saves warehouse table
			cout << "Please type the ID of the warehouse you wish to delete\n";
			parser.Evaluate("SHOW " + projectName + "Warehouse");
			cin >> id;
			parser.Evaluate("DELETE FROM " + projectName + "Warehouse WHERE IDNumber ==" + id);
			// parser.Evaluate("DELETE FROM " + projectName + "WarehouseStoreLink");
			break;
		case 1: // saves store table
			cout << "Please type the ID of the Store you wish to delete\n";
			parser.Evaluate("SHOW " + projectName + "Store");
			cin >> id;
			// parser.Evaluate("DELETE FROM " + projectName + "StoreItemLink");
			// parser.Evaluate("DELETE FROM " + projectName + "WarehouseStoreLink");
			parser.Evaluate("DELETE FROM " + projectName + "Store WHERE IDNumber ==" + id);
			break;
		case 2: // saves item table
			cout << "Please type the Barcode of the Item you wish to delete\n";
			parser.Evaluate("SHOW " + projectName + "Item");
			cin >> id;
			// parser.Evaluate("DELETE FROM " + projectName + "StoreItemLink");
			parser.Evaluate("DELETE FROM " + projectName + "Item WHERE Barcode ==" + id);
			break;
		default:
			cout << "Incorrect input";
			break;
	}
}

void TableDelete(string projectName) {

	//variables
	int input;
	string id, barcode;
	char name[50], address[200], warehouse[50], brand[50], aisle[50];

	// cannot do the commas, does not keep spaces
	cout << "What would you like to delete?\n Warehouse(0)\n Store(1)\n Item(2)\n";
	cin >> input;

	switch(input){
		case 0: // deletes warehouse table
			cout << "Please type the ID of the warehouse you wish to delete\n";
			parser.Evaluate("SHOW " + projectName + "Warehouse");
			cin >> id;
			parser.Evaluate("DELETE FROM " + projectName + "Warehouse WHERE IDNumber ==" + id);
			parser.Evaluate("DELETE FROM " + projectName + "WarehouseStoreLink WHERE IDNumber ==" + id);
			break;
		case 1: // deletes store table
			cout << "Please type the ID of the Store you wish to delete\n";
			parser.Evaluate("SHOW " + projectName + "Store");
			cin >> id;
			parser.Evaluate("DELETE FROM " + projectName + "StoreItemLink WHERE StoreID==" + id);
			parser.Evaluate("DELETE FROM " + projectName + "WarehouseStoreLink WHERE StoreID==" + id);
			parser.Evaluate("DELETE FROM " + projectName + "Store WHERE StoreID ==" + id);
			break;
		case 2: // deletes item table
			cout << "Please type the Barcode of the Item you wish to delete\n";
			parser.Evaluate("SHOW " + projectName + "Item");
			cin >> id;
			parser.Evaluate("DELETE FROM " + projectName + "StoreItemLink WHERE Barcode ==" + id);
			parser.Evaluate("DELETE FROM " + projectName + "Item WHERE Barcode ==" + id);
			break;
		default:
			cout << "Incorrect input";
			break;
	}

}

void InStock(string storeNumber, string projectName) {
	string input = "temp <- " + projectName + "Item JOIN " + projectName + "StoreItemLink";
	parser.Evaluate(input);

	input = "temp1 <- select(StoreID==" + storeNumber + ") temp";
	parser.Evaluate(input);

	input = "In_Stock <- project (Name, Brand, Aisle, Barcode) temp1";
	Table inStock = parser.EvaluateTable(input);

	cout << endl << "Items in stock at store number: " << storeNumber << endl;
	
	for (auto i : inStock.table[0])
		cout << i << endl;

	parser.Evaluate("CLOSE temp");
	parser.Evaluate("CLOSE temp1");
}

void ItemLocated(string barcode, string projectName) {
	string input = "temp <- " + projectName + "Store JOIN " + projectName + "StoreItemLink";
	parser.Evaluate(input);

	input = "temp1 <- select(Barcode==" + barcode + ") temp";
	parser.Evaluate(input);


	input = "Item_Location <- project (Name, Location, StoreID) temp1";
	Table itemLocated = parser.EvaluateTable(input);

	cout << endl << "Item Number " << barcode << " is located at the following stores" << endl;
	
	for (auto i : itemLocated.table[0])
		cout << i << endl;


	parser.Evaluate("CLOSE temp");
	parser.Evaluate("CLOSE temp1");
}








