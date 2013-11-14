#ifndef CDLIST_H
#define CDLIST_H

// -----------------------------------------------------------------------------
//                                    Info
// -----------------------------------------------------------------------------

/// @file    cdlist.h
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
/// A simple, generic circular doubly linked list structure using a generic data
/// structure.

// -----------------------------------------------------------------------------
//                                 Structures
// -----------------------------------------------------------------------------

/// Individual elements within a circular doubly linked list
///
/// These should almost universally be created and managed by the cdlist_
/// functions. You should only be referencing them.
struct cdlist_elem {
    struct cdlist_elem *next;
    struct cdlist_elem *prev;
    void *data;
};

/// A generic circular doubly linked list struct
///
/// This structure must be initialised with cdlist_init() before use. When done
/// with, use list_destroy. Note that this differs by not providing a
/// transparent data structure -- to access the head (or tail) element you must
/// use a getter function. The "link" member of this struct is an empty list
/// element used for handle termination when iterating correctly.
struct cdlist {
    struct cdlist_elem link;
};

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

/// Initialises a circular doubly linked list. This operation must be called on
/// a circular doubly linked list before the cdlist can be used with any other
/// operation. Obligation to free is passed out to the caller through the list
/// parameter.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing an initialised cdlist to this function is undefined
/// behaviour. Expect a memory leak.
///
/// @param cdlist The circular doubly linked list to initialise
void cdlist_init(/*@out@*/ struct cdlist *cdlist);

/// Destroys a circular doubly linked list. No other operations are permitted
/// after destroying unless cdlist_init is called on the list again. This
/// function removes all elements from the list and calls destroy on their data
/// unless destroy is NULL.
///
/// COMPLEXITY: O(n)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param cdlist The list to destroy
/// @param destroy The function to use to free all element data.
void cdlist_destroy(/*@notnull@*/ struct cdlist *cdlist,
                    /*@null@*/ void (*destroy)(void *data));

// -----------------------------------------------------------------------------
//                                 Accessors
// -----------------------------------------------------------------------------

/// Returns the first element of a circular doubly linked list. Returns NULL if
/// the cdlist is empty.
///
/// COMPLEXITY: O(1)
///
/// @param cdlist The circular doubly linked list to return the head element of
///
// @return The first element of the cdlist or NULL for an empty cdlist
/*@null@*/
struct cdlist_elem* cdlist_get_head(/*@notnull@*/ const struct cdlist *cdlist);

/// Counts the elements in a cdlist. This is highly inefficient and probably not
/// a good use of a linked list.
///
/// COMPLEXITY: O(n)
///
/// @param cdlist Circular doubly linked list whose elements to count
///
/// @return Number of elements in list.
int cdlist_get_size(/*@notnull@*/ const struct cdlist *cdlist);

/// Returns the last element of a circular doubly linked list. Returns NULL if
/// the cdlist is empty.
///
/// COMPLEXITY: O(1)
///
/// @param cdlist The circular doubly linked list to return the tail element of
///
// @return The first element of the cdlist or NULL for an empty cdlist
/*@null@*/
struct cdlist_elem* cdlist_get_tail(/*@notnull@*/ const struct cdlist *cdlist);

/// Determine whether a circularly doubly linked list is empty
///
/// COMPLEXITY: O(1)
///
/// @param cdlist The cdlist to test for emptiness
///
/// @return 1 if the cdlist contains any elements, else 0
int cdlist_is_empty(/*@notnull@*/ const struct cdlist *cdlist);

// -----------------------------------------------------------------------------
//                                Manipulation
// -----------------------------------------------------------------------------

/// Inserts an element into a circular doubly linked list at the head.
///
/// COMPLEXITY: O(1)
///
/// @param cdlist The list to insert at the head of
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int cdlist_ins_head(/*@notnull@*/ struct cdlist *cdlist,
                    /*@null@*/ void *data);

/// Inserts an element to a circular doubly linked list after the given element.
///
/// COMPLEXITY: O(1)
///
/// @param elem The element to insert after
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int cdlist_ins_next(/*@notnull@*/ struct cdlist_elem *elem,
                    /*@null@*/ void *data);

/// Inserts an element to a circular doubly linked list before the given
/// element.
///
/// COMPLEXITY: O(1)
///
/// @param cdlist The parent list. Used for resetting the list head
/// @param elem The element to insert before
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int cdlist_ins_prev(/*@notnull@*/ struct cdlist_elem *elem,
                    /*@null@*/ void *data);

/// Inserts an element into a circular doubly linked list at the tail end.
///
/// COMPLEXITY: O(1)
///
/// @param cdlist The list to insert at the tail of
/// @param data The data the newly created element should point to
///
/// @return 0 for success, -1 for failure
int cdlist_ins_tail(/*@notnull@*/ struct cdlist *cdlist,
                    /*@null@*/ void *data);

/// Removes an element from a circular doubly linked list. The destroyed element
/// will have destroy() called upon elem->data to free it if destroy is
/// non-NULL.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param cdlist Parent list to remove from
/// @param elem The element to remove
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int cdlist_rem_elem(/*@notnull@*/ struct cdlist_elem *elem,
                    /*@null@*/ void (*destroy)(void *data));

/// Removes an element from the head of a circular doubly linked list. If
/// destroy is non-NULL it will be used to free the element's data.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param cdlist The cdlist to remove from the head of
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int cdlist_rem_head(/*@notnull@*/ struct cdlist *cdlist,
                    /*@null@*/ void (*destroy)(void *data));

/// Removes an element from the tail of a circular doubly linked list. If
/// destroy is non-NULL it will be used to free the element's data.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing NULL as destroy may leave you with leaky memory
///
/// @param cdlist The cdlist to remove from the tail of
/// @param destroy Callback function for freeing the element's data
///
/// @return 0 on success, -1 on failure
int cdlist_rem_tail(/*@notnull@*/ struct cdlist *cdlist,
                    /*@null@*/ void (*destroy)(void *data));

// -----------------------------------------------------------------------------
//                               Looping Macros
// -----------------------------------------------------------------------------

/// A macro for generating for loops - loop over all the elements of a cdlist
///
/// COMPLEXITY: O(n)
///
/// @param cdlist The cdlist to iterate over
/// @param name The name used for the iterator
#define cdlist_for_each(cdlist, name)                   \
    for (struct cdlist_elem * name = cdlist->link.next; \
         name != &cdlist->link;                         \
         name = name->next)

/// A macro for generating for loops - loop over all the elements of a
/// cdlist. This safe version allows for removal of the current element
///
/// COMPLEXITY: O(n)
///
/// @param cdlist The cdlist to iterate over
/// @param name The name used for the iterator
#define cdlist_for_each_safe(cdlist, name)                      \
    for (struct cdlist_elem                                     \
             * name = cdlist->link.next,                        \
             * __temp_elem = name->next;                        \
         name != &cdlist->link;                                 \
         name = __temp_elem, __temp_elem = __temp_elem->next)

/// A macro for generating for loops - loop over all the elements of a cdlist
/// backwards, starting with the tail and ending with the head
///
/// COMPLEXITY: O(n)
///
/// @param cdlist The cdlist to iterate over
/// @param name The name used for the iterator
#define cdlist_for_each_rev(cdlist, name)               \
    for (struct cdlist_elem * name = cdlist->link.prev; \
         name != &cdlist->link;                         \
         name = name->prev)

/// A macro for generating for loops - loop over all the elements of a
/// cdlist. This safe version allows for removal of the current element
///
/// COMPLEXITY: O(n)
///
/// @param cdlist The cdlist to iterate over
/// @param name The name used for the iterator
#define cdlist_for_each_rev_safe(cdlist, name)                  \
    for (struct cdlist_elem                                     \
             * name = cdlist->link.prev,                        \
             * __temp_elem = name->prev;                        \
         name != &cdlist->link;                                 \
         name = __temp_elem, __temp_elem = __temp_elem->prev)

// -----------------------------------------------------------------------------
//                                    End
// -----------------------------------------------------------------------------

#endif // CDLIST_H
