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

void ShowProject(string projectName){

	parser.Evaluate("SHOW " + projectName + "Warehouse");
	parser.Evaluate("SHOW " + projectName + "Store");
	parser.Evaluate("SHOW " + projectName + "Item");
	parser.Evaluate("SHOW " + projectName + "WarehouseStoreLink ");
	parser.Evaluate("SHOW " + projectName + "StoreItemLink");
}

void OpenProject(string projectName){
	engine.Open(projectName + "Warehouse");
	engine.Open(projectName + "Store");
	engine.Open(projectName + "Item");
	engine.Open(projectName + "WarehouseStoreLink ");
	engine.Open(projectName + "StoreItemLink");
}











