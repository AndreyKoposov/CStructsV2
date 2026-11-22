CC 		?= gcc
CFLAGS  ?= -Wall -Wextra -O2 -Wpedantic -Iinclude
TFLAGS  := -Wall -Wextra -O0 -Wpedantic -Iinclude -Itests -g
AR 		:= ar
ARFLAGS := rcs
VFLAGS 	:= valgrind --leak-check=full --track-origins=yes

SRC 	:= src
TESTS   := tests
BUILD   := build
EXAMPLE := examples
LIB  	:= libcstructs.a


.PHONY: lib test clean example

# === Tests ===
test: lib $(BUILD)/test
	$(VFLAGS) $(BUILD)/test $(suite)

$(BUILD)/test: $(BUILD)/test.o $(BUILD)/test_vector.o $(BUILD)/test_btree.o $(BUILD)/test_list.o
	$(CC) $(TFLAGS) $^ -Lbuild -lcstructs -lcunit -o $@

$(BUILD)/test.o: $(TESTS)/test.c
	$(CC) $(TFLAGS) -c $^ -o $@

# Vector
$(BUILD)/test_vector.o: $(TESTS)/test_vector.c
	$(CC) $(TFLAGS) -c $^ -o $@
# BTree
$(BUILD)/test_btree.o: $(TESTS)/test_btree.c
	$(CC) $(TFLAGS) -c $^ -o $@
# List
$(BUILD)/test_list.o: $(TESTS)/test_list.c
	$(CC) $(TFLAGS) -c $^ -o $@

# === Lib ===
lib: $(BUILD)/${LIB}

$(BUILD)/${LIB}: $(BUILD)/vector.o $(BUILD)/btree.o $(BUILD)/list.o $(BUILD)/comparators.o
	$(AR) $(ARFLAGS) $@ $^
# Vector
$(BUILD)/vector.o: $(SRC)/vector.c
	$(CC) $(CFLAGS) -c $^ -o $@
# BTree
$(BUILD)/btree.o: $(SRC)/btree.c
	$(CC) $(CFLAGS) -c $^ -o $@
# List
$(BUILD)/list.o: $(SRC)/list.c
	$(CC) $(CFLAGS) -c $^ -o $@
# Comparators
$(BUILD)/comparators.o: $(SRC)/comparators.c
	$(CC) $(CFLAGS) -c $^ -o $@

# === Example ===
example: $(BUILD)/vector_example
	$(BUILD)/vector_example

$(BUILD)/vector_example: ${BUILD}/example_vector.o
	$(CC) ${CFLAGS} $^ -L${BUILD} -lcstructs -o $@

${BUILD}/example_vector.o: ${EXAMPLE}/vector.c
	$(CC) ${CFLAGS} -c $^ -o $@

# === Clean up ===
clean:
	rm -r $(BUILD) ; mkdir -p build

