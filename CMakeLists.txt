cmake_minimum_required(VERSION 3.11)
project(bomberman VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/libs/Irrlicht")
set(Irrlicht_FIND_REQUIRED true)
include(FindIrrlicht)


set(SOURCES
    src/Main.cpp
    src/Core.cpp
    src/Menu/Menu.cpp
    src/Menu/Button.cpp
    src/Menu/Option.cpp
    src/Menu/Adventure.cpp
    src/Game/window.cpp
    src/Game/Player.cpp
    src/Game/Wall.cpp
    src/Game/ground.cpp
    src/Game/map.cpp
    src/Game/bomb.cpp
    src/Game/UI.cpp
    src/Game/Music.cpp
    src/Game/Path.cpp
    src/Menu/Arcade.cpp
    src/Game/GameOver.cpp
    src/Game/Win.cpp
)

set(CMAKE_CXX_STANDARD 17)

link_directories("./libs/Irrlicht")
link_directories("./libs/SFML")
link_libraries(${Irrlicht_LIBRARIES} sfml-audio -lpthread)

if (MSVC)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/Irrlicht/irrlicht.dll
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/sfml-audio-2.dll
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/sfml-system-2.dll
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/openal32.dll
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
    include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/libs/Irrlicht/include/
        ${CMAKE_CURRENT_LIST_DIR}/libs/SFML/include/
    )
else (MSVC)
    add_compile_options()
    include_directories(
        ${Irrlicht_INCLUDE_DIRS}
    )
endif (MSVC)



add_executable(${PROJECT_NAME} ${SOURCES})
