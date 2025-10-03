#ifndef MP3PLAYERAPP_H
#define MP3PLAYERAPP_H

#include "MP3Player.h"
#include "Playlist.h"
#include "PlaylistPersistence.h"
#include "DirectoryScanner.h"
#include <memory>
#include <vector>
#include <string>
#include <functional>

/**
 * @brief Controlador principal da aplicação
 * 
 * Esta classe demonstra:
 * - Composição: Agrega todos os componentes principais
 * - Gerenciamento de recursos: Gerencia ciclo de vida dos componentes
 * - Design patterns: Padrão Facade para interface simplificada
 * - Classes e Objetos: Coordenação em nível de aplicação
 */
class MP3PlayerApp {
private:
    std::unique_ptr<MP3Player> player;
    std::unique_ptr<Playlist> currentPlaylist;
    std::unique_ptr<JsonPlaylistPersistence> persistence;
    std::unique_ptr<MediaScanner> scanner;
    
    std::vector<std::unique_ptr<Playlist>> loadedPlaylists;
    std::string applicationPath;
    std::string playlistsDirectory;

    // Callbacks para integração com UI
    std::function<void(std::shared_ptr<Track>)> trackChangedCallback;
    std::function<void(const std::string&)> errorCallback;
    std::function<void(double)> positionCallback;

    void initializeComponents();
    void setupCallbacks();

public:
    // Construtor e destrutor
    MP3PlayerApp();
    explicit MP3PlayerApp(const std::string& appPath);
    ~MP3PlayerApp();

    // Inicialização
    bool initialize();
    void shutdown();

    // Controle do player
    bool playTrack(std::shared_ptr<Track> track);
    bool playCurrentTrack();
    bool pausePlayback();
    bool stopPlayback();
    bool seekTo(double position);
    void setVolume(double volume);
    double getVolume() const;

    // Gerenciamento de playlist
    bool loadPlaylist(const std::string& name);
    bool saveCurrentPlaylist(const std::string& name);
    bool createNewPlaylist(const std::string& name);
    std::vector<std::string> getAvailablePlaylists() const;
    Playlist* getCurrentPlaylist() const { return currentPlaylist.get(); }

    // Gerenciamento de faixas
    bool addTrackToCurrentPlaylist(const std::string& filePath);
    bool addDirectoryToCurrentPlaylist(const std::string& directoryPath);
    std::vector<std::shared_ptr<Track>> scanDirectory(const std::string& path);

    // Navegação
    bool nextTrack();
    bool previousTrack();
    bool jumpToTrack(size_t index);

    // Controle do equalizador
    Equalizer* getEqualizer() const;
    void setEqualizerPreset(const std::string& preset);

    // Gerenciamento de callbacks
    void setTrackChangedCallback(std::function<void(std::shared_ptr<Track>)> callback);
    void setErrorCallback(std::function<void(const std::string&)> callback);
    void setPositionCallback(std::function<void(double)> callback);

    // Estado da aplicação
    bool isInitialized() const;
    bool isPlaying() const;
    std::shared_ptr<Track> getCurrentTrack() const;
    double getCurrentPosition() const;

    // Configuração
    void setPlaylistsDirectory(const std::string& directory);
    const std::string& getPlaylistsDirectory() const { return playlistsDirectory; }

    // Métodos de menu (implementação CLI)
    void menuReproducao();
    void menuBiblioteca();
    void menuPlaylists();
    void menuConfiguracao();
    void escanearDiretorio();
    void adicionarMusica();
    void listarMusicas();
    void ajustarVolume();
    void configurarEqualizador();
    void mostrarEstatisticas();
    void buscarMusica();
    void criarPlaylist();
    void listarPlaylists();
    void selecionarPlaylist();
    void salvarPlaylist();
    void carregarPlaylist();
    void buscarPosicao();
    void configurarModoReproducao();
    void adicionarMusicaPlaylist();
    void removerMusicaPlaylist();
    void removerMusica();
    void excluirPlaylist();

    // Utilitários
    void mostrarBoasVindas();
    void mostrarMenuPrincipal();
    int lerOpcao();
    void processarOpcao(int opcao);

    // Getter para player (para CLI)
    MP3Player* getPlayer() const { return player.get(); }

private:
    void onTrackChanged(std::shared_ptr<Track> track);
    void onError(const std::string& message);
    void onPositionChanged(double position);
};

#endif // MP3PLAYERAPP_H