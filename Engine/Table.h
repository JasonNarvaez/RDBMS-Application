
/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: Table.h
  
Author: JustGoogleIt

Date: February 14, 2016

Class: Table

Functions:
	Table (string name, vector <string> primaryKey);
  	Table ();
  	int FindColumnKey (string columnnName);
  	void AddColumn (string name, string type);
  	vector <int> FindRows (string columnName, string data); 
  	vector <int> FindRows (string columnName, string conditionType, string data); 
  	void AddEntry (vector <string> data);
	void UpdateEntry (string columnnName, vector <int> rows, string data);
	void DeleteEntry (vector <int> rows);

	Table Selection (string conditionColum, string conditionType, string condition);
  	Table Projection (vector<string> columns);
  	Table Rename (vector<string> oldColumnNames, vector<string> newColumnNames);
  	Table SetDifference (Table table2);
  	Table SetUnion (Table table2);
	Table CrossProduct (Table table2);
	Table NaturalJoin (Table table2);
------------------------------------------------------------------------------ */

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include "Header.h"

using namespace std;

class Table {
   public:
  	string name;
  	vector <string> primaryKey;

  	vector<Header> header;
  	vector<vector<string> > table;

  	Table (string name, vector <string> primaryKey);
  	Table ();
  	int FindColumnKey (string columnnName);
  	void AddColumn (string name, string type);
  	vector <int> FindRows (string columnName, string data); 
  	vector <int> FindRows (string columnName, string conditionType, string data); 
  	void AddEntry (vector <string> data);
	void UpdateEntry (string columnnName, vector <int> rows, string data);
	void DeleteEntry (vector <int> rows);

	Table Selection (string conditionColum, string conditionType, string condition);
  	Table Projection (vector<string> columns);
  	Table Rename (vector<string> newColumnNames);
  	Table SetDifference (Table table2);
  	Table SetUnion (Table table2);
	Table CrossProduct (Table table2);
	Table NaturalJoin (Table table2);

};

/*--------------------------------------------------
Constructors
--------------------------------------------------*/
Table::Table(string _name, vector <string> _primaryKey) {
	name = _name;
	primaryKey = _primaryKey;
}

Table::Table() {

}

/*--------------------------------------------------
Adds a column to a specific table by creating a 
new header object and then adding a string that says 
"NULL" into that column.
--------------------------------------------------*/
void Table::AddColumn (string name, string type) {
	vector<string> newColumn;
	newColumn.push_back("NULL");
	table.push_back(newColumn);
	Header newHeader (name, type);
	header.push_back(newHeader);
}

/*--------------------------------------------------
Searches the inputted column for the data and then
returns the index of those rows in a vector
--------------------------------------------------*/
vector <int> Table::FindRows (string columnName, string data) {
	vector <int> rows;
	int columnKey = FindColumnKey (columnName);


	for (int i=0; i<table[columnKey].size(); i++) {
		if (table[columnKey][i] == data) {
			rows.push_back(i);
		}
	}	

	return rows;
}

/*--------------------------------------------------------
Searches the inputted column based on different conditions
and returns the index of the those rows that meet that 
conditinon in a vector
SUPPORTS: == , != , > , < , >= , <=
-------------------------------------------------------*/
vector <int> Table::FindRows (string columnName, string conditionType, string data) {	
	vector <int> rows;

	int columnKey = FindColumnKey (columnName);	

	if (conditionType == "==") {
		for (int i=0; i<table[columnKey].size(); i++) {			
			if (table[columnKey][i] == data) {
				rows.push_back(i);
			}
		}	
	}
	else if (conditionType == "!=") {
		for (int i=0; i<table[columnKey].size(); i++) {
			if (table[columnKey][i] != data) {
				rows.push_back(i);
			}
		}
	}
	else if (conditionType == ">") {
		//Check to see if column in an integer
		if (header[columnKey].type != "INTEGER") {
			cerr << "CAN NOT PERFORM THIS SELECTION: COLUMN IS NOT AN INTEGER" << endl;
		}
		else {
			int condition = stoi(data);
			for(int i=0; i<table[columnKey].size(); i++) {
				int test = stoi(table[columnKey][i]);
				if (test > condition) {
					rows.push_back(i);
				}
			}
		}
	}
	else if (conditionType == "<") {
		//Check to see if column in an integer
		if (header[columnKey].type != "INTEGER") {
			cerr << "CAN NOT PERFORM THIS SELECTION: COLUMN IS NOT AN INTEGER" << endl;
		}
		else {
			int condition = stoi(data);
			
			for(int i=0; i<table[columnKey].size(); i++) {
				int test = stoi(table[columnKey][i]);
				if (test < condition) {
					rows.push_back(i);
				}
			}
		}
	}
	else if (conditionType == ">=") {
		//Check to see if column in an integer
		if (header[columnKey].type != "INTEGER") {
			cerr << "CAN NOT PERFORM THIS SELECTION: COLUMN IS NOT AN INTEGER" << endl;
		}
		else {
			int condition = stoi(data);
			
			for(int i=0; i<table[columnKey].size(); i++) {
				int test = stoi(table[columnKey][i]);
				if (test >= condition) {
					rows.push_back(i);
				}
			}
		}
	}
	else if (conditionType == "<=") {
		//Check to see if column in an integer
		if (header[columnKey].type != "INTEGER") {
			cerr << "CAN NOT PERFORM THIS SELECTION: COLUMN IS NOT AN INTEGER" << endl;
		}
		else {
			int condition = stoi(data);
			
			for(int i=0; i<table[columnKey].size(); i++) {
				int test = stoi(table[columnKey][i]);
				if (test <= condition) {
					rows.push_back(i);
				}
			}
		}
	}
	else {
		cerr << "ERROR IN CONDITION TYPE FORMAT" << endl;
	}

	return rows;
}

/*--------------------------------------------------
Searches the header vector and returns the index
of the column based on the inputted name
--------------------------------------------------*/
int Table::FindColumnKey (string columnnName) {
	int key = -1;
	for (int i=0; i<header.size(); i++) {
		if (header[i].name == columnnName) {
			key = i;
		}
	}

	return key;
}


/*--------------------------------------------------
Adds entry to the table. Checks the header vector
to make sure the input is the correct type and length
--------------------------------------------------*/
void Table::AddEntry (vector <string> data) {
	if (data.size() != header.size()) {
		cout << "ERROR IN INPUT FORMAT" << endl;
	}
	else {

		bool isCorrectType = true;

		for (int i=0; i<data.size(); i++) {
			if (data[i] != "NULL") {
				if (header[i].type == "INTEGER") {
					for (int j=0; j<data[i].size(); j++) {
						if (!isdigit(data[i][j])) {
							isCorrectType = false;
							cerr << "INPUT IS NOT AN INTEGER" << endl;
						}
					}
				}
				else {
					int pos1 = header[i].type.find("("); 
					int pos2 = header[i].type.find(")");

					int length = stoi(header[i].type.substr(pos1 +1, pos2-pos1-1));

					if (data[i].size() > length) {
						isCorrectType = false;
						cerr << "INPUT IS TOO LONG" << endl;
					}
				}
			}
		}

		if (isCorrectType) {
			vector <int> primaryKeysCol;
			for (int i=0; i< primaryKey.size(); i++) {
				if (FindColumnKey(primaryKey[i]) != -1) {
					primaryKeysCol.push_back(FindColumnKey(primaryKey[i]));
				}
			}

			bool isDuplicate = false;	

			vector <string> newKeys;
			for (int i=0; i<primaryKeysCol.size(); i++) {
				newKeys.push_back(data[primaryKeysCol[i]]);
			}	

			for (int i=0; i<table[0].size(); i++) {
				vector <string> testKeys;			

				for (int j=0; j< primaryKeysCol.size(); j++) {
					int col = primaryKeysCol[j];
					string test = table[col][i];
					testKeys.push_back(test);
				}	

				if (testKeys.size() != 0) {
					if ((testKeys == newKeys)  && (testKeys[0] != "NULL")) {
						isDuplicate = true;
						cerr << name << ": DUPLICATE PRIMARY KEYS" << endl;;
					}
				}
			
			}		

			if (isDuplicate == false) {
				if (table[0][0]== "NULL") {
					for (int i=0; i<table.size(); i++) { 
						table[i][0] = (data[i]);
					}
				}
				else {
					for (int i=0; i<table.size(); i++) { 
						table[i].push_back(data[i]);
					}
				}
			}
		}	
	}
} 

/*------------------------------------------------------
Updates data in a specific column in any number of rows
------------------------------------------------------*/
void Table::UpdateEntry (string columnnName, vector <int> rows, string data) {
	int columnKey = FindColumnKey (columnnName);
	for (int i=0; i<rows.size(); i++) {
		int row = rows[i];
		table[columnKey][row] = data;
	}
}

/*------------------------------------------------------
Delete rows in the table
------------------------------------------------------*/
void Table::DeleteEntry (vector <int> rows) {
	if (rows.size() == table[0].size()) {
		for (int i=0; i<rows.size()-1; i++) {
			int row = rows[i];
			for  (int j=0; j<table.size(); j++) {
				table[j].erase(table[j].begin() + (row - i));
			}
		}	

		for  (int i=0; i<table.size(); i++) {
			table[i][0] = "NULL";
		}

	}

	else {
		for (int i=0; i<rows.size(); i++) {
			int row = rows[i];
			for  (int j=0; j<table.size(); j++) {
				table[j].erase(table[j].begin() + (row - i));
			}
		}
	}
}

/*----------------------------------------------------------------------
Returns a table with the rows that meet the condition and condition type
SUPPORTS: == , != , > , < , >= , <=
----------------------------------------------------------------------*/
Table Table::Selection (string conditionColum, string conditionType, string condition) {	
	vector <int> rows = FindRows(conditionColum, conditionType, condition);
	vector <string> pk;
	pk.push_back("selection");

	string newName  = name + " - Selection"; 
	Table selectionTable(newName, pk);

	for (int i=0; i<header.size(); i++) {
		selectionTable.AddColumn(header[i].name, header[i].type);
	}

	for (int i=0; i<rows.size(); i++) {
		vector <string> newData;

		for (int j=0; j<table.size(); j++) {
			int row = rows[i];
			string data = table[j][row];
			newData.push_back(data);
		}
		selectionTable.AddEntry(newData);
	}

	return selectionTable;
}

/*-------------------------------------------------------
Returns a table with only the columns that are inputted
-------------------------------------------------------*/
Table Table::Projection (vector<string> columns) {
	vector <string> pk;
	pk.push_back("projection");
	string newName  = name + " - Projection"; 
	Table projectionTable(newName, pk);

	vector <int> col;
	for (int i=0; i<columns.size(); i++) {
		col.push_back(FindColumnKey(columns[i]));
		Header selectionHeader = header[FindColumnKey(columns[i])];
		projectionTable.AddColumn(selectionHeader.name, selectionHeader.type);
	}

	vector < vector <string> > previousRows;
	for (int i=0; i<table[0].size(); i++) {
		vector <string> newData;
		bool isDuplicate = false;
		for (int j=0; j<col.size(); j++) {
			int colum = col[j];
			int row = i;
			newData.push_back(table[colum][row]);
		}

		for (int j=0; j<previousRows.size(); j++) {
			if (previousRows[j] == newData) {
				isDuplicate = true;
			}
		}

		if (!isDuplicate) {
			previousRows.push_back(newData);
			projectionTable.AddEntry(newData);
		}

	}

	return projectionTable;
}

/*------------------------------------
Returns a table with renamed columns
------------------------------------*/
Table Table::Rename (vector<string> newColumnNames) {
	Table renamedTable (name, primaryKey);
	renamedTable.table = table;

	renamedTable.name = renamedTable.name + " - Renamed";

	vector <Header> renamedHeader = header;

	for (int i=0; i<header.size(); i++) {
		renamedHeader[i].name = newColumnNames[i];
	}

	renamedTable.header = renamedHeader;

	return renamedTable;
}

/*---------------------------------------------------------------
Returns a table with the rows that are NOT located in both tables.
Checks to see if the union is compatible, if they are not then
an empty table is returned
---------------------------------------------------------------*/
Table Table::SetDifference (Table table2) {
	bool isCompatible = false;
	if (header.size() == table2.header.size()) {
		for (int i=0; i<header.size(); i++) {
			if (header[i].name == table2.header[i].name) {
				if (header[i].type == table2.header[i].type) {
					isCompatible = true;
				}
			}
		}
	}

	if (isCompatible){
		string newName = name + " (Set Difference) " + table2.name;
		Table setDifferenceTable (newName, primaryKey);
		
		for (int i=0; i<header.size(); i++) {
			setDifferenceTable.AddColumn(header[i].name, header[i].type);
		}
	
		for (int i=0; i<table[0].size(); i++) {
			bool isDuplicate = false;
			vector <string> testData1;
			for (int j=0; j<table.size(); j++) {
				testData1.push_back(table[j][i]);
			}

			for (int n=0; n<table2.table[0].size(); n++) {
				vector <string> testData2;
				for (int x=0; x<table2.table.size(); x++) {
					testData2.push_back(table2.table[x][n]);
				}

				if (testData1 == testData2) {
					isDuplicate = true;
				}	
			}

			if (!isDuplicate) {
					setDifferenceTable.AddEntry(testData1);
			}
		}
		return setDifferenceTable;
	}
	else {
		vector <string> pk;
		Table emptyTable ("empty",pk);

		return emptyTable;
	}
	
}

/*---------------------------------------------------------------
Returns a table with the rows that are located in both tables.
Checks to see if the union is compatible, if they are not then
an empty table is returned
---------------------------------------------------------------*/
Table Table::SetUnion (Table table2) {
	bool isCompatible = false;
	if (header.size() == table2.header.size()) {
		for (int i=0; i<header.size(); i++) {
			if (header[i].name == table2.header[i].name) {
				if (header[i].type == table2.header[i].type) {
					isCompatible = true;
				}
			}
		}
	}

	if (isCompatible){

		string newName = name + " (Set Union) " + table2.name;
		Table setUnionTable (newName, primaryKey);
			
			for (int i=0; i<header.size(); i++) {
				setUnionTable.AddColumn(header[i].name, header[i].type);
			}
			vector <int> duplicateRows;
			for (int i=0; i<table[0].size(); i++) {
				
				bool isDuplicate = false;
				vector <string> testData1; 		
				for (int j=0; j<table.size(); j++) {
					testData1.push_back(table[j][i]);
				}

				vector <vector <string> > secondTable;
				for (int x=0; x < table2.table[0].size(); x++) {
					vector <string> row;
					for (int y=0; y < table2.table.size(); y++) {
						
						row.push_back(table2.table[y][x]);
					}
					secondTable.push_back(row);
				}
				
				
				for (int x=0; x<secondTable.size(); x++) {
					if (testData1 == secondTable[x]) {
						int duplicateRow = x;
						duplicateRows.push_back(x);
					}
				}
				
				setUnionTable.AddEntry(testData1);
				
			}
			
			for(int i=0; i<table2.table[0].size(); i++) {
				vector <string> row;
				for (int y=0; y < table2.table.size(); y++) {
					
					row.push_back(table2.table[y][i]);
				}
				bool isDuplicate =  false;
				for (int x=0; x<duplicateRows.size(); x++) {
					if (i == duplicateRows[x]) {
						isDuplicate =  true;
					}
				}
				if (!isDuplicate) {
					setUnionTable.AddEntry(row);
				}
			}

		return setUnionTable;
	}
	else {
		vector <string> pk;
		Table emptyTable ("empty",pk);

		return emptyTable;
	}
	
}

/*-------------------------------------------------------
Returns a table with the cross product of the two tables
-------------------------------------------------------*/
Table Table::CrossProduct (Table table2){
	string newName = name + " x " + table2.name;
	vector <string> pk = {""};
	Table CrossProdTable (newName, pk);
	
	int maxRows = table[0].size() * table2.table[0].size();
	
	for (int i=0; i<header.size(); i++) {
		CrossProdTable.AddColumn(header[i].name, header[i].type);
	}
	for (int i=0; i<table2.header.size(); i++) {
		CrossProdTable.AddColumn(table2.header[i].name, table2.header[i].type);
	}

	for (int i=0; i<table[0].size(); i++) {//for the length of table1
		vector <string> testData1;
		for (int j=0; j<table.size(); j++) {
			testData1.push_back(table[j][i]);
		}
	
		for (int n=0; n<table2.table[0].size(); n++) {//for the length of table2's columns
			vector <string> finalData;
			vector <string> testData2;
			vector <string>::iterator it;
			for (int x=0; x<table2.table.size(); x++) {//gets the entire row
				testData2.push_back(table2.table[x][n]);
			}
			
			finalData = testData1;
			it = finalData.end();
			finalData.insert(it,testData2.begin(),testData2.end());//create final row
			CrossProdTable.AddEntry(finalData);
			
		}	
	}
	return CrossProdTable;
}

Table Table::NaturalJoin (Table table2){
	string newName = name + " |><| " + table2.name;
	vector <string> pk = {""};
	Table NatJoinTable (newName, pk);
	
	int maxRows = table[0].size() * table2.table[0].size();
	string commonName;
	bool isCompatible = false;
	
	for (int i=0; i<header.size(); i++) {
		for(int j=0; j<table2.header.size(); j++){
			if (header[i].name == table2.header[j].name) {
				if (header[i].type == table2.header[j].type) {
					isCompatible = true;
					commonName = header[i].name;//cout commonName for debugging
				}
			}
		}
	}

	int table2Column = table2.FindColumnKey(commonName);
	
	for (int i=0; i<header.size()-1; i++) {//add one less column since 
		NatJoinTable.AddColumn(header[i].name, header[i].type);
	}
	for (int i=0; i<table2.header.size(); i++) {
		NatJoinTable.AddColumn(table2.header[i].name, table2.header[i].type);
	}

	if(isCompatible){
		
		for (int i=0; i<table[0].size(); i++) {//for the length of table1
			vector <string> testData1;
			string currentAttribute = table[table.size()-1][i];//the current attribute is in last column of table1

			for (int j=0; j<table.size()-1; j++) {//get rid of the last column in table1 to avoid duplicate columns w/ table2
				testData1.push_back(table[j][i]);
			}
			
			for (int n=0; n<table2.table[0].size(); n++) {//for the length of table2's columns
				vector <string> finalData;
				vector <string> testData2;
				vector <string>::iterator it;
				bool isFound = false;
				string attribute2 = table2.table[table2Column][n];//attribute on the left-most column
				
				if (currentAttribute == attribute2){
					isFound = true;
				}
				
				if (isFound){
					for (int x=0; x<table2.table.size(); x++) {//gets the entire row
						testData2.push_back(table2.table[x][n]);
					}
					
					finalData = testData1;
					it = finalData.end();
					finalData.insert(it,testData2.begin(),testData2.end());//create final row
					
					NatJoinTable.AddEntry(finalData);
				}
			}	
		}
		return NatJoinTable;
	}
	else{
		cerr << "Table(s) do not have a common attribute!" << endl;
		vector <string> pk;
		Table emptyTable ("empty",pk);

		return emptyTable;
	}
}

#endif