//============================================================================
// FILE: setdemo.c
//============================================================================
// Author: David Smallwood
// Modified: Barnaby Stewart
// Last Modified: 29/01/15
//----------------------------------------------------------------------------


#include <stdio.h>
#include <stdarg.h>
#include "any.h"
#include "set.h"
#include "avl_any.h"


void intprn(any x)
{
	printf("%li", (long)x);
}

int inteq(any x, any y)
{
	if ((long)x == (long)y)
	return 1;
	else
	return 0;
}


// Keeping track of demo sets
//----------------------------------------------------------------------------
#define SET_OF_INTS 1
#define SET_OF_SETS 2

#define MAX_SET_NAME 20

typedef struct setmetadata
{
	int   type;
	char* name[MAX_SET_NAME];
	set*  ptr;
} setmeta;

int setmeta_lessthan (any item1, any item2)
{
	return strcmp (((setmeta*)item1)->name, ((setmeta*)item2)->name) < 0;
}


// Command processing
//----------------------------------------------------------------------------
typedef struct command
{
	int (*func)();
	char* name;
	char* parms;
} cmd;

int cmd_isempty()
{
	printf ("<Command 'isempty' Not Yet Implemented>\n");
}

int cmd_issubset()
{
	printf ("<Command 'issubset' Not Yet Implemented>\n");
}

int cmd_isequal()
{
	printf ("<Command 'isequal' Not Yet Implemented>\n");
}

int cmd_issubeq()
{
	printf ("<Command 'issubeq' Not Yet Implemented>\n");
}

int cmd_count()
{
	printf ("<Command 'count' Not Yet Implemented>\n");
}

int cmd_isin()
{
	printf ("<Command 'isin' Not Yet Implemented>\n");
}

int cmd_insert()
{
	printf ("<Command 'insert' Not Yet Implemented>\n");
}

int cmd_remove()
{
	printf ("<Command 'remove' Not Yet Implemented>\n");
}

int cmd_intersect()
{
	printf ("<Command 'intersect' Not Yet Implemented>\n");
}

int cmd_union()
{
	printf ("<Command 'union' Not Yet Implemented>\n");
}

int cmd_minus()
{
	printf ("<Command 'minus' Not Yet Implemented>\n");
}

int cmd_powerset()
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

int parsecommand (char* input)
{
	int index;
	int max = sizeof(commands) / sizeof(cmd);
	for (index=0; index<max; index++)
	{
		if (strcmp (input, commands[index].name) == 0)
		{
			commands[index].func();
			return 1;
		}
	}
	return 0;
}

void OldTests (void)
{
	set * s, *t, *u;
	s = new_set(intprn,inteq);
	t = new_set(intprn,inteq);

	printset (s, "s");
	addintstoset (s, 3, 3, 5, 7);
	printset (s, "s");

	addintstoset (t, 3, 4, 5, 6);
	printset (t, "t");

	set* ps = set_powerset (s);
	printset (ps, "ps");

	u = new_set(setprn,seteq);
	set_insertInto(u,s);
	set_insertInto(u,t);
	printset (u, "u");

	set_insertInto(s,(any)9);
	printset (s, "s");
	printset (u, "u");


	set_release (s);
	set_release (t);
	set_release (u);
	set_release (ps);
}

int main()
{
	printf ("\n");
	printf ("======================================================================\n");
	printf ("CTEC2901/Week 18 Lab/setdemo                         (Barnaby Stewart)\n");
	printf ("======================================================================\n");
	printf ("\n");


	OldTests();
	

	avl_any* demosets = new_avl_any (setmeta_lessthan);

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
				if (parsecommand (input) == 0)
				{
					printf ("Unrecognised input, please try again...\n");
				}
		}
	} while (input[0] != 'q');

	avl_any_release (demosets);

	printf ("\n");
	printf ("----------------------------------------------------------------------\n");
	printf ("Program 'setdemo' Terminating\n");
	printf ("----------------------------------------------------------------------\n");
	printf ("\n");
}

