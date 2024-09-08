CARGS = gcc -g -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage

APP_ARCHIVE = SmartCalc_v1.0

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lpthread -lcheck -pthread -lrt -lm -lsubunit
	APP_NAME = frontend_calc
else
	CHECK_FLAGS = -lcheck
	APP_NAME = frontend_calc.app
endif

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: install

calc_backend.a:
	$(CARGS) -c backend_calc/*.c
	ar rcs calc_backend.a *.o
	rm -rf *.o

test: calc_backend.a
	$(CARGS) unit_tests/*.c calc_backend.a $(CHECK_FLAGS) -o unit_test
	./unit_test

gcov_report: calc_backend.a
	$(CARGS) $(GCOVFLAGS) unit_tests/*.c backend_calc/*.c $(CHECK_FLAGS) -o gcov_test
	./gcov_test
	gcov *.c
	gcov testc/*.c
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	rm -rf *.o *.gcno *.gcda
	$(OPEN_CMD) ./report/index.html

install: uninstall
	mkdir -p ~/SmartCalc
	cd frontend_calc && \
	qmake && \
	make && \
	make clean && \
	rm -f Makefile && \
	cd .. && \
	mv frontend_calc/$(APP_NAME) ~/SmartCalc/$(APP_NAME)

uninstall:
	rm -rf ~/SmartCalc/$(APP_NAME)

open:
	open ~/SmartCalc/$(APP_NAME)

run: install open

dist: install
	rm -rf $(APP_ARCHIVE)/
	mkdir $(APP_ARCHIVE)
	mkdir $(APP_ARCHIVE)/src/
	cp -r ~/SmartCalc/$(APP_NAME) $(APP_ARCHIVE)/src/$(APP_NAME)
	tar -cvzf $(APP_ARCHIVE).tgz $(APP_ARCHIVE)/
	rm -rf $(APP_ARCHIVE)

dvi:
	$(OPEN_CMD) dvi.html

clang:
	clang-format -n unit_tests/*.c
	clang-format -n unit_tests/*.h
	clang-format -n backend_calc/*.c
	clang-format -n backend_calc/*.h
	clang-format -n frontend_calc/*.cpp
	clang-format -n frontend_calc/*.h

clang-fix:
	clang-format -i unit_tests/*.c
	clang-format -i unit_tests/*.h
	clang-format -i backend_calc/*.c
	clang-format -i backend_calc/*.h
	clang-format -i frontend_calc/*.cpp
	clang-format -i frontend_calc/*.h

leaks: test
	CK_FORK=no leaks --atExit -- ./unit_test

valgrind: test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./unit_test

clean:
	rm -rf build*
	rm -rf /frontend_calc/*.stash
	rm -rf *.o *.gcno *.gcda *.a *.info report *.out *.dSYM
	rm -rf $(APP_ARCHIVE)/
	rm -rf *.tgz
	rm -f unit_test
	rm -f gcov_test
	rm -f out
