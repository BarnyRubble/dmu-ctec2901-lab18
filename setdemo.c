//============================================================================
// FILE: setdemo.c
//============================================================================
// Author: Davis Smallwood
// Modified: Barnaby Stewart
// Last Modified: 29/01/15
//----------------------------------------------------------------------------


#include <stdio.h>
#include <stdarg.h>
#include "any.h"
#include "set.h"


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

typedef struct command
{
	int (*func)();
	char* name;
	char* parms;
} cmd;

int fn_isempty()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_issubset()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_isequal()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_issubeq()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_count()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_isin()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_insert()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_remove()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_intersect()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_union()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_minus()
{
	printf ("<Function Not Yet Implemented>\n");
}

int fn_powerset()
{
	printf ("<Function Not Yet Implemented>\n");
}

cmd commands[] = {
	{fn_isempty,   "isempty",   "<set>"},
	{fn_issubset,  "issubset",  "<set1> <set2>"},
	{fn_isequal,   "isequal",   "<set1> <set2>"},
	{fn_issubeq,   "issubeq",   "<set1> <set2>"},
	{fn_count,     "count",     "<set>"},
	{fn_isin,      "isin",      "<set1> <int>"},
	{fn_insert,    "insert",    "<set1> <int>"},
	{fn_remove,    "remove",    "<set1> <int>"},
	{fn_intersect, "intersect", "<set1> <set2>"},
	{fn_union,     "union",     "<set1> <set2>"},
	{fn_minus,     "minus",     "<set1> <set2>"},
	{fn_powerset,  "powerset",  "<set>"}
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

int main()
{
	printf ("\n");
	printf ("======================================================================\n");
	printf ("CTEC2901/Week 18 Lab/setdemo                         (Barnaby Stewart)\n");
	printf ("======================================================================\n");
	printf ("\n");



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

	set_release (s);
	set_release (t);
	set_release (u);
	set_release (ps);

	printf ("\n");
	printf ("----------------------------------------------------------------------\n");
	printf ("Program 'setdemo' Terminating\n");
	printf ("----------------------------------------------------------------------\n");
	printf ("\n");
}

