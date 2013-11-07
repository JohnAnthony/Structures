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
/// structure.

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
/// @param dlist The doubly linked list to initialise
///
/// :: Unsafe :: dlist is already initialised
void dlist_init(/*@out@*/ /*@notnull@*/ struct dlist *dlist);

/// Destroys a doubly linked list. No other operations are permitted after
/// destroying unless dlist_init is called again. This function removes all
/// elements from the list and calls the given destroy function on them unless
/// destroy is set to NULL.
///
/// COMPLEXITY: O(n)
///
/// @param dlist The list to destroy
/// @param destroy The function to use to free all the list element data
///
/// ::  Safe  :: dlist is an empty list
/// :: Unsafe :: dlist is not initialised
void dlist_destroy(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data));

/// Inserts an element into a doubly-linked list at the head.
///
/// COMPLEXITY: O(n)
///
/// @param dlist The list to insert at the head of
/// @param data The data the newly created element should point to
///
/// :: Unsafe :: dlist not initialised
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
/// ::  Safe  :: elem is the last element in a list
///
/// @return 0 for success, -1 for failure
int dlist_ins_next(/*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void *data);

/// Inserts an element to a doubly-linked list before the given element. If
/// dlist is provided and elem is the head element, the list's head is reset
/// appropriately. You may pass NULL as dlist but you are responsible for
/// moving your list head if appropriate.
///
/// COMPLEXITY: O(1)
///
/// @param dlist The parent list. Used for resetting the list head
/// @param elem The element to insert before
/// @param data The data the newly created element should point to
///
/// ::  Safe  :: elem is the first element in a list is that list is dlist
/// :: Unsafe :: dlist not initialised
///
/// @return 0 for success, -1 for failure
int dlist_ins_prev(/*@null@*/ struct dlist *dlist,
                   /*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void *data);

/// Removes an element from the head of a doubly-linked list. If destroy is
/// non-NULL it will be used to free the element's data.
///
/// COMPLEXITY: O(1)
///
/// @param dlist The dlist to remove from the head of
/// @param destroy Callback function for freeing the element's data
///
/// ::  Safe  :: dlist is an empty list
/// :: Unsafe :: dlist not initialised
///
/// @return 0 on success, -1 on failure
int dlist_rem_head(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data));

/// Removes an element from a doubly-linked list. Provides a mechanism for
/// safely handling removing the first element of a list through dlist. You
/// may pass NULL as dlist but you are then responsible for ensuring that you
/// don't accidentally remove the head element of a list, thereby invalidating
/// the list.
///
/// COMPLEXITY: O(1)
///
/// @param dlist List to remove from. Used to prevent accidental removal of a
/// head element
/// @param elem The element to remove after
/// @param destroy Callback function for freeing the element's data
///
/// ::  Safe  :: elem is the last element in a list
/// :: Unsafe :: elem is the first element in a list other than dlist
/// :: Unsafe :: dlist is non-NULL and not initialised and elem is dlist->head
///
/// @return 0 on success, -1 on failure
int dlist_rem(/*@null@*/ struct dlist *dlist,
              /*@notnull@*/ struct dlist_elem *elem,
              /*@null@*/ void (*destroy)(void *data));

/// Counts the elements in a list. This is highly inefficient and probably not a
/// good use of a linked list
///
/// COMPLEXITY: O(n)
///
/// @param dlist Doubly-linked list whose elements to count
///
/// :;  Safe  :: dlist is an empty list
/// :: Unsafe :: dlist is not initialised
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
/// ::  Safe  :: dlist is an empty list
/// :: Unsafe :: dlist is not initialised
///
/// @return The last element of the list or NULL for an empty list
/*@null@*/
struct dlist_elem* dlist_tail(/*@notnull@*/ const struct dlist *dlist);

// -----------------------------------------------------------------------------

/// A macro for generating for loops - loop over all the elements of a list
///
/// COMPLEXITY: O(n)
///
/// @param list The list to iterate over
/// @param name The name used for the iterator
///
/// ::  Safe  :: list is an empty list
/// :: Unsafe :: list is NULL
/// :: Unsafe :: list is not initialised
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
///
/// ::  Safe  :: list is an empty list
/// :: Unsafe :: list is NULL
/// :: Unsafe :: list is not initialised
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
///
/// ::  Safe  :: elem is NULL
/// ::  Safe  :: elem is at any position within a list
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
///
/// ::  Safe  :: elem is NULL
/// ::  Safe  :: elem is at any position within a list
#define dlist_for_each_elem_safe(elem, name, temp) \
    if (elem != NULL)                              \
        for (struct dlist_elem                     \
                 * name = elem,                    \
                 * temp = elem->next;              \
             name;                                 \
             name = temp, temp = temp->next)

/// A macro for looping over a list from a given element
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
///
/// ::  Safe  :: elem is NULL
/// ::  Safe  :: elem is at any position within a list
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
///
/// ::  Safe  :: elem is NULL
/// ::  Safe  :: elem is at any position within a list
#define dlist_for_each_elem_rev_safe(elem, name, temp)  \
    if (elem != NULL)                                   \
        for (struct dlist_elem                          \
                 * name = elem,                         \
                 * temp = elem->prev;                   \
             name;                                      \
             name = temp, temp = temp->prev)

// -----------------------------------------------------------------------------

#endif // DLIST_H
