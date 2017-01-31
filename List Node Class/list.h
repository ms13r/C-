// Fig. 21.4: list.h
// Template List class definition.
// Work done by Miroslav Sanader with adaptation from textbook (Introduction to C++)
#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::cout;

#include <new>
#include "listnode.h"  

template< class NODETYPE >
class List {

public:
   List();      // constructor
   ~List();     // destructor
   void insertAtFront( const NODETYPE & );
   void insertAtBack( const NODETYPE & );
   void insertMiddle( const NODETYPE &value , const int index);
   bool removeFromFront( NODETYPE & );
   bool removeFromBack( NODETYPE & );
   bool removeMiddle( NODETYPE & , const int index);
   
   bool isEmpty() const;
   void print() const;

private:
   ListNode< NODETYPE > *firstPtr;  // pointer to first node
   ListNode< NODETYPE > *lastPtr;   // pointer to last node

   // utility function to allocate new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE & );

}; // end class List

// default constructor
template< class NODETYPE >
List< NODETYPE >::List()   : firstPtr( 0 ),  lastPtr( 0 ) 
{ 
} 

// destructor
template< class NODETYPE >
List< NODETYPE >::~List()
{
   if ( !isEmpty() ) {    // List is not empty

      ListNode< NODETYPE > *currentPtr = firstPtr;
      ListNode< NODETYPE > *tempPtr;

      while ( currentPtr != 0 )         // delete remaining nodes
      {  
         tempPtr = currentPtr;
         currentPtr = currentPtr->nextPtr;
         delete tempPtr;

      }

   }

} // end List destructor

// insert node at front of list
template< class NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else { 
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;
   } 

} // end function insertAtFront

template<class NODETYPE>
void List<NODETYPE>::insertMiddle( const NODETYPE &value , const int index)
{
	ListNode<NODETYPE> * temp = getNewNode(value);
	ListNode<NODETYPE> * currentPtr = firstPtr;
	
	int counter = 2;
	
	if(isEmpty() || (index <= 0))		//If empty or index is negative
		insertAtFront(value);
	else
	{
		while(currentPtr->nextPtr != 0 && (counter < index))
		{
			currentPtr = currentPtr->nextPtr;
			counter++;
		}
		if(currentPtr->nextPtr == 0)
			insertAtBack(value);
		else
		{
			temp->nextPtr = currentPtr->nextPtr;
			currentPtr->nextPtr = temp;
		}
	}
}

// insert node at back of list
template< class NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      lastPtr->nextPtr = newPtr;
      lastPtr = newPtr;

   } // end else

} // end function insertAtBack

// delete node from front of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value )
{
   if ( isEmpty() )  // List is empty
      return false;  // delete unsuccessful

   else {  
      ListNode< NODETYPE > *tempPtr = firstPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else
         firstPtr = firstPtr->nextPtr;

      value = tempPtr->data;  // data being removed
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromFront



template<class NODETYPE>
bool List<NODETYPE>::removeMiddle( NODETYPE &value, const int index)
{
	if(isEmpty() || (index <= 0))
		return false;
	else if(index == 1)
		removeFromFront(value);
	else
	{
		int counter = 2;
		ListNode<NODETYPE> * currentPtr = firstPtr;
		ListNode<NODETYPE> * previous = currentPtr;
		
		while((currentPtr->nextPtr != 0) && (counter <= index))
		{
			previous = currentPtr;
			currentPtr = currentPtr->nextPtr;
			counter++;
		}
		if(counter < index)
			return false;
		if(currentPtr->nextPtr == 0)
			removeFromBack(value);
		else 
		{	
			previous->nextPtr = currentPtr->nextPtr;
			value = currentPtr->data;
			delete currentPtr;
		}
		return true;
	}
}


// delete node from back of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
   if ( isEmpty() )
      return false;  // delete unsuccessful

   else {
      ListNode< NODETYPE > *tempPtr = lastPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else {
         ListNode< NODETYPE > *currentPtr = firstPtr;

         // locate second-to-last element
         while ( currentPtr->nextPtr != lastPtr )
            currentPtr = currentPtr->nextPtr;

         lastPtr = currentPtr;
         currentPtr->nextPtr = 0;

      } // end else

      value = tempPtr->data;
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromBack

// is List empty?
template< class NODETYPE > 
bool List< NODETYPE >::isEmpty() const 
{ 
   return firstPtr == 0; 
   
} // end function isEmpty

// return pointer to newly allocated node
template< class NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode( 
   const NODETYPE &value )
{
   return new ListNode< NODETYPE >( value );

} // end function getNewNode

// display contents of List
template< class NODETYPE >
void List< NODETYPE >::print() const
{
   if ( isEmpty() ) {
      cout << "The list is empty\n\n";
      return;

   } // end if

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;

   } // end while

   cout << "\n\n";

} // end function print

#endif
