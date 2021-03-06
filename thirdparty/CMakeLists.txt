# Create a library name from our current directory.
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Create lists or our files for this library.
set(HEADER_FILES
    inc/cmd_modules/checksum.h
    inc/cmd_modules/command.h
    inc/cmd_modules/file_command.h
    inc/cmd_modules/virtual_constructor.h
    inc/cmd_modules/word_count.h
    inc/cmd_modules/word_freq.h
    )

set(SOURCE_FILES
    src/checksum.cpp
    src/virtual_constructor.cpp
    src/word_count.cpp
    src/word_freq.cpp
    )
	
# Create our library and add our source files.
add_library(${LIBRARY_NAME} ${SOURCE_FILES})

# Link to libraries that this library ueses
target_link_libraries(${LIBRARY_NAME} LINK_PRIVATE thirdparty)

# Make sure that when we are linked to other libraries can find our files.
target_include_directories(${LIBRARY_NAME} PUBLIC ${HEADER_FILES})

