CC := gcc
CFLAGS := -Wall -Wextra -O2 -Wpedantic -Iinclude
TFLAGS := -Wall -Wextra -O0 -Wpedantic -Iinclude -Itests
AR := ar
ARFLAGS := rcs
VFLAGS := valgrind --leak-check=full

SRC := src
TESTS := tests
BUILD := build


.PHONY: lib test clean 

# === Tests ===
test: $(BUILD)/test lib
	$(VFLAGS) $<

$(BUILD)/test: $(BUILD)/test.o $(BUILD)/test_vector.o
	$(CC) $(CFLAGS) $^ -Lbuild -lstructs -lcunit -o $@

$(BUILD)/test.o: $(TESTS)/test.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD)/test_vector.o: $(TESTS)/test_vector.c
	$(CC) $(CFLAGS) -c $^ -o $@

# === Lib ===
lib: $(BUILD)/libstructs.a

$(BUILD)/libstructs.a: $(BUILD)/int.o $(BUILD)/vector.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILD)/int.o: $(SRC)/int.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD)/vector.o: $(SRC)/vector.c
	$(CC) $(CFLAGS) -c $^ -o $@

# === Clean up ===
clean:
	rm -r $(BUILD)

