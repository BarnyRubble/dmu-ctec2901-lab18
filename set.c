// A set implementation using a clist
// Author: drs

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "clist.h"
#include "set.h"

struct set_implementation
{
	clist * items;
	printer item_printer;
	equals item_compare;
};

set * new_set(printer item_printer, equals item_compare)
{
	set * s = (set *) malloc (sizeof(set));
	assert (s!=NULL);
	s->items = new_clist();
	s->item_printer = item_printer;
	s->item_compare = item_compare;
	return s;
}

int set_isempty(set *s)
{
	assert(s!=NULL);
	return clist_isempty(s->items);
}

int set_isSubset(set *s, set * t)
{
	assert(s!=NULL);
	assert(t!=NULL);

	if (set_isSubsetEq(s, t))
	{
		return set_count(s) < set_count(t); // all in t, but check t is larger than s
	}
	return 0;
}

int set_isEqualTo(set *s, set * t)
{
	assert(s!=NULL);
	assert(t!=NULL);

	if (set_isSubsetEq(s, t))
	{
		return set_count(s) == set_count(t); // all in t, but check size is same
	}
	return 0;
}

int set_isSubsetEq(set *s, set * t)
{
	assert(s!=NULL);
	assert(t!=NULL);

	clist_goto_head(s->items);
	while (clist_cursor_inlist(s->items))
	{
		if (!set_isin(t,clist_get_item(s->items)))
			return 0; // if not in t then not a subset
		else
			clist_goto_next(s->items);
	}
	return 1;
}

int set_count(set *s)
{
	assert(s!=NULL);
	return clist_size(s->items);
}

int set_isin(set *s, any x)
{
	assert(s!=NULL);
	clist_goto_head(s->items);
	while (clist_cursor_inlist(s->items))
	{
		if (s->item_compare(clist_get_item(s->items),x))
			return 1; // found it
		else
			clist_goto_next(s->items);
	}
	return 0; // not found
}

void set_insertInto(set *s, any x) // s = s u {x}
{
	assert(s!=NULL);
	if (!set_isin(s,x))
		clist_ins_before(s->items,x);
}

void set_removeFrom(set *s, any x) // s = s \ {x}
{
	assert(s!=NULL);
	if (set_isin(s,x)) // the cursor will be at the found item
	{
		clist_delete(s->items);
	}
}

void set_intersectWith(set *s, set * t) // s = s n t t is unchanged
{
	assert(s!=NULL);
	assert(t!=NULL);
	clist_goto_head(s->items);
	while (clist_cursor_inlist(s->items))
	{
		if (!set_isin(t,clist_get_item(s->items)))
			clist_delete (s->items);
		else
			clist_goto_next(s->items);
	}
}

void set_unionWith(set *s, set * t) // s = s u t t is unchanged
{
	assert(s!=NULL);
	assert(t!=NULL);
	clist_goto_head(t->items);
	while (clist_cursor_inlist(t->items))
	{
		set_insertInto (s, clist_get_item(t->items));
	}
}

void set_minusWith(set *s, set * t) // s = s \ t t is unchanged
{
	assert(s!=NULL);
	assert(t!=NULL);
	clist_goto_head(s->items);
	while (clist_cursor_inlist(s->items))
	{
		if (set_isin(t,clist_get_item(s->items)))
			clist_delete (s->items);
		else
			clist_goto_next(s->items);
	}
}

struct psnode
{
	any item;
	struct psnode* parent;
};

void set_recursePowerset (set* powerset, set* sourceset, int size, struct psnode* parent)
{
	assert(powerset!=NULL);
	assert(sourceset!=NULL);

	struct psnode this;

	if (size == 0)
	{
		set* newset = new_set (sourceset->item_printer, sourceset->item_compare);
		while (parent)
		{
			set_insertInto (newset, parent->item);
			parent = parent->parent;
		}
		set_insertInto (powerset, newset);
	}
	else
	{
		int index;
		clist_goto_head (sourceset->items);
		for (index = 0; index < size-1; index++)
		{
			clist_goto_next (sourceset->items);
		}
		
		this.parent = parent;
		this.item = clist_get_item (sourceset->items);
		set_recursePowerset (powerset, sourceset, size - 1, parent);
		set_recursePowerset (powerset, sourceset, size - 1, &this);
	}
}

set* set_powerset(set *s) // generates new set
{
	assert(s!=NULL);

	set* powerset = new_set (setprn, seteq);
	set_recursePowerset (powerset, s, clist_size(s->items), NULL);
	return powerset;
}

void set_print(set *s)
{
	assert(s!=NULL);
	printf("{");
	clist_goto_head(s->items);
	if (clist_cursor_inlist(s->items))
	{
		s->item_printer(clist_get_item(s->items));
		clist_goto_next(s->items);
		while (clist_cursor_inlist(s->items))
		{
			printf(", ");
			s->item_printer(clist_get_item(s->items));
			clist_goto_next(s->items);
		}
	}
	printf("}");
}

void set_release(set *s)
{
	assert(s!=NULL);
	assert(clist_isempty(s->items));
	clist_release(s->items);
	free(s);
}

int seteq(any s, any t)
{
	return set_isEqualTo((set*)s,(set*)t);
}

void setprn(any s)
{
	set_print((set*)s);
}

