#ifndef LIST_H
#define LIST_H

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

// -----------------------------------------------------------------------------

/// Initialises a linked list. This operation must be called for a linked list
/// before the list can be used with any other operation. Obligation to free is
/// passed out to the caller through the list parameter.
///
/// COMPLEXITY: O(1)
///
/// @param list The list to initialise
void list_init(/*@out@*/ struct list *list);

/// Destroys a linked list. No other operations are permitted after destroying
/// unless list_init is called again. This function removes all elements from
/// the list and calls the given destroy function on them unless destroy is set
/// to NULL.
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
int list_ins_head(struct list *list, void *data);

/// Inserts an element to a list after the given element.
///
/// COMPLEXITY: O(1)
///
/// @param elem The element to insert after
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int list_ins_next(struct list_elem *elem, void *data);

/// Removes an element from the head of a list. It is the user's responsibility
/// to free the element's data. If destroy is non-NULL it will be called on the
/// element's data to free it.
///
/// COMPLEXITY: O(1)
///
/// @param list The llist to remove from the head of
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int list_rem_head(struct list *list, void (*destroy)(void *data));

/// Removes a list element from the list position after the given one.  It is
/// the user's responsibility to free the element's data. If destroy is non-NULL
/// it will be called on the element's data to free it.
///
/// COMPLEXITY: O(1)
///
/// @param elem The element to remove after
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int list_rem_next(struct list_elem *elem, void (*destroy)(void *data));

/// Counts the elements in a list. This is highly inefficient and probably not a
/// good use of a linked list
///
/// COMPLEXITY: O(n)
///
/// @param list List whose elements to count
///
/// @return Number of elements in list.
int list_size(const struct list *list);

/// Returns the last element of a list. Returns NULL if the list is empty. This
/// is highly inefficient and you should probably rethink what you're doing.
///
/// COMPLEXITY: O(n)
///
/// @param list The list to return the tail element of
///
/// @return The last element of the list or NULL for an empty list
/*@null@*/
struct list_elem* list_tail(const struct list *list);

// -----------------------------------------------------------------------------

/// A macro for generating for loops - loop over all the elements of a list
///
/// COMPLEXITY: O(n)
///
/// @param list The list to iterate over
/// @param name The name used for the iterator
#define list_for_each(list, name)                                       \
    for (struct list_elem * name = (list)->head; name; name = name->next)

/// A macro for generating for loops - loop over all the elements of a
/// list. this safe version allows for removal of the current element
///
/// COMPELXITY: O(n)
///
/// @param list The list to iterate over
/// @param name The name used for the iterator
/// @param temp Name to use for temporary storage
#define list_for_each_safe(list, name, temp)    \
    if ((list)->head)                           \
        for (struct list_elem                   \
                 * name = (list)->head,         \
                 * temp = (list)->head->next;   \
             name;                              \
             name = temp, temp = temp->next)

/// A macro for looping over a list from a given element
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
#define list_for_each_elem(elem, name)                              \
    for (struct list_elem * name = elem; name; name = name->next)

/// A macro for looping over a list from a given element. Safe against element
/// destruction.
///
/// COMPLEXITY: O(n)
///
/// @param elem The element to start with
/// @param name The label to use for the iterator
/// @param temp Name to use for temporary storage
#define list_for_each_elem_safe(elem, name, temp) \
    for (struct list_elem                         \
             * name = elem,                       \
             * temp = elem->next;                 \
         name;                                    \
         name = temp, temp = temp->next)

// -----------------------------------------------------------------------------

#endif // LIST_H
