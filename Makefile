jsonc:
	g++ -std=c++20 -o bin/jsonc jsonc.cpp

clean:
	rm bin/jsonc
	rm bin/test

test:
	g++ -std=c++20 -o bin/test test.cpp
	bin/test
	@echo OK


.PHONY: test