# Create a library name from our current directory.
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${LIBRARY_NAME})

# Create lists of our files for this library.
set(HEADER_FILES
    inc/async_design/command_modules.h
    inc/async_design/virtual_constructor.h
    )

set(SOURCE_FILES
    src/virtual_constructor.cpp
    )

# Create our library and add our source files.
add_library(${LIBRARY_NAME} ${SOURCE_FILES})

# Add our include directoies.
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# Link to libraries that this project ueses.
target_link_libraries(${LIBRARY_NAME}
    cmd_modules
    fpic_modules
    # thirdparty
    tools
    )

###############################################
# Create our executable.
add_executable(${LIBRARY_NAME}_bin src/main.cpp)

target_link_libraries(${LIBRARY_NAME}_bin ${LIBRARY_NAME} glog gflags)
