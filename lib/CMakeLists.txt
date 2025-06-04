set(WITH_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/json)
add_subdirectory(thirdparty/eternal)
add_subdirectory(thirdparty/cml)

add_library(neo STATIC
        src/neo/IApplication.cpp
        src/neo/JSON.cpp
        include/neo/math/Vector2.h
        include/neo/math/Math.h
        src/neo/Math.cpp
        include/neo/math/Rectangle.h
        include/neo/math/Color.h
        src/neo/Terminal.cpp
)

if(MSVC)
    target_compile_options(neo PUBLIC /EHsc)
else()
    target_compile_options(neo PUBLIC -fexceptions)
endif()

target_link_libraries(neo PUBLIC eternal nlohmann_json::nlohmann_json)

target_include_directories(neo PUBLIC ${eternal_SOURCE_DIR}/include)
target_include_directories(neo PUBLIC ${cml_SOURCE_DIR})

target_include_directories(neo PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)