# Esta linha é importante para garantir que não se tente usar uma versão antiga
# do CMake. Freqüentemente são introduzidas novas features, então é importante.
cmake_minimum_required(VERSION 2.8.3)

# Cria uma variável com um valor inicial e também a torna acessível para o
# usuário através da interface gráfica ou curses.
set(FW_PATH "../fw" CACHE STRING "Path to the FW")

# Procura pelo OpenCV instalado na máquina. Se não existir, vai dar erro.
find_package(OpenCV REQUIRED)

# Aqui verificamos se o OpenCV foi encontrado. Note que estamos testando a
# variável, e não o valor dela.
if (OpenCV_VERSION)

  # Se o OpenCV foi encontrado, informa ao usuário qual a versão presente no
  # sistema.
  message(STATUS "OpenCV version: " ${OpenCV_VERSION_MAJOR} "." ${OpenCV_VERSION_MINOR} "." ${OpenCV_VERSION_PATCH})

  # Se a versão do OpenCV for menor que 2.2.3, emitimos um fatal error.
  if(${OpenCV_VERSION_MAJOR} LESS 2 OR (${OpenCV_VERSION_MAJOR} EQUAL 2 AND ${OpenCV_VERSION_MINOR} LESS 3))
    message(FATAL_ERROR "You need OpenCV version 2.3.0 or later!")
  endif()

endif()

# Adicionamos o diretório de include deste projeto.
#include_directories(include)

# O diretório de include do framework também é adicionado,
#include_directories(${FW_PATH}/include)

# assim como o diretório onde espera-se encontrar a biblioteca.
#link_directories(${FW_PATH}/build)

# Este comando busca todos os arquivos *.cpp dentro do diretório src, e armazena a lista na variável
# lib_sources.
file(GLOB sources *.cpp)

# Aqui dizemos ao CMake que queremos construir uma biblioteca chamada boosted (que
# será libboosted.so no Linux e ex.dll no Windows) composta pelos arquivos contidos
# na variável sources.
add_library(boosted STATIC ${sources})

# Esta biblioteca que estamos criando depende das bibliotecas do OpenCV e do
# framework.
target_link_libraries(boosted ${OpenCV_LIBS}) #fw)

# Informamos ao CMake para criar um executável chamado run (run.exe no
# Windows) a partir do arquivo detect.cpp.
add_executable(rotation rotation.cpp)
add_executable(kalman_filter kalman_filter_main.cpp)
add_executable(sobel sobel.cpp)
add_executable(test test.cpp)
add_executable(surf surf.cpp)

# Este executável depende da biblioteca ex, também construída por este arquivo.
target_link_libraries(rotation boosted)
target_link_libraries(kalman_filter boosted)
target_link_libraries(sobel boosted)
target_link_libraries(test boosted)
target_link_libraries(surf boosted)
