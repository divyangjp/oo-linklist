/**
* File Name 	: linklist.h
* Functionality : Generic implementation of linklist in C++.
*		  This can be used in various data-structure algos.

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


#include <iostream>
#include <new>
using namespace std;

template <class T>
struct Node
{
	T nodeData_;
        Node<T> *nextNode_;
};

template <class T>
class linklist
{
	 private:
		Node<T> *headNode_;
                int nodeCount_;

	public:
		linklist();
		linklist( const linklist& obj );
		~linklist();

		linklist& operator=( const linklist& obj );

		void append( const T& data ) throw(bad_alloc);
		void insert( const T& data, const int& position );
		void remove( const int& pos );
		int size();
		T first();
		int find( const T& elem );
		void print();
		void sort();
		Node<T>* mergeSort( Node<T>* head, int count );
		Node<T>* merge( Node<T>* leftnode, int lcount, Node<T>* rightnode, int rcount);

};

/*********************************************
 Function 	: Default constructor
 
 Purpose 	: Initialization
*********************************************/

template <class T>
linklist<T>::linklist():headNode_(0), nodeCount_(0)
{
}

/********************************************
 Function 	: Copy constructor

 Purpose	: Copy one list to other
*******************************************/

template <class T>
linklist<T>::linklist( const linklist& obj )
{
	headNode_ = NULL;
	int tmpcount = obj.nodeCount_;
	Node<T>* objTmpHeadNode = obj.headNode_;

	for( int i = 1; i <= tmpcount; i++ )
	{
		try
		{
			this->append( objTmpHeadNode->nodeData_ );
		}
		catch(bad_alloc& ba)
		{
			cout << "Memory can not be allocated" << endl;
			cout << ba.what();
		}
		objTmpHeadNode = objTmpHeadNode->nextNode_;
	}
}

/*******************************************
 Function 	: Destructor

 Purpose	: Correctly free the memory
*******************************************/

template <class T>
linklist<T>::~linklist()
{
#ifdef DEBUG
	cout << "Destructing list" << endl ;
#endif	
	Node<T>* tmpNode = headNode_;

	while(headNode_)
	{
		headNode_ = tmpNode->nextNode_;
		delete tmpNode;
		tmpNode = headNode_;
	}
}


/********************************************
 Function 	: Assignment Operator (operator=)

 Purpose	: Copy one list to other
*******************************************/

template <class T>
linklist<T>& linklist<T>::operator=( const linklist<T>& obj )
{
#ifdef DEBUG
	cout << "operator= invoked" << endl;
#endif
	headNode_ = NULL;
        int tmpcount = obj.nodeCount_;
        Node<T>* objTmpHeadNode = obj.headNode_;

        for( int i = 1; i <= tmpcount; i++ )
        {
		try
		{
                	this->append( objTmpHeadNode->nodeData_ );
		}
		catch(bad_alloc& ba)
		{
			cout << "Memory can not be allocated" << endl;
			cout << ba.what();
		}
                objTmpHeadNode = objTmpHeadNode->nextNode_;
        }
	
}


/*********************************************************************************************
	
	Function	: append

	Purpose		: Appends "data" to the end of list
			  If list is empty, adds the first node.

**********************************************************************************************/

template <class T>
void linklist<T>::append( const T& data ) throw(bad_alloc)
{
	Node<T>* newNode = new Node<T>;
	newNode->nodeData_ = data;
	newNode->nextNode_ = NULL;

	if(!headNode_)
	{
		headNode_ = newNode;
	}
	else
	{
		Node<T>* tmpNode = headNode_;
		while( tmpNode->nextNode_ != NULL )
		{
			tmpNode = tmpNode->nextNode_;
		}
		tmpNode->nextNode_ = newNode;
	}

	nodeCount_++;
}

/**********************************************************************************************

	Function	: insert

	Purpose		: Insert "data" at "position" in the list

	Params In	: const T& data, const int& position

	Params Out	:

	Return		: Inserts the data at given position.
			  If list is empty, adds data as first node.
			  If position is greater then the total nodes, can't insert node.
			  If list contains nodes and position is '0', error of invalid position.

************************************************************************************************/

template <class T>
void linklist<T>::insert( const T& data, const int& position )
{
	// If there are no nodes. Insert this as first node.
	if( nodeCount_ == 0 ) 
	{
		this->append( data );
		return;
	}
	if( position == 0 )
	{
		cout << "Invalid position " << position << " to insert data" << endl;
		return;
	}
	if( position > nodeCount_ )
	{
		cout << "There are only "<< nodeCount_ << " nodes in list. Can't insert your data" << endl;
		return;
	}
	else
	{	
		
		Node<T>* newNode = new Node<T>;
		newNode->nodeData_ = data;

		if( position == 1 )
		{
			newNode->nextNode_ = headNode_;
			headNode_ = newNode;
			nodeCount_++;
			return;
		}
	
		Node<T> * tmpNode, * prevNode;
		tmpNode = headNode_;

		for(int i = 1; i<position ; i++)
		{
			prevNode = tmpNode;
			tmpNode = tmpNode->nextNode_;
		}

		newNode->nextNode_ = tmpNode;

		prevNode->nextNode_ = newNode;

		nodeCount_++;
	}
}

/******************************************************************************************************************

	Function	: remove

	Purpose		: Deletes node at given position ('pos' ).

	Params In	: const int& pos
				Position of the node to be deleted.

	Return		: Deletes node at the give position.
			  If list is empty, throw error.
			  If position is '0', throw error invalid position
			  If position is greater than total nodes, throw error incorrect position.

********************************************************************************************************************/

template <class T>
void linklist<T>::remove( const int& pos )
{
	Node<T>* tmpNode = headNode_;
	Node<T>* prevNode = 0;

	// If the list is empty
	if( nodeCount_ == 0 )
	{
		cout << "List is empty. Can't remove" << endl;
		return;
	}

	// If trying to delete 0th node when nodeCount_ > 0
	if( pos == 0 )
	{
		cout << "Invalid position " << pos << endl;
		return;
	}

	// If there are less nodes then the position given
	if( pos > nodeCount_ )
	{
		cout<< "There are only " << nodeCount_ << " nodes in list." << endl;
		return;
	}
	// If everything is Ok. Go ahead with removing node.
	else
	{
		if( pos == 1 )
		{
			headNode_ = tmpNode->nextNode_;
			delete tmpNode;
			nodeCount_--;
			return;
		}
		for( int i = 1; i<pos; i++ )
		{
			prevNode = tmpNode;
			tmpNode = tmpNode->nextNode_;	
		}

		prevNode->nextNode_ = tmpNode->nextNode_;
		delete tmpNode;
		nodeCount_--;
	}
}

/**************************************************************************************************

	Function	: size

	Params In	:

	Params Out	: Total number of nodes

	Returns		: Gives total number of nodes in the list

**************************************************************************************************/

template <class T>
int linklist<T>::size()
{
	return nodeCount_;
}

template <class T>
T linklist<T>::first()
{
	return headNode_->nodeData_;
}

/*************************************************************************************************

	Function	: find

	Purpose		: Finds the element in the list and if present returns the position

	Param In	: const T& elem
				Element to be found

	Param Out	: position of the element

	Return		: Position of the element if SUCCESS.
			  0 if FAILURE	

*************************************************************************************************/

template <class T>
int linklist<T>::find( const T& elem )
{
	Node<T> *tmpNode = headNode_;
	int pos = 1;
	bool found = false;

	while( tmpNode )
	{
		if( tmpNode->nodeData_ == elem )
		{
			found = true;
			return pos;
		}
		else
		{
			tmpNode = tmpNode->nextNode_;
			pos++;
		}	
	}

	if(!found)
	{
	#ifdef DEBUG
		cout << "Element " << elem << " not found in list." << endl;
	#endif	
		return 0;
	}

	return pos;
}

template <class T>
void linklist<T>::print()
{
	Node<T> *tmpNode = headNode_;

	if(tmpNode)
	{
		while(tmpNode)
		{
			cout << "|" << tmpNode->nodeData_ << "|--> " ;
			tmpNode = tmpNode->nextNode_;
		}
		cout << "NULL" << endl; 
	}
	else
	{
		cout<< "List empty" << endl;
	}
}

/*************************************************************************************

	Function :	sort

	Purpose	 :	Sorts list in ascending order using Merge-sort technique.
			Merge-sort provides O(nlogn) complexity.
			sort() uses recursive calls to mergeSort function.
			mergeSort in turn calls merge function.

*************************************************************************************/

template <class T>
void linklist<T>::sort()
{
	headNode_ = mergeSort( headNode_, nodeCount_ );	
}

template <class T>
Node<T>* linklist<T>::mergeSort( Node<T>* first, int total )
{
	if (total < 1) { return first; }
  	if (total < 2) { first->nextNode_ = NULL; return first;}

  	Node<T> * curr = first;
  	int count = total/2;
      	while (count--)
    	{
      		curr = curr->nextNode_;
    	}


  	count = total/2;
  	first = mergeSort(first, count);

  	curr = mergeSort(curr, total-count);

  	return merge(first, count, curr, total-count);

}


template <class T>
Node<T>* linklist<T>::merge( Node<T>* left, int count_left, Node<T>* right, int count_right )
{
    Node<T> * head = NULL;
    Node<T> ** current = &head;

    while (count_left > 0 || count_right > 0)
    {
        if( count_right == 0 || (count_left > 0 && left->nodeData_ < right->nodeData_ ))
        {
            *current = left;
            left = left->nextNode_;
            --count_left;
        }
        else
        {
            *current = right;
            right = right->nextNode_;
            --count_right;
        }
        current = &(*current)->nextNode_;
    }
    return head;

}
