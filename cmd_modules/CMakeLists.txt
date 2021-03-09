# Create a library name from our current directory.
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${LIBRARY_NAME})

# Create lists of our files for this library.
set(HEADER_FILES
    inc/cmd_modules/checksum.h
    inc/cmd_modules/command.h
    inc/cmd_modules/command_modules.h
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

# Add our include directories. 
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# Link to libraries that this library ueses.
target_link_libraries(${LIBRARY_NAME}
    tools
    #thirdparty
    )


