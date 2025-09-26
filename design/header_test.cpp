/**
 * @file header_test.cpp
 * @brief Teste de compilação para todos os arquivos de cabeçalho
 * 
 * Este arquivo inclui todos os headers para garantir que compilem corretamente
 * e tenham include guards e dependências apropriados.
 */

// Testa se todos os headers podem ser incluídos
#include "MediaPlayer.h"
#include "Track.h"
#include "MP3Player.h"
#include "Playlist.h"
#include "Equalizer.h"
#include "PlaylistPersistence.h"
#include "DirectoryScanner.h"
#include "MP3PlayerApp.h"
#include "CLI.h"

#include <iostream>
#include <memory>

/**
 * @brief Teste simples de compilação
 * 
 * Esta função cria instâncias das classes principais para garantir
 * que possam ser instanciadas e operações básicas funcionem.
 */
int main() {
    std::cout << "=== Teste de Compilação de Headers do MP3 Player ===" << std::endl;
    
    try {
        // Teste criação de Track
        auto track = std::make_shared<Track>();
        std::cout << "✓ Compilação da classe Track OK" << std::endl;
        
        // Teste criação de Playlist
        Playlist playlist("Playlist de Teste");
        std::cout << "✓ Compilação da classe Playlist OK" << std::endl;
        
        // Teste criação de Equalizer
        auto equalizer = Equalizer::createFlat();
        std::cout << "✓ Compilação da classe Equalizer OK" << std::endl;
        
        // Teste template DirectoryScanner
        auto scanner = createMP3Scanner();
        std::cout << "✓ Compilação do template DirectoryScanner OK" << std::endl;
        
        // Teste interface de persistência
        auto persistence = std::make_unique<JsonPlaylistPersistence>();
        std::cout << "✓ Compilação da interface PlaylistPersistence OK" << std::endl;
        
        // Teste aplicação principal
        MP3PlayerApp app;
        std::cout << "✓ Compilação da classe MP3PlayerApp OK" << std::endl;
        
        // Teste CLI
        CLI cli;
        std::cout << "✓ Compilação da classe CLI OK" << std::endl;
        
        std::cout << "\n=== Todos os Headers Compilados com Sucesso! ===" << std::endl;
        std::cout << "Validação da arquitetura aprovada." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Erro durante teste de compilação: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}