// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "map.cpp"
#include "Iterator.h"
#include <iostream>
#include <string>

void main()
{
	//0 - black
	//1 - red
	


	map<int, char> map;
	map.insert(9, 'a');
	map.insert(8, 'b');
	map.insert(7, 'c');
	map.insert(6, 'd');
	map.insert(1, 'e');
	map.remove(7);
    map.get_value(); //elem key color
  //  map.get_keys();

	getchar();
}