#ifndef CLIST_H
#define CLIST_H

// -----------------------------------------------------------------------------
//                                    Info
// -----------------------------------------------------------------------------

/// @file    clist.h
/// @author  John Anthony <john@jo.hnanthony.com>
/// @version 0.1
///
/// @section LICENSE
///
/// Copyright (C) 2013 John Anthony
///
/// This program is free software: you can redistribute it and/or modify it under
/// the terms of the GNU General Public License as published by the Free Software
/// Foundation, either version 3 of the License, or (at your option) any later
/// version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
/// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
/// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
/// details.
///
/// You should have received a copy of the GNU General Public License along with
/// this program.  If not, see <http://www.gnu.org/licenses/>.
///
/// @section DESCRIPTION
///
/// A simple, generic circularly linked list structure using a generic data
/// structure.

// -----------------------------------------------------------------------------
//                                 Structures
// -----------------------------------------------------------------------------

/// Individual elements within a circular linked list
///
/// These should almost universally be created and managed by the clist_
/// functions. You should only be referencing them.
struct clist_elem {
    struct clist_elem *next;
    struct clist_elem *prev;
    void *data;
};

/// A generic circular linked list struct
///
/// This structure must be initialised with clist_init() before use. When done
/// with, use list_destroy. Note that this differs by not providing a
/// transparent data structure -- to access the head (or tail) element you must
/// use a getter function. The "link" member of this struct is an empty list
/// element used for handle termination when iterating correctly.
struct clist {
    struct clist_elem link;
};

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

/// Initialises a circularly linked list. This operation must be called on a
/// circularly linked list before the clist can be used with any other
/// operation. Obligation to free is passed out to the caller through the list
/// parameter.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing an initialised clist to this function is undefined
/// behaviour. Expect a memory leak.
///
/// @param clist The circular linked list to initialise
void clist_init(/*@out@*/ struct clist *clist);

/// Destroys a circularly linked list. No other operations are permitted after
/// destroying unless clist_init is called on the list again. This function
/// removes all elements from the list and calls destroy on their data unless
/// destroy is NULL.
///
/// COMPLEXITY: O(n)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param clist The list to destroy
/// @param destroy The function to use to free all element data.
void clist_destroy(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data));

// -----------------------------------------------------------------------------
//                                 Accessors
// -----------------------------------------------------------------------------

/// Returns the first element of a circularly linked list. Returns NULL if the
/// clist is empty.
///
/// COMPLEXITY: O(1)
///
/// @param clist The circularly linked list to return the head element of
///
// @return The first element of the clist or NULL for an empty dlist
/*@null@*/
struct list_elem* clist_get_head(/*@notnull@*/ struct clist *clist);

/// Returns the last element of a circularly linked list. Returns NULL if the
/// clist is empty.
///
/// COMPLEXITY: O(1)
///
/// @param clist The circularly linked list to return the head element of
///
// @return The first element of the clist or NULL for an empty dlist
/*@null@*/
struct list_elem* clist_get_tail(/*@notnull@*/ struct clist *clist);

// -----------------------------------------------------------------------------
//                                Manipulation
// -----------------------------------------------------------------------------

/// Inserts an element into a circularly linked list at the head.
///
/// COMPLEXITY: O(1)
///
/// @param clist The list to insert at the head of
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int clist_ins_head(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void *data);

/// Inserts an element to a circularly linked list after the given element.
///
/// COMPLEXITY: O(1)
///
/// @param elem The element to insert after
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int clist_ins_next(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void *data);

/// Inserts an element to a circularly linked list before the given element.
/// clist is required so that when elem is the list's head element, the list's
/// head is reset appropriately.
///
/// COMPLEXITY: O(1)
///
/// @param clist The parent list. Used for resetting the list head
/// @param elem The element to insert before
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int clist_ins_prev(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void *data);

/// Inserts an element into a circularly linked list at the tail end.
///
/// COMPLEXITY: O(1)
///
/// @param clist The list to insert at the tail of
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int clist_ins_tail(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void *data);

/// Removes an element from a circularly linked list. dlist is required so that
/// clist->head can be changed if we are removing the head of the list. The
/// destroyed element will have destroy() called upon elem->data to free it if
/// destroy is non-NULL.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param clist Parent list to remove from
/// @param elem The element to remove
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int clist_rem_elem(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void (*destroy)(void *data));

/// Removes an element from the head of a circularly-linked list. If destroy is
/// non-NULL it will be used to free the element's data.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param clist The clist to remove from the head of
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int clist_rem_head(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data));

/// Removes an element from the tail of a circularly-linked list. If destroy is
/// non-NULL it will be used to free the element's data.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param clist The clist to remove from the tail of
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int clist_rem_tail(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data));

/// Counts the elements in a clist. This is highly inefficient and probably not
/// a good use of a linked list.
///
/// COMPLEXITY: O(n)
///
/// @param dlist Doubly-linked list whose elements to count
///
/// @return Number of elements in list.
int clist_size(/*@notnull@*/ const struct clist *clist);

// -----------------------------------------------------------------------------
//                               Looping Macros
// -----------------------------------------------------------------------------

/// A macro for generating for loops - loop over all the elements of a clist
///
/// COMPLEXITY: O(n)
///
/// @param clist The clist to iterate over
/// @param name The name used for the iterator
#define clist_for_each(clist, name)                         \
    for (struct clist_elem * name = clist->link->next;      \
         name != clist->link;                               \
         name = name->next)

/// A macro for generating for loops - loop over all the elements of a
/// clist. This safe version allows for removal of the current element
///
/// COMPLEXITY: O(n)
///
/// @param clist The clist to iterate over
/// @param name The name used for the iterator
/// @param temp Name to use for temporary storage
#define clist_for_each_safe(clist, name, temp)                \
    for (struct clist_elem                                    \
             * name = clist->link->next,                      \
             * __temp_elem = name->next;                      \
         name != clist->link;                                 \
         name = __temp_elem, __temp_elem = __temp_elem->next)

/// A macro for generating for loops - loop over all the elements of a clist
/// backwards, starting with the tail and ending with the head
///
/// COMPLEXITY: O(n)
///
/// @param clist The clist to iterate over
/// @param name The name used for the iterator
#define clist_for_each_rev(clist, name)                     \
    for (struct clist_elem * name = clist->link->prev;      \
         name != clist->link;                               \
         name = name->prev)

/// A macro for generating for loops - loop over all the elements of a
/// clist. This safe version allows for removal of the current element
///
/// COMPLEXITY: O(n)
///
/// @param clist The clist to iterate over
/// @param name The name used for the iterator
/// @param temp Name to use for temporary storage
#define clist_for_each_rev_safe(clist, name, temp)            \
    for (struct clist_elem                                    \
             * name = clist->link->prev,                      \
             * __temp_elem = name->prev;                      \
         name != clist->link;                                 \
         name = __temp_elem, __temp_elem = __temp_elem->prev)

// -----------------------------------------------------------------------------
//                                    End
// -----------------------------------------------------------------------------

#endif // CLIST_H
