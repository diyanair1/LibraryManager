cmake_minimum_required(VERSION 3.16)
project(library_server VERSION 0.1 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Homebrew prefix (change if you use /usr/local)
if(NOT DEFINED HOMEBREW_PREFIX)
  set(HOMEBREW_PREFIX "/opt/homebrew" CACHE PATH "Homebrew prefix")
endif()

# Source files
set(SOURCES
  api_server.cpp
  main.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories (Homebrew-installed libs)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${HOMEBREW_PREFIX}/opt/fmt/include
  ${HOMEBREW_PREFIX}/opt/boost/include
  ${HOMEBREW_PREFIX}/opt/nlohmann-json/include
  ${HOMEBREW_PREFIX}/opt/libpq/include
)

# Link directories (where the .dylib/.a files live)
target_link_directories(${PROJECT_NAME} PRIVATE
  ${HOMEBREW_PREFIX}/opt/fmt/lib
  ${HOMEBREW_PREFIX}/opt/boost/lib
  ${HOMEBREW_PREFIX}/opt/libpq/lib
  ${HOMEBREW_PREFIX}/lib
)

# Link libraries (same as -l flags in your g++ command)
# Note: 'pthread' is generally provided by the system; on macOS it is usually not required as a separate link,
# but we keep it here for parity with your current command.
target_link_libraries(${PROJECT_NAME} PRIVATE
  fmt
  pqxx
  pq
  pthread
)

# Ensure runtime loader can find Homebrew libs on macOS (RPATH)
set_target_properties(${PROJECT_NAME} PROPERTIES
  INSTALL_RPATH "${HOMEBREW_PREFIX}/lib;${HOMEBREW_PREFIX}/opt/libpq/lib;${HOMEBREW_PREFIX}/opt/boost/lib;${HOMEBREW_PREFIX}/opt/fmt/lib"
  BUILD_WITH_INSTALL_RPATH ON
)
