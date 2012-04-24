/*
 * =====================================================================================
 *
 *       Filename:  test_heap.c
 *
 *    Description:  Petit programme de test des tas
 *
 *        Version:  1.0
 *        Created:  26/03/2012 12:37:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DUVILLIE Guillerme (mfreeze), guillerme.duvillie@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "heap.h"

int main (int argc, char **argv) {
	int i = 0;
	Heap *pat = allocHeap (20);
	if (!pat)
		return 0;

	for (i=0; i < 5; i++, h_print(pat)) 
		h_insertNode (pat, i, i);

	int retour;
	while ((retour = h_remNode(pat)) != -1) {
		printf ("Suivant : %d \n\n", retour);
		h_print(pat);
	}

	printf ("\n");
	return 1;
}
