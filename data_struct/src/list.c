#include "list.h"


// {{{ Memory management
// {{{ allocList
List * allocList() {
  List * res = (List *) malloc(sizeof(List));
  nb(res) = 0;
  begin(res) = NULL;
  end(res) = NULL;
  return res;
}
// }}}

// {{{ freeList
void   freeList(List * l) {
  Item * it = begin(l);
  while (it != NULL) {
		Item *tmp = it;
		it = next(it);
    free(tmp); 
  }
  free (l);
}
// }}}

// {{{ copyList
List * copyList(List * l) {
  List * res = allocList();
  if (nb(l) !=0) {
    Item * it = begin(l);
    while (it != NULL) {
      pushTail(res, num(it), val(it));
      it = next(it);
    }
  }
  return res;    
}
// }}}
// }}}

// {{{ Display functions
// {{{ printList
void printList (FILE * f, List * l) {
  fprintf(f,"nb = %d : ", nb(l));
  Item * it = begin(l);
  while (it != NULL) {
    fprintf(f, "%2d (%2d) - ", num(it), val(it));
    it = next(it);
  }
  fprintf(f, "\n");
}
// }}}

// {{{ printListReverse
void printListReverse (FILE * f, List * l) {
  fprintf(f,"nb = %d : ", nb(l));
  Item * it = end(l);
  while (it != NULL) {
    fprintf(f, "%2d (%2d) - ", num(it), val(it));
    it = prev(it);
  }
  fprintf(f, "\n");
}
// }}}
// }}}

// {{{ List operations
// {{{ pushHead
void pushHead(List * l, int num, int val) {
  Item * it = (Item*) malloc(SIZE_ITEM);
  num(it) = num;
  val(it) = val;
  prev(it) = NULL;
  next(it) = begin(l);
  if (nb(l) == 0) end(l) = it;
  else prev(begin(l)) = it;
  begin(l) = it;
  nb(l)++;
}
// }}}

// {{{ pushTail
void pushTail(List * l, int num, int val) {
  Item * it = (Item*) malloc(SIZE_ITEM);
  num(it) = num;
  val(it) = val;
  prev(it) = end(l);
  next(it) = NULL;
  if (nb(l) == 0) begin(l) = it;
  else next(end(l)) = it;
  end(l) = it;
  nb(l)++;
}
// }}}

// {{{ insertNum
void insertNum(List * l, int num, int val) {
  if (val == 0) popNum(l,num);
  else if (nb(l) == 0 || num(begin(l)) > num) pushHead(l, num, val);
  else if (num(end(l)) < num) pushTail(l, num, val);
  else {
    Item * it = begin(l);
    while (num(it) < num) it = next(it);
    if (num(it) == num) val(it) = val;
    else {
      Item * i = (Item*) malloc(SIZE_ITEM);
      num(i) = num; val(i) = val;
      prev(i) = prev(it); next(i) = it;
      next(prev(it)) = i; prev(it) = i;
      nb(l)++;
    }
  }
}
// }}}

// {{{ popHead
void popHead(List * l) {
  if (nb(l) == 0) return;
  Item * it = begin(l);
  if (nb(l) > 1) prev(next(it)) = NULL;
  begin(l) = next(it);
  free (it);
  nb(l)--;
}
// }}}

// {{{ popTail
void popTail(List * l) {
  Item * it = end(l);
  if (nb(l) > 1) next(prev(it)) = NULL;
  end(l) = prev(it);
  free (it);
  nb(l)--;
}
// }}}

// {{{ popNum
void popNum(List * l, int num) {
  if (nb(l) == 0) return;
  if (num(begin(l)) == num) { popHead(l); return; }
  if (num(end(l)) == num) {popTail(l); return; }
  Item * it = begin(l);
  while (it != NULL && num(it) < num) it = next(it);
  if (it == NULL || num(it) > num) return;
  else {
    next(prev(it)) = next(it);
    prev(next(it)) = prev(it);
    free(it);
    nb(l)--;
  }
}
// }}}
// }}}

// {{{ Item Informations
// {{{ valOfNum
int valOfNum(List * l, int num) {
	if (l) {
  	if (nb(l) == 0 || num(begin(l)) > num || num(end(l)) < num) return 0;
  	Item * it = begin(l);
  	while (num(it) < num) it = next(it);
  	if (num(it) == num) return val(it);
	}
  return 0;
}
// }}}
// }}}
