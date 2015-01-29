// A set data structure
// Author: drs

#ifndef SET_H
#define SET_H

#include "any.h"

typedef struct set_implementation set;
typedef int (*equals)(any x, any y); // returns one if the items are equal, else zero
typedef void (*printer)(any x); // outputs item x on stdout

set* new_set (printer item_printer, equals item_compare);
int set_isempty (set *s);
int set_isSubset (set *s, set * t);
int set_isEqualTo (set *s, set * t);
int set_isSubsetEq (set *s, set * t);
int set_count (set *s);
int set_isin (set *s, any x);
void set_insertInto (set *s, any x); // s = s u {x}
void set_removeFrom (set *s, any x); // s = s \ {x}
void set_intersectWith (set *s, set * t); // s = s n t t is unchanged
void set_unionWith (set *s, set * t); // s = s u t t is unchanged
void set_minusWith (set *s, set * t); // s = s \ t t is unchanged
set* set_powerset (set *s); // generates new set
void set_print (set *s);
void set_release (set *s);
int seteq (any s, any t); // in case of creating sets of sets
void setprn (any s); // these cover functions please the typechecker

#endif
