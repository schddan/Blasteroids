cmake_minimum_required(VERSION 3.15)
project(Blasteroids C)

include_directories(/usr/include/allegro5/)
link_libraries(/usr/lib/x86_64-linux-gnu/liballegro.so)
link_libraries(/usr/lib/x86_64-linux-gnu/liballegro_primitives.so)

add_executable(Blasteroids)

target_sources(
    Blasteroids
    PRIVATE
        blast.c
        asteroid.c
        main.c
        spaceship.c
        collisions.c
        blast.h
        asteroid.h
        spaceship.h
        consts.h
        collisions.h
)


target_link_libraries(Blasteroids PRIVATE -lm)
