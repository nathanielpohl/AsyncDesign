# Create a library name from our current directory.
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${LIBRARY_NAME})

# Create lists of our files for this library.
set(HEADER_FILES
    inc/interview/adding_two_numbers.h
    inc/interview/count_complete_tree_nodes.h
    inc/interview/decode_string.h
    inc/interview/exam_room.h
    inc/interview/fruit_into_basket.h
    inc/interview/guess_the_word.h
    inc/interview/longest_increasing_path_matrix.h
    inc/interview/median_of_two_sorted_arrays.h
    inc/interview/most_stones_removed_with_same_row_or_column.h
    inc/interview/odd_even_jump.h
    inc/interview/redundant_connection.h
    inc/interview/unique_email_addresses.h
    inc/interview/valid_number.h
    )

set(SOURCE_FILES
    src/adding_two_numbers.cpp
    src/count_complete_tree_nodes.cpp
    src/decode_string.cpp
    src/exam_room.cpp
    src/fruit_into_basket.cpp
    src/guess_the_word.cpp
    src/longest_increasing_path_matrix.cpp
    src/most_stones_removed_with_same_row_or_column.cpp
    src/median_of_two_sorted_arrays.cpp
    src/odd_even_jump.cpp
    src/redundant_connection.cpp
    src/unique_email_addresses.cpp
    src/valid_number.cpp
    )
	
# Create our library and add our source files.
add_library(${LIBRARY_NAME} ${SOURCE_FILES})

# Add our include directories. 
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# Link to libraries that this library ueses.
target_link_libraries(${LIBRARY_NAME}
    tools
    #thirdparty
    )


