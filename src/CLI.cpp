#include "CLI.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

CLI::CLI() : app(std::make_unique<MP3PlayerApp>()) {}

CLI::~CLI() = default;

void CLI::run() {
    try {
        showWelcome();
        app->inicializar();
        
        bool running = true;
        while (running) {
            try {
                showPrompt();
                std::string input = readInput();
                
                if (input.empty()) continue;
                
                auto command = parseCommand(input);
                if (command.empty()) continue;
                
                if (command[0] == "quit" || command[0] == "exit" || command[0] == "q") {
                    running = false;
                    continue;
                }
                
                executeCommand(command);
                
            } catch (const std::exception& e) {
                showError("Erro na execução do comando: " + std::string(e.what()));
            }
        }
        
        app->finalizar();
        showGoodbye();
        
    } catch (const std::exception& e) {
        showError("Erro crítico: " + std::string(e.what()));
    }
}

void CLI::showWelcome() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                      MP3 PLAYER CLI                         ║\n";
    std::cout << "║                Sistema de Música Avançado                   ║\n";
    std::cout << "║                     POO 2024 - Etapa 2                      ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════════╝\n";
    std::cout << "\nDigite 'help' para ver os comandos disponíveis.\n";
    std::cout << "Digite 'quit' para sair.\n\n";
}

void CLI::showGoodbye() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                     Obrigado por usar o                     ║\n";
    std::cout << "║                      MP3 PLAYER CLI!                        ║\n";
    std::cout << "║                      Até a próxima!                         ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════════╝\n\n";
}

void CLI::showPrompt() {
    std::cout << "\n> ";
}

std::string CLI::readInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::vector<std::string> CLI::parseCommand(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void CLI::executeCommand(const std::vector<std::string>& command) {
    if (command.empty()) return;
    
    const std::string& cmd = command[0];
    
    // Comandos de controle de reprodução
    if (cmd == "play") {
        cmdPlay(command);
    }
    else if (cmd == "pause") {
        cmdPause();
    }
    else if (cmd == "stop") {
        cmdStop();
    }
    else if (cmd == "next") {
        cmdNext();
    }
    else if (cmd == "prev" || cmd == "previous") {
        cmdPrevious();
    }
    else if (cmd == "volume" || cmd == "vol") {
        cmdVolume(command);
    }
    else if (cmd == "seek") {
        cmdSeek(command);
    }
    
    // Comandos de playlist
    else if (cmd == "playlist" || cmd == "pl") {
        cmdPlaylist(command);
    }
    else if (cmd == "add") {
        cmdAdd(command);
    }
    else if (cmd == "remove" || cmd == "rm") {
        cmdRemove(command);
    }
    else if (cmd == "list" || cmd == "ls") {
        cmdList(command);
    }
    
    // Comandos de biblioteca
    else if (cmd == "scan") {
        cmdScan(command);
    }
    else if (cmd == "search" || cmd == "find") {
        cmdSearch(command);
    }
    
    // Comandos de configuração
    else if (cmd == "equalizer" || cmd == "eq") {
        cmdEqualizer(command);
    }
    
    // Comandos de informação
    else if (cmd == "status" || cmd == "info") {
        cmdStatus();
    }
    else if (cmd == "current" || cmd == "now") {
        cmdCurrent();
    }
    else if (cmd == "help" || cmd == "h") {
        cmdHelp(command);
    }
    
    // Comandos de arquivo
    else if (cmd == "save") {
        cmdSave(command);
    }
    else if (cmd == "load") {
        cmdLoad(command);
    }
    
    else {
        showError("Comando desconhecido: " + cmd + ". Digite 'help' para ver os comandos disponíveis.");
    }
}

void CLI::cmdPlay(const std::vector<std::string>& args) {
    auto player = app->getPlayer();
    
    if (args.size() > 1) {
        // Tentar tocar música específica por índice
        try {
            int index = std::stoi(args[1]) - 1; // Converter para índice base 0
            auto playlist = player->getCurrentPlaylist();
            if (playlist && index >= 0 && index < static_cast<int>(playlist->size())) {
                const auto& tracks = playlist->getTracks();
                player->loadTrack(tracks[index]);
                player->play();
                showSuccess("Reproduzindo: " + tracks[index]->getTitle());
            } else {
                showError("Índice de música inválido.");
            }
        } catch (const std::exception&) {
            showError("Índice inválido. Use: play [número]");
        }
    } else {
        // Play/resume música atual
        player->play();
        if (auto track = player->getCurrentTrack()) {
            showSuccess("Reproduzindo: " + track->getTitle());
        } else {
            showInfo("Reprodução iniciada (nenhuma música selecionada).");
        }
    }
}

void CLI::cmdPause() {
    auto player = app->getPlayer();
    player->pause();
    showInfo("Reprodução pausada.");
}

void CLI::cmdStop() {
    auto player = app->getPlayer();
    player->stop();
    showInfo("Reprodução parada.");
}

void CLI::cmdNext() {
    auto player = app->getPlayer();
    player->next();
    if (auto track = player->getCurrentTrack()) {
        showInfo("Próxima música: " + track->getTitle());
    } else {
        showInfo("Próxima música (lista vazia).");
    }
}

void CLI::cmdPrevious() {
    auto player = app->getPlayer();
    player->previous();
    if (auto track = player->getCurrentTrack()) {
        showInfo("Música anterior: " + track->getTitle());
    } else {
        showInfo("Música anterior (lista vazia).");
    }
}

void CLI::cmdVolume(const std::vector<std::string>& args) {
    auto player = app->getPlayer();
    
    if (args.size() > 1) {
        try {
            float volume = std::stof(args[1]);
            if (volume < 0 || volume > 100) {
                showError("Volume deve estar entre 0 e 100.");
                return;
            }
            player->setVolume(volume);
            showSuccess("Volume ajustado para " + std::to_string(static_cast<int>(volume)) + "%");
        } catch (const std::exception&) {
            showError("Volume inválido. Use: volume [0-100]");
        }
    } else {
        showInfo("Volume atual: " + std::to_string(static_cast<int>(player->getVolume())) + "%");
    }
}

void CLI::cmdSeek(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        showError("Use: seek [posição em segundos]");
        return;
    }
    
    try {
        double position = std::stod(args[1]);
        auto player = app->getPlayer();
        player->seek(position);
        showSuccess("Posição ajustada para " + std::to_string(static_cast<int>(position)) + " segundos");
    } catch (const std::exception&) {
        showError("Posição inválida. Use: seek [segundos]");
    }
}

void CLI::cmdPlaylist(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        // Listar playlists disponíveis
        auto player = app->getPlayer();
        const auto& playlists = player->getPlaylists();
        
        if (playlists.empty()) {
            showInfo("Nenhuma playlist encontrada.");
            return;
        }
        
        std::cout << "\n--- PLAYLISTS DISPONÍVEIS ---\n";
        for (size_t i = 0; i < playlists.size(); ++i) {
            const auto& playlist = playlists[i];
            std::cout << std::setw(3) << (i + 1) << ". " << playlist->getName() 
                      << " (" << playlist->size() << " músicas)\n";
        }
        return;
    }
    
    const std::string& action = args[1];
    
    if (action == "create" || action == "new") {
        if (args.size() < 3) {
            showError("Use: playlist create [nome]");
            return;
        }
        
        std::string name = args[2];
        for (size_t i = 3; i < args.size(); ++i) {
            name += " " + args[i];
        }
        
        auto player = app->getPlayer();
        auto playlist = std::make_shared<Playlist>(name);
        player->addPlaylist(playlist);
        showSuccess("Playlist '" + name + "' criada.");
    }
    else if (action == "select" || action == "use") {
        if (args.size() < 3) {
            showError("Use: playlist select [número ou nome]");
            return;
        }
        
        auto player = app->getPlayer();
        const auto& playlists = player->getPlaylists();
        
        try {
            int index = std::stoi(args[2]) - 1;
            if (index >= 0 && index < static_cast<int>(playlists.size())) {
                player->setCurrentPlaylist(playlists[index]);
                showSuccess("Playlist selecionada: " + playlists[index]->getName());
            } else {
                showError("Índice de playlist inválido.");
            }
        } catch (const std::exception&) {
            // Tentar buscar por nome
            std::string name = args[2];
            for (size_t i = 3; i < args.size(); ++i) {
                name += " " + args[i];
            }
            
            for (const auto& playlist : playlists) {
                if (playlist->getName() == name) {
                    player->setCurrentPlaylist(playlist);
                    showSuccess("Playlist selecionada: " + name);
                    return;
                }
            }
            showError("Playlist não encontrada: " + name);
        }
    }
    else {
        showError("Ação inválida. Use: playlist [create|select] [parâmetros]");
    }
}

void CLI::cmdAdd(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        showError("Use: add [caminho do arquivo]");
        return;
    }
    
    std::string filePath = args[1];
    for (size_t i = 2; i < args.size(); ++i) {
        filePath += " " + args[i];
    }
    
    try {
        auto track = Track::createFromFile(filePath);
        if (!track) {
            showError("Não foi possível carregar a música.");
            return;
        }
        
        auto player = app->getPlayer();
        auto currentPlaylist = player->getCurrentPlaylist();
        
        if (!currentPlaylist) {
            // Criar playlist padrão
            auto defaultPlaylist = std::make_shared<Playlist>("Biblioteca Principal");
            player->addPlaylist(defaultPlaylist);
            player->setCurrentPlaylist(defaultPlaylist);
            currentPlaylist = defaultPlaylist;
        }
        
        currentPlaylist->addTrack(track);
        showSuccess("Música adicionada: " + track->getTitle());
    } catch (const std::exception& e) {
        showError("Erro ao adicionar música: " + std::string(e.what()));
    }
}

void CLI::cmdRemove(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        showError("Use: remove [índice da música]");
        return;
    }
    
    try {
        int index = std::stoi(args[1]) - 1;
        
        auto player = app->getPlayer();
        auto currentPlaylist = player->getCurrentPlaylist();
        
        if (!currentPlaylist) {
            showError("Nenhuma playlist selecionada.");
            return;
        }
        
        if (index < 0 || index >= static_cast<int>(currentPlaylist->size())) {
            showError("Índice inválido.");
            return;
        }
        
        const auto& tracks = currentPlaylist->getTracks();
        std::string title = tracks[index]->getTitle();
        
        currentPlaylist->removeTrack(index);
        showSuccess("Música removida: " + title);
    } catch (const std::exception&) {
        showError("Índice inválido. Use: remove [número]");
    }
}

void CLI::cmdList(const std::vector<std::string>& args) {
    auto player = app->getPlayer();
    auto currentPlaylist = player->getCurrentPlaylist();
    
    if (!currentPlaylist) {
        showError("Nenhuma playlist selecionada.");
        return;
    }
    
    const auto& tracks = currentPlaylist->getTracks();
    
    if (tracks.empty()) {
        showInfo("Playlist vazia.");
        return;
    }
    
    std::cout << "\n--- MÚSICAS NA PLAYLIST: " << currentPlaylist->getName() << " ---\n";
    for (size_t i = 0; i < tracks.size(); ++i) {
        const auto& track = tracks[i];
        std::cout << std::setw(3) << (i + 1) << ". " 
                  << std::setw(30) << std::left << track->getTitle()
                  << " - " << std::setw(20) << track->getArtist()
                  << " (" << track->getDurationFormatted() << ")\n";
    }
    
    std::cout << "\nTotal: " << tracks.size() << " músicas, " 
              << currentPlaylist->getTotalDurationFormatted() << "\n";
}

void CLI::cmdScan(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        showError("Use: scan [caminho do diretório]");
        return;
    }
    
    std::string directoryPath = args[1];
    for (size_t i = 2; i < args.size(); ++i) {
        directoryPath += " " + args[i];
    }
    
    try {
        showInfo("Escaneando diretório: " + directoryPath);
        
        auto scanner = createAudioScanner();
        auto tracks = scanner->scanForTracks(directoryPath);
        
        if (tracks.empty()) {
            showInfo("Nenhuma música encontrada.");
            return;
        }
        
        auto player = app->getPlayer();
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
        
        showSuccess("Adicionadas " + std::to_string(tracks.size()) + " músicas à biblioteca.");
    } catch (const std::exception& e) {
        showError("Erro ao escanear: " + std::string(e.what()));
    }
}

void CLI::cmdSearch(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        showError("Use: search [termo de busca]");
        return;
    }
    
    std::string searchTerm = args[1];
    for (size_t i = 2; i < args.size(); ++i) {
        searchTerm += " " + args[i];
    }
    
    auto player = app->getPlayer();
    auto currentPlaylist = player->getCurrentPlaylist();
    
    if (!currentPlaylist) {
        showError("Nenhuma playlist selecionada.");
        return;
    }
    
    const auto& tracks = currentPlaylist->getTracks();
    std::vector<std::pair<size_t, std::shared_ptr<Track>>> results;
    
    std::string lowerTerm = searchTerm;
    std::transform(lowerTerm.begin(), lowerTerm.end(), lowerTerm.begin(), ::tolower);
    
    for (size_t i = 0; i < tracks.size(); ++i) {
        const auto& track = tracks[i];
        
        std::string title = track->getTitle();
        std::string artist = track->getArtist();
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        std::transform(artist.begin(), artist.end(), artist.begin(), ::tolower);
        
        if (title.find(lowerTerm) != std::string::npos || 
            artist.find(lowerTerm) != std::string::npos) {
            results.push_back({i, track});
        }
    }
    
    if (results.empty()) {
        showInfo("Nenhuma música encontrada para: " + searchTerm);
        return;
    }
    
    std::cout << "\n--- RESULTADOS DA BUSCA: \"" << searchTerm << "\" ---\n";
    for (const auto& result : results) {
        const auto& track = result.second;
        std::cout << std::setw(3) << (result.first + 1) << ". "
                  << std::setw(30) << std::left << track->getTitle()
                  << " - " << track->getArtist() << "\n";
    }
    
    std::cout << "\nEncontradas " << results.size() << " música(s).\n";
}

void CLI::cmdEqualizer(const std::vector<std::string>& args) {
    auto player = app->getPlayer();
    auto equalizer = player->getEqualizer();
    
    if (!equalizer) {
        showError("Equalizador não disponível.");
        return;
    }
    
    if (args.size() < 2) {
        // Mostrar preset atual e disponíveis
        std::cout << "\nEqualizador atual: " << equalizer->getCurrentPreset() << "\n";
        std::cout << "\nPresets disponíveis:\n";
        const auto& presets = equalizer->getAvailablePresets();
        for (size_t i = 0; i < presets.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << presets[i] << "\n";
        }
        return;
    }
    
    const std::string& preset = args[1];
    
    try {
        equalizer->setPreset(preset);
        showSuccess("Preset aplicado: " + preset);
    } catch (const std::exception& e) {
        showError("Preset inválido: " + preset);
    }
}

void CLI::cmdStatus() {
    auto player = app->getPlayer();
    
    std::cout << "\n--- STATUS DO PLAYER ---\n";
    std::cout << "Estado: " << (player->isPlaying() ? "Reproduzindo" : "Parado") << "\n";
    std::cout << "Volume: " << static_cast<int>(player->getVolume()) << "%\n";
    
    if (auto equalizer = player->getEqualizer()) {
        std::cout << "Equalizador: " << equalizer->getCurrentPreset() << "\n";
    }
    
    if (auto playlist = player->getCurrentPlaylist()) {
        std::cout << "Playlist atual: " << playlist->getName() 
                  << " (" << playlist->size() << " músicas)\n";
    } else {
        std::cout << "Playlist atual: Nenhuma\n";
    }
    
    std::cout << "Total de playlists: " << player->getPlaylists().size() << "\n";
}

void CLI::cmdCurrent() {
    auto player = app->getPlayer();
    
    if (auto track = player->getCurrentTrack()) {
        std::cout << "\n--- MÚSICA ATUAL ---\n";
        std::cout << "Título: " << track->getTitle() << "\n";
        std::cout << "Artista: " << track->getArtist() << "\n";
        std::cout << "Álbum: " << track->getAlbum() << "\n";
        std::cout << "Duração: " << track->getDurationFormatted() << "\n";
        std::cout << "Arquivo: " << track->getFilePath() << "\n";
    } else {
        showInfo("Nenhuma música sendo reproduzida.");
    }
}

void CLI::cmdSave(const std::vector<std::string>& args) {
    auto player = app->getPlayer();
    auto currentPlaylist = player->getCurrentPlaylist();
    
    if (!currentPlaylist) {
        showError("Nenhuma playlist selecionada.");
        return;
    }
    
    std::string filename;
    if (args.size() > 1) {
        filename = args[1];
    } else {
        filename = "playlist_" + currentPlaylist->getName() + ".json";
    }
    
    try {
        auto persistence = std::make_unique<JsonPlaylistPersistence>();
        persistence->savePlaylist(*currentPlaylist, filename);
        showSuccess("Playlist salva em: " + filename);
    } catch (const std::exception& e) {
        showError("Erro ao salvar: " + std::string(e.what()));
    }
}

void CLI::cmdLoad(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        showError("Use: load [nome do arquivo]");
        return;
    }
    
    const std::string& filename = args[1];
    
    try {
        auto persistence = std::make_unique<JsonPlaylistPersistence>();
        auto playlistOpt = persistence->loadPlaylist(filename);
        
        if (playlistOpt) {
            auto player = app->getPlayer();
            auto playlist = std::make_shared<Playlist>(*playlistOpt);
            player->addPlaylist(playlist);
            
            showSuccess("Playlist carregada: " + playlist->getName());
        } else {
            showError("Não foi possível carregar a playlist.");
        }
    } catch (const std::exception& e) {
        showError("Erro ao carregar: " + std::string(e.what()));
    }
}

void CLI::cmdHelp(const std::vector<std::string>& args) {
    if (args.size() > 1) {
        showDetailedHelp(args[1]);
        return;
    }
    
    std::cout << "\n=== COMANDOS DISPONÍVEIS ===\n\n";
    
    std::cout << "CONTROLE DE REPRODUÇÃO:\n";
    std::cout << "  play [número]     - Reproduzir música (por índice opcional)\n";
    std::cout << "  pause             - Pausar reprodução\n";
    std::cout << "  stop              - Parar reprodução\n";
    std::cout << "  next              - Próxima música\n";
    std::cout << "  prev              - Música anterior\n";
    std::cout << "  volume [0-100]    - Ajustar volume\n";
    std::cout << "  seek [segundos]   - Buscar posição\n\n";
    
    std::cout << "GERENCIAMENTO DE PLAYLISTS:\n";
    std::cout << "  playlist          - Listar playlists\n";
    std::cout << "  playlist create   - Criar nova playlist\n";
    std::cout << "  playlist select   - Selecionar playlist\n";
    std::cout << "  add [arquivo]     - Adicionar música\n";
    std::cout << "  remove [número]   - Remover música\n";
    std::cout << "  list              - Listar músicas da playlist\n\n";
    
    std::cout << "BIBLIOTECA:\n";
    std::cout << "  scan [diretório]  - Escanear diretório por músicas\n";
    std::cout << "  search [termo]    - Buscar músicas\n\n";
    
    std::cout << "CONFIGURAÇÃO:\n";
    std::cout << "  equalizer [preset] - Configurar equalizador\n\n";
    
    std::cout << "INFORMAÇÕES:\n";
    std::cout << "  status            - Status do player\n";
    std::cout << "  current           - Música atual\n\n";
    
    std::cout << "ARQUIVOS:\n";
    std::cout << "  save [arquivo]    - Salvar playlist\n";
    std::cout << "  load [arquivo]    - Carregar playlist\n\n";
    
    std::cout << "SISTEMA:\n";
    std::cout << "  help [comando]    - Ajuda detalhada\n";
    std::cout << "  quit              - Sair do programa\n\n";
    
    std::cout << "Digite 'help [comando]' para ajuda detalhada sobre um comando específico.\n";
}

void CLI::showDetailedHelp(const std::string& command) {
    std::cout << "\n=== AJUDA DETALHADA: " << command << " ===\n\n";
    
    if (command == "play") {
        std::cout << "COMANDO: play [número]\n";
        std::cout << "DESCRIÇÃO: Inicia ou retoma a reprodução\n";
        std::cout << "EXEMPLOS:\n";
        std::cout << "  play      - Retomar reprodução atual\n";
        std::cout << "  play 3    - Reproduzir música número 3 da playlist\n";
    }
    else if (command == "playlist") {
        std::cout << "COMANDO: playlist [create|select] [parâmetros]\n";
        std::cout << "DESCRIÇÃO: Gerencia playlists\n";
        std::cout << "EXEMPLOS:\n";
        std::cout << "  playlist              - Listar todas as playlists\n";
        std::cout << "  playlist create Rock  - Criar playlist chamada 'Rock'\n";
        std::cout << "  playlist select 2     - Selecionar playlist número 2\n";
    }
    else if (command == "scan") {
        std::cout << "COMANDO: scan [diretório]\n";
        std::cout << "DESCRIÇÃO: Escaneia um diretório em busca de arquivos de música\n";
        std::cout << "FORMATOS: MP3, WAV, OGG\n";
        std::cout << "EXEMPLO:\n";
        std::cout << "  scan C:\\Music  - Escanear pasta C:\\Music\n";
    }
    else {
        std::cout << "Comando não encontrado ou sem ajuda detalhada disponível.\n";
        std::cout << "Digite 'help' para ver todos os comandos.\n";
    }
}

void CLI::showSuccess(const std::string& message) {
    std::cout << "✓ " << message << "\n";
}

void CLI::showError(const std::string& message) {
    std::cout << "✗ ERRO: " << message << "\n";
}

void CLI::showInfo(const std::string& message) {
    std::cout << "ℹ " << message << "\n";
}