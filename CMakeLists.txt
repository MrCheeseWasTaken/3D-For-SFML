cmake_minimum_required(VERSION 3.21)

set(SANDBOX_ON TRUE)

set(PROJECT_NAME sfml3D)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB_RECURSE source_files
   src/**.cpp
   src/**.hpp
)

file(GLOB_RECURSE lib_files

   lib/libsfml-audio.a
   lib/libsfml-window.a
   lib/libsfml-network.a
   lib/libsfml-graphics.a
   lib/libsfml-system.a
   lib/libsfml-main.a

   lib/libFLAC.a
   lib/libfreetype.a
   lib/libogg.a
   lib/libopengl32.a
   lib/libvorbis.a
   lib/libvorbisenc.a
   lib/libvorbisfile.a

)

set(SOURCES ${source_files})
set(CMAKE_CXX_STANDARD 17)

if (${SANDBOX_ON})


   set(SandboxName game)

   file(GLOB_RECURSE sandbox_source
      ${source_files}
      sandbox/src/**.cpp
      sandbox/src/**.hpp
   )

   add_executable(${SandboxName} ${sandbox_source})
   target_include_directories(${SandboxName} PRIVATE "include" "src" "sandbox/src")
   target_link_libraries(${SandboxName} ${lib_files})

   file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

   RETURN()
   
endif()

#----------------------Static--------------------------#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SFML3D)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SFML3D)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SFML3D)

set(StaticName "sfml3D-static")
add_library(${StaticName} STATIC ${SOURCES})
target_include_directories(${StaticName} PRIVATE "include" "src")
target_link_libraries(${StaticName} ${lib_files})

# #----------------------Dynamic-------------------------#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SFML3D)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SFML3D)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SFML3D)

set(DynamicName "sfml3D-dynamic")
add_library(${DynamicName} SHARED ${SOURCES})
target_include_directories(${DynamicName} PRIVATE "include" "src")
target_link_libraries(${DynamicName} ${lib_files})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (FALSE)

   set(ExampleName "cubes")

   file(GLOB_RECURSE src
      examples/cubes/main.cpp
   )

   file(GLOB_RECURSE libs
      ${lib_files}
      lib/libsfml3D-dynamic.dll.a
   )

   add_executable(${ExampleName} ${src})
   target_include_directories(${ExampleName} PRIVATE "include")
   target_link_libraries(${ExampleName} ${libs})

endif()

if (FALSE)

   set(ExampleName "rendertexture")

   file(GLOB_RECURSE src
      examples/rendertexture/main.cpp
   )

   file(GLOB_RECURSE libs
      ${lib_files}
      lib/libsfml3D-dynamic.dll.a
   )

   add_executable(${ExampleName} ${src})
   target_include_directories(${ExampleName} PRIVATE "include")
   target_link_libraries(${ExampleName} ${libs})

endif()

if (FALSE)

   set(ExampleName "model")

   file(GLOB_RECURSE src
      examples/model/main.cpp
   )

   file(GLOB_RECURSE libs
      ${lib_files}
      lib/libsfml3D-dynamic.dll.a
   )

   add_executable(${ExampleName} ${src})
   target_include_directories(${ExampleName} PRIVATE "include")
   target_link_libraries(${ExampleName} ${libs})

endif()

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
