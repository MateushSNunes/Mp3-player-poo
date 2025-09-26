#ifndef PLAYLISTPERSISTENCE_H
#define PLAYLISTPERSISTENCE_H

#include "Playlist.h"
#include <string>
#include <memory>
#include <optional>
#include <vector>

/**
 * @brief Interface abstrata para persistência de playlist
 * 
 * Esta classe demonstra:
 * - Abstração: Interface abstrata para diferentes formatos de armazenamento
 * - Polimorfismo: Métodos virtuais para diferentes implementações
 * - Tratamento de exceções: Métodos que podem lançar exceções
 */
class PlaylistPersistence {
public:
    virtual ~PlaylistPersistence() = default;

    // Métodos virtuais puros
    virtual bool savePlaylist(const Playlist& playlist, const std::string& filePath) = 0;
    virtual std::optional<Playlist> loadPlaylist(const std::string& filePath) = 0;
    virtual bool deletePlaylist(const std::string& filePath) = 0;

    // Interface comum
    virtual std::vector<std::string> listPlaylists(const std::string& directory) = 0;
    virtual bool isValidFormat(const std::string& filePath) const = 0;
    virtual std::string getDefaultExtension() const = 0;
};

/**
 * @brief Implementação JSON da persistência de playlist
 * 
 * Esta classe demonstra:
 * - Herança: Herda de PlaylistPersistence
 * - Tratamento de exceções: Lida com erros de I/O de arquivo e parsing JSON
 * - Gerenciamento de recursos: RAII para handles de arquivo
 */
class JsonPlaylistPersistence : public PlaylistPersistence {
private:
    std::string formatVersion;
    bool prettyPrint;

    // Métodos auxiliares para serialização JSON
    std::string serializeTrack(const Track& track) const;
    std::optional<Track> deserializeTrack(const std::string& jsonTrack) const;
    std::string serializePlaylist(const Playlist& playlist) const;

public:
    JsonPlaylistPersistence();
    explicit JsonPlaylistPersistence(bool prettyFormat);
    ~JsonPlaylistPersistence() override = default;

    // Implementação da interface PlaylistPersistence
    bool savePlaylist(const Playlist& playlist, const std::string& filePath) override;
    std::optional<Playlist> loadPlaylist(const std::string& filePath) override;
    bool deletePlaylist(const std::string& filePath) override;
    std::vector<std::string> listPlaylists(const std::string& directory) override;
    bool isValidFormat(const std::string& filePath) const override;
    std::string getDefaultExtension() const override { return ".json"; }

    // Funcionalidade específica do JSON
    void setPrettyPrint(bool enabled) { prettyPrint = enabled; }
    bool getPrettyPrint() const { return prettyPrint; }
    const std::string& getFormatVersion() const { return formatVersion; }

    // Classes de exceção para tratamento de erro
    class JsonException : public std::exception {
    private:
        std::string message;
    public:
        explicit JsonException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
    };

    class FileException : public JsonException {
    public:
        explicit FileException(const std::string& filePath) 
            : JsonException("Erro de arquivo: " + filePath) {}
    };

    class ParseException : public JsonException {
    public:
        explicit ParseException(const std::string& details) 
            : JsonException("Erro de parsing JSON: " + details) {}
    };
};

#endif // PLAYLISTPERSISTENCE_H