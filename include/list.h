#ifndef LIST_H
#define LIST_H

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
/// A simple, generic singularly linked list implementation using a generic data
/// structure.

// -----------------------------------------------------------------------------

/// Individual elements within a linked list
///
/// These should almost universally be created and managed by the list_
/// functions. You should only be referencing them.
struct list_elem {
    struct list_elem *next;
    void *data;
};

/// A generic list struct
///
/// When first initialised and when empty, head is NULL. This structure must be
/// initialised with list_init() before use. When done with, use list_destroy.
struct list {
    struct list_elem *head;
};

/// Initialises a linked list. this operation must be called for a linked list
/// before the list before the list can be used with any other operation.
///
/// COMPLEXITY: O(1)
///
/// @param list The list to initialise
void list_init(struct list *list);

/// Destroys a linked list. No other operations are permitted after destroying
/// unless list_init is called again. This function removes all elements from
/// the list and calles the list's destroy function on them unless destroy is
/// set to NULL.
///
/// COMPLEXITY: O(n)
///
/// @param list The list to destroy
/// @param destroy The function to use to free all the list element data
void list_destroy(struct list *list, void (*destroy)(void *data));

/// Inserts an element into a list at the head.
///
/// COMPLEXITY: O(n)
///
/// @param list The list to insert at the head of
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int list_ins_head(struct list *list, const void *data);

/// Inserts an element to a list. If elem is NULL it is inserted at the head of
/// the list.
///
/// COMPLEXITY: O(1)
///
/// @param elem The element to insert after
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int list_ins_next(struct list_elem *elem, const void *data);

/// Removes an element from the head of a list. Upon return data contains the
/// memory pointed to by the element. It is the caller's responsibility to
/// manage the storage associated with the data.
///
/// COMPLEXITY: O(1)
///
/// @param list The llist to remove from the head of
/// @param data Will be set to point to the data of the element that was removed
///
/// @return 0 on success, -1 on failure
int list_rem_head(struct list *list, void **data);

/// Removes an element from a list. Upon return data contains the memory pointed
/// to by the element. It is the caller's responsibility to manage the storage
/// associated with the data.
///
/// COMPLEXITY: O(1)
///
/// @param elem The element to remove after
/// @param data Will be set to point to the data of the element that was removed
///
/// @return 0 on success, -1 on failure
int list_rem_next(struct list_elem *elem, void **data);

/// Counts the elements in a list. This is highly inefficient and probably not a
/// good use of a linked list
///
/// COMPLEXITY: O(n)
///
/// @param list List whose elements to count
///
/// @return Number of elements in list.
int list_size(struct list *list);

/// Returns the last element of a list. Returns NULL if the list is empty. This
/// is highly inefficient and you should probably rethink what you're doing.
///
/// COMPLEXITY: O(n)
///
/// @param list The list to return the tail element of
///
/// @return The last element of the list or NULL for an empty list
struct list_elem* list_tail(struct list *list);

#endif // LIST_H
