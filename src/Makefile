FLAGS = -Wall -Werror -Wextra -std=c11
TEST_FLAGS = -Wall -Werror -Wextra -std=c11 -w
LIB = -lcheck -lsubunit -L. s21_string.a -lm
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
C_FILE = s21_string.c s21_sprintf.c s21_sscanf.c s21_special.c
OBJECT = s21_string.o s21_sprintf.o s21_sscanf.o s21_special.o

all: check_deps s21_string.a test gcov_report

check_deps:
	@command -v gcc > /dev/null || (@echo "Error: gcc is not installed. Please install it." && exit 1)
	@command -v lcov > /dev/null || (@echo "Error: lcov is not installed. Please install it." && exit 1)
	@command -v genhtml > /dev/null || (@echo "Error: genhtml is not installed. Please install it." && exit 1)
	@ldconfig -p | grep libsubunit > /dev/null || (@echo "Error: libsubunit is not installed. Please install it (e.g., 'sudo apt install libsubunit-dev')." && exit 1)

s21_string.a:
	gcc $(FLAGS) -c $(C_FILE)
	ar rcs s21_string.a $(OBJECT)

test:
	gcc $(TEST_FLAGS) s21_string_test.c -o s21_string_test.o $(LIB)
	./s21_string_test.o
	gcc $(TEST_FLAGS) s21_sprintf_test.c -o s21_sprintf_test.o $(LIB)
	./s21_sprintf_test.o
	gcc $(TEST_FLAGS) s21_sscanf_test.c -o s21_sscanf_test.o $(LIB)
	./s21_sscanf_test.o
	gcc $(TEST_FLAGS) s21_special_test.c -o s21_special_test.o $(LIB)
	./s21_special_test.o

gcov_report:
	gcc $(GCOV_FLAGS) -c $(C_FILE)
	gcc $(GCOV_FLAGS) -o s21_string_test.o $(OBJECT) s21_string_test.c $(LIB)
	gcc $(GCOV_FLAGS) -o s21_sprintf_test.o $(OBJECT) s21_sprintf_test.c $(LIB)
	gcc $(GCOV_FLAGS) -o s21_sscanf_test.o $(OBJECT) s21_sscanf_test.c $(LIB)
	gcc $(GCOV_FLAGS) -o s21_special_test.o $(OBJECT) s21_special_test.c $(LIB)
	./s21_string_test.o
	./s21_sprintf_test.o
	./s21_sscanf_test.o
	./s21_special_test.o
	gcov s21_string.c s21_sprintf.c s21_sscanf.c s21_special.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory html
	@echo "Отчет готов. Пожалуйста, откройте html/index.html в браузере."

clean:
	rm -f s21_string.a
	rm -f *.o *.o
	rm -f *.gcda *.gcno *.gcov
	rm -f coverage.info
	rm -rf ./html

rebuild: 
	clean all

format: 
	clang-format -n *.c
	clang-format -n *.h