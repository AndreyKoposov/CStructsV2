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

$(BUILD)/test: $(BUILD)/test.o $(BUILD)/test_vector.o $(BUILD)/test_btree.o
	$(CC) $(TFLAGS) $^ -Lbuild -lcstructs -lcunit -o $@

$(BUILD)/test.o: $(TESTS)/test.c
	$(CC) $(TFLAGS) -c $^ -o $@

$(BUILD)/test_vector.o: $(TESTS)/test_vector.c
	$(CC) $(TFLAGS) -c $^ -o $@

$(BUILD)/test_btree.o: $(TESTS)/test_btree.c
	$(CC) $(TFLAGS) -c $^ -o $@

# === Lib ===
lib: $(BUILD)/${LIB}

$(BUILD)/${LIB}: $(BUILD)/vector.o $(BUILD)/btree.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILD)/vector.o: $(SRC)/vector.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD)/btree.o: $(SRC)/btree.c
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

