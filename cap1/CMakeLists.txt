# executable
add_executable(cap1 WIN32 cap1.cpp cap1_res.rc)

# link
target_link_libraries(cap1 comctl32 avicap32)
