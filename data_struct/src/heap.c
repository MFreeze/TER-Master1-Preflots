/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description:  Implementation of heap
 *
 *        Version:  1.0
 *        Created:  26/03/2012 11:29:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DUVILLIE Guillerme (mfreeze), guillerme.duvillie@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "heap.h"

Heap *allocHeap (int n, int *lab) {
	Heap *h = (Heap *) malloc (SIZE_HEAP);
	if (!h) {
		fprintf (stderr, "Erreur malloc heap.\n");
		return NULL;
	}

	max(h) = n;
	cur(h)= 0;
	htlab(h) = lab;

	nodes(h) = (int *) calloc (n, sizeof(int));
	if (!nodes(h)) {
		fprintf (stderr, "Erreur malloc array.\n");
		free (h);
	}

	return h;
}

void freeHeap (Heap *p) {
	free(nodes(p));
	free(p);
}

int h_insertNode (Heap *p, int node) {
	if (cur(p) >= max(p))
		return -1;

	int index = cur(p);

	nodes(p)[cur(p)++] = node;
	while (index && hlab(p,node) > hlab(p,fath(p,index))) {
		int tmp = fath(p,index);
		fath(p,index) = node(p,index);
		node(p,index) = tmp;
		index = index >> 1;
	}

	return index;
}

int h_remNode (Heap *p) {
	if (!cur(p))
		return -1;

	int ret = node(p,0);

	node(p,0) = node(p,--cur(p));

	int index = 0;
	while (1) {
		int indr = (index + 1) * 2; int indl = indr - 1;
		int labl = -1, labr = -1;
		if (indl < cur(p))
			labl = hlab(p,lchild(p,index));
		if (indr < cur(p))
			labr = hlab(p,rchild(p,index));

		if (labl == -1 && labr == -1)
			break;

		if (labr == -1) {
			if (hlab(p,node(p,index)) >= labl)
				break;
			else {
				int tmp = lchild(p,index);
				lchild(p,index) = node(p,index);
				node(p,index) = tmp;
				index = indl;
			}
		}
		else{
			if (labl >= labr) {
				if (hlab(p,node(p,index)) >= labl)
					break;
				int tmp = lchild(p,index);
				lchild(p,index) = node(p,index);
				node(p,index) = tmp;
				index = indl;
			}
			else {
				if (hlab(p,node(p,index)) >= labr)
					break;
				int tmp = rchild(p,index);
				rchild(p,index)= node(p,index);
				node(p,index) = tmp;
				index = indr;
			}
		}
	}
	return ret;
}

void h_print(Heap *p){
	int compteur = 0;
	int max = 1;
	int i;
	for (i=0; i < cur(p); i++) {
		printf("%d ", hlab(p,node(p,i)));
		compteur ++;
		if (compteur == max){
			compteur = 0;
			max *= 2;
			printf("\n");
		}
	}
	printf ("\n\n");
}
