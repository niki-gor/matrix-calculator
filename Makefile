.PHONY: clean build

clean:
	rm -rf build

build: clean
	mkdir build && cd build && cmake .. && make

rebuild: clean build

test: build
	ctest --test-dir build