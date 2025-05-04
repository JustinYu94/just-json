cmake_minimum_required(VERSION 3.14)

add_library(JustJson STATIC
    src/JustJson.h
    src/JustJson.c
)

add_executable(JustJsonTest
    tests/JustJsonTest.c
)
target_link_libraries(JustJsonTest
    PRIVATE JustJson
)