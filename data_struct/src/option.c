#include "option.h"

// {{{ print_help
void print_help (FILE *stream) {
	fprintf (stream, "NAME\n\n");
	fprintf (stream, "\tflowgraph\n\n");
	fprintf (stream, "SYNOPSIS\n\n");
	fprintf (stream, "\tflowgraph [-vh] [-f graphfile] [-s outstream]\n\n");
	fprintf (stream, "DESCRIPTION\n\n");
	fprintf (stream, "\t-h,\n\tprint help and exit\n\n");
	fprintf (stream, "\t-v,\n\tactivate graphviz graph representation\n\n");
	fprintf (stream, "\t-f FILE,\n\tread graph in the given file\n\n");
	fprintf (stream, "\t-s STREAM,\n\tredirect the standard output on the given stream\n\n");
}
// }}}

// {{{ treatOption
int treatOption (int argc, char **argv, int *viz, char **graph_file, char **stream) {
	int opt;
	while ((opt = getopt (argc, argv, "f:s:vh")) != EOF) {
		switch (opt) {
			case 'v':
				*viz = 1;
				break;
			case 'h':
				print_help(stdout);
				return -1;
			case 'f':
				*graph_file = optarg;
				break;
			case 's':
				*stream = optarg;
				break;
		}
	}
	return 1;
}
// }}}
