#ifndef LIST_H
#define LIST_H 1

/**
 * \file list.h
 * \brief Implementation of a doubly-linked list
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


// {{{ Structures
/** \brief Basic implementation of items contained in a  doubly linked list
 *
 * Really basic impementation of items stored in a doubly linked list which 
 * will be used in list-represented graph
 * */
typedef struct Item_s {
    /** Number field of an item. 
     * It is an integer representing a vertex number. */
    int _num;
    /** Value field of an item. 
     * It is an integer representing a value or capacity. */
    int _val;
    
    /** Next field of an item. 
     * It points to the next item or NULL if it is the tail. */ 
    struct Item_s * _next;
    /** Previous field of an item. 
     * It points to the previous item or NULL if it is the head. */
    struct Item_s * _prev;
} Item;

/** Macro for the number field of an item. */
#define num(e)  e->_num
/** Macro for the value field of an item. */
#define val(e)  e->_val
/** Macro for the next field of an item. */
#define next(e) e->_next
/** Macro for the previous field of an item. */
#define prev(e) e->_prev

#define SIZE_ITEM (2*sizeof(int) + 2*sizeof(Item *))

/**
 * Structure representing a doubly-linked list.
 */
typedef struct {
    /** Number of item in the list. */
    int _nb;
    
    /** Begin field of a list.
     * Points to the head of the list or NULL if the list is empty. */
    Item * _begin;
    /** End field of a list.
     * Points to the tail of the list or NULL if the list is empty. */
    Item * _end;
} List;
// }}}

// {{{ Macros
/** Macro for the begin field of a list. */
#define begin(l) l->_begin
/** Macro for the end field of a list. */
#define end(l)   l->_end
/** Macro for the number if item field of a list. */
#define nb(l)    l->_nb
// }}}

#define SIZE_LIST (sizeof(int) + 2*sizeof(Item *))

// {{{ Memory management
/**
 * Allocates the memory and returns an empty List.
 * \return A pointer to a new empty List.
 */
List * allocList();
/**
 * Free the memory.
 * \param l A pointer to the list that will be freed.
 */
void   freeList(List * l);
/**
 * Return a copy of a list.
 * Allocate a new list and copy each item.
 * \param l A pointer to the list that will be copied.
 * \return A pointer to the copied List.
 */
List * copyList(List * l);
//}}}

// {{{ Display Functions
/**
 * Print a List.
 * \param f File descriptor the List will be printed on.
 * \param l Pointer to the List that will be printed.
 */
void printList (FILE * f, List * l);
/**
 * Print a list in the reverse order.
 * \param f File descriptor the list will be printed on.
 * \param l Pointer to the list that will be printed.
 */
void printListReverse (FILE * f, List * l);
// }}}

// {{{ List Operations
/**
 * Push an element at the head of a List.
 * \param l Pointer to the list.
 * \param num Number field of the new item.
 * \param val Value field of the new item.
 */
void pushHead(List * l, int num, int val);
/**
 * Push an element at the tail of a List.
 * \param l Pointer to the list.
 * \param num Number field of the new item.
 * \param val Value field of the new item.
 */

void pushTail(List * l, int num, int val);
/**
 * Insert an element in an ordered List.
 * \param l Pointer to a List assumed to be number-ordered.
 * \param num Number field of the new item.
 * \param val Value field of the new item.
 */
void insertNum(List * l, int num, int val);

/**
 * Pop the first element of a List.
 * \param l Pointer to the List to be head-popped.
 */
void popHead(List * l);
/**
 * Pop the last element of a List.
 * \param l Pointer to the List to be tail-popped.
 */
void popTail(List * l);
/**
 * Pop the item with specific number field.
 * \param l Pointer to a List which is assumed to be number-ordered.
 * \param num The number field of the item to pop.
 */
void popNum(List * l, int num);
// }}}

// {{{ Item informations
/**
 * Returns the value field of the item with a specific number field
 * or 0 if not found.
 * \param l Pointer to a List.
 * \param num The number field to find.
 */ 
int valOfNum(List * l, int num);
// }}}

#endif /* LIST_H */





