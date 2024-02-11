CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: custom_string.a tests gcov_report

custom_string.a:
	$(CC) -c ${CFLAGS} functions/custom_string.c -o functions/custom_string.o
	$(CC) -c ${CFLAGS} functions/custom_string_from_cs.c -o functions/custom_string_from_cs.o
	$(CC) -c ${CFLAGS} functions/custom_sprintf.c -o functions/custom_sprintf.o
	$(CC) -c ${CFLAGS} functions/custom_sscanf.c -o functions/custom_sscanf.o
	ar rcs custom_string.a functions/*.o

tests:
	$(CC) ${CFLAGS} tests/custom_test_string.c -L. custom_string.a -o test_sprintf -lcheck -lm -lsubunit
	$(CC) ${CFLAGS} tests/custom_test_sscanf.c -L. custom_string.a -o test_sscanf -lcheck -lm -lsubunit
	./test_sprintf
	./test_sscanf

gcov_report:
	$(CC) -c $(CFLAGS) --coverage functions/custom_string.c -o functions/custom_string.o
	$(CC) -c $(CFLAGS) --coverage functions/custom_string_from_cs.c -o functions/custom_string_from_cs.o
	$(CC) -c $(CFLAGS) --coverage functions/custom_sprintf.c -o functions/custom_sprintf.o
	$(CC) -c $(CFLAGS) --coverage functions/custom_sscanf.c -o functions/custom_sscanf.o
	ar rcs custom_string.a functions/*.o
	$(CC) $(CFLAGS) --coverage tests/custom_test_string.c -o custom_string_tests -L. custom_string.a -lcheck -lm -lsubunit -lgcov
	$(CC) $(CFLAGS) --coverage tests/custom_test_sscanf.c -o custom_sscanf_tests -L. custom_string.a -lcheck -lm -lsubunit -lgcov
	./custom_string_tests > report.txt || true
	./custom_sscanf_tests > report.txt || true
	lcov -o string_tests.info -c -d .
	genhtml -o report string_tests.info

clean:
	rm -rf functions/*.o functions/*.h.gch functions/*.gcda functions/*.gcno
	rm -rf functions/sprintf/*.o functions/sprintf/*.h.gch
	rm -f *.gcda *.gcno
	rm -f custom_sscanf_tests
	rm -f custom_string_tests
	rm -f string_tests.info
	rm -f report.txt
	rm -rf report
	rm -f custom_string.a
	rm -f test_sprintf
	rm -f test_sscanf
	rm -f test
	rm -f custom_string.o
	rm -f tests/*.gcno