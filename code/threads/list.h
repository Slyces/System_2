// list.h
//      Data structures to manage LISP-like lists.
//
//      As in LISP, a list can contain any type of data structure
//      as an item on the list: thread control blocks,
//      pending interrupts, etc.  That is why each item is a "void *",
//      or in other words, a "pointers to anything".
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef LIST_H
#define LIST_H

#include "copyright.h"
#include "utility.h"

// The following class defines a "list element" -- which is
// used to keep track of one item on a list.  It is equivalent to a
// LISP cell, with a "car" ("next") pointing to the next element on the list,
// and a "cdr" ("item") pointing to the item on the list.
//
// Internal data structures kept public so that List operations can
// access them directly.

class ListElement:dontcopythis
{
  public:
    ListElement (void *itemPtr, long long sortKey);	// initialize a list element

    ListElement *next;		// next element on list,
    // NULL if this is the last
    long long key;			// priority, for a sorted list
    void *item;			// pointer to item on the list

};

// The following class defines a "list" -- a singly linked list of
// list elements, each of which points to a single item on the list.
//
// By using the "Sorted" functions, the list can be kept in sorted
// in increasing order by "key" in ListElement.

class List:dontcopythis
{
  public:
    List ();			// initialize the list
    ~List ();			// de-allocate the list

    void Prepend (void *item);	// Put item at the beginning of the list
    void Append (void *item);	// Put item at the end of the list
    void *Remove ();		// Take item off the front of the list

    void Mapcar (VoidFunctionPtr func);	// Apply "func" to every element
    // on the list
    bool IsEmpty ();		// is the list empty?


    // Routines to put/get items on/off list in order (sorted by key)
    void SortedInsert (void *item, long long sortKey);	// Put item into list
    void *SortedRemove (long long *keyPtr);	// Remove first item from list

  private:
    ListElement * first;	// Head of the list, NULL if list is empty
    ListElement *last;		// Last element of list
    #ifdef CHANGED
    int length;
    #endif //CHANGED
};

#ifdef CHANGED

class IndexedElement
{
  public:
    IndexedElement (void *itemPtr, int sortKey);	// initialize a list element
    ~IndexedElement();
    void InsertAfter (IndexedElement *elt);
    void InsertBefore (IndexedElement *elt);
    void Detach();

    IndexedElement *next;		// next element on list,
    IndexedElement *prev;   // previous element on list
    // NULL if this is the last
    int key;			// priority, for a sorted list
    void *item;			// pointer to item on the list
};

class IndexedList
{
public:
  IndexedList ();			// initialize the list
  ~IndexedList ();			// de-allocate the list

  // on the list
  bool IsEmpty ();		// is the list empty?

  int Insert (void *item);	// Put item into first key available
  void *Remove (int key);	// Remove the item of given key
  void *Find (int key);		// Gets the item of given key

private:
  bool Select(int key);

  IndexedElement *current;
  IndexedElement *first;	// Head of the list, NULL if list is empty
  IndexedElement *last;		// Last element of list
};

#endif //CHANGED

#endif // LIST_H
