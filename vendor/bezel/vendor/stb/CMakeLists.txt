cmake_minimum_required(VERSION 3.6)
project(stb)

set(SOURCE_FILES "stb_image.cpp" "stb_image.h")
add_library(stb STATIC ${SOURCE_FILES})

target_link_libraries( ${PROJECT_NAME}
  Engine
  )