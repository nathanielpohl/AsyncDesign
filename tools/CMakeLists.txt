# Create a library name from our current directory.
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${LIBRARY_NAME})

# Create lists of our files for this library.
set(HEADER_FILES
    inc/tools/csv_parser.h
    )

set(SOURCE_FILES
    src/csv_parser.cpp
    )
	
# Create our library and add our source files.
add_library(${LIBRARY_NAME} ${SOURCE_FILES})

# Make sure that when we are linked to other libraries can find our files.
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# Link to libraries that this library uses.
target_link_libraries(${LIBRARY_NAME}
    #thirdparty
    )
