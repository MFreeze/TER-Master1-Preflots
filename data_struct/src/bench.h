#include <glib.h>
#include <string.h>

// {{{ Structures declaration
typedef struct {
	double _st1, _st2, _st3, _st4;
} stat_t;
// }}}

stat_t elapsedTime (int n, int m, int c, int nb_iter);
