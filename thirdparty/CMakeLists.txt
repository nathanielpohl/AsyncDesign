# Create a library name from our current directory.
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Create lists of our files for this library.
set(HEADER_FILES
    )

set(SOURCE_FILES
    )
	
# Create our library and add our source files.
add_library(${LIBRARY_NAME} ${SOURCE_FILES})

# Add our include directories.
target_link_libraries(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

