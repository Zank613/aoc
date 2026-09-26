cmake_minimum_required(VERSION 3.20)

project(aoc
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ataerk's Advent Library
add_subdirectory(aal)

# Automatically discover Advent of Code solutions.
file(GLOB_RECURSE AOC_MAIN_FILES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/20*/day*/main.cpp"
)

foreach(MAIN_FILE IN LISTS AOC_MAIN_FILES)

    get_filename_component(DAY_DIR
            "${MAIN_FILE}" DIRECTORY
    )

    get_filename_component(DAY_NAME
            "${DAY_DIR}" NAME
    )

    get_filename_component(YEAR_DIR
            "${DAY_DIR}" DIRECTORY
    )

    get_filename_component(YEAR_NAME
            "${YEAR_DIR}" NAME
    )

    # Example: 2015_day25
    set(TARGET_NAME "${YEAR_NAME}_${DAY_NAME}")

    # Discover all C++ source files for this day.
    file(GLOB DAY_SOURCES
            CONFIGURE_DEPENDS
            "${DAY_DIR}/*.cpp"
    )

    add_executable(${TARGET_NAME}
            ${DAY_SOURCES}
    )

    # Link Ataerk's Advent Library.
    target_link_libraries(${TARGET_NAME}
            PRIVATE aal
    )

    # Include day-specific headers.
    target_include_directories(${TARGET_NAME}
            PRIVATE "${DAY_DIR}"
    )

    # Copy puzzle inputs next to the executable.
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/data")
        add_custom_command(
                TARGET ${TARGET_NAME}
                POST_BUILD

                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/data"
                "$<TARGET_FILE_DIR:${TARGET_NAME}>/data"

                COMMENT "Copying AoC input files"
        )
    endif()

endforeach()