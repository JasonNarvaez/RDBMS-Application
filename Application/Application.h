//Application.h


/*
	void CreateNewProject(string name)
		takes a name and creates a new project

	void ShowProject(string projectName);
		takes a prexisting project name and displays
		the name of project tables

	int OpenProject(string projectName);
		opens a prexisting project file
		if any part of the project fails the
		project does not open

	void ProjectInsert(string projectName);
		inserts an object
			0 - warehouse
				asks for name, address, ID
				inserts and shows result
			1 - store
				asks for name, address, ID
				inserts and shows result
			2 - item
				asks for name, brand, aisle, barcode
	  default - prints "not acceptable choice"

			**asks for name twice for error**

	void LinkProject(string projectName);
			0: item store
				takes Barcode
				takes ID of a store 
				table shows before each input is accepted 
				then the insert and show happen
			1: store warehouse
				takes ID of a warehouse
				takes ID of a store 
				table shows before each input is accepted 
				then the insert and show happen
			Default:
				Print “not acceptable choice”

	void SingleTableSave(string projectName);
		saves some aspect of the project
			0 – save warehouse
			1 – save store table
			2 – save item table
			3 – save warehouse roster
			4 – save store inventory
	  default - "issue with option"

	void TableUpdate(string projectName);
		Updates a file, shows a table and takes the id for the object
			0 – saves warehouse table
			1 – saves store table
			2 – saves item table
	  Default – “incorrect input”

	void TableDelete(string projectName);
		Delete table 
			0 – deletes warehouse
			1 – Deletes store table
			2 – Deletes item
	  Default - “incorrect input”

	void InStock(string storeNumber, string projectName);
		Prints items in a store
	void ItemLocated(string barcode, string projectName);
		Prints where an item is located
	void WarehouseSupplies(string warehouseID, string projectName);
		Prints where a warehouse stocks

*/
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
	void WarehouseSupplies(string warehouseID, string projectName);
};

// create a table warehouses
void CreateNewProject(string name){

	// create warehouse table
	parser.Evaluate("CREATE TABLE " + name + "Warehouse (Name VARCHAR(50), Location VARCHAR(200), WarehouseID INTEGER) PRIMARY KEY (WarehouseID)");

	// create a table stores
	parser.Evaluate("CREATE TABLE " + name + "Store (Name VARCHAR(100), Location VARCHAR(200), StoreID INTEGER) PRIMARY KEY (StoreID)");

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

			parser.Evaluate("INSERT INTO " + projectName + "WarehouseStoreLink VALUES FROM (" + storeID + "," + warehouseID + ")");
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
	string input = "In_Stock <- project (Name, Brand, Aisle, Barcode) (select(StoreID==" + storeNumber + ")  (" + projectName + "Item JOIN " + projectName + "StoreItemLink))";
	Table inStock = parser.EvaluateTable(input);

	cout << endl << "Items in stock at store number: " << storeNumber << endl << endl;
	
	cout << setw(30) << "Name";
	cout << setw(30) << "Brand";
	cout << setw(30) << "Aisle";
	cout << setw(30) << "Barcode" << endl;
	cout << setfill('-') << setw(120) <<  "" << endl;

	cout << setfill(' ');

	for (int i=0; i<inStock.table[0].size(); i++) {
		for (int j=0; j<inStock.table.size(); j++) {
			cout << setw(30) << inStock.table[j][i];
		}
		cout << endl;
	}

}

void ItemLocated(string barcode, string projectName) {
	string input = "Item_Location <- project (Name, Location, StoreID) (select(Barcode==" + barcode + ") (" + projectName + "Store JOIN " + projectName + "StoreItemLink))";
	Table itemLocated = parser.EvaluateTable(input);

	cout << endl << "Item Number " << barcode << " is located at the following stores" << endl << endl;

	cout << setw(30) << "Name";
	cout << setw(30) << "Location";
	cout << setw(30) << "Store ID" << endl;
	cout << setfill('-') << setw(90) <<  "" << endl;

	cout << setfill(' ');
	
	for (int i=0; i<itemLocated.table[0].size(); i++) {
		for (int j=0; j<itemLocated.table.size(); j++) {
			cout << setw(30) << itemLocated.table[j][i];
		}
		cout << endl;
	}
}

void WarehouseSupplies(string warehouseID, string projectName) {
	string input = "warehouseSupplies <- project (Name, Location, WarehouseID) (select(WarehouseID==" + warehouseID + ") (" + projectName + "Warehouse JOIN " + projectName + "WarehouseStoreLink))";
	Table warehouseSupplies = parser.EvaluateTable(input);

	cout << endl << "Warehouse number " << warehouseID << " stocks the following stores" << endl << endl;

	cout << setw(30) << "Name";
	cout << setw(30) << "Location";
	cout << setw(30) << "Warehouse ID" << endl;
	cout << setfill('-') << setw(90) <<  "" << endl;

	cout << setfill(' ');
	
	for (int i=0; i<warehouseSupplies.table[0].size(); i++) {
		for (int j=0; j<warehouseSupplies.table.size(); j++) {
			cout << setw(30) << warehouseSupplies.table[j][i];
		}
		cout << endl;
	}
}







