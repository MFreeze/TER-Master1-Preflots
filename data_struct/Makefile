CC = gcc -c 
LINK = gcc 
CFLAGS = -Wall -O2 -lm -lglib-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/lib/glib-2.0/include
CBFLAGS = -Wall -g -lm -lglib-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/lib/glib-2.0/include
OFLAG = -o
OBJ_ALL =  $(OBJ_DIR)main.o $(OBJ_DIR)algo.o $(OBJ_DIR)graph.o  $(OBJ_DIR)mat_graph.o  \
           $(OBJ_DIR)list_graph.o  $(OBJ_DIR)list.o  $(OBJ_DIR)option.o $(OBJ_DIR)bench.o \
					 $(OBJ_DIR)heap.o
ECHO = echo
SRC_DIR = src/
OBJ_DIR = obj/
BIN_DIR = bin/
DOC_DIR = doc/

flowgraph: $(BIN_DIR)flowgraph
test: $(BIN_DIR)test
test_noeud: $(BIN_DIR)test_noeud
fifo: $(BIN_DIR)fifo
all: flowgraph test doc test_noeud
doc: $(OBJ_ALL)
	doxygen

$(OBJ_DIR)option.o: $(SRC_DIR)option.c $(SRC_DIR)option.h
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)list.o: $(SRC_DIR)list.c $(SRC_DIR)list.h
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)mat_graph.o: $(SRC_DIR)mat_graph.c $(SRC_DIR)mat_graph.h \
                       $(SRC_DIR)list.h
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)list_graph.o: $(SRC_DIR)list_graph.c $(SRC_DIR)list_graph.h \
                        $(SRC_DIR)list.h
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)graph.o: $(SRC_DIR)graph.c $(SRC_DIR)graph.h \
                   $(SRC_DIR)mat_graph.h $(SRC_DIR)list_graph.h $(SRC_DIR)list.h
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)algo.o: $(SRC_DIR)algo.c $(SRC_DIR)algo.h $(OBJ_DIR)heap.o $(OBJ_DIR)graph.o
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)main.o: $(SRC_DIR)main.c $(OBJ_DIR)graph.o
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)bench.o: $(SRC_DIR)bench.c $(SRC_DIR)bench.h
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)heap.o: $(SRC_DIR)heap.c $(SRC_DIR)heap.h
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(OBJ_DIR)fifo.o: $(SRC_DIR)fifo.c $(OBJ_DIR)graph.o $(OBJ_DIR)algo.o
	$(CC) $(CFLAGS) $(OFLAG) $@ $<

$(BIN_DIR)flowgraph: $(OBJ_ALL)
	$(LINK) $(CFLAGS) $(OFLAG) $@ $(OBJ_ALL)

$(OBJ_DIR)test.o : $(SRC_DIR)test.c
	$(CC) $(CFLAGS) $(OFLAG) $@ $^	

$(OBJ_DIR)test_noeud.o : $(SRC_DIR)test_noeud.c
	$(CC) $(CFLAGS) $(OFLAG) $@ $^	

$(BIN_DIR)test: $(OBJ_DIR)algo.o $(OBJ_DIR)graph.o  $(OBJ_DIR)mat_graph.o  \
           $(OBJ_DIR)list_graph.o  $(OBJ_DIR)list.o  $(OBJ_DIR)option.o $(OBJ_DIR)test.o\
		   $(OBJ_DIR)bench.o $(OBJ_DIR)heap.o
	$(LINK) $(CFLAGS) $(OFLAG) $@ $^ 

$(BIN_DIR)test_noeud: $(OBJ_DIR)algo.o $(OBJ_DIR)graph.o  $(OBJ_DIR)mat_graph.o  \
           $(OBJ_DIR)list_graph.o  $(OBJ_DIR)list.o  $(OBJ_DIR)option.o $(OBJ_DIR)test_noeud.o\
		   $(OBJ_DIR)bench.o $(OBJ_DIR)heap.o
	$(LINK) $(CFLAGS) $(OFLAG) $@ $^ 

$(BIN_DIR)fifo: $(OBJ_DIR)algo.o $(OBJ_DIR)graph.o  $(OBJ_DIR)mat_graph.o  \
           $(OBJ_DIR)list_graph.o  $(OBJ_DIR)list.o  $(OBJ_DIR)option.o $(OBJ_DIR)fifo.o\
		   $(OBJ_DIR)heap.o
	$(LINK) $(CFLAGS) $(OFLAG) $@ $^ 
