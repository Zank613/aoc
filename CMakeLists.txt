cmake_minimum_required(VERSION 3.20)
project(advent_of_code)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE AOC_MAIN_FILES
        CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/20*/day*/main.cpp"
)

foreach(MAIN_FILE IN LISTS AOC_MAIN_FILES)
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}" "${MAIN_FILE}")

    get_filename_component(DAY_DIR "${MAIN_FILE}" DIRECTORY)
    get_filename_component(DAY_NAME "${DAY_DIR}" NAME)

    get_filename_component(YEAR_DIR "${DAY_DIR}" DIRECTORY)
    get_filename_component(YEAR_NAME "${YEAR_DIR}" NAME)

    set(TARGET_NAME "${YEAR_NAME}_${DAY_NAME}")

    add_executable(${TARGET_NAME} "${MAIN_FILE}")

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/data"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>/data"
    )
endforeach()