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


int main()
{
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
}

