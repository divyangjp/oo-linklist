/**
* File Name 	: uselist.cpp
* Functionality : Testing linklist class

* Copyright (C) 2012 Divyang Patel

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include "linklist.h"

using namespace std;

int main()
{
	linklist<int> intList;

	intList.append(1);
	intList.append(2);
	intList.append(3);
	intList.append(4);

	intList.print();

	intList.remove(2);
	intList.insert( 22, 3 );
	intList.print();

	intList.insert(10,1);
	intList.print();

	intList.remove(1);
	intList.print();

	intList.insert(11,0);
	intList.insert(11,1);
	intList.insert(55, intList.size());
	intList.print();


	cout << "Element 3 found at position " << intList.find(3) << endl; 
	cout << "Element 55 found at position " << intList.find(55) << endl; 
	cout << "Element 44 found at position " << intList.find(44) << endl; 
	// Case2

	linklist<int> intList2;

	intList2.remove(0);
	intList2.insert(1,5);
	intList2.remove(0);
	intList2.print();

	// Case 3 : Test copy ctor
	
	cout << endl << "****************************************************" << endl;
        cout << "                 Testing copy ctor for list              " << endl;
        cout << "****************************************************" << endl;

	linklist<int> intList3(intList);
	intList3.print();
	cout << "Size of intList3 = " << intList3.size() << endl;
	cout << "Size of intList = " << intList.size() << endl;


	// Case 4 : Test sort

	cout << endl << "****************************************************" << endl;
	cout << "                 Testing Sort for list		     " << endl;
	cout << "****************************************************" << endl;
	intList.sort();

	intList.print();

	// Case 5 : Test operator= (Assignment operator)

	cout << endl << "****************************************************" << endl;
        cout << "                 Testing operator=		     " << endl;
        cout << "****************************************************" << endl;

	linklist<int>	assignList;
	assignList = intList;
	assignList.print();

	return 0;
}
