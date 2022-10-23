FROM leshiy1295/gcc_linters_valgrind_cmake_gtest

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make