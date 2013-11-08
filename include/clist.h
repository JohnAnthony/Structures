#ifndef CLIST_H
#define CLIST_H

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

/// Individual elements within a circular linked list
///
/// These should almost universally be created and managed by the clist_
/// functions. You should only be referencing them.
struct clist_elem {
    struct clist_elem *next;
    struct clist_elem *prev;
    void *data;
};

/// A generic circular llinked list struct
///
/// When first initialised and when empty, head is NULL. This structure must be
/// initialised with clist_init() before use. When done with, use list_destroy.
struct clist {
    struct clist_elem *head;
};

// -----------------------------------------------------------------------------

/// Initialises a circularly linked list. This operation must be called on a
/// circularly linekd list before the clist can be used with any other
/// operation. Obligation to free is passed out to the caller through the list
/// parameter.
///
/// COMPLEXITY: O(1)
///
/// @warning Passing an initialised clist to this funciton is undefined
/// behaviour. Expect a memory leak.
///
/// @param clist The circular linked list to initialise
void clist_init(/*@out@*/ struct clist *clist);


void clist_destroy(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data));
int clist_ins_head(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void *data);
int clist_ins_next(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void *data);
int clist_ins_prev(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void *data);
int clist_rem_head(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data));
int clist_rem_elem(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void (*destroy)(void *data));
int clist_size(/*@notnull@*/ const struct clist *clist);

// -----------------------------------------------------------------------------

// TODO: Macros

// -----------------------------------------------------------------------------

#endif // CLIST_H
