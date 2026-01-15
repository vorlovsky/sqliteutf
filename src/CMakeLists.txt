# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(sqliteutf_library VERSION 0.0.1 LANGUAGES C)

add_library(sqliteutf SHARED
  "sqliteutf.c"
)

set_target_properties(sqliteutf PROPERTIES
  OUTPUT_NAME "sqliteutf"
)

target_compile_definitions(sqliteutf PUBLIC DART_SHARED_LIB)

if (ANDROID)
  # Support Android 15 16k page size.
  target_link_options(sqliteutf PRIVATE "-Wl,-z,max-page-size=16384")
endif()
