
#include <iostream>
#include <string>
#include "QueryNodes.h"
#include "../Engine/Engine.h"
#include "Parser.h"
#include "gtest/gtest.h"

using namespace std;

TEST(TestFileIO, FileShow_CreateTable_Insert){
	Parser parser;

	parser.createTable("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)");
	parser.insert("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4)");
	
	parser.show("SHOW animals");
	
	EXPECT_EQ("animals", engine.allTables[0].name );
}
TEST(TestFileIO, FileCreateTable){
	Parser parser;

	parser.createTable("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)");
	parser.insert("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4)");
//	parser.createTable("CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind)");
	
	
	//EXPECT_EQ("animals", engine.allTables[0].name );
	//EXPECT_EQ("species", engine.allTables[1].name );
}
TEST(TestFileIO, FileExit){
	Parser parser;

	parser.createTable("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)");
	parser.insert("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4)");
	
	parser.exit();
	EXPECT_EQ("animals", engine.allTables[0].name );
}
TEST(TestFileIO, FileClose){
	Parser parser;

	parser.createTable("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)");
	parser.insert("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4)");
	
	parser.close("animals");
	EXPECT_EQ("---------", engine.allTables[0].name );
}
