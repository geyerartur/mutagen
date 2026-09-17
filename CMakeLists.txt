cmake_minimum_required(VERSION 3.31)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mutagen)

set(CURSES_NEED_WIDE TRUE)
unset(CURSES_CURSES_LIBRARY CACHE)
unset(CURSES_NCURSES_LIBRARY CACHE)
unset(CURSES_FORM_LIBRARY CACHE)
unset(CURSES_INCLUDE_PATH CACHE)
find_package(Curses REQUIRED)

add_executable(${PROJECT_NAME} 
  main.cpp
  game/game.cpp
  input/input.cpp
  renderer/renderer.cpp
)


target_include_directories(mutagen PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(mutagen PRIVATE ${CURSES_LIBRARIES} panelw)
