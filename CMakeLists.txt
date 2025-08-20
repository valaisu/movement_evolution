cmake_minimum_required(VERSION 3.10)
project(MyGameProject VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SFML
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE) # Optional: disable if not needed
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "" FORCE) # Use shared libraries
add_subdirectory(external/SFML)

# Add Box2D
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(external/box2d)

# Torch # yeah it seems I should just download the cpu torch and use that
# bc I mean I think the learning tasks we will be running will be quite light
# Or more like the overhead will be relatively heavy, anyways
set(CMAKE_PREFIX_PATH "/home/valaisu/Documents/libraries/libtorch-shared-with-deps-2.8.0+cpu/libtorch" CACHE PATH "" FORCE)
find_package(Torch REQUIRED)

# Your game source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/box2d/include
)

# Link libraries (Torch, SFML, Box2D all together)
target_link_libraries(${PROJECT_NAME} PRIVATE
    "${TORCH_LIBRARIES}"
    sfml-graphics
    sfml-window
    sfml-system
    box2d
)

# Torch ABI flags (important!)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Copy SFML DLLs to output directory on Windows
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
