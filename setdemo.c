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

printcommands()
{
	printf ("Valid Commands are...\n");
	printf ("  isempty   <set> .......... \n");
	printf ("  issubset  <set1> <set2> .. \n");
	printf ("  isequal   <set1> <set2> .. \n");
	printf ("  issubeq   <set1> <set2> .. \n");
	printf ("  count     <set> .......... \n");
	printf ("  isin      <set1> <int> ... \n");
	printf ("  insert    <set1> <int> ... \n");
	printf ("  remove    <set1> <int> ... \n");
	printf ("  intersect <set1> <set2> .. \n");
	printf ("  union     <set1> <set2> .. \n");
	printf ("  minus     <set1> <set2> .. \n");
	printf ("  powerset  <set1> ......... \n");
}

int main()
{
	printf ("\n");
	printf ("======================================================================\n");
	printf ("CTEC2901/Week 18 Lab/setdemo                         (Barnaby Stewart)\n");
	printf ("======================================================================\n");
	printf ("\n");


	char input[256];

	set * s, *t, *u;
	s = new_set(intprn,inteq);
	t = new_set(intprn,inteq);

	addintstoset (s, 3, 3, 5, 7);
	printf("s = ");
	set_print(s);
	printf("\n");

	addintstoset (t, 3, 4, 5, 6);
	printf("t = ");
	set_print(t);
	printf("\n");

	u = new_set(setprn,seteq);
	set_insertInto(u,s);
	set_insertInto(u,t);
	printf("u = ");
	set_print(u);
	printf("\n");

	set_insertInto(s,(any)9);
	printf("s = ");
	set_print(s);
	printf("\n");
	printf("u = ");
	set_print(u);
	printf("\n");

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
			/*
			case 'd':
				scanf (" %c", &c);
				bst_char_delete (tree, c);
				treechanged = 1;
				break;
			case '[':
				printf ("Prefix traversal: ");
				bst_char_preorder_print (tree, print_char);
				putchar ('\n');
				break;
			case '-':
				printf ("Infix traversal: ");
				bst_char_inorder_print (tree, print_char);
				putchar ('\n');
				break;
			case ']':
				printf ("Postfix traversal: ");
				bst_char_postorder_print (tree, print_char);
				putchar ('\n');
				break;
			*/
			default:
				printf ("Unrecognised input, please try again...\n");
		}
	} while (input[0] != 'q');

	printf ("\n");
	printf ("----------------------------------------------------------------------\n");
	printf ("Program 'setdemo' Terminating\n");
	printf ("----------------------------------------------------------------------\n");
	printf ("\n");
}

