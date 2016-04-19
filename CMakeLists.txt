
cmake_minimum_required(VERSION 3.2)
project(life)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

add_executable(life WIN32 main.cpp mainwindow.cpp life.cpp lifeview.cpp)

qt5_use_modules(life Widgets)
