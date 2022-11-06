.PHONY: clean build test

clean:
	rm -rf build

build: clean
	mkdir build && cd build && cmake .. && make && cd ..

test: build
	./build/tests/tests

rebuild: clean build