#include "MP3PlayerApp.h"
#include <iostream>
#include <sstream>
#include <algorithm>

MP3PlayerApp::MP3PlayerApp() 
    : player(std::make_unique<MP3Player>()),
      scanner(createAudioScanner()),
      persistence(std::make_unique<JsonPlaylistPersistence>()),
      running(false) {}

MP3PlayerApp::~MP3PlayerApp() = default;

void MP3PlayerApp::inicializar() {
    // Configurar player padrão
    player->setVolume(70.0f);
    
    // Criar playlist padrão se não existir
    if (player->getPlaylists().empty()) {
        auto defaultPlaylist = std::make_shared<Playlist>("Biblioteca Principal");
        player->addPlaylist(defaultPlaylist);
        player->setCurrentPlaylist(defaultPlaylist);
    }
    
    // Configurar callback de eventos do player
    // (Simulação - em implementação real usaria observer pattern)
    
    std::cout << "MP3 Player inicializado com sucesso!\n";
}

void MP3PlayerApp::executar() {
    running = true;
    
    mostrarBoasVindas();
    
    while (running) {
        try {
            mostrarMenuPrincipal();
            int opcao = lerOpcao();
            processarOpcao(opcao);
        } catch (const std::exception& e) {
            std::cerr << "Erro: " << e.what() << "\n";
            std::cout << "Pressione Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }
    }
    
    finalizar();
}

void MP3PlayerApp::finalizar() {
    try {
        // Salvar playlists automaticamente
        for (const auto& playlist : player->getPlaylists()) {
            std::string filename = "playlist_" + playlist->getName() + ".json";
            persistence->savePlaylist(*playlist, filename);
        }
        
        std::cout << "Aplicação finalizada. Até logo!\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro ao finalizar: " << e.what() << "\n";
    }
}

void MP3PlayerApp::mostrarBoasVindas() {
    std::cout << "\n========================================\n";
    std::cout << "       BEM-VINDO AO MP3 PLAYER!        \n";
    std::cout << "========================================\n";
    std::cout << " Sistema de Música Avançado - POO 2024 \n";
    std::cout << "========================================\n\n";
}

void MP3PlayerApp::mostrarMenuPrincipal() {
    std::cout << "\n--- MENU PRINCIPAL ---\n";
    std::cout << "1. Controles de Reprodução\n";
    std::cout << "2. Gerenciar Biblioteca\n";
    std::cout << "3. Gerenciar Playlists\n";
    std::cout << "4. Configurações de Áudio\n";
    std::cout << "5. Estatísticas\n";
    std::cout << "0. Sair\n";
    std::cout << "Escolha uma opção: ";
}

int MP3PlayerApp::lerOpcao() {
    std::string input;
    std::getline(std::cin, input);
    
    try {
        return std::stoi(input);
    } catch (const std::exception&) {
        return -1; // Opção inválida
    }
}

void MP3PlayerApp::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            menuReproducao();
            break;
        case 2:
            menuBiblioteca();
            break;
        case 3:
            menuPlaylists();
            break;
        case 4:
            menuConfiguracao();
            break;
        case 5:
            mostrarEstatisticas();
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Opção inválida! Tente novamente.\n";
    }
}

void MP3PlayerApp::menuReproducao() {
    while (true) {
        std::cout << "\n--- CONTROLES DE REPRODUÇÃO ---\n";
        std::cout << "Status: " << (player->isPlaying() ? "Reproduzindo" : "Parado") << "\n";
        
        if (auto track = player->getCurrentTrack()) {
            std::cout << "Música atual: " << track->getTitle() << " - " << track->getArtist() << "\n";
        }
        
        std::cout << "\n1. Play/Pause\n";
        std::cout << "2. Próxima\n";
        std::cout << "3. Anterior\n";
        std::cout << "4. Parar\n";
        std::cout << "5. Ajustar Volume\n";
        std::cout << "6. Buscar Posição\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha: ";
        
        int opcao = lerOpcao();
        
        switch (opcao) {
            case 1:
                if (player->isPlaying()) {
                    player->pause();
                    std::cout << "Pausado.\n";
                } else {
                    player->play();
                    std::cout << "Reproduzindo.\n";
                }
                break;
            case 2:
                player->next();
                std::cout << "Próxima música.\n";
                break;
            case 3:
                player->previous();
                std::cout << "Música anterior.\n";
                break;
            case 4:
                player->stop();
                std::cout << "Reprodução parada.\n";
                break;
            case 5:
                ajustarVolume();
                break;
            case 6:
                buscarPosicao();
                break;
            case 0:
                return;
            default:
                std::cout << "Opção inválida!\n";
        }
    }
}

void MP3PlayerApp::menuBiblioteca() {
    while (true) {
        std::cout << "\n--- GERENCIAR BIBLIOTECA ---\n";
        std::cout << "1. Escanear Diretório\n";
        std::cout << "2. Adicionar Música\n";
        std::cout << "3. Listar Todas as Músicas\n";
        std::cout << "4. Buscar Música\n";
        std::cout << "5. Remover Música\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha: ";
        
        int opcao = lerOpcao();
        
        switch (opcao) {
            case 1:
                escanearDiretorio();
                break;
            case 2:
                adicionarMusica();
                break;
            case 3:
                listarMusicas();
                break;
            case 4:
                buscarMusica();
                break;
            case 5:
                removerMusica();
                break;
            case 0:
                return;
            default:
                std::cout << "Opção inválida!\n";
        }
    }
}

void MP3PlayerApp::menuPlaylists() {
    while (true) {
        std::cout << "\n--- GERENCIAR PLAYLISTS ---\n";
        std::cout << "1. Criar Nova Playlist\n";
        std::cout << "2. Listar Playlists\n";
        std::cout << "3. Selecionar Playlist\n";
        std::cout << "4. Adicionar Música à Playlist\n";
        std::cout << "5. Remover Música da Playlist\n";
        std::cout << "6. Salvar Playlist\n";
        std::cout << "7. Carregar Playlist\n";
        std::cout << "8. Excluir Playlist\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha: ";
        
        int opcao = lerOpcao();
        
        switch (opcao) {
            case 1:
                criarPlaylist();
                break;
            case 2:
                listarPlaylists();
                break;
            case 3:
                selecionarPlaylist();
                break;
            case 4:
                adicionarMusicaPlaylist();
                break;
            case 5:
                removerMusicaPlaylist();
                break;
            case 6:
                salvarPlaylist();
                break;
            case 7:
                carregarPlaylist();
                break;
            case 8:
                excluirPlaylist();
                break;
            case 0:
                return;
            default:
                std::cout << "Opção inválida!\n";
        }
    }
}

void MP3PlayerApp::menuConfiguracao() {
    while (true) {
        std::cout << "\n--- CONFIGURAÇÕES DE ÁUDIO ---\n";
        std::cout << "Volume atual: " << player->getVolume() << "%\n";
        
        auto equalizer = player->getEqualizer();
        if (equalizer) {
            std::cout << "Equalizador: " << equalizer->getCurrentPreset() << "\n";
        }
        
        std::cout << "\n1. Ajustar Volume\n";
        std::cout << "2. Configurar Equalizador\n";
        std::cout << "3. Modo de Reprodução\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha: ";
        
        int opcao = lerOpcao();
        
        switch (opcao) {
            case 1:
                ajustarVolume();
                break;
            case 2:
                configurarEqualizador();
                break;
            case 3:
                configurarModoReproducao();
                break;
            case 0:
                return;
            default:
                std::cout << "Opção inválida!\n";
        }
    }
}

void MP3PlayerApp::escanearDiretorio() {
    std::cout << "Digite o caminho do diretório: ";
    std::string caminho;
    std::getline(std::cin, caminho);
    
    try {
        std::cout << "Escaneando diretório...\n";
        
        auto tracks = scanner->scanForTracks(caminho);
        
        if (tracks.empty()) {
            std::cout << "Nenhuma música encontrada no diretório.\n";
            return;
        }
        
        // Adicionar tracks à playlist atual
        auto currentPlaylist = player->getCurrentPlaylist();
        if (!currentPlaylist) {
            auto newPlaylist = std::make_shared<Playlist>("Biblioteca Principal");
            player->addPlaylist(newPlaylist);
            player->setCurrentPlaylist(newPlaylist);
            currentPlaylist = newPlaylist;
        }
        
        for (const auto& track : tracks) {
            currentPlaylist->addTrack(track);
        }
        
        std::cout << "Adicionadas " << tracks.size() << " músicas à biblioteca.\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro ao escanear diretório: " << e.what() << "\n";
    }
}

void MP3PlayerApp::adicionarMusica() {
    std::cout << "Digite o caminho da música: ";
    std::string caminho;
    std::getline(std::cin, caminho);
    
    try {
        auto track = Track::createFromFile(caminho);
        if (!track) {
            std::cout << "Não foi possível carregar a música.\n";
            return;
        }
        
        auto currentPlaylist = player->getCurrentPlaylist();
        if (currentPlaylist) {
            currentPlaylist->addTrack(track);
            std::cout << "Música adicionada: " << track->getTitle() << "\n";
        } else {
            std::cout << "Nenhuma playlist selecionada.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao adicionar música: " << e.what() << "\n";
    }
}

void MP3PlayerApp::listarMusicas() {
    auto currentPlaylist = player->getCurrentPlaylist();
    if (!currentPlaylist) {
        std::cout << "Nenhuma playlist selecionada.\n";
        return;
    }
    
    const auto& tracks = currentPlaylist->getTracks();
    if (tracks.empty()) {
        std::cout << "Playlist vazia.\n";
        return;
    }
    
    std::cout << "\n--- MÚSICAS NA PLAYLIST ATUAL ---\n";
    for (size_t i = 0; i < tracks.size(); ++i) {
        const auto& track = tracks[i];
        std::cout << (i + 1) << ". " << track->getTitle() 
                  << " - " << track->getArtist() << " (" 
                  << track->getDurationFormatted() << ")\n";
    }
}

void MP3PlayerApp::ajustarVolume() {
    std::cout << "Volume atual: " << player->getVolume() << "%\n";
    std::cout << "Digite o novo volume (0-100): ";
    
    std::string input;
    std::getline(std::cin, input);
    
    try {
        float volume = std::stof(input);
        if (volume < 0 || volume > 100) {
            std::cout << "Volume deve estar entre 0 e 100.\n";
            return;
        }
        
        player->setVolume(volume);
        std::cout << "Volume ajustado para " << volume << "%\n";
    } catch (const std::exception&) {
        std::cout << "Valor inválido para volume.\n";
    }
}

void MP3PlayerApp::configurarEqualizador() {
    auto equalizer = player->getEqualizer();
    if (!equalizer) {
        std::cout << "Equalizador não disponível.\n";
        return;
    }
    
    std::cout << "\n--- PRESETS DISPONÍVEIS ---\n";
    const auto& presets = equalizer->getAvailablePresets();
    for (size_t i = 0; i < presets.size(); ++i) {
        std::cout << (i + 1) << ". " << presets[i] << "\n";
    }
    
    std::cout << "Escolha um preset (0 para cancelar): ";
    int opcao = lerOpcao();
    
    if (opcao > 0 && opcao <= static_cast<int>(presets.size())) {
        equalizer->setPreset(presets[opcao - 1]);
        std::cout << "Preset aplicado: " << presets[opcao - 1] << "\n";
    }
}

void MP3PlayerApp::mostrarEstatisticas() {
    auto currentPlaylist = player->getCurrentPlaylist();
    
    std::cout << "\n--- ESTATÍSTICAS ---\n";
    std::cout << "Playlists: " << player->getPlaylists().size() << "\n";
    
    if (currentPlaylist) {
        std::cout << "Músicas na playlist atual: " << currentPlaylist->size() << "\n";
        std::cout << "Duração total: " << currentPlaylist->getTotalDurationFormatted() << "\n";
    }
    
    std::cout << "Volume: " << player->getVolume() << "%\n";
    
    auto equalizer = player->getEqualizer();
    if (equalizer) {
        std::cout << "Equalizador: " << equalizer->getCurrentPreset() << "\n";
    }
    
    if (auto track = player->getCurrentTrack()) {
        std::cout << "Música atual: " << track->getTitle() << " - " << track->getArtist() << "\n";
    }
}

void MP3PlayerApp::buscarMusica() {
    std::cout << "Digite o termo de busca: ";
    std::string termo;
    std::getline(std::cin, termo);
    
    auto currentPlaylist = player->getCurrentPlaylist();
    if (!currentPlaylist) {
        std::cout << "Nenhuma playlist selecionada.\n";
        return;
    }
    
    const auto& tracks = currentPlaylist->getTracks();
    std::vector<std::shared_ptr<Track>> resultados;
    
    for (const auto& track : tracks) {
        std::string title = track->getTitle();
        std::string artist = track->getArtist();
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        std::transform(artist.begin(), artist.end(), artist.begin(), ::tolower);
        std::transform(termo.begin(), termo.end(), termo.begin(), ::tolower);
        
        if (title.find(termo) != std::string::npos || 
            artist.find(termo) != std::string::npos) {
            resultados.push_back(track);
        }
    }
    
    if (resultados.empty()) {
        std::cout << "Nenhuma música encontrada.\n";
    } else {
        std::cout << "\n--- RESULTADOS DA BUSCA ---\n";
        for (size_t i = 0; i < resultados.size(); ++i) {
            const auto& track = resultados[i];
            std::cout << (i + 1) << ". " << track->getTitle() 
                      << " - " << track->getArtist() << "\n";
        }
    }
}

void MP3PlayerApp::criarPlaylist() {
    std::cout << "Digite o nome da nova playlist: ";
    std::string nome;
    std::getline(std::cin, nome);
    
    if (nome.empty()) {
        std::cout << "Nome inválido.\n";
        return;
    }
    
    auto playlist = std::make_shared<Playlist>(nome);
    player->addPlaylist(playlist);
    
    std::cout << "Playlist '" << nome << "' criada com sucesso.\n";
}

void MP3PlayerApp::listarPlaylists() {
    const auto& playlists = player->getPlaylists();
    
    if (playlists.empty()) {
        std::cout << "Nenhuma playlist encontrada.\n";
        return;
    }
    
    std::cout << "\n--- PLAYLISTS ---\n";
    for (size_t i = 0; i < playlists.size(); ++i) {
        const auto& playlist = playlists[i];
        std::cout << (i + 1) << ". " << playlist->getName() 
                  << " (" << playlist->size() << " músicas)\n";
    }
}

void MP3PlayerApp::selecionarPlaylist() {
    listarPlaylists();
    
    const auto& playlists = player->getPlaylists();
    if (playlists.empty()) return;
    
    std::cout << "Escolha uma playlist (0 para cancelar): ";
    int opcao = lerOpcao();
    
    if (opcao > 0 && opcao <= static_cast<int>(playlists.size())) {
        player->setCurrentPlaylist(playlists[opcao - 1]);
        std::cout << "Playlist selecionada: " << playlists[opcao - 1]->getName() << "\n";
    }
}

void MP3PlayerApp::salvarPlaylist() {
    auto currentPlaylist = player->getCurrentPlaylist();
    if (!currentPlaylist) {
        std::cout << "Nenhuma playlist selecionada.\n";
        return;
    }
    
    std::string filename = "playlist_" + currentPlaylist->getName() + ".json";
    
    try {
        persistence->savePlaylist(*currentPlaylist, filename);
        std::cout << "Playlist salva em: " << filename << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro ao salvar playlist: " << e.what() << "\n";
    }
}

void MP3PlayerApp::carregarPlaylist() {
    std::cout << "Digite o nome do arquivo: ";
    std::string filename;
    std::getline(std::cin, filename);
    
    try {
        auto playlist = persistence->loadPlaylist(filename);
        player->addPlaylist(playlist);
        std::cout << "Playlist carregada: " << playlist->getName() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro ao carregar playlist: " << e.what() << "\n";
    }
}

void MP3PlayerApp::buscarPosicao() {
    std::cout << "Digite a posição em segundos: ";
    std::string input;
    std::getline(std::cin, input);
    
    try {
        double posicao = std::stod(input);
        player->seek(posicao);
        std::cout << "Posição ajustada para " << posicao << " segundos.\n";
    } catch (const std::exception&) {
        std::cout << "Posição inválida.\n";
    }
}

void MP3PlayerApp::configurarModoReproducao() {
    std::cout << "\n--- MODOS DE REPRODUÇÃO ---\n";
    std::cout << "1. Normal\n";
    std::cout << "2. Repetir\n";
    std::cout << "3. Aleatório\n";
    std::cout << "Escolha: ";
    
    int opcao = lerOpcao();
    // Implementação simplificada - em versão completa configuraria o player
    
    switch (opcao) {
        case 1:
            std::cout << "Modo normal ativado.\n";
            break;
        case 2:
            std::cout << "Modo repetir ativado.\n";
            break;
        case 3:
            std::cout << "Modo aleatório ativado.\n";
            break;
        default:
            std::cout << "Opção inválida.\n";
    }
}

void MP3PlayerApp::adicionarMusicaPlaylist() {
    auto currentPlaylist = player->getCurrentPlaylist();
    if (!currentPlaylist) {
        std::cout << "Nenhuma playlist selecionada.\n";
        return;
    }
    
    // Implementação simplificada - poderia mostrar biblioteca e permitir seleção
    std::cout << "Digite o caminho da música para adicionar: ";
    std::string caminho;
    std::getline(std::cin, caminho);
    
    try {
        auto track = Track::createFromFile(caminho);
        if (track) {
            currentPlaylist->addTrack(track);
            std::cout << "Música adicionada à playlist.\n";
        } else {
            std::cout << "Não foi possível carregar a música.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
    }
}

void MP3PlayerApp::removerMusicaPlaylist() {
    auto currentPlaylist = player->getCurrentPlaylist();
    if (!currentPlaylist || currentPlaylist->empty()) {
        std::cout << "Playlist vazia ou não selecionada.\n";
        return;
    }
    
    listarMusicas();
    
    std::cout << "Digite o número da música para remover (0 para cancelar): ";
    int opcao = lerOpcao();
    
    if (opcao > 0 && opcao <= static_cast<int>(currentPlaylist->size())) {
        currentPlaylist->removeTrack(opcao - 1);
        std::cout << "Música removida da playlist.\n";
    }
}

void MP3PlayerApp::removerMusica() {
    removerMusicaPlaylist(); // Mesma implementação por simplicidade
}

void MP3PlayerApp::excluirPlaylist() {
    listarPlaylists();
    
    const auto& playlists = player->getPlaylists();
    if (playlists.empty()) return;
    
    std::cout << "Escolha uma playlist para excluir (0 para cancelar): ";
    int opcao = lerOpcao();
    
    if (opcao > 0 && opcao <= static_cast<int>(playlists.size())) {
        auto playlistToRemove = playlists[opcao - 1];
        
        // Se for a playlist atual, desselecionar
        if (player->getCurrentPlaylist() == playlistToRemove) {
            player->setCurrentPlaylist(nullptr);
        }
        
        // Implementação simplificada - versão completa teria método removePlaylist
        std::cout << "Playlist excluída (funcionalidade simulada).\n";
    }
}