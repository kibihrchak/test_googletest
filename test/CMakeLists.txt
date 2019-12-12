add_executable(
    hello_googletest
    hello_1.cc
    hello_2.cc
    )
target_link_libraries(hello_googletest gmock_main)

add_test(
    NAME hello_googletest
    COMMAND hello_googletest)
