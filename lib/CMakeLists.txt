set(WITH_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/json)
add_subdirectory(thirdparty/eternal)


add_library(neo STATIC
        src/neo/neo.cpp
        include/neo/IApplication.h
        include/neo/JSON.h
        src/neo/JSON.cpp
        include/neo/Primitives.h
)

target_link_libraries(neo PUBLIC eternal nlohmann_json::nlohmann_json)

target_include_directories(neo PUBLIC ${eternal_SOURCE_DIR}/include)

target_include_directories(neo PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)