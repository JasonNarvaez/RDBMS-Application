/* ------------------------------------------------------------------------------
This software is in the public domain, furnished "as is", without technical
support, and with no warranty, express or implied, as to its usefulness for
any purpose.
  
File: Table.h
  
Author: JustGoogleIt

Date: February 14, 2016

Class: Table

Functions:
	Header(string, string);
------------------------------------------------------------------------------ */

#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

using namespace std;

class Header {

public:
	string name;
	string type;

  	Header(string, string);
};

/*--------------------------------------------------
Constructors
--------------------------------------------------*/
Header::Header(string _name, string _type) {
	name = _name;
	type = _type;
}

#endif