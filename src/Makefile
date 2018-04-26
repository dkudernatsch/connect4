all: ascii

ascii: *.cpp
	g++ -std=c++17 -ggdb -o ascii *.cpp

tests: *.cpp *.h
	g++ -std=c++17 -DTESTS -I../gtest/include ../gtest/lib/gtest_main.a -ggdb -o UEB2_tests *.cpp

run: ascii
	drmemory -- ascii

run_tests: tests
	drmemory -- UEB2_tests

clean:
	rm -f ascii.exe ascii UEB*_tests.exe UEB*_tests *.o