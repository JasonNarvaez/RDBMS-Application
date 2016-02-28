
#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <vector> 
#include "QueryNodes.h"
// #include "../Engine/Engine.h"

using namespace std;

class Parser {
public:
  void Evaluate (string expression);
	void show (string expression); //1
	void createTable (string expression); //done
	void insert (string expression); //2
	void close (string expression); //0
	void write (string expression); //5
	void exit ();
	void Query(string input); //6
	int openFile(string filename); 
	void Delete(string input); //3
	void Update(string input); //4

  Table EvaluateTable(string expression);

  Table QueryTable(string input);


};

Parser parser;
/*------------------------------
Show Class
------------------------------*/

void Parser::show(string expression){
  //check to see if it is an atomic expression
  //if it's not, display the table
  expression = removeSemiColon(expression);
  expression = removeWhiteSpace(expression);
  expression.erase(0, 4);
  int marker = 0;
  for(int i = 0; i<engine.allTables.size(); i++){
    engine.allTables[i].name = removeWhiteSpace(engine.allTables[i].name);
    if(engine.allTables[i].name == expression){
      engine.DisplayTable(expression);
      marker = 1;
    }
  }
  if (marker == 1) return;
  Query(expression);
}
/*------------------------------
Create Table function
------------------------------*/

void Parser::createTable(string expression){

	expression = removeWhiteSpace(expression);

	expression = removeSemiColon(expression);

  vector<string> keys;
  string primaryKeyDelimiter = ")PRIMARY KEY(";
  string varcharDelimiter = "VARCHAR";
  string parenthesisDelimiter = "(";
  string commaDelimiter = ",";

  // gets the table name and deltes it from the expression
  size_t pos = 0;
  pos = expression.find(parenthesisDelimiter);
  string name = expression.substr(0, expression.find("("));
  expression.erase(0, pos + parenthesisDelimiter.length());
  name.erase(name.begin(), name.begin()+11);
  // RelationNameNode* x = new RelationNameNode(name);

  // gets rid of the primary key words and adds a comma at the end of the list for parsing
  string typedAttributeList = expression.substr(0, expression.find(")PRIMARYKEY("));
  pos = expression.find(")PRIMARYKEY(");
  expression.erase(0, pos + primaryKeyDelimiter.length()-1);
  expression.erase(expression.length()-1, expression.length()); 
  typedAttributeList = typedAttributeList + ",";

  // puts the keys into a vector
  keys = splitStrings(expression, ',');
  for(int i = 0; i<keys.size(); i++){
    keys[i] = removeWhiteSpace(keys[i]);
  }
  // removes any white space from the table name
  name = removeWhiteSpace(name);
  // creates table
  engine.CreateTable(name, keys);

  string type = "";
  string kind = "";
  vector<string> attributeList;

  while(typedAttributeList != ""){
    // splits up the attributes
    string current = typedAttributeList.substr(0, typedAttributeList.find(","));
    pos = typedAttributeList.find(commaDelimiter);
    // erases the current attribute list from the expression
    typedAttributeList.erase(0, pos + commaDelimiter.length()); 
    // splits up current attribute list
    if(std::string::npos != current.find("VARCHAR")){
      pos = current.find("VARCHAR");
      string kind = current.substr(0, current.find("VARCHAR"));
      current.erase(0, pos);
      attributeList.push_back(kind);
      attributeList.push_back(current);
    }
    else if(std::string::npos != current.find("INTEGER")){
      pos = current.find("INTEGER");
      string kind = current.substr(0, current.find("INTEGER"));
      current.erase(0, pos);
      attributeList.push_back(kind);
      attributeList.push_back(current);
    }
    else cerr << "You wrote " << current << "You haven't written in INTEGER or VARCHAR: ";
    engine.AddColumn(name,attributeList[0], attributeList[1]);

	attributeList.clear();

  }
}

/*------------------------------
Insert Functions
------------------------------*/

void Parser::insert(string expression){

  //finds relation name and takes it out of the expression
  string primaryKeyDelimiter = "VALUESFROM";
  string parenthesisDelimiter = "(";
  string commaDelimiter = ",";
  vector <string> literals;

  // extracting the name
  expression = removeWhiteSpace(expression);
  expression = removeSemiColon(expression);
  size_t pos = expression.find(primaryKeyDelimiter);
  string name = expression.substr(0, expression.find(primaryKeyDelimiter));
  expression.erase(0, pos + parenthesisDelimiter.length() + 9);
  name.erase(name.begin(), name.begin() + 10);
  RelationNameNode* x = new RelationNameNode(name);
  // testing to see if it is a relation or not
  size_t found = expression.find("RELATION");
  size_t foundQuotes;
  int tableKey;
  //if is relation
  if(found != std::string::npos){
    expression.erase(0, 8);
  	queryNode newQuery("temp",  expression);
    Table newTable = newQuery.Solve();
    for(int i = 0; i<engine.allTables.size();i++){
        if(name == engine.allTables[i].name){
          tableKey = i;
          break;
        }
    }
    Table tab = engine.allTables[tableKey];

    Table what = engine.SetUnion(engine.allTables[tableKey], newTable);

   


  }
  //if not relation
  else{
    expression.erase(expression.begin()); // taking off second parenthesis
    expression.erase(expression.size()-1); // taking off second parenthesis
    literals = splitStrings(expression, ','); // loading into a vector
    engine.AddEntry(name, literals); // adding entry
  }
}  

void Parser::close(string tableName){
  tableName = removeWhiteSpace(tableName);
	tableName =  tableName.erase(0,5);
	engine.DeleteTable(tableName);
}
void Parser::write(string tableName){
	tableName =  tableName.erase(0,5);
	engine.Save(tableName);
}
void Parser::exit(){
	for(int i = 0; i<engine.allTables.size();i++)
	{
		if(engine.allTables[i].name != "---------"){
      cout << engine.allTables[i].name << endl;
			engine.Save(engine.allTables[i].name);
		}
		
	}
}

void Parser::Evaluate(string expression){
  size_t position = 0;



  expression = removeWhiteSpace(expression);

	expression = removeSemiColon(expression);//input is not used in comparing or passed in
    if (expression.find("SHOW") == 0) {
      show(expression);
    }
    else if(expression.find("CREATE") == 0){
      createTable(expression);
    }
    else if(expression.find("INSERT") == 0){
      insert(expression);
    }
    else if(expression.find("CLOSE") == 0){
      close(expression);
    }
    else if(expression.find("WRITE") == 0){
      write(expression);
    }
    else if(expression.find("EXIT") == 0){
      exit();
    }
    else if(expression.find("UPDATE") == 0){
      Update(expression);
    }
    else if(expression.find("DELETE") == 0){
      Delete(expression);
    }
    else if (expression.find("<-") != string::npos){
      Query(expression);
    }
    else if (expression == "") {

    }
    else cerr << "the input \"" << expression <<"\" is not valid" << endl;
    
}

Table Parser::EvaluateTable(string expression) {
    expression = removeWhiteSpace(expression);
    expression = removeSemiColon(expression);

    return QueryTable(expression);

}

void Parser::Query(string input) {
	// input = removeWhiteSpace(input);
	size_t position = 0;
	position = input.find("<-");
	string relationName = input.substr(0, position);
	string expression = input.substr(position+2);
	queryNode query(relationName, expression);
	query.Evaluate();
}

Table Parser::QueryTable(string input) {
  // input = removeWhiteSpace(input);
  size_t position = 0;
  position = input.find("<-");
  string relationName = input.substr(0, position);
  string expression = input.substr(position+2);
  queryNode query(relationName, expression);
  return query.Solve();
}


int Parser::openFile(string filename){
    return engine.Open(filename);
}


void Parser::Delete(string input) {
 input = removeWhiteSpace(input);
 input = removeSemiColon(input);

 input =  input.erase(0,10);

 size_t whereDelimiter = input.find("WHERE");
 string tableName =  input.substr(0, whereDelimiter);

 input = input.erase(0, whereDelimiter+5);

 string condition = input;

 int middleConditionKey = findMiddleCondition(condition);

    string conditionType;
    string conditionValue;

    if ((condition.find("==") == string::npos) && (condition.find("!=") == string::npos) && 
       (condition.find(">=") == string::npos) && (condition.find("<=") == string::npos)) {
            conditionType = condition.substr(middleConditionKey,1);
            conditionValue = condition.substr(middleConditionKey+1);
    }
    else {
         conditionType = condition.substr(middleConditionKey,2);
         conditionValue = condition.substr(middleConditionKey+2);
    }
   
    string conditionColumn = condition.substr(0, middleConditionKey);

 engine.DeleteEntry(tableName, conditionColumn, conditionType, conditionValue);
}

void Parser::Update(string input) {
	input = removeWhiteSpace(input);
 	input = removeSemiColon(input);

 	input = input.erase(0,6);

 	size_t setDelimiter = input.find("SET");
 	string tableName = input.substr(0,setDelimiter); cout << tableName << endl;
 	input = input.erase(0,setDelimiter+3);
 	size_t eqDelimiter = input.find_first_of("==");
 	string columnName = input.substr(0,eqDelimiter); 

 	input = input.erase(0,eqDelimiter+1); 
 	size_t whereDelimiter = input.find("WHERE");
 	string newValue = input.substr(0, whereDelimiter); 

 	input = input.erase(0, whereDelimiter + 5);

string condition = input; 

 int middleConditionKey = findMiddleCondition(condition); 

    string conditionType;
    string conditionValue;

    if ((condition.find("==") == string::npos) && (condition.find("!=") == string::npos) && 
       (condition.find(">=") == string::npos) && (condition.find("<=") == string::npos)) {
            conditionType = condition.substr(middleConditionKey,1);
            conditionValue = condition.substr(middleConditionKey+1); 
    }
    else {
         conditionType = condition.substr(middleConditionKey,2);
         conditionValue = condition.substr(middleConditionKey+2);
    }
   
    string conditionColumn = condition.substr(0, middleConditionKey); 

 engine.UpdateEntry(tableName, newValue, columnName, conditionColumn, conditionType, conditionValue);
}











