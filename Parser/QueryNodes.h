#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "../Engine/Engine.h"


using namespace std; 

Engine engine;

class RelationNameNode; 
class SelectionNode; 
class ProjectionNode; 
class RenamingNode; 
class UnionNode; 
class DifferenceNode; 
class ProductNode; 
class NaturalJoinNode; 

/*------------------------------
String helper functions
------------------------------*/
string removeWhiteSpace (string str) {
  string newStr = "";
  for (int i=0; i<str.length(); i++) {
    if (str[i] != ' ') {
      newStr = newStr + str[i];
    }
  }
  return newStr;
}

string removeSemiColon (string str) {
  string newStr = "";
  for (int i=0; i<str.length(); i++) {
    if (str[i] != ';') {
      newStr = newStr + str[i];
    }
  }
  return newStr;  
}

int findMiddleOperation (string str) {
    int numOpenParenthesis = 0;
    int numCloseParenthesis = 0;
    int middleOperationIndex = -1;

    if (str.find('(') != string::npos) {
        int i = 0;
        while (middleOperationIndex == -1) {  
            if (str[i] == '(') {
                numOpenParenthesis++;
            }
            if (str[i] == ')') {
                numCloseParenthesis++;

            }
            if (numCloseParenthesis != 0) {
                if (numOpenParenthesis == numCloseParenthesis) {
                    middleOperationIndex = i;
                }
            }
            i++;
        }
    }

    if (middleOperationIndex == -1) {
        middleOperationIndex = str.find_first_of("+-*J");
    }

    if (middleOperationIndex == (str.length()-1)) {
        middleOperationIndex = str.find_first_of("+-*J");
    }

    return middleOperationIndex;
}


int findMiddleCondition (string str) {
    int numOpenParenthesis = 0;
    int numCloseParenthesis = 0;
    int middleOperationIndex = -1;

    if (str.find('(') != string::npos) {
        int i = 0;
        while (middleOperationIndex == -1) {  
            if (str[i] == '(') {
                numOpenParenthesis++;
            }
            if (str[i] == ')') {
                numCloseParenthesis++;

            }
            if (numCloseParenthesis != 0) {
                if (numOpenParenthesis == numCloseParenthesis) {
                    middleOperationIndex = i;
                }
            }
            i++;
        }
    }

    if (middleOperationIndex == -1) {
        middleOperationIndex = str.find_first_of("=!><");
    }

    if (middleOperationIndex == (str.length()-1)) {
        middleOperationIndex = str.find_first_of("=!><");
    }

    return middleOperationIndex;
}

int countParenthesis(string str){
	int numOpenParenthesis = 0;
    int numCloseParenthesis = 0;
    int middleOperationIndex = -1;

    if (str.find('(') != string::npos) {
        int i = 0;
        while (middleOperationIndex == -1) {  
            if (str[i] == '(') {
                numOpenParenthesis++;
            }
            if (str[i] == ')') {
                numCloseParenthesis++;

            }
            if (numCloseParenthesis != 0) {
                if (numOpenParenthesis == numCloseParenthesis) {
                    middleOperationIndex = i;
                }
            }
            i++;
        }
    }
	if (numOpenParenthesis != numCloseParenthesis){
		cerr << "Parenthesis mismatch!" << endl; 
	}
    return numCloseParenthesis;
}

int findLastParenthesis (string str) {
    int numOpenParenthesis = 0;
    int numCloseParenthesis = 0;
    int middleOperationIndex = -1;

    if (str.find('(') != string::npos) {
        
        for (int i=0; i<str.length(); i++) {  
            if (str[i] == '(') {
                numOpenParenthesis++;
            }
            if (str[i] == ')') {
                numCloseParenthesis++;
				if (numOpenParenthesis == numCloseParenthesis) {
                    return i;
                }
            }
            
        }
    }

	cerr << "No matching end parenthesis!" << endl;
    return -1;
}

string removeOuterParenthesis (string str) {
	string temp;
	if(str.find_first_of("(") != string::npos && str.find_last_of(")") != string::npos){
		temp = str.substr(1, str.length()-2);
		return temp;
	}
	else if (str.find_first_of("(") != string::npos) {
		temp = str.substr(1, str.length()-1);
		return temp;
	}
	else if (str.find_last_of(")") != string::npos) {
		temp = str.substr(0, str.length()-2);
		return temp;
	}
	else {
		cout << "not outer parenthesis found!" << endl;
		return str;
	}
}

/*------------------------------
Relation Name Class
------------------------------*/
class RelationNameNode {
  public:
  	string name;

  	RelationNameNode(string _name) {
  		name = _name;
  	}
};

/*------------------------------
Expression Class
------------------------------*/
class ExpressionNode {
  public:
	string expression;
  bool RelationNameCheck;

  int expressionType;
  /*  0 = relation name
      1 = select
      2 = project
      3 = rename
      4 = Union
      5 = Difference
      6 = Product
      7 = join    */


  RelationNameNode* relationPointer;
  SelectionNode* selectionPointer;
  ProjectionNode* projectionPointer;
  RenamingNode* renamePointer;
  UnionNode* unionPointer;
  DifferenceNode* differencePointer;
  ProductNode* productPointer;
  NaturalJoinNode* joinPointer;

	ExpressionNode(string _expression) {
		expression = _expression;
    RelationNameCheck = false;
	}

  void Evaluate();
  bool isRelationName();
  Table Solve();

};

/*------------------------------
Condition Class
------------------------------*/
class ConditionStatement {
  public:
	string leftCond;
	string rightCond;
	string operation;//operation between the two sides
	//ConditionStatement* nestedLeft;
	//ConditionStatement* nestedRight;
	ConditionStatement(string left, string right, string op): leftCond(left), rightCond(right), operation(op) { }
	
	bool isEmpty() { if (leftCond.empty()&&rightCond.empty()) return true; }
	void evaluateCondition();
};

void ConditionStatement::evaluateCondition(){
	string leftTemp;
	string rightTemp;
	leftCond = removeOuterParenthesis(leftCond);
	rightCond = removeOuterParenthesis(rightCond);
	/*
	if (operation.find("&&") != string::npos){
		cout << "&& condition parsed" << endl;
		leftTemp = removeOuterParenthesis(leftCond);
		rightTemp = removeOuterParenthesis(rightCond);
		cout << "left cond: " << leftTemp << endl;
		cout << "right cond: " << rightTemp << endl;
		leftCond = leftTemp;
		rightCond = rightTemp;
		
	}
	else if (operation.find("||") != string::npos){
		cout << "|| condition parsed" << endl;
		leftTemp = removeOuterParenthesis(leftCond);
		rightTemp = removeOuterParenthesis(rightCond);
		cout << "left cond: " << leftTemp << endl;
		cout << "right cond: " << rightTemp << endl;
		leftCond = leftTemp;
		rightCond = rightTemp;
	}
	else {
		cout << "error parsing conditon" << endl;
	}
	*/
}

/*------------------------------
Selection Class
------------------------------*/
class SelectionNode {
  public:
  	string condition;
  	ExpressionNode* expression;
	ExpressionNode* leftExpr;
	ExpressionNode* rightExpr;
	ConditionStatement* condStatement;
	bool isSingleCondition;

  	SelectionNode(string selectExpression) {
  		int start = selectExpression.find("(");
  		int end = selectExpression.find(")");
		int numParenthesis;
		
		
		numParenthesis = countParenthesis(selectExpression);
		
  		condition = selectExpression.substr(start+1, end-start-1);
		
  		string _expression = selectExpression.substr(end+1);
		
		if (_expression[0] == '(') {
  			_expression = _expression.substr(1,_expression.length()-2);
  		}
		if (numParenthesis == 1){//no nested conditions
			isSingleCondition = true;
			expression = new ExpressionNode(_expression);
			expression -> Evaluate();
		}
		else {
			int lastParenIndex = findLastParenthesis(selectExpression);
			string entireCondition = selectExpression.substr(start,lastParenIndex-start+1);
			isSingleCondition = false;
			
			
			
			_expression = selectExpression.substr(lastParenIndex+1);
			
			if (entireCondition[0] == '(') {
				entireCondition = entireCondition.substr(1,entireCondition.length()-2);
			}
			
			
			int conditionIndex = -1;
			conditionIndex = findMiddleCondition(entireCondition);
			
			string leftSide = entireCondition.substr(0,conditionIndex+1);
			string rightSide = entireCondition.substr(conditionIndex+3,entireCondition.length()-1);
			condition = entireCondition.substr(conditionIndex+1,2);
			
			condStatement = new ConditionStatement(leftSide, rightSide, condition);
			
			expression = new ExpressionNode(_expression);
			expression -> Evaluate();
			condStatement->evaluateCondition();
			//leftExpr = new ExpressionNode(leftSide);
			//rightExpr = new ExpressionNode(rightSide);
			//leftExpr -> Evaluate();
			//rightExpr -> Evaluate();
		}
         
  	}

    Table Solve();
	Table tableIntersection(Table table1, Table table2);
};



/*------------------------------
Projection Class
------------------------------*/
class ProjectionNode {
  public:
  	string columns;
  	ExpressionNode* expression;

  	ProjectionNode(string selectExpression) {
  		int start = selectExpression.find("(");
  		int end = selectExpression.find(")");

  		columns = selectExpression.substr(start+1, end-start-1);

  		string _expression = selectExpression.substr(end+1);

		if (_expression[0] == '(') {
  			_expression = _expression.substr(1,_expression.length()-2);
  		}
  		
  		expression = new ExpressionNode(_expression);
  		expression -> Evaluate();

           	}

    Table Solve();

};

/*------------------------------
Renaming Class
------------------------------*/
class RenamingNode {
  public:
  	string newColumnNames;
  	ExpressionNode* expression;

  	RenamingNode(string selectExpression) {
  		int start = selectExpression.find("(");
  		int end = selectExpression.find(")");

  		newColumnNames = selectExpression.substr(start+1, end-start-1);

  		string _expression = selectExpression.substr(end+1);

		if (_expression[0] == '(') {
  			_expression = _expression.substr(1,_expression.length()-2);
  		}
  		
  		expression = new ExpressionNode(_expression);
  		expression -> Evaluate();

           	}

    Table Solve();
};

/*------------------------------
Union Class
------------------------------*/
class UnionNode {
  public:
  	ExpressionNode* leftSide;
  	ExpressionNode* rightSide;

  	UnionNode(string unionExpression) {
  		int delimeter = findMiddleOperation(unionExpression);
        if (delimeter == -1) {
            delimeter = unionExpression.find('+');
        }

  		string left = unionExpression.substr(0, delimeter);
  		string right  = unionExpression.substr(delimeter+1);

        if (right[0] == '+') {
            right = right.substr(1);
        }

  		if (right[0] == '(') {
  			right = right.substr(1);
  		}

        if (right[(right.length()-1)] == ')') {
            right = right.substr(0,right.length()-1);
        }

  		if (left[0] == '(') {
  			left = left.substr(1);
  		}

  		leftSide = new ExpressionNode (left);
  		rightSide = new ExpressionNode (right);

  		leftSide -> Evaluate();
  		rightSide -> Evaluate();

         
  	}

    Table Solve();

};

/*------------------------------
Difference Class
------------------------------*/
class DifferenceNode {
  public:
  	ExpressionNode* leftSide;
  	ExpressionNode* rightSide;

  	DifferenceNode(string diffExpression) {
  		int delimeter = findMiddleOperation(diffExpression);
        if (delimeter == -1) {
            delimeter = diffExpression.find('-');
        }
        

  		string left = diffExpression.substr(0, delimeter);
  		string right  = diffExpression.substr(delimeter+1);

        if (right[0] == '-') {
            right = right.substr(1);
        }

  		if (right[0] == '(') {
            right = right.substr(1);
        }

        if (right[(right.length()-1)] == ')') {
            right = right.substr(0,right.length()-1);
        }

        if (left[0] == '(') {
            left = left.substr(1);
        }

  		leftSide = new ExpressionNode (left);
  		rightSide = new ExpressionNode (right);

  		leftSide -> Evaluate();
  		rightSide -> Evaluate();

         
  	}

    Table Solve();

};



/*------------------------------
Product Class
------------------------------*/
class ProductNode {
  public:
  	ExpressionNode* leftSide;
  	ExpressionNode* rightSide;

  	ProductNode(string prodExpression) {
  		int delimeter = findMiddleOperation(prodExpression);
        if (delimeter == -1) {
            delimeter = prodExpression.find('-');
        }

  		string left = prodExpression.substr(0, delimeter);
  		string right  = prodExpression.substr(delimeter+1);

        if (right[0] == '*') {
            right = right.substr(1);
        }
        
        if (right[0] == '(') {
            right = right.substr(1);
        }

        if (right[(right.length()-1)] == ')') {
            right = right.substr(0,right.length()-1);
        }

        if (left[0] == '(') {
            left = left.substr(1);
        }

  		leftSide = new ExpressionNode (left);
  		rightSide = new ExpressionNode (right);

  		leftSide -> Evaluate();
  		rightSide -> Evaluate();
        
         
  	}

    Table Solve();

};



/*------------------------------
Natural Join Class
------------------------------*/
class NaturalJoinNode {
  public:
  	ExpressionNode* leftSide;
  	ExpressionNode* rightSide;

  	NaturalJoinNode(string joinExpression) {
  		int delimeter = findMiddleOperation(joinExpression);
        if (delimeter == -1) {
            delimeter = joinExpression.find('-');
        }

  		string left = joinExpression.substr(0, delimeter);
  		string right  = joinExpression.substr(delimeter+4);

  		if (right[0] == '(') {
            right = right.substr(1);
        }

        if (left[0] == '(') {
            left = left.substr(1);
        }

  		leftSide = new ExpressionNode (left);
  		rightSide = new ExpressionNode (right);

  		leftSide -> Evaluate();
  		rightSide -> Evaluate();
        
         
  	}

    Table Solve();

};



void ExpressionNode::Evaluate() {//determine what type of expression it is
	if (expression.find("select") == 0) {
		selectionPointer = new SelectionNode(expression); 
        expressionType =  1;
	}
	else if (expression.find("project") == 0) {
		projectionPointer = new ProjectionNode(expression);
        expressionType =  2;
	}
	else if (expression.find("rename") == 0) {
		renamePointer = new RenamingNode(expression);
        expressionType =  3;

	}
    else if (expression.find_first_of("+-*J") != string::npos) {//setUnion, setDifference, cross product, or natural join
        int middleOperationIndex = findMiddleOperation(expression);
        char middleOperation = expression[middleOperationIndex];
        if (middleOperation == ')') {
            middleOperation = expression[middleOperationIndex+1];
        }

        if (middleOperation == '+') {
            unionPointer = new UnionNode(expression);
            expressionType =  4;
        }
        else if (middleOperation == '-') {
            differencePointer = new DifferenceNode(expression);
            expressionType =  5;
        }
        else if (middleOperation == '*') {
            productPointer = new ProductNode(expression);
            expressionType =  6;
        }
        else {
            joinPointer = new NaturalJoinNode(expression);
            expressionType =  7;
        }
    }
	else {// the atomic expression is just a relation
    relationPointer = new RelationNameNode(expression);
    RelationNameCheck = true; 
    expressionType =  0;
	}
}

bool ExpressionNode::isRelationName() {
  return RelationNameCheck;
}

/*------------------------------
Query Class
------------------------------*/
class queryNode {
  public:
    RelationNameNode* relationName;
    ExpressionNode* expression;

    queryNode(string name, string expression);
    void Evaluate();
    Table Solve();
    void Display();

};

queryNode::queryNode(string name, string _expression) {

	_expression = removeWhiteSpace(_expression);
	_expression = removeSemiColon(_expression);



	RelationNameNode* x  = new RelationNameNode(name);
	ExpressionNode* y = new ExpressionNode(_expression);

	relationName = x;
	expression = y;
}

void queryNode::Display() {
}

void queryNode::Evaluate() {
  expression -> Evaluate(); 
  engine.CreateTable(relationName -> name, expression -> Solve());
}

Table queryNode::Solve() {
    expression -> Evaluate(); 
    return expression -> Solve();
}

Table SelectionNode::tableIntersection(Table table1, Table table2){
	
}

Table ExpressionNode::Solve() {
    Table table;
    string tableName;
    switch (expressionType) {
          /*  0 = relation name
          1 = select
          2 = project
          3 = rename
          4 = Union
          5 = Difference
          6 = Product
          7 = join    */
        // case 0:
        //     tableName = expression -> relationPointer -> name;
        //     return engine.Selection(tableName, conditionColumn, conditionType, conditionValue);
        // break;

        case 1:
            return selectionPointer -> Solve();
        break;

        case 2:
            return projectionPointer -> Solve(); 
        break;

        case 3:
            return renamePointer -> Solve();
        break;

        case 4:
            return unionPointer -> Solve();
        break;

        case 5:
            return differencePointer -> Solve();
        break;

        case 6:
            return productPointer -> Solve();
        break;
        
        case 7:
            return joinPointer -> Solve();
        break;
   
    }
}

Table SelectionNode::Solve() {//find what the next atomic expression is and then evaluate it 
    int middleConditionKey = findMiddleCondition(condition);

    string conditionType;
    string conditionValue;
	if (isSingleCondition){
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
		
		Table table;
		string tableName;
		switch (expression -> expressionType) {
			  /*  0 = relation name
			  1 = select
			  2 = project
			  3 = rename
			  4 = Union
			  5 = Difference
			  6 = Product
			  7 = join    */
			case 0:
				tableName = expression -> relationPointer -> name;
				return engine.Selection(tableName, conditionColumn, conditionType, conditionValue);

			break;

			case 1:
				table = expression -> selectionPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 2:
				table = expression -> projectionPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 3:
				table = expression -> renamePointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 4:
				table = expression -> unionPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 5:
				table = expression -> differencePointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 6:
				table = expression -> productPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 7:
				table = expression -> joinPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;
	   
		}
	}
	
	else {//case where we have two conditions
		
		string conditionType1;
		string conditionValue1;
		string conditionType2;
		string conditionValue2;
		int middleConditionKey1 = findMiddleCondition(condStatement->leftCond);
		 if ((condStatement->leftCond.find("==") == string::npos) && (condStatement->leftCond.find("!=") == string::npos) && 
			(condStatement->leftCond.find(">=") == string::npos) && (condStatement->leftCond.find("<=") == string::npos)) {
            conditionType1 = condStatement->leftCond.substr(middleConditionKey1,1);
            conditionValue1 = condStatement->leftCond.substr(middleConditionKey1+1);
		}
		else {
			 conditionType1 = condStatement->leftCond.substr(middleConditionKey1,2);
			 conditionValue1 = condStatement->leftCond.substr(middleConditionKey1+2);
		}
		
		string conditionColumn1 = condStatement->leftCond.substr(0, middleConditionKey1);
		
		
		int middleConditionKey2 = findMiddleCondition(condStatement->rightCond);
		 if ((condStatement->rightCond.find("==") == string::npos) && (condStatement->rightCond.find("!=") == string::npos) && 
			(condStatement->rightCond.find(">=") == string::npos) && (condStatement->rightCond.find("<=") == string::npos)) {
            conditionType2 = condStatement->rightCond.substr(middleConditionKey2,1);
            conditionValue2 = condStatement->rightCond.substr(middleConditionKey2+1);
		}
		else {
			 conditionType2 = condStatement->rightCond.substr(middleConditionKey2,2);
			 conditionValue2 = condStatement->rightCond.substr(middleConditionKey2+2);
		}
	   
		
		string conditionColumn2 = condStatement->rightCond.substr(0, middleConditionKey2);
		
		
		Table table1;
		Table table2;
		Table table4;
		Table table5;
		string tableName1;
		string tableName2;
		
		if (condStatement->operation == "&&") {
			tableName1 = expression -> relationPointer -> name;
			table1 = engine.Selection(tableName1, conditionColumn1, conditionType1, conditionValue1);
			
			tableName2 = expression -> relationPointer -> name;
			table2 = engine.Selection(tableName2, conditionColumn2, conditionType2, conditionValue2);
			Table table3 = engine.SetUnion(table1, table2);
			
			engine.DisplayTable(table2);
			
			if (conditionType1 == "==") {
				table4 = engine.Selection(tableName1, conditionColumn1, "!=", conditionValue1);
				
				
			}
			else if (conditionType1 == "!=") {
				table4 = engine.Selection(tableName1, conditionColumn1, "==", conditionValue1);
				
			}
			else if (conditionType1 == ">=") {
				table4 = engine.Selection(tableName1, conditionColumn1, "<", conditionValue1);
				
			}
			else if (conditionType1 == "<=") {
				table4 = engine.Selection(tableName1, conditionColumn1, ">", conditionValue1);
				
			}
			else if (conditionType1 == ">") {
				table4 = engine.Selection(tableName1, conditionColumn1, "<=", conditionValue1);
				
			}
			else if (conditionType1 == "<") {
				table4 = engine.Selection(tableName1, conditionColumn1, ">=", conditionValue1);
				
			}
			
			if (conditionType2 == "==") {
				table5 = engine.Selection(tableName2, conditionColumn2, "!=", conditionValue2);
				
				
			}
			else if (conditionType2 == "!=") {
				table5 = engine.Selection(tableName2, conditionColumn2, "==", conditionValue2);
				
			}
			else if (conditionType2 == ">=") {
				table5 = engine.Selection(tableName2, conditionColumn2, "<", conditionValue2);
				
			}
			else if (conditionType2 == "<=") {
				table5 = engine.Selection(tableName2, conditionColumn2, ">", conditionValue2);
				
			}
			else if (conditionType2 == ">") {
				table5 = engine.Selection(tableName2, conditionColumn2, "<=", conditionValue2);
				
			}
			else if (conditionType2 == "<") {
				table5 = engine.Selection(tableName2, conditionColumn2, ">=", conditionValue2);
				
			}
			
			Table table6 = engine.SetUnion(table4, table5);
			return engine.SetDifference(table3, table6);
		
		}
		else if (condStatement->operation == "||") {
			tableName1 = expression -> relationPointer -> name;
			table1 = engine.Selection(tableName1, conditionColumn1, conditionType1, conditionValue1);
			tableName2 = expression -> relationPointer -> name;
			table2 = engine.Selection(tableName2, conditionColumn2, conditionType2, conditionValue2);
			return engine.SetUnion(table1, table2);
		}
		
		/*
		switch (expression -> expressionType) {
			  /*  0 = relation name
			  1 = select
			  2 = project
			  3 = rename
			  4 = Union
			  5 = Difference
			  6 = Product
			  7 = join    *//*
			case 0:
				tableName = expression -> relationPointer -> name;
				return engine.Selection(tableName, conditionColumn, conditionType, conditionValue);

			break;

			case 1:
				table = expression -> selectionPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 2:
				table = expression -> projectionPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 3:
				table = expression -> renamePointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 4:
				table = expression -> unionPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 5:
				table = expression -> differencePointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 6:
				table = expression -> productPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;

			case 7:
				table = expression -> joinPointer -> Solve();
				return engine.Selection(table, conditionColumn, conditionType, conditionValue);
			break;
		}
			*/
    
	
	}
}

Table ProjectionNode::Solve() {
    size_t position = 0;
    string delimeter = ",";
    string columnsCopy = columns;
    vector <string> columnNames;
    while ((position = columnsCopy.find(delimeter)) != string::npos) {
        string columnName = columnsCopy.substr(0,position);
        columnNames.push_back(columnName);
        columnsCopy.erase(0, position + delimeter.length());
    }
    columnNames.push_back(columnsCopy);

    Table table;
    string tableName;
    switch (expression -> expressionType) {
          /*  0 = relation name
          1 = select
          2 = project
          3 = rename
          4 = Union
          5 = Difference
          6 = Product
          7 = join    */
        case 0:
            tableName = expression -> relationPointer -> name;
            return engine.Projection(tableName,columnNames);
        break;

        case 1:
            table = expression -> selectionPointer -> Solve();
            return engine.Projection(table, columnNames);
        break;

        case 2:
            table = expression -> projectionPointer -> Solve();
            return engine.Projection(table, columnNames);
        break;

        case 3:
            table = expression -> renamePointer -> Solve();
            return engine.Projection(table, columnNames);
        break;

        case 4:
            table = expression -> unionPointer -> Solve();
            return engine.Projection(table, columnNames);
        break;

        case 5:
            table = expression -> differencePointer -> Solve();
            return engine.Projection(table, columnNames);
        break;

        case 6:
            table = expression -> productPointer -> Solve();
            return engine.Projection(table, columnNames);
        break;

        case 7:
            table = expression -> joinPointer -> Solve();
            return engine.Projection(table, columnNames);
        break;
        default: 
        break;
    }
}

Table RenamingNode::Solve() {
    size_t position = 0;
    string delimeter = ",";
    string columnsCopy = newColumnNames;
    vector <string> columnNames;
    while ((position = columnsCopy.find(delimeter)) != string::npos) {
        string columnName = columnsCopy.substr(0,position);
        columnNames.push_back(columnName);
        columnsCopy.erase(0, position + delimeter.length());
    }

    columnNames.push_back(columnsCopy);

    Table table;
    string tableName;
    switch (expression -> expressionType) {
          /*  0 = relation name
          1 = select
          2 = project
          3 = rename
          4 = Union
          5 = Difference
          6 = Product
          7 = join    */
        case 0:
            tableName = expression -> relationPointer -> name;
            return engine.Rename(tableName,columnNames);
        break;

        case 1:
            table = expression -> selectionPointer -> Solve();
            return engine.Rename(table, columnNames);
        break;

        case 2:
            table = expression -> projectionPointer -> Solve();
            return engine.Rename(table, columnNames);
        break;

        case 3:
            table = expression -> renamePointer -> Solve();
            return engine.Rename(table, columnNames);
        break;

        case 4:
            table = expression -> unionPointer -> Solve();
            return engine.Rename(table, columnNames);
        break;

        case 5:
            table = expression -> differencePointer -> Solve();
            return engine.Rename(table, columnNames);
        break;

        case 6:
            table = expression -> productPointer -> Solve();
            return engine.Rename(table, columnNames);
        break;

        case 7:
            table = expression -> joinPointer -> Solve();
            return engine.Rename(table, columnNames);
        break;
    }
}


Table UnionNode::Solve() {//left and right side can be atomic expressions, so recursively evaluate them
    string tableName1;
    string tableName2;
    if (((leftSide -> expressionType) == 0) && ((rightSide -> expressionType) == 0)){//case where both are relation names
        tableName1 = leftSide -> relationPointer -> name;
        tableName2 = rightSide -> relationPointer -> name;
        return engine.SetUnion(tableName1, tableName2);
    }

    else {
        Table table1;
        int tableKey;
        switch (leftSide -> expressionType) {
              /* 0 = relation name
              1 = select
              2 = project
              3 = rename
              4 = Union
              5 = Difference
              6 = Product
              7 = join    */
            
            case 0:
                tableKey = engine.FindTableKey(leftSide -> relationPointer -> name);
                table1 = engine.allTables[tableKey];
            break;
            
            case 1:
                table1 = leftSide -> selectionPointer -> Solve();
            break;
    
            case 2:
                table1 = leftSide -> projectionPointer -> Solve();
            break;
    
            case 3:
                table1 = leftSide -> renamePointer -> Solve();
            break;
    
            case 4:
                table1 = leftSide -> unionPointer -> Solve();
            break;
    
            case 5:
                table1 = leftSide -> differencePointer -> Solve();
            break;
    
            case 6:
                table1 = leftSide -> productPointer -> Solve();
            break;
    
            case 7:
                table1 = leftSide -> joinPointer -> Solve();
            break;
        }
    
        Table table2;
        switch (rightSide -> expressionType) {
              /* 0 = relation name
              1 = select
              2 = project
              3 = rename
              4 = Union
              5 = Difference
              6 = Product
              7 = join    */
            
            case 0:
                tableKey = engine.FindTableKey(rightSide -> relationPointer -> name);
                table2 = engine.allTables[tableKey];
            break;
    
            case 1:
                table2 = rightSide -> selectionPointer -> Solve();
            break;
    
            case 2:
                table2 = rightSide -> projectionPointer -> Solve();
            break;
    
            case 3:
                table2 = rightSide -> renamePointer -> Solve();
            break;
    
            case 4:
                table2 = rightSide -> unionPointer -> Solve();
            break;
    
            case 5:
                table2 = rightSide -> differencePointer -> Solve();
            break;
    
            case 6:
                table2 = rightSide -> productPointer -> Solve();
            break;
    
            case 7:
                table2 = rightSide -> joinPointer -> Solve();
            break;
        }
    
        return engine.SetUnion(table1, table2);
    }

}

Table DifferenceNode::Solve() {
    string tableName1;
    string tableName2;
    if (((leftSide -> expressionType) == 0) && ((rightSide -> expressionType) == 0)){
        tableName1 = leftSide -> relationPointer -> name;
        tableName2 = rightSide -> relationPointer -> name;
        return engine.SetDifference(tableName1, tableName2);
    }

    else {
        Table table1;
        int tableKey;
        switch (leftSide -> expressionType) {
              /* 0 = relation name
              1 = select
              2 = project
              3 = rename
              4 = Union
              5 = Difference
              6 = Product
              7 = join    */
            
            case 0:
                tableKey = engine.FindTableKey(leftSide -> relationPointer -> name);
                table1 = engine.allTables[tableKey];
            break;
            
            case 1:
                table1 = leftSide -> selectionPointer -> Solve();
            break;
    
            case 2:
                table1 = leftSide -> projectionPointer -> Solve();
            break;
    
            case 3:
                table1 = leftSide -> renamePointer -> Solve();
            break;
    
            case 4:
                table1 = leftSide -> unionPointer -> Solve();
            break;
    
            case 5:
                table1 = leftSide -> differencePointer -> Solve();
            break;
    
            case 6:
                table1 = leftSide -> productPointer -> Solve();
            break;
    
            case 7:
                table1 = leftSide -> joinPointer -> Solve();
            break;
        }
    
        Table table2;
        switch (rightSide -> expressionType) {
              /* 0 = relation name
              1 = select
              2 = project
              3 = rename
              4 = Union
              5 = Difference
              6 = Product
              7 = join    */
            
            case 0:
                tableKey = engine.FindTableKey(rightSide -> relationPointer -> name);
                table2 = engine.allTables[tableKey];
            break;
    
            case 1:
                table2 = rightSide -> selectionPointer -> Solve();
            break;
    
            case 2:
                table2 = rightSide -> projectionPointer -> Solve();
            break;
    
            case 3:
                table2 = rightSide -> renamePointer -> Solve();
            break;
    
            case 4:
                table2 = rightSide -> unionPointer -> Solve();
            break;
    
            case 5:
                table2 = rightSide -> differencePointer -> Solve();
            break;
    
            case 6:
                table2 = rightSide -> productPointer -> Solve();
            break;
    
            case 7:
                table2 = rightSide -> joinPointer -> Solve();
            break;
        }
        return engine.SetDifference(table1, table2);
    }
}


Table ProductNode::Solve() {
    string tableName1;
    string tableName2;
    if (((leftSide -> expressionType) == 0) && ((rightSide -> expressionType) == 0)){
        tableName1 = leftSide -> relationPointer -> name;
        tableName2 = rightSide -> relationPointer -> name;
        return engine.CrossProduct(tableName1, tableName2);
    }

    else {
        Table table1;
        int tableKey;
        switch (leftSide -> expressionType) {
              /* 0 = relation name
              1 = select
              2 = project
              3 = rename
              4 = Union
              5 = Difference
              6 = Product
              7 = join    */
            
            case 0:
                tableKey = engine.FindTableKey(leftSide -> relationPointer -> name);
                table1 = engine.allTables[tableKey];
            break;
            
            case 1:
                table1 = leftSide -> selectionPointer -> Solve();
            break;
    
            case 2:
                table1 = leftSide -> projectionPointer -> Solve();
            break;
    
            case 3:
                table1 = leftSide -> renamePointer -> Solve();
            break;
    
            case 4:
                table1 = leftSide -> unionPointer -> Solve();
            break;
    
            case 5:
                table1 = leftSide -> differencePointer -> Solve();
            break;
    
            case 6:
                table1 = leftSide -> productPointer -> Solve();
            break;
    
            case 7:
                table1 = leftSide -> joinPointer -> Solve();
            break;
        }
    
        Table table2;
        switch (rightSide -> expressionType) {
              /* 0 = relation name
              1 = select
              2 = project
              3 = rename
              4 = Union
              5 = Difference
              6 = Product
              7 = join    */
            
            case 0:
                tableKey = engine.FindTableKey(rightSide -> relationPointer -> name);
                table2 = engine.allTables[tableKey];
            break;
    
            case 1:
                table2 = rightSide -> selectionPointer -> Solve();
            break;
    
            case 2:
                table2 = rightSide -> projectionPointer -> Solve();
            break;
    
            case 3:
                table2 = rightSide -> renamePointer -> Solve();
            break;
    
            case 4:
                table2 = rightSide -> unionPointer -> Solve();
            break;
    
            case 5:
                table2 = rightSide -> differencePointer -> Solve();
            break;
    
            case 6:
                table2 = rightSide -> productPointer -> Solve();
            break;
    
            case 7:
                table2 = rightSide -> joinPointer -> Solve();
            break;
        }
        return engine.CrossProduct(table1, table2);
    }
}

Table NaturalJoinNode::Solve() {
    string tableName1;
    string tableName2;
    if (((leftSide -> expressionType) == 0) && ((rightSide -> expressionType) == 0)){
        tableName1 = leftSide -> relationPointer -> name;
        tableName2 = rightSide -> relationPointer -> name;
        return engine.NaturalJoin(tableName1, tableName2);
    }

    else {
        Table table1;
        int tableKey;
        switch (leftSide -> expressionType) {
              /* 0 = relation name
              1 = select
              2 = project
              3 = rename
              4 = Union
              5 = Difference
              6 = Product
              7 = join    */
            
            case 0:
                tableKey = engine.FindTableKey(leftSide -> relationPointer -> name);
                table1 = engine.allTables[tableKey];
            break;
            
            case 1:
                table1 = leftSide -> selectionPointer -> Solve();
            break;
    
            case 2:
                table1 = leftSide -> projectionPointer -> Solve();
            break;
    
            case 3:
                table1 = leftSide -> renamePointer -> Solve();
            break;
    
            case 4:
                table1 = leftSide -> unionPointer -> Solve();
            break;
    
            case 5:
                table1 = leftSide -> differencePointer -> Solve();
            break;
    
            case 6:
                table1 = leftSide -> productPointer -> Solve();
            break;
    
            case 7:
                table1 = leftSide -> joinPointer -> Solve();
            break;
        }
    
        Table table2;
        switch (rightSide -> expressionType) {
              /* 0 = relation name
              1 = select
              2 = project
              3 = rename
              4 = Union
              5 = Difference
              6 = Product
              7 = join    */
            
            case 0:
                tableKey = engine.FindTableKey(rightSide -> relationPointer -> name);
                table2 = engine.allTables[tableKey];
            break;
    
            case 1:
                table2 = rightSide -> selectionPointer -> Solve();
            break;
    
            case 2:
                table2 = rightSide -> projectionPointer -> Solve();
            break;
    
            case 3:
                table2 = rightSide -> renamePointer -> Solve();
            break;
    
            case 4:
                table2 = rightSide -> unionPointer -> Solve();
            break;
    
            case 5:
                table2 = rightSide -> differencePointer -> Solve();
            break;
    
            case 6:
                table2 = rightSide -> productPointer -> Solve();
            break;
    
            case 7:
                table2 = rightSide -> joinPointer -> Solve();
            break;
        }
        return engine.NaturalJoin(table1, table2);
    }
}









