#include "gtest/gtest.h"
#include "Table.h"
#include "Engine.h"
#include "Header.h"

using namespace std;

TEST(TestTableCreation, TableCreation){
	Table table_2;
	string name = "Camis_Table";
	
	vector <string> pk;
	pk.push_back ("test");
	pk.push_back ("2");

	Table table_1(name, pk);

	EXPECT_EQ("Camis_Table", table_1.name);
	EXPECT_EQ("test", table_1.primaryKey[0]);	
	EXPECT_EQ("2", table_1.primaryKey[1]);
}

TEST(TestTableCreation, EngineCreation){
//creates engine, names, primary keys and data
	Engine engine;
	string name_1  = "test_table";
	string name_2 = "test_table2";
	
	vector <string> pk;
	pk.push_back ("1");
	pk.push_back ("2");
	
/*	vector <string> data;
	data.push_back("1");
	data.push_back("2");
	data.push_back("3");
	vector <string> data2;
	data2.push_back("2");
	data2.push_back("2");
	data2.push_back("3");*/
//inserts names and primary keys into engine	
	engine.CreateTable(name_1, pk);
	engine.CreateTable(name_2, pk);
/*	adds columns to each table	
	engine.AddColumn("test_table","test_1", "int");
	engine.AddColumn("test_table","test_1", "int");
	engine.AddColumn("test_table","test_1 ", "int");
	
	engine.AddColumn("test_table2","test_1", "int");
	engine.AddColumn("test_table2","test_1", "int");
	engine.AddColumn("test_table2","test_1 ", "int");*/
/*	adds column entry
	engine.AddEntry("test_table", data);
	engine.AddEntry("test_table", data);
	engine.AddEntry("test_table", data2);*/
	
	EXPECT_EQ("test_table", engine.allTables[0].name);
	EXPECT_EQ("test_table2", engine.allTables[1].name);
	EXPECT_EQ("1", engine.allTables[0].primaryKey[0]);
	EXPECT_EQ("2", engine.allTables[1].primaryKey[1]);
}

TEST(TestTableCreation, HeaderCreation){
	
	Header head("one", "string");
	Header head_2("two", "int");
	
	EXPECT_EQ("one", head.name);
	EXPECT_EQ("two", head_2.name);
	EXPECT_EQ("string", head.type);
	EXPECT_EQ("int", head_2.type);
	
}

