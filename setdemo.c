//============================================================================
// FILE: setdemo.c
//============================================================================
// Author: David Smallwood
// Modified: Barnaby Stewart
// Last Modified: 29/01/15
//----------------------------------------------------------------------------


#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "any.h"
#include "set.h"
#include "clist.h"

#define TRACE(text) printf("TRACE: %s\n", text)


void intprn (any x)
{
	printf("%li", (long)x);
}

int inteq (any x, any y)
{
	if ((long)x == (long)y)
		return 1;
	else
		return 0;
}


//----------------------------------------------------------------------------
// Keeping track of demo sets
//----------------------------------------------------------------------------
#define SET_OF_INTS 1
#define SET_OF_SETS 2

#define MAX_SET_NAME 20

typedef struct setmetadata
{
	int  type;
	char name[MAX_SET_NAME];
	set* ptr;
} setmeta;

int setmeta_lessthan (any item1, any item2)
{
	return strcmp (((setmeta*)item1)->name, ((setmeta*)item2)->name) < 0;
}

setmeta* finddemoset (clist* demosets, char* name)
{
	assert (demosets != NULL);
	assert (name != NULL);

	setmeta* nextset = 0;
	setmeta* foundset = 0;
	clist_goto_head (demosets);
	while (clist_cursor_inlist (demosets))
	{
		nextset = (setmeta*)clist_get_item (demosets);
		if (strcmp (nextset->name, name) == 0)
		{
			foundset = nextset;
			break;
		}
		clist_goto_next (demosets);
	}
	return foundset;
}

void freedemosets (clist* demosets)
{
	setmeta* nextset = 0;
	clist_goto_head (demosets);
	while (clist_cursor_inlist (demosets))
	{
		nextset = (setmeta*)clist_get_item (demosets);
		set_release (nextset->ptr); // release the set memory
		clist_delete (demosets);    // remove the entry from the list
	}
}


//----------------------------------------------------------------------------
// Interactive Testing
//----------------------------------------------------------------------------
typedef struct command
{
	void (*func)(clist* demosets);
	char* name;
	char* parms;
} cmd;

setmeta* getsetfrominput (clist* demosets)
{
	char input[256];
	scanf (" %s", input);
	return finddemoset (demosets, input);
}

void cmd_isempty (clist* demosets)
{
	setmeta* pSet = getsetfrominput (demosets);
	if (pSet != NULL)
	{
		if (set_isempty (pSet->ptr))
			printf ("::Set '%s' is empty\n", pSet->name);
		else
			printf ("::Set '%s' is not empty\n", pSet->name);
	}
	else
	{
		printf ("::Set '%s' not found.\n", pSet->name);
	}
}

void cmd_issubset (clist* demosets)
{
	printf ("<Command 'issubset' Not Yet Implemented>\n");
}

void cmd_isequal (clist* demosets)
{
	printf ("<Command 'isequal' Not Yet Implemented>\n");
}

void cmd_issubeq (clist* demosets)
{
	printf ("<Command 'issubeq' Not Yet Implemented>\n");
}

void cmd_count (clist* demosets)
{
	printf ("<Command 'count' Not Yet Implemented>\n");
}

void cmd_isin (clist* demosets)
{
	printf ("<Command 'isin' Not Yet Implemented>\n");
}

void cmd_insert (clist* demosets)
{
	printf ("<Command 'insert' Not Yet Implemented>\n");
}

void cmd_remove (clist* demosets)
{
	printf ("<Command 'remove' Not Yet Implemented>\n");
}

void cmd_intersect (clist* demosets)
{
	printf ("<Command 'intersect' Not Yet Implemented>\n");
}

void cmd_union (clist* demosets)
{
	printf ("<Command 'union' Not Yet Implemented>\n");
}

void cmd_minus (clist* demosets)
{
	printf ("<Command 'minus' Not Yet Implemented>\n");
}

void cmd_powerset (clist* demosets)
{
	printf ("<Command 'powerset' Not Yet Implemented>\n");
}

cmd commands[] = {
	{cmd_isempty,   "isempty",   "<set>"},
	{cmd_issubset,  "issubset",  "<set1> <set2>"},
	{cmd_isequal,   "isequal",   "<set1> <set2>"},
	{cmd_issubeq,   "issubeq",   "<set1> <set2>"},
	{cmd_count,     "count",     "<set>"},
	{cmd_isin,      "isin",      "<set1> <int>"},
	{cmd_insert,    "insert",    "<set1> <int>"},
	{cmd_remove,    "remove",    "<set1> <int>"},
	{cmd_intersect, "intersect", "<set1> <set2>"},
	{cmd_union,     "union",     "<set1> <set2>"},
	{cmd_minus,     "minus",     "<set1> <set2>"},
	{cmd_powerset,  "powerset",  "<set>"}
};

printcommands()
{
	printf ("Valid Commands are...\n");

	int index;
	int max = sizeof(commands) / sizeof(cmd);
	for (index=0; index<max; index++)
	{
		printf ("  %-9s %s\n", commands[index].name, commands[index].parms);
	}
}

int parsecommand (char* input, clist* demosets)
{
	int index;
	int max = sizeof(commands) / sizeof(cmd);
	for (index=0; index<max; index++)
	{
		if (strcmp (input, commands[index].name) == 0)
		{
			commands[index].func (demosets);
			return 1;
		}
	}
	return 0;
}

void InteractiveTests()
{
	printf ("Interactive Test....\n");
	clist* demosets = new_clist (setmeta_lessthan);

	char input[256];
	do
	{
		printf ("\n");
		printf ("Enter Command (? for help) :>");

		scanf (" %s", input);
		switch (input[0])
		{
			case 'q':
				break;
			case '?':
				printcommands();
				break;
			default:
				if (parsecommand (input, demosets) == 0)
				{
					printf ("Unrecognised input, please try again...\n");
				}
		}
	} while (input[0] != 'q');

	freedemosets (demosets);
}


//----------------------------------------------------------------------------
// Fixed Testing
//----------------------------------------------------------------------------
void addintstoset (set* dest, int numargs, ...)
{
	int arg, argnum;
	va_list ap;

	va_start(ap, numargs);
	for (argnum=0; argnum<numargs; argnum++)
	{
		arg = va_arg (ap, int);
		set_insertInto (dest,(any)arg);
	}
	va_end(ap);
}

void printset (set* s, char* name)
{
	printf ("%s = ", name);
	set_print (s);
	printf ("\n");
}

void FixedTests (void)
{
	printf ("Fixed Tests...\n");

	set * s, *t, *u;
	s = new_set (intprn, inteq);
	t = new_set (intprn, inteq);

	printset (s, "s");
	addintstoset (s, 3, 3, 5, 7);
	printset (s, "s");

	addintstoset (t, 4, 4, 5, 6, 8);
	printset (t, "t");

	set* ps_s = set_powerset (s);
	printset (ps_s, "ps_s");

	set* ps_t = set_powerset (t);
	printset (ps_t, "ps_t");

	u = new_set (setprn, seteq);
	set_insertInto(u,s);
	set_insertInto(u,t);
	printset (u, "u");

	set_insertInto(s,(any)9);
	printset (s, "s");
	printset (u, "u");


	set* ps_u = set_powerset (u);
	printset (ps_u, "ps_u");

	set_release (s);
	set_release (t);
	set_release (u);
	set_release (ps_s);
	set_release (ps_t);
	set_release (ps_u);
}

//----------------------------------------------------------------------------
// FUNCTION: main()
//----------------------------------------------------------------------------
int main()
{
	printf ("\n");
	printf ("======================================================================\n");
	printf ("CTEC2901/Week 18 Lab/setdemo                         (Barnaby Stewart)\n");
	printf ("======================================================================\n");
	printf ("\n");

	FixedTests();
	
	InteractiveTests();

	printf ("\n");
	printf ("----------------------------------------------------------------------\n");
	printf ("Program 'setdemo' Terminating\n");
	printf ("----------------------------------------------------------------------\n");
	printf ("\n");
}

