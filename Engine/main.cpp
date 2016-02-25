/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: main.cpp
  
Author: JustGoogleIt

Date: February 14, 2016

Description: 	This file test all of the functions that our database performs
				We would read the output and then check whether or not it matched
				with what we expected.
------------------------------------------------------------------------------ */

#include <iostream>
#include "Engine.h"
#include "Header.h"
#include "Table.h"

using namespace std;

int main () {
	Engine engine;

	// Uncomment these lines and comment everything else out to set the reading a database from a file
	// engine.Open("save.txt");
	// engine.DisplayTable("animals");

	vector <string> primaryKey;
	primaryKey.push_back("name");
	primaryKey.push_back("kind");
	engine.CreateTable("animals", primaryKey);
	engine.AddColumn("animals","name", "VARCHAR(20)");
	engine.AddColumn("animals","kind", "VARCHAR(8)");
	engine.AddColumn("animals","years", "INTEGER");

	vector <string> data = {"Joe", "cat", "4"};
	vector <string> data1 = {"Spot", "dog", "10"};
	vector <string> data2 = {"Snoopy", "dog", "3"};
	vector <string> data3 = {"Tweety", "bird", "1"};
	vector <string> data4 = {"Joe", "bird", "2"};
	engine.AddEntry("animals", data);
	engine.AddEntry("animals", data1);
	engine.AddEntry("animals", data2);
	engine.AddEntry("animals", data3);
	engine.AddEntry("animals", data4);



	engine.CreateTable("animals2", primaryKey);
	engine.AddColumn("animals2","name", "VARCHAR(20)");
	engine.AddColumn("animals2","kind", "VARCHAR(8)");
	engine.AddColumn("animals2","years", "INTEGER");
	vector <string> data_5 = {"Jake", "lizard", "1"};
	engine.AddEntry("animals2", data);
	engine.AddEntry("animals2", data_5);
	engine.AddEntry("animals2", data4);

	engine.DisplayTable("animals2");

	engine.DisplayTable(engine.SetUnion("animals","animals2"));


	engine.DisplayTable("animals");

	engine.CreateTable("dogs", engine.Selection("animals","kind", "==", "dog"));
	engine.DisplayTable("dogs");

	engine.CreateTable("old_dogs", engine.Selection("dogs","years", ">", "9"));
	engine.DisplayTable("old_dogs");

	vector <string> columns = {"name", "years"};
	engine.DisplayTable(engine.Projection("animals", columns));
	
	engine.DisplayTable(engine.CrossProduct("animals","dogs"));
	
	vector <string> primaryKey2 = { "breed", "name" };
	engine.CreateTable("breeds", primaryKey2);
	engine.AddColumn("breeds","breed","VARCHAR(20)");
	engine.AddColumn("breeds","name","VARCHAR(20)");
	
	vector <string> data5 = {"boxer","Spot"};
	vector <string> data6 = {"beagle","Snoopy"};
	engine.AddEntry("breeds", data5);
	engine.AddEntry("breeds", data6);
	
	engine.DisplayTable("breeds");

	engine.DisplayTable(engine.NaturalJoin("breeds","animals"));

	vector <string> newNames = {"type", "age"};
	engine.DisplayTable(engine.Rename("animals", newNames));

	engine.Save("save.txt");



	
}