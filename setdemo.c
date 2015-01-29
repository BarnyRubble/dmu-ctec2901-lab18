//============================================================================
// FILE: setdemo.c
//============================================================================
// Author: Davis Smallwood
// Modified: Barnaby Stewart
// Last Modified: 29/01/15
//----------------------------------------------------------------------------


#include <stdio.h>
#include "any.h"
#include "set.h"
#include "ht.h"

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
	char input[256];

	set * s, *t, *u;
	s = new_set(intprn,inteq);
	t = new_set(intprn,inteq);
	set_insertInto(s,(any)3);
	set_insertInto(s,(any)5);
	set_insertInto(s,(any)7);
	printf("s = ");
	set_print(s);
	printf("\n");
	set_insertInto(t,(any)4);
	set_insertInto(t,(any)5);
	set_insertInto(t,(any)6);
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
}

