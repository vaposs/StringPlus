# Компилятор и флаги
CC = gcc
CFLAGS = -std=c11 -pedantic -Werror -Wall -Wextra
CHECK_LIB = `pkg-config --cflags --libs check`

# Директории
SRC_DIR = .
BUILD_DIR = ../build
TEST_DIR = ../tests

# Файлы
SRC_FILES = $(SRC_DIR)/s21_string.c $(SRC_DIR)/s21_strtok.c $(SRC_DIR)/s21_sscanf.c $(SRC_DIR)/s21_sprintf.c
OBJ_FILES = $(BUILD_DIR)/s21_string.o $(BUILD_DIR)/s21_strtok.o $(BUILD_DIR)/s21_sscanf.o $(BUILD_DIR)/s21_sprintf.o
TEST_FILES = $(TEST_DIR)/test_s21_string.c
TEST_OBJ_FILES = $(BUILD_DIR)/test_s21_string.o

# Цель - тесты без репорта
TARGET = $(BUILD_DIR)/tests_runner

# Главная цель
all: s21_string.a

# Создание директории build
$(BUILD_DIR):
	mkdir -p $@

# Запуск тестов без отчета gcov
test: $(TARGET)
	./$(TARGET)

# Связывание тестов и библиотеки без отчета gcov
$(TARGET): s21_string.a $(TEST_OBJ_FILES)
	$(CC) $(TEST_OBJ_FILES) $(BUILD_DIR)/s21_string.a -o $@ $(CHECK_LIB) -lm

# Создание статической библиотеки s21_string.a
s21_string.a: $(OBJ_FILES)
	ar rcs $(BUILD_DIR)/s21_string.a $^
	cp $(BUILD_DIR)/s21_string.a $(SRC_DIR)

# Компиляция библиотечных файлов с исходным кодом
$(BUILD_DIR)/s21_string.o: $(SRC_DIR)/s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/s21_strtok.o: $(SRC_DIR)/s21_strtok.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/s21_sscanf.o: $(SRC_DIR)/s21_sscanf.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/s21_sprintf.o: $(SRC_DIR)/s21_sprintf.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция тестов
$(BUILD_DIR)/test_s21_string.o: $(TEST_DIR)/test_s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@




# Сборка с генерацией отчета gcov

# + Директория
REPORT_DIR = ../report

# + Цель (тесты с репортом)
TARGET_GCOV = $(BUILD_DIR)/tests_runner_gcov

# + Файлы
GCOV_OBJ_FILES = $(BUILD_DIR)/s21_string_gcov.o $(BUILD_DIR)/s21_strtok_gcov.o $(BUILD_DIR)/s21_sscanf_gcov.o $(BUILD_DIR)/s21_sprintf_gcov.o

# Создание директории report
$(REPORT_DIR):
	mkdir -p $@

gcov_report: $(TARGET_GCOV)
	./$(TARGET_GCOV)
	lcov --directory $(BUILD_DIR) --capture --output-file $(REPORT_DIR)/coverage.info
	genhtml $(REPORT_DIR)/coverage.info -o $(REPORT_DIR)/
	open $(REPORT_DIR)/index.html

# Связывание тестов и объектных файлов библиотеки с отчетом gcov
$(TARGET_GCOV): $(GCOV_OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(TEST_OBJ_FILES) $(GCOV_OBJ_FILES) -o $@ $(CHECK_LIB) -lgcov -lm

# Компиляция библиотечных файлов с исходным кодом с флагами для gcov
$(BUILD_DIR)/s21_string_gcov.o: $(SRC_DIR)/s21_string.c | $(BUILD_DIR) $(REPORT_DIR)
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c $< -o $@

$(BUILD_DIR)/s21_strtok_gcov.o: $(SRC_DIR)/s21_strtok.c | $(BUILD_DIR) $(REPORT_DIR)
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c $< -o $@

$(BUILD_DIR)/s21_sscanf_gcov.o: $(SRC_DIR)/s21_sscanf.c | $(BUILD_DIR) $(REPORT_DIR)
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c $< -o $@

$(BUILD_DIR)/s21_sprintf_gcov.o: $(SRC_DIR)/s21_sprintf.c | $(BUILD_DIR) $(REPORT_DIR)
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(REPORT_DIR) $(SRC_DIR)/s21_string.a

rebuild: clean all

style: $(SRC_DIR)/*.c $(SRC_DIR)/*.h $(TEST_DIR)/*.c
	clang-format -i $^

valgrind: $(TARGET)
	valgrind -q --tool=memcheck --leak-check=yes $(TARGET)

check: $(SRC_DIR)
	cppcheck -q --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction $(SRC_DIR)/*.c

.PHONY: all clean rebuild style test gcov_report valgrind