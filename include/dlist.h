#ifndef DLIST_H
#define DLIST_H

// -----------------------------------------------------------------------------

/// @file
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
/// structure. All functions are safe to use with empty lists except dlist_init
/// for obvious reasons.

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
/// list_destroy.
struct dlist {
    struct dlist_elem *head;
};

// -----------------------------------------------------------------------------

/// Initialises a doubly linked list. This operation must be called for a doubly
/// linked list before the list can be used with any other operation. Obligation
/// to free is passed out to the caller through the list parameter.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing an initialised list to this function is undefined
/// behaviour. Expect a memory leak.
///
/// @param dlist The doubly linked list to initialise
void dlist_init(/*@out@*/ /*@notnull@*/ struct dlist *dlist);

/// Destroys a doubly linked list. No other operations are permitted after
/// destroying unless dlist_init is called again. This function removes all
/// elements from the list and calls the given destroy function on them unless
/// destroy is set to NULL.
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// COMPLEXITY: O(n)
///
/// @param dlist The list to destroy
/// @param destroy The function to use to free all the list element data
void dlist_destroy(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data));

/// Inserts an element into a doubly-linked list at the head.
///
/// COMPLEXITY: O(n)
///
/// @param dlist The list to insert at the head of
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
/// is required so that when elem is the list's head element, the list's head is
/// reset appropriately.
///
/// COMPLEXITY: O(1)
///
/// @param dlist The parent list. Used for resetting the list head
/// @param elem The element to insert before
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int dlist_ins_prev(/*@notnull@*/ struct dlist *dlist,
                   /*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void *data);

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

/// Removes an element from a doubly-linked list. dlist is required so that
/// dlist->head can be changed if we are removing the head of the list. The
/// destroyed element will have destroy() called upon elem->data to free it is
/// destroy is non-NULL.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param dlist Parent list to remove from
/// @param elem The element to remove
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int dlist_rem(/*@notnull@*/ struct dlist *dlist,
              /*@notnull@*/ struct dlist_elem *elem,
              /*@null@*/ void (*destroy)(void *data));

/// Counts the elements in a list. This is highly inefficient and probably not a
/// good use of a linked list
///
/// COMPLEXITY: O(n)
///
/// @param dlist Doubly-linked list whose elements to count
///
/// @return Number of elements in list.
int dlist_size(/*@notnull@*/ const struct dlist *dlist);

/// Returns the last element of a doubly-linked list. Returns NULL if the list
/// is empty. This is highly inefficient and you should probably rethink what
/// you're doing.
///
/// COMPLEXITY: O(n)
///
/// @param dlist The doubly-linked list to return the tail element of
///
// @return The last element of the list or NULL for an empty list
/*@null@*/
struct dlist_elem* dlist_tail(/*@notnull@*/ const struct dlist *dlist);

// -----------------------------------------------------------------------------

/// A macro for generating for loops - loop over all the elements of a list
///
/// COMPLEXITY: O(n)
///
/// @param list The list to iterate over
/// @param name The name used for the iterator
#define dlist_for_each(list, name)                                      \
    for (struct dlist_elem * name = (list)->head; name; name = name->next)

/// A macro for generating for loops - loop over all the elements of a
/// list. This safe version allows for removal of the current element
///
/// COMPELXITY: O(n)
///
/// @param list The list to iterate over
/// @param name The name used for the iterator
/// @param temp Name to use for temporary storage
#define dlist_for_each_safe(list, name, temp)                \
    if ((list)->head)                                        \
        for (struct dlist_elem                               \
                 * name = (list)->head,                      \
                 * temp = (list)->head->next;                \
             name;                                           \
             name = temp, temp = temp->next)

/// A macro for looping over a list from a given element
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
#define dlist_for_each_elem(elem, name)                             \
    for (struct dlist_elem * name = elem; name; name = name->next)

/// A macro for looping over a list from a given element. Safe against element
/// destruction.
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
/// @param temp Name to use for temporary storage
#define dlist_for_each_elem_safe(elem, name, temp) \
    for (struct dlist_elem                         \
             * name = elem,                        \
             * temp = elem->next;                  \
         name;                                     \
         name = temp, temp = temp->next)

/// A macro for looping over a list from a given element
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
#define dlist_for_each_elem_rev(elem, name)                         \
    for (struct dlist_elem * name = elem; name; name = name->prev)

/// A macro for looping over a list from a given element. Safe against element
/// destruction.
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
/// @param temp Name to use for temporary storage
#define dlist_for_each_elem_rev_safe(elem, name, temp)  \
    for (struct dlist_elem                              \
             * name = elem,                             \
             * temp = elem->prev;                       \
         name;                                          \
         name = temp, temp = temp->prev)

// -----------------------------------------------------------------------------

#endif // DLIST_H
