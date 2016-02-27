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
	parser.createTable("CREATE TABLE " + name + "Warehouse (Name VARCHAR(50), Location VARCHAR(100), IDNumber INTEGER) PRIMARY KEY (IDNumber)");

	// create a table stores
	parser.createTable("CREATE TABLE " + name + "Store (Name VARCHAR(50), Location VARCHAR(100), IDNumber INTEGER) PRIMARY KEY (IDNumber)");

	// create a table items
	parser.createTable("CREATE TABLE " + name + "Item (Name VARCHAR(50), Brand VARCHAR(50), Aisle VARCHAR(100), Barcode INTEGER) PRIMARY KEY (IDNumber)");

	// create a Table link the store with the warehouse
	parser.createTable("CREATE TABLE " + name + "WarehouseStoreLink (StoreID INTEGER, WarehouseID INTEGER) PRIMARY KEY (IDNumber)");

	// create a Table to link the item to the store
	parser.createTable("CREATE TABLE " + name + "StoreItemLink (StoreID INTEGER, ItemID INTEGER) PRIMARY KEY (IDNumber)");

	cout << "\nNew Project for " + name + " Created!\n\n";
}

void ShowProject(string projectName){

	parser.show("SHOW " + projectName + "Warehouse");
	parser.show("SHOW " + projectName + "Store");
	parser.show("SHOW " + projectName + "Item");
	parser.show("SHOW " + projectName + "WarehouseStoreLink ");
	parser.show("SHOW " + projectName + "StoreItemLink");
}