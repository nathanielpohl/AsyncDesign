# Create a library name from our current directory.
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Create lists or our files for this library.
set(SOURCE_FILES
    main.cpp
    )

set(HEADER_FILES
    )


# Create our library and add our source files.
# add_library(${LIBRARY_NAME} ${SOURCE_FILES})

# Create our executable.
add_executable(${LIBRARY_NAME} ${SOURCE_FILES})

# Link to libraries that this library ueses
target_link_libraries(${LIBRARY_NAME}
    cmd_modules
    # thirdparty
    tools
    )

# Make sure that when we are linked to other libraries can find our files.
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
