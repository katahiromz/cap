# executable
add_executable(cap2 WIN32 cap2.cpp cap2_res.rc)

# link
target_link_libraries(cap2 comctl32 avicap32)
