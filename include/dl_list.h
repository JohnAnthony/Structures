#ifndef DL_LIST_H
#define DL_LIST_H

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
/// These should almost universally be created and managed by the dl_list_
/// functions. You should only be referencing them.
struct dl_list_elem {
    struct dl_list_elem *next;
    struct dl_list_elem *prev;
    void *data;
};

/// A generic doubly-linked list struct
///
/// When first initialised and when empty, head is NULL. This structure must be
/// initialised with dl_list_init() before use. When done with, use
/// list_destroy.
struct dl_list {
    struct dl_list_elem *head;
};

// -----------------------------------------------------------------------------

/// Initialises a doubly linked list. This operation must be called for a doubly
/// linked list before the list can be used with any other operation. Obligation
/// to free is passed out to the caller through the list parameter.
///
/// COMPLEXITY: O(1)
///
/// @param dl_list The doubly linked list to initialise
void dl_list_init(/*@out@*/ struct dl_list *dl_list);

/// Destroys a doubly linked list. No other operations are permitted after
/// destroying unless dl_list_init is called again. This function removes all
/// elements from the list and calls the given destroy function on them unless
/// destroy is set to NULL.
///
/// COMPLEXITY: O(n)
///
/// @param dl_list The list to destroy
/// @param destroy The function to use to free all the list element data
void dl_list_destroy(struct dl_list *dl_list, void (*destroy)(void *data));

/// Inserts an element into a doubly-linked list at the head.
///
/// COMPLEXITY: O(n)
///
/// @param dl_list The list to insert at the head of
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int dl_list_ins_head(struct dl_list *dl_list, void *data);

/// Inserts an element to a doubly-linked list after the given element.
///
/// COMPLEXITY: O(1)
///
/// @param elem The element to insert after
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int dl_list_ins_next(struct dl_list_elem *elem, void *data);

/// Inserts an element to a doubly-linked list before the given element. If
/// dl_list is provided and elem is the head element, the list's head is reset
/// appropriately. You may pass NULL as dl_list but you are responsible for
/// moving your list head if appropriate.
///
/// COMPLEXITY: O(1)
///
/// @param dl_list The parent list. Used for resetting the list head
/// @param elem The element to insert before
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int dl_list_ins_prev(struct dl_list *dl_list,
                     struct dl_list_elem *elem,
                     void *data);

/// Removes an element from the head of a doubly-linked list. If destroy is
/// non-NULL it will be used to free the element's data.
///
/// COMPLEXITY: O(1)
///
/// @param dl_list The dl_list to remove from the head of
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int dl_list_rem_head(struct dl_list *dl_list, void (*destroy)(void *data));

/// Removes an element from a doubly-linked list. Provides a mechanism for
/// safely handling removing the first element of a list through dl_list. You
/// may pass NULL as dl_list but you are then responsible for ensuring that you
/// don't accidentally remove the head element of a list, thereby invalidating
/// the list.
///
/// COMPLEXITY: O(1)
///
/// @param dl_list List to remove from. Used to prevent accidental removal of a
/// head element
/// @param elem The element to remove after
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int dl_list_rem(struct dl_list *dl_list,
                struct dl_list_elem *elem,
                void (*destroy)(void *data));

/// Counts the elements in a list. This is highly inefficient and probably not a
/// good use of a linked list
///
/// COMPLEXITY: O(n)
///
/// @param dl_list Doubly-linked list whose elements to count
///
/// @return Number of elements in list.
int dl_list_size(const struct dl_list *dl_list);

/// Returns the last element of a doubly-linked list. Returns NULL if the list
/// is empty. This is highly inefficient and you should probably rethink what
/// you're doing.
///
/// COMPLEXITY: O(n)
///
/// @param dl_list The doubly-linked list to return the tail element of
///
/// @return The last element of the list or NULL for an empty list
/*@null@*/
struct dl_list_elem* dl_list_tail(const struct dl_list *dl_list);

// -----------------------------------------------------------------------------

/// A macro for generating for loops - loop over all the elements of a list
///
/// COMPLEXITY: O(n)
///
/// @param list The list to iterate over
/// @param name The name used for the iterator
#define dl_list_for_each(list, name) \
    for (struct dl_list_elem * name = (list)->head; name; name = name->next)

// -----------------------------------------------------------------------------

#endif // DL_LIST_H
