// list.cc
//
//      Routines to manage a singly-linked list of "things".
//
//      A "ListElement" is allocated for each item to be put on the
//      list; it is de-allocated when the item is removed. This means
//      we don't need to keep a "next" pointer in every object we
//      want to put on a list.
//
//      NOTE: Mutual exclusion must be provided by the caller.
//      If you want a synchronized list, you must use the routines
//      in synchlist.cc.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "list.h"

//----------------------------------------------------------------------
// ListElement::ListElement
//      Initialize a list element, so it can be added somewhere on a list.
//
//      "itemPtr" is the item to be put on the list.  It can be a pointer
//              to anything.
//      "sortKey" is the priority of the item, if any.
//----------------------------------------------------------------------

ListElement::ListElement (void *itemPtr, long long sortKey)
{
    item = itemPtr;
    key = sortKey;
    next = NULL;		// assume we'll put it at the end of the list
}

//----------------------------------------------------------------------
// List::List
//      Initialize a list, empty to start with.
//      Elements can now be added to the list.
//----------------------------------------------------------------------

List::List ()
{
    first = last = NULL;
    #ifdef CHANGED
    length = 0;
    #endif //CHANGED
}

//----------------------------------------------------------------------
// List::~List
//      Prepare a list for deallocation.  If the list still contains any
//      ListElements, de-allocate them.  However, note that we do *not*
//      de-allocate the "items" on the list -- this module allocates
//      and de-allocates the ListElements to keep track of each item,
//      but a given item may be on multiple lists, so we can't
//      de-allocate them here.
//----------------------------------------------------------------------

List::~List ()
{
    while (Remove () != NULL)
	;			// delete all the list elements
}

//----------------------------------------------------------------------
// List::Append
//      Append an "item" to the end of the list.
//
//      Allocate a ListElement to keep track of the item.
//      If the list is empty, then this will be the only element.
//      Otherwise, put it at the end.
//
//      "item" is the thing to put on the list, it can be a pointer to
//              anything.
//----------------------------------------------------------------------

void
List::Append (void *item)
{
    ListElement *element = new ListElement (item, 0);

    if (IsEmpty ())
      {				// list is empty
    	  first = element;
    	  last = element;
      }
    else
      {				// else put it after last
    	  last->next = element;
    	  last = element;
      }
      #ifdef CHANGED
      length++;
      #endif //CHANGED
}

//----------------------------------------------------------------------
// List::Prepend
//      Put an "item" on the front of the list.
//
//      Allocate a ListElement to keep track of the item.
//      If the list is empty, then this will be the only element.
//      Otherwise, put it at the beginning.
//
//      "item" is the thing to put on the list, it can be a pointer to
//              anything.
//----------------------------------------------------------------------

void
List::Prepend (void *item)
{
    ListElement *element = new ListElement (item, 0);

    if (IsEmpty ()) {				// list is empty
    	  first = element;
    	  last = element;
      }
    else {				// else put it before first
    	  element->next = first;
    	  first = element;
      }
      #ifdef CHANGED
      length++;
      #endif //CHANGED
}

//----------------------------------------------------------------------
// List::Remove
//      Remove the first "item" from the front of the list.
//
// Returns:
//      Pointer to removed item, NULL if nothing on the list.
//----------------------------------------------------------------------

void *
List::Remove ()
{
    return SortedRemove (NULL);	// Same as SortedRemove, but ignore the key
}

//----------------------------------------------------------------------
// List::Mapcar
//      Apply a function to each item on the list, by walking through
//      the list, one element at a time.
//
//      Unlike LISP, this mapcar does not return anything!
//
//      "func" is the procedure to apply to each element of the list.
//----------------------------------------------------------------------

void
List::Mapcar (VoidFunctionPtr func)
{
    for (ListElement * ptr = first; ptr != NULL; ptr = ptr->next)
      {
	  DEBUG ('l', "In mapcar, about to invoke 0x%x(0x%x)\n", func, ptr->item);
	  (*func) (ptr->item);
      }
}

//----------------------------------------------------------------------
// List::IsEmpty
//      Returns TRUE if the list is empty (has no items).
//----------------------------------------------------------------------

bool
List::IsEmpty ()
{
    if (first == NULL)
	return TRUE;
    else
	return FALSE;
}

//----------------------------------------------------------------------
// List::SortedInsert
//      Insert an "item" into a list, so that the list elements are
//      sorted in increasing order by "sortKey".
//
//      Allocate a ListElement to keep track of the item.
//      If the list is empty, then this will be the only element.
//      Otherwise, walk through the list, one element at a time,
//      to find where the new item should be placed.
//
//      "item" is the thing to put on the list, it can be a pointer to
//              anything.
//      "sortKey" is the priority of the item.
//----------------------------------------------------------------------

void
List::SortedInsert (void *item, long long sortKey)
{
    ListElement *element = new ListElement (item, sortKey);
    ListElement *ptr;		// keep track

    #ifdef CHANGED
    length++;
    #endif //CHANGED
    if (IsEmpty ())
      {				// if list is empty, put
    	  first = element;
    	  last = element;
      }
    else if (sortKey < first->key)
      {
	  // item goes on front of list
    	  element->next = first;
    	  first = element;
      }
    else
      {				// look for first elt in list bigger than item
    	  for (ptr = first; ptr->next != NULL; ptr = ptr->next) {
      		if (sortKey < ptr->next->key) {
      		      element->next = ptr->next;
      		      ptr->next = element;
      		      return;
      		  }
    	    }
    	  last->next = element;	// item goes at end of list
    	  last = element;
      }
}

//----------------------------------------------------------------------
// List::SortedRemove
//      Remove the first "item" from the front of a sorted list.
//
// Returns:
//      Pointer to removed item, NULL if nothing on the list.
//      Sets *keyPtr to the priority value of the removed item
//      (this is needed by interrupt.cc, for instance).
//
//      "keyPtr" is a pointer to the location in which to store the
//              priority of the removed item.
//----------------------------------------------------------------------

void *
List::SortedRemove (long long *keyPtr)
{
    ListElement *element = first;
    void *thing;

    if (IsEmpty ())
	     return NULL;

    #ifdef CHANGED
    length--;
    #endif //CHANGED

    thing = first->item;
    if (first == last)
      {				// list had one item, now has none
	  first = NULL;
	  last = NULL;
      }
    else
      {
	  first = element->next;
      }
    if (keyPtr != NULL)
	*keyPtr = element->key;
    delete element;
    return thing;
}

#ifdef CHANGED
// =============================================================================
IndexedElement::IndexedElement (void *itemPtr, int integerKey)
{
    item = itemPtr;
    key = integerKey;
    next = NULL;
    prev = NULL;
}

IndexedElement::~IndexedElement () {
    delete next;
    delete prev;
}

void
IndexedElement::InsertAfter(IndexedElement *elt)
{
  // printf("insert 0x%x between 0x%x and 0x%x", this, elt, elt->next);
  prev = elt;
  next = elt->next;
  elt->next = this;
  if (next != NULL)
    next->prev = this;
}

void
IndexedElement::InsertBefore(IndexedElement *elt)
{
  // printf("insert 0x%x between 0x%x and 0x%x", this, elt->prev, elt);
  next = elt;
  prev = elt->prev;
  elt->prev = this;
  if (prev != NULL)
    prev->next = this;
}

void
IndexedElement::Detach()
{
  // printf("detach 0x%x from 0x%x and 0x%x", this, this->prev, this->next);

  if (next != NULL)
    next->prev = prev;
  if (prev != NULL)
    prev->next = next;
}

// =============================================================================

IndexedList::IndexedList ()
{
    first = last = current = NULL;
}

IndexedList::~IndexedList ()
{
    while (first != NULL) {
      Remove(first->key);
    }
}

int
IndexedList::Insert (void *item)
{
    IndexedElement *element = new IndexedElement (item, -1);
    IndexedElement *next_elt;		// keep track

    // printf("Insert Call [first = 0x%x] [last = 0x%x] | ", first, last);

    int key = 0;

    if (IsEmpty()) {
      // printf("empty - created 0x%x [new first]\n", element);
      element->key = key;
    	first = element;
      last = element;
    } else {
    	  for(next_elt = first; next_elt != NULL; next_elt = next_elt->next) {
          if (key < next_elt->key) {
            // printf("[ %d < %d] ", key, next_elt->key);
            element->key = key;
            element->InsertBefore(next_elt);
            if (key == 0) {
              first = element;
              // printf("[new first]\n");
            } // else printf(" => created %d\n", key);
            return key;
          }
          key++;
        } // last
        element->key = key;
        element->InsertAfter(last);
        last = element;
        printf(" [new last] ");
    }
    printf(" => created %d\n", key);
    return key;
}

bool
IndexedList::Select(int key)
{
  if (IsEmpty()) return false;
  if(current == NULL) current = first;
  if (current->key <= key) {
    for (current = current; current->key <= key; current = current->next) {
      if (current->key == key) {
        return true;
      }
    }
  } else if (key <= current->key) {
    for (current = current; current->key >= key; current = current->prev) {
      if (current->key == key) {
        return true;
      }
    }
  }
  return false;
}

void *
IndexedList::Find (int key)
{
  if (Select(key))
    return current->item;
  else
    return NULL;
}

void *
IndexedList::Remove (int key)
{
  if (Select(key)) {
    current->Detach();
    if (current == first)
      first = current->next;
    if (current == last)
      last = current->prev;
    void * return_item = current->item;
    // delete current;
    current = first;
    printf("Deleted %d\n", key);
    return return_item;
  } else return NULL;
}

bool
IndexedList::IsEmpty ()
{
    if (first == NULL) return TRUE;
    else return FALSE;
}



#endif //CHANGED
