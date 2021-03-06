/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: Engine.h
  
Author: JustGoogleIt

Date: February 14, 2016

Class: Engine

Functions:
	int FindTableKey (string name);
  	void CreateTable (string name, vector <string> primaryKey);
  	void CreateTable (string name, Table table);
  	void DeleteTable (string tableName);
  	void AddColumn (string tableName, string columnName, string type);
  	void AddEntry (string tableName, vector <string> data);
  	void UpdateEntry (string tableName, string data, string columnName, string condition);
	void DeleteEntry (string tableName, string columnName, string condition);
  	void DisplayTable (string name);
  	void DisplayTable (Table table);

  	void Save (string filename);
  	void Open (string filename);

  	Table Selection (string tableName, string conditionColum, string conditionType ,string condition);
  	Table Projection (string tableName, vector<string> columns);
  	Table Rename (string tableName, vector<string> oldColumnNames, vector<string> newColumnNames);
  	Table SetDifference (string tableName1, string tableName2);
  	Table SetUnion (string tableName1, string tableName2);
	Table CrossProduct(string tableName1, string tableName2);
	Table NaturalJoin (string tableName1, string tableName2);
------------------------------------------------------------------------------ */

#ifndef ENGINE_H
#define ENGINE_H

#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Table.h"
#include "Header.h"


using namespace std;

class Engine {
	
  
  public:

  	vector <Table> allTables;
  	int FindTableKey (string name);
  	void CreateTable (string name, vector <string> primaryKey);
  	void CreateTable (string name, Table table);
  	void DeleteTable (string tableName);
  	void AddColumn (string tableName, string columnName, string type);
  	void AddEntry (string tableName, vector <string> data);
  	void UpdateEntry (string tableName, string data, string columnName, string condition);
	void DeleteEntry (string tableName, string columnName, string condition);
  	void DisplayTable (string name);
  	void DisplayTable (Table table);

  	void Save (string filename);
  	void Open (string filename);

  	// Relational Algebra
  	Table Selection (string tableName, string conditionColum, string conditionType ,string condition);
  	Table Projection (string tableName, vector<string> columns);
  	Table Rename (string tableName, vector<string> oldColumnNames, vector<string> newColumnNames);
  	Table SetDifference (string tableName1, string tableName2);
  	Table SetUnion (string tableName1, string tableName2);
	Table CrossProduct(string tableName1, string tableName2);
	Table NaturalJoin (string tableName1, string tableName2);
  };

//----------------Helper Functions---------------------

vector<string> splitStrings(string const & str, char splitCharacter)
{
    vector<string> result;
    istringstream inputstream(str);

    for (string token; getline(inputstream, token, splitCharacter); ){
        if(!token.empty()){
        	result.push_back(token);
        }
    }
    return result;
}

//trim from beginning
static inline string &lefttrim(string &str) {
        str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));
        return str;
}

// trim from end
static inline string &righttrim(string &str) {
        str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());
        return str;
}

static inline string &trim(string &str) {
        return lefttrim(righttrim(str));
}

int Engine::FindTableKey(string name) {
	int key = -1;
	for (int i=0; i<allTables.size(); i++) {
		if (allTables[i].name  ==  name) {
			key = i;
		}
	}
	return key;
}

//-------------Engine Functions-----------------------
void Engine::CreateTable (string name, vector <string> primaryKey) {
	bool isDuplicateName = false;
	for (int i=0; i<allTables.size(); i++) {
		if (allTables[i].name == name) {
			isDuplicateName = true;
		}
	}

	if (isDuplicateName) {
		cerr << "DUPLICATE TABLE NAME" << endl;
	}
	else {
		Table newTable(name, primaryKey);
		if (allTables.size() == 0) {
			allTables.push_back(newTable);
		}
		else if (allTables[0].name == "---------") {
			allTables[0] = newTable;
		}
		else {
			allTables.push_back(newTable);
		}
	} 	
}

void Engine::CreateTable (string name, Table table) {
	bool isDuplicateName = false;
	for (int i=0; i<allTables.size(); i++) {
		if (allTables[i].name == name) {
			isDuplicateName = true;
		}
	}

	if (isDuplicateName) {
		cerr << "DUPLICATE TABLE NAME" << endl;
	}
	else {
		table.name = name;
		allTables.push_back(table);
	}
}

void Engine::DeleteTable (string tableName) {
	if (allTables.size() == 1) {
		allTables[0].name  = "---------";
	}
	else {
		int key = FindTableKey(tableName);
		allTables.erase(allTables.begin() + (key-1));
	}
}

void Engine::AddColumn (string tableName, string columnName, string type) {
	int key  = FindTableKey(tableName);
	allTables[key].AddColumn(columnName, type);
}

void Engine::AddEntry (string tableName, vector <string> data) {
	int key = FindTableKey(tableName);
	allTables[key].AddEntry(data);
}

void Engine::UpdateEntry (string tableName, string data, string columnName, string condition) {
	int tableKey  = FindTableKey(tableName);
	vector <int> rows = allTables[tableKey].FindRows(columnName, condition);
	allTables[tableKey].UpdateEntry(columnName, rows, data);
}

void Engine::DeleteEntry (string tableName, string columnName, string condition) {
	int tableKey  = FindTableKey(tableName);
	vector <int> rows = allTables[tableKey].FindRows(columnName, condition);
	allTables[tableKey].DeleteEntry(rows);
}

void Engine::DisplayTable (string name) {
	int tableKey  = FindTableKey(name);
	if (tableKey != -1) {
		Table currentTable = allTables[tableKey];

		cout << endl << "Table: " << currentTable.name << endl << endl;

		int width = 10;

		for (int i=0; i<currentTable.header.size(); i++) {
			string headerString = currentTable.header[i].name + ","  + currentTable.header[i].type;
			cout << setw(width) << left << headerString<< " | ";
		}

		cout << endl;
		if (currentTable.table.size() > 0) {
			for (int i=0; i<currentTable.table[0].size(); i++) {
				for (int j=0; j<currentTable.table.size(); j++) {
					cout << setw(width) << currentTable.table[j][i] << " | ";
				}
				cout << endl;
			}
		}
	}
}

void Engine::DisplayTable (Table currentTable) {
	cout << endl << "Table: " << currentTable.name << endl << endl;

	int width = 10;

	for (int i=0; i<currentTable.header.size(); i++) {
		string headerString = currentTable.header[i].name + ","  + currentTable.header[i].type;
		cout << setw(width) << left << headerString<< " | ";
	}

	cout << endl;
	if (currentTable.table.size() > 0) {
		for (int i=0; i<currentTable.table[0].size(); i++) {
			for (int j=0; j<currentTable.table.size(); j++) {
				cout << setw(width) << currentTable.table[j][i] << " | ";
			}
			cout << endl;
		}
	}
}


void Engine::Save(string filename){

	ofstream textfile;
	textfile.open (filename);

	for(int it = 0; it < allTables.size(); it++){

		textfile << "-|" << allTables[it].name;
		for(int pkiterator = 0; pkiterator < allTables[it].primaryKey.size(); pkiterator++){
			textfile << "|" << allTables[it].primaryKey[pkiterator];
		}
		textfile << "\n";
		int key = FindTableKey(allTables[it].name);
		if (key != -1){
			Table currentTable = allTables[key];
			textfile << "<|";
			for (int i=0; i<currentTable.header.size(); i++) {
				string headerString = currentTable.header[i].name + ","  + currentTable.header[i].type;
				textfile << headerString << "|" ;
			}
			textfile << endl;

			if (currentTable.table.size() > 0) {
				for (int i=0; i<currentTable.table[0].size(); i++) {
					textfile << "*|";
					for (int j=0; j<currentTable.table.size(); j++) {
						textfile << currentTable.table[j][i] << "|";
					}
					textfile << endl;
				}
			}
		}
	}

	textfile.close();
}

void Engine::Open(string filename){

	ifstream input(filename);
	string word;
	string EngineName;
	vector<string> data;
	vector<string> ByPipe;
	vector<string> ByComma;	
	vector <string> pk;
	while(getline(input,word)){
		if (trim(word) != ""){
			ByPipe = splitStrings(word, '|');
			if(ByPipe[0] == "-"){
				for(int i = 2; i < ByPipe.size(); i++){
					pk.push_back(ByPipe[i]);
				}
				CreateTable(ByPipe[1], pk);
				EngineName = ByPipe[1];
				pk.clear();
			}
			else if(ByPipe[0] == "<"){
				for(int it = 1; it < ByPipe.size(); it++){
					ByComma = splitStrings(ByPipe[it], ',');
					AddColumn(EngineName, ByComma[0], ByComma[1]);
				}
			}
			else if(ByPipe[0] == "*"){
				for(int it = 1; it < ByPipe.size(); it++){
					data.push_back(ByPipe[it]);
				}
				AddEntry(EngineName, data);
				data.clear();
			}
		}
	}
}

Table Engine::Selection (string tableName, string conditionColum, string conditionType, string condition) {
	int tableKey = FindTableKey(tableName);
	Table selectionTable = allTables[tableKey].Selection(conditionColum, conditionType, condition);

	return selectionTable;
}

Table Engine::Projection (string tableName, vector<string> columns) {
	int tableKey = FindTableKey(tableName);
	Table projectionTable = allTables[tableKey].Projection(columns);

	return projectionTable;
}

Table Engine::Rename (string tableName, vector<string> oldColumnNames, vector<string> newColumnNames) {
	int tableKey = FindTableKey(tableName);
	Table renamedTable = allTables[tableKey].Rename(oldColumnNames, newColumnNames);

	return renamedTable;
}

Table Engine::SetDifference (string tableName1, string tableName2) {
	int tableKey1 = FindTableKey(tableName1);
	int tableKey2 = FindTableKey(tableName2);

	Table setDifferenceTable = allTables[tableKey1].SetDifference(allTables[tableKey2]);

	return setDifferenceTable;
}

Table Engine::SetUnion (string tableName1, string tableName2) {
	int tableKey1 = FindTableKey(tableName1);
	int tableKey2 = FindTableKey(tableName2);

	Table setUnionTable = allTables[tableKey1].SetUnion(allTables[tableKey2]);

	return setUnionTable;
}

Table Engine::CrossProduct (string tableName1, string tableName2){
	int tableKey1 = FindTableKey(tableName1);
	int tableKey2 = FindTableKey(tableName2);

	Table crossProdTable = allTables[tableKey1].CrossProduct(allTables[tableKey2]);

	return crossProdTable;
}

Table Engine::NaturalJoin (string tableName1, string tableName2){
	int tableKey1 = FindTableKey(tableName1);
	int tableKey2 = FindTableKey(tableName2);

	Table naturalJoinTable = allTables[tableKey1].NaturalJoin(allTables[tableKey2]);

	return naturalJoinTable;
}


#endif