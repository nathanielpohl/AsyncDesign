# Create a library name from our current directory.
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${LIBRARY_NAME})

# Create lists of our files for this library.
set(HEADER_FILES
    inc/fpic_modules/fpincppch2.h
    inc/fpic_modules/fpincppch3.h
    inc/fpic_modules/fpincppch4.h
    inc/fpic_modules/fpincppch6.h
    inc/fpic_modules/fpincppch7.h
    )

set(SOURCE_FILES
    src/fpincppch2.cpp
    src/fpincppch3.cpp
    src/fpincppch4.cpp
    src/fpincppch6.cpp
    src/fpincppch7.cpp
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


