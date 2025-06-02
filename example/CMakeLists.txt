add_executable(example main.cpp)

target_link_libraries(example PRIVATE neo)

install(TARGETS example DESTINATION bin)