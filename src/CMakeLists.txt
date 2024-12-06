add_library(src
        util/log.cpp
)


# Link libraries (if needed)
target_link_libraries(src PUBLIC argparse)

# Include directories
target_include_directories(src PUBLIC
        ${GLIB_INCLUDE_DIR}
        ${argparse_SOURCE_DIR}
)
