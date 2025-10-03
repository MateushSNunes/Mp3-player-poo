cmake_minimum_required(VERSION 3.16)
project(MP3Player VERSION 1.0.0 LANGUAGES CXX)

# Definir padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Definir tipo de build se não especificado
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Opções específicas do compilador
if(MSVC)
    add_compile_options(/W4 /EHsc)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Diretórios de include
include_directories(${CMAKE_SOURCE_DIR}/include)

# Encontrar pacotes
find_package(Threads REQUIRED)

# Opcional: Encontrar Qt6 para futura implementação GUI
find_package(Qt6 QUIET COMPONENTS Core Widgets Multimedia)
if(Qt6_FOUND)
    message(STATUS "Qt6 encontrado - suporte GUI disponível")
    add_definitions(-DQTX_AVAILABLE)
endif()

# Opcional: Encontrar bibliotecas de áudio (para implementação futura)
# find_package(PkgConfig QUIET)
# if(PkgConfig_FOUND)
#     pkg_check_modules(SNDFILE QUIET sndfile>=1.0.25)
#     pkg_check_modules(PORTAUDIO QUIET portaudio-2.0>=19.6.0)
# endif()

# Arquivos fonte (apenas headers por enquanto)
set(HEADER_FILES
    include/MediaPlayer.h
    include/Track.h
    include/MP3Player.h
    include/Playlist.h
    include/Equalizer.h
    include/PlaylistPersistence.h
    include/DirectoryScanner.h
    include/MP3PlayerApp.h
    include/CLI.h
)

# Arquivos fonte implementados
set(SOURCE_FILES
    src/MediaPlayer.cpp
    src/Track.cpp
    src/MP3Player.cpp
    src/Playlist.cpp
    src/Equalizer.cpp
    src/PlaylistPersistence.cpp
    src/DirectoryScanner.cpp
    src/MP3PlayerApp.cpp
    src/CLI.cpp
    src/main.cpp
)

# Criar biblioteca header-only para verificação de compilação
add_library(mp3player_headers INTERFACE)
target_sources(mp3player_headers INTERFACE ${HEADER_FILES})
target_include_directories(mp3player_headers INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Target de teste de compilação
add_executable(header_test
    ${CMAKE_CURRENT_SOURCE_DIR}/design/header_test.cpp
)
target_link_libraries(header_test mp3player_headers)

# Executável principal
add_executable(mp3player ${SOURCE_FILES})
target_include_directories(mp3player PRIVATE include)
target_compile_features(mp3player PRIVATE cxx_std_17)
target_link_libraries(mp3player 
    Threads::Threads
)

# Configurações específicas por plataforma
if(WIN32)
    target_compile_options(mp3player PRIVATE /utf-8)
    set_target_properties(mp3player PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endif()

# Configurações para Debug/Release
set_target_properties(mp3player PROPERTIES
    DEBUG_POSTFIX "_d"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# if(Qt6_FOUND)
#     target_link_libraries(mp3player Qt6::Core Qt6::Widgets Qt6::Multimedia)
# endif()

# Configuração de instalação
install(TARGETS mp3player mp3player_headers
    EXPORT MP3PlayerTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include/mp3player)

# Configuração de exportação
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "MP3PlayerConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

export(EXPORT MP3PlayerTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MP3PlayerTargets.cmake"
    NAMESPACE MP3Player::
)

# Configuração CPack para empacotamento
set(CPACK_PACKAGE_NAME "MP3Player")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MP3 Player Orientado a Objetos em C++")
set(CPACK_PACKAGE_VENDOR "Projeto POO")

include(CPack)

# Imprimir resumo da configuração
message(STATUS "=== Resumo da Configuração MP3Player ===")
message(STATUS "Tipo de build: ${CMAKE_BUILD_TYPE}")
message(STATUS "Padrão C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Suporte Qt6: ${Qt6_FOUND}")
message(STATUS "Prefixo de instalação: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "========================================")