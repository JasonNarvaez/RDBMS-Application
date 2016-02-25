# RDBMS
<strong>Team: </strong>JustGoogleIt <br>
<strong>Members: </strong>Cat Ockman, Camila Barney, Jason Narvaez, Joshua Churning

<h3>Development Log</h3>
https://docs.google.com/document/d/1jCeiHIZrsFMUjXuWPWD7mqUyc7AsgWJRsMEUlqFJPvo/edit?usp=sharing

<h3>Description</h3>
This is the relational database management system (RDBMS) engine for our team project for CSCE 315 - Programming studio.

<h3>Compile / Run Instructions</h3>
Navigate to the engine folder first <br>
<strong>Compile: </strong>make <br>
<strong>Run: </strong>make run <br>
<strong>Clean: </strong> make c

<h3>Compile / Run Unit Testing</h3>
Navigate to the googleTest folder <br>
<strong>Compile: </strong>make <br>
<strong>Run: </strong>./testCreation<br>


<h3>Table Functions</h3>
<strong>CreateTable</strong> (string name, vector \<string\> primaryKey) <br>
<strong>CreateTable</strong> (string name, Table table) <br>
<strong>AddColumn</strong> (string tableName, string columnName, string type)<br>
<strong>UpdateEntry</strong> (string tableName, string data, string columnName, string condition)<br>
<strong>DeleteTable</strong> (string tableName, string columnName, string condition)<br>
<strong>DisplayTable</strong> (string tableName)<br>
<strong>DisplayTable</strong> (Table table)<br>

<h3>Relational Algebra Functions</h3>
<strong>Selection</strong> (string tableName, string conditionColum, string conditionType ,string condition)<br>
<strong>Projection</strong> (string tableName, vector \<string\> columns)<br>
<strong>Renaming</strong> (string tableName, vector \<string\> oldColumnNames, vector \<string\> newColumnNames)<br>
<strong>SetUnion</strong> (string taleName1, string taleName2)<br>
<strong>SetDifference</strong> (string tableName1, string tableName2)<br>
<strong>CrossProduct</strong> (string tableName1, string tableName2)<br>

<h3>Other Functions</h3>
<strong>NaturalJoin</strong> (string tableName1, string tableName2)<br>
<strong>Save</strong> (string filename)<br>
<strong>Open</strong> (string filename)<br>



