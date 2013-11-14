#ifndef DLIST_H
#define DLIST_H

// -----------------------------------------------------------------------------
//                                    Info
// -----------------------------------------------------------------------------

/// @file    dlist.h
/// @author  John Anthony <john@jo.hnanthony.com>
/// @version 0.1
///
/// @section LICENSE
///
/// Copyright (C) 2013 John Anthony
///
/// This program is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the Free
/// Software Foundation, either version 3 of the License, or (at your option)
/// any later version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
/// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
/// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
/// more details.
///
/// You should have received a copy of the GNU General Public License along with
/// this program.  If not, see <http://www.gnu.org/licenses/>.
///
/// @section DESCRIPTION
///
/// A simple, generic doubly linked list implementation using a generic data
/// structure. All functions are safe to use with empty dlists except dlist_init
/// for obvious reasons.

// -----------------------------------------------------------------------------
//                                 Structures
// -----------------------------------------------------------------------------

/// Individual elements within a doubly linked list
///
/// These should almost universally be created and managed by the dlist_
/// functions. You should only be referencing them.
struct dlist_elem {
    struct dlist_elem *next;
    struct dlist_elem *prev;
    void *data;
};

/// A generic doubly-linked list struct
///
/// When first initialised and when empty, head is NULL. This structure must be
/// initialised with dlist_init() before use. When done with, use
/// dlist_destroy.
struct dlist {
    struct dlist_elem *head;
};

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

/// Initialises a doubly linked list. This operation must be called for a doubly
/// linked list before the dlist can be used with any other operation.
/// Obligation to free is passed out to the caller through the dlist parameter.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing an initialised dlist to this function is undefined
/// behaviour. Expect a memory leak.
///
/// @param dlist The doubly linked list to initialise
void dlist_init(/*@out@*/ /*@notnull@*/ struct dlist *dlist);

/// Destroys a doubly linked list. No other operations are permitted after
/// destroying unless dlist_init is called again. This function removes all
/// elements from the dlist and calls the given destroy function on them unless
/// destroy is set to NULL.
///
/// COMPLEXITY: O(n)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param dlist The dlist to destroy
/// @param destroy The function to use to free all the dlist element data
void dlist_destroy(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data));

// -----------------------------------------------------------------------------
//                                 Accessors
// -----------------------------------------------------------------------------

/// Returns the first element of a doubly-linked list. Returns NULL if the dlist
/// is empty.
///
/// COMPLEXITY: O(1)
///
/// @param dlist The doubly-linked list to return the head element of
///
// @return The first element of the dlist or NULL for an empty dlist
/*@null@*/
struct dlist_elem* dlist_get_head(/*@notnull@*/ const struct dlist *dlist);

/// Counts the elements in a dlist. This is highly inefficient and probably not
/// a good use of a linked list.
///
/// COMPLEXITY: O(n)
///
/// @param dlist Doubly-linked list whose elements to count
///
/// @return Number of elements in dlist.
int dlist_get_size(/*@notnull@*/ const struct dlist *dlist);

/// Returns the last element of a doubly-linked list. Returns NULL if the dlist
/// is empty. This is highly inefficient and you should probably rethink what
/// you're doing.
///
/// COMPLEXITY: O(n)
///
/// @param dlist The doubly-linked list to return the tail element of
///
// @return The last element of the dlist or NULL for an empty dlist
/*@null@*/
struct dlist_elem* dlist_get_tail(/*@notnull@*/ const struct dlist *dlist);

// -----------------------------------------------------------------------------
//                                Manipulation
// -----------------------------------------------------------------------------

/// Inserts an element into a doubly-linked list at the head.
///
/// COMPLEXITY: O(1)
///
/// @param dlist The dlist to insert at the head of
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int dlist_ins_head(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void *data);

/// Inserts an element to a doubly-linked list after the given element.
///
/// COMPLEXITY: O(1)
///
/// @param elem The element to insert after
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int dlist_ins_next(/*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void *data);

/// Inserts an element to a doubly-linked list before the given element. dlist
/// is required so that when elem is the dlist's head element, the list's head
/// is reset appropriately.
///
/// COMPLEXITY: O(1)
///
/// @param dlist The parent dlist. Used for resetting the dlist head
/// @param elem The element to insert before
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int dlist_ins_prev(/*@notnull@*/ struct dlist *dlist,
                   /*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void *data);

/// Inserts an element at the end of a dlist
///
/// COMPLEXITY: O(n)
///
/// @warning cdlists offer O(1) tail insertion. Consider using a cdlist
///
/// @param list The list to insert at the end of
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int dlist_ins_tail(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void *data);

/// Removes an element from a doubly-linked list. dlist is required so that
/// dlist->head can be changed if we are removing the head of the dlist. The
/// destroyed element will have destroy() called upon elem->data to free it if
/// destroy is non-NULL.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param dlist Parent dlist to remove from
/// @param elem The element to remove
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int dlist_rem_elem(/*@notnull@*/ struct dlist *dlist,
                   /*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void (*destroy)(void *data));

/// Removes an element from the head of a doubly-linked list. If destroy is
/// non-NULL it will be used to free the element's data.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param dlist The dlist to remove from the head of
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int dlist_rem_head(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data));

/// Removes an element from the tail of a list. It is the user's responsibility
/// to free the element's data. If destroy is non-NULL it will be called on the
/// element's data to free it.
///
/// COMPLEXITY: O(n)
///
/// @warning cdlists do this operation in O(1). Consider using a cdlist
///
/// @param list The list to remove from the head of
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int dlist_rem_tail(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data));

// -----------------------------------------------------------------------------
//                               Looping Macros
// -----------------------------------------------------------------------------

/// A macro for generating for loops - loop over all the elements of a dlist
///
/// COMPLEXITY: O(n)
///
/// @param dlist The dlist to iterate over
/// @param name The name used for the iterator
#define dlist_for_each(dlist, name)                                     \
    for (struct dlist_elem * name = (dlist)->head; name; name = name->next)

/// A macro for generating for loops - loop over all the elements of a
/// dlist. This safe version allows for removal of the current element
///
/// COMPLEXITY: O(n)
///
/// @param dlist The dlist to iterate over
/// @param name The name used for the iterator
#define dlist_for_each_safe(dlist, name)                            \
    if ((dlist)->head)                                              \
        for (struct dlist_elem                                      \
                 * name = (dlist)->head,                            \
                 * __temp_elem = (dlist)->head->next;               \
             name;                                                  \
             name = __temp_elem, __temp_elem = __temp_elem->next)

/// A macro for looping over a dlist from a given element
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
#define dlist_for_each_elem(elem, name)                             \
    for (struct dlist_elem * name = elem; name; name = name->next)

/// A macro for looping over a dlist from a given element. Safe against element
/// destruction.
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
#define dlist_for_each_elem_safe(elem, name)                    \
    for (struct dlist_elem                                      \
             * name = elem,                                     \
             * __temp_elem = elem->next;                        \
         name;                                                  \
         name = __temp_elem, __temp_elem = __temp_elem->next)

/// A macro for looping over a dlist from a given element
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
#define dlist_for_each_elem_rev(elem, name)                         \
    for (struct dlist_elem * name = elem; name; name = name->prev)

/// A macro for looping over a dlist from a given element. Safe against element
/// destruction.
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
#define dlist_for_each_elem_rev_safe(elem, name)               \
    for (struct dlist_elem                                     \
             * name = elem,                                    \
             * __temp_elem = elem->prev;                       \
         name;                                                 \
         name = __temp_elem, __temp_elem = __temp_elem->prev)

// -----------------------------------------------------------------------------
//                                    End
// -----------------------------------------------------------------------------

#endif // DLIST_H
