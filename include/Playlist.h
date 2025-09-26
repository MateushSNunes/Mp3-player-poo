#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Track.h"
#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <functional>
#include <random>

/**
 * @brief Gerencia uma coleção de faixas
 * 
 * Esta classe demonstra:
 * - Composição: Contém objetos Track (relacionamento tem-um)
 * - Templates e STL: Usa std::vector, std::optional
 * - Sobrecarga de operadores: Operador subscrito
 * - Classes e Objetos: Modelo de domínio para gerenciamento de playlist
 */
class Playlist {
private:
    std::string name;
    std::vector<std::shared_ptr<Track>> tracks;
    size_t currentIndex;
    bool shuffleMode;
    bool repeatMode;
    std::mt19937 randomGenerator;
    std::vector<size_t> shuffleOrder;

    void generateShuffleOrder();

public:
    // Construtores
    Playlist();
    explicit Playlist(const std::string& playlistName);
    Playlist(const std::string& playlistName, 
             const std::vector<std::shared_ptr<Track>>& initialTracks);

    // Regra dos cinco
    Playlist(const Playlist& other);
    Playlist(Playlist&& other) noexcept;
    Playlist& operator=(const Playlist& other);
    Playlist& operator=(Playlist&& other) noexcept;
    ~Playlist() = default;

    // Operações básicas (CRUD)
    void addTrack(std::shared_ptr<Track> track);
    void addTracks(const std::vector<std::shared_ptr<Track>>& newTracks);
    bool removeTrack(size_t index);
    bool removeTrack(std::shared_ptr<Track> track);
    void clear();

    // Operações de acesso
    std::shared_ptr<Track> getTrack(size_t index) const;
    std::shared_ptr<Track> getCurrentTrack() const;
    std::optional<size_t> findTrack(std::shared_ptr<Track> track) const;

    // Sobrecarga de operadores
    std::shared_ptr<Track> operator[](size_t index) const;
    Playlist& operator+=(std::shared_ptr<Track> track);
    Playlist& operator+=(const Playlist& other);

    // Navegação
    std::shared_ptr<Track> next();
    std::shared_ptr<Track> previous();
    bool setCurrentIndex(size_t index);

    // Propriedades
    const std::string& getName() const { return name; }
    void setName(const std::string& newName);
    size_t size() const { return tracks.size(); }
    bool empty() const { return tracks.empty(); }
    size_t getCurrentIndex() const { return currentIndex; }

    // Modos de reprodução
    bool getShuffleMode() const { return shuffleMode; }
    void setShuffleMode(bool enabled);
    bool getRepeatMode() const { return repeatMode; }
    void setRepeatMode(bool enabled);

    // Funções utilitárias
    std::chrono::seconds getTotalDuration() const;
    std::vector<std::shared_ptr<Track>> getAllTracks() const;
    void sortByTitle();
    void sortByArtist();
    void sortByAlbum();
    void sortBy(std::function<bool(const Track&, const Track&)> comparator);

    // Funcionalidade de busca
    std::vector<std::shared_ptr<Track>> searchByTitle(const std::string& query) const;
    std::vector<std::shared_ptr<Track>> searchByArtist(const std::string& query) const;

    // Suporte a iteradores para loops baseados em range
    auto begin() const -> decltype(tracks.begin()) { return tracks.begin(); }
    auto end() const -> decltype(tracks.end()) { return tracks.end(); }
};

#endif // PLAYLIST_H