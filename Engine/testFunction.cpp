//function testing

#include "gtest/gtest.h"
#include "Table.h"
#include "Engine.h"
#include "Header.h"

using namespace std;

TEST(TestTableFunction, TableFunction){
	Engine engine;
	
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


	engine.CreateTable("dogs", engine.Selection("animals","kind", "==", "dog"));
	engine.DisplayTable("dogs");
	
	EXPECT_EQ("dogs", engine.allTables[1].name );
}
