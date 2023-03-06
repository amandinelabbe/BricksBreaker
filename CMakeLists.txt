cmake_minimum_required(VERSION 3.23)
project(CasseBriques C)

set(CMAKE_C_STANDARD 99)

set(SDL2_PATH "C:\\Users\\amand\\Downloads\\x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "C:\\Users\\amand\\Downloads\\SDL2_image-devel-2.6.2-VC\\SDL2_image-2.6.2")
set(SDL2_TTF_PATH "C:\\Users\\amand\\Downloads\\SDL2_ttf-devel-2.20.1-VC\\SDL2_ttf-2.20.1")
set(SDL_MIXER_PATH "C:\\Users\\amand\\Downloads\\SDL2_ttf-devel-2.20.1-VC\\SDL2_ttf-2.20.1")


find_package(SDL2 REQUIRED)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL_MIXER REQUIRED)

include_directories( ${SDL2_INCLUDE_DIR} )
include_directories( ${SDL2_IMAGE_INCLUDE_DIRS} )
include_directories( ${SDL2_TTF_INCLUDE_DIRS} )
include_directories( ${SDL_MIXER_INCLUDE_DIRS} )

add_executable(HelloSDL main.c UserInput.c UserInput.h Briques.c Briques.h Menu.c Menu.h)

target_link_libraries(HelloSDL ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL_MIXER_LIBRARY})
