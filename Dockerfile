FROM leshiy1295/gcc_linters_valgrind_cmake_gtest

RUN apt install -y lcov

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make