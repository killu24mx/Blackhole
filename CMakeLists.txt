cmake_minimum_required(VERSION 3.5)
project(Blackhole)
add_executable(main
    src/animation.cpp
    src/background.cpp
    src/blackhole.cpp
    src/bullet.cpp
    src/clockslow.cpp
    src/enemy.cpp
    src/entity.cpp
    src/game.cpp
    src/hard.cpp
    src/health.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/menu.cpp
    src/portal.cpp
    src/score.cpp
    src/sounds.cpp
    src/spaceship.cpp
)
include_directories(./include)

find_package(SFML 2.6.1 REQUIRED system window graphics network audio)
target_link_libraries(main sfml-graphics sfml-audio sfml-network sfml-window sfml-system)

