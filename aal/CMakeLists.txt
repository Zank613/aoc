
cmake_minimum_required(VERSION 3.20)

project(aal
        VERSION 0.1.0
        LANGUAGES CXX
)

# Automatically discover AAL implementation files.
file(GLOB_RECURSE AAL_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(aal STATIC
        ${AAL_SOURCES}
)

target_compile_features(aal
        PUBLIC cxx_std_17
)

target_include_directories(aal
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Convenient alias for other CMake projects.
add_library(aal::aal ALIAS aal)

set_target_properties(aal PROPERTIES
        VERSION ${PROJECT_VERSION}
        OUTPUT_NAME "aal"
)