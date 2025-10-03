#include "PlaylistPersistence.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

JsonPlaylistPersistence::JsonPlaylistPersistence() 
    : formatVersion("1.0"), prettyPrint(true) {}

JsonPlaylistPersistence::JsonPlaylistPersistence(bool prettyFormat)
    : formatVersion("1.0"), prettyPrint(prettyFormat) {}

bool JsonPlaylistPersistence::savePlaylist(const Playlist& playlist, const std::string& filePath) {
    try {
        // Criar diretório se não existir
        auto dir = std::filesystem::path(filePath).parent_path();
        if (!dir.empty()) {
            std::filesystem::create_directories(dir);
        }
        
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw FileException(filePath);
        }
        
        std::string jsonContent = serializePlaylist(playlist);
        file << jsonContent;
        file.close();
        
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::optional<Playlist> JsonPlaylistPersistence::loadPlaylist(const std::string& filePath) {
    try {
        if (!std::filesystem::exists(filePath)) {
            throw FileException(filePath);
        }
        
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw FileException(filePath);
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        
        std::string content = buffer.str();
        
        // Parsing JSON simples (implementação básica)
        Playlist playlist;
        
        // Extrair nome da playlist
        size_t nameStart = content.find("\"name\":\"") + 8;
        size_t nameEnd = content.find("\"", nameStart);
        if (nameStart != std::string::npos && nameEnd != std::string::npos) {
            std::string name = content.substr(nameStart, nameEnd - nameStart);
            playlist.setName(name);
        }
        
        // Extrair tracks (implementação básica)
        size_t tracksStart = content.find("\"tracks\":[");
        if (tracksStart != std::string::npos) {
            // Para esta implementação básica, vamos criar algumas tracks de exemplo
            // Em uma implementação real, faria parsing completo do JSON
        }
        
        return playlist;
    } catch (const std::exception& e) {
        return std::nullopt;
    }
}

bool JsonPlaylistPersistence::deletePlaylist(const std::string& filePath) {
    try {
        return std::filesystem::remove(filePath);
    } catch (const std::exception&) {
        return false;
    }
}

std::vector<std::string> JsonPlaylistPersistence::listPlaylists(const std::string& directory) {
    std::vector<std::string> playlists;
    
    try {
        if (!std::filesystem::exists(directory)) {
            return playlists;
        }
        
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                playlists.push_back(entry.path().filename().string());
            }
        }
        
        std::sort(playlists.begin(), playlists.end());
    } catch (const std::exception&) {
        // Retornar lista vazia em caso de erro
    }
    
    return playlists;
}

bool JsonPlaylistPersistence::isValidFormat(const std::string& filePath) const {
    return std::filesystem::path(filePath).extension() == ".json";
}

std::string JsonPlaylistPersistence::serializeTrack(const Track& track) const {
    std::stringstream ss;
    ss << "    {\n";
    ss << "      \"filePath\": \"" << track.getFilePath() << "\",\n";
    ss << "      \"title\": \"" << track.getTitle() << "\",\n";
    ss << "      \"artist\": \"" << track.getArtist() << "\",\n";
    ss << "      \"album\": \"" << track.getAlbum() << "\",\n";
    ss << "      \"genre\": \"" << track.getGenre() << "\",\n";
    ss << "      \"year\": " << track.getYear() << ",\n";
    ss << "      \"duration\": " << track.getDuration().count() << ",\n";
    ss << "      \"format\": \"" << track.getFormat() << "\"\n";
    ss << "    }";
    return ss.str();
}

std::optional<Track> JsonPlaylistPersistence::deserializeTrack(const std::string& jsonTrack) const {
    // Implementação básica de parsing JSON
    // Em uma implementação real, usaria uma biblioteca JSON como nlohmann/json
    try {
        Track track;
        // Por simplicidade, retornar track padrão
        return track;
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

std::string JsonPlaylistPersistence::serializePlaylist(const Playlist& playlist) const {
    std::stringstream ss;
    
    ss << "{\n";
    ss << "  \"formatVersion\": \"" << formatVersion << "\",\n";
    ss << "  \"name\": \"" << playlist.getName() << "\",\n";
    ss << "  \"shuffleMode\": " << (playlist.getShuffleMode() ? "true" : "false") << ",\n";
    ss << "  \"repeatMode\": " << (playlist.getRepeatMode() ? "true" : "false") << ",\n";
    ss << "  \"currentIndex\": " << playlist.getCurrentIndex() << ",\n";
    ss << "  \"tracks\": [\n";
    
    auto tracks = playlist.getAllTracks();
    for (size_t i = 0; i < tracks.size(); ++i) {
        if (tracks[i]) {
            ss << serializeTrack(*tracks[i]);
            if (i < tracks.size() - 1) {
                ss << ",";
            }
            ss << "\n";
        }
    }
    
    ss << "  ]\n";
    ss << "}\n";
    
    return ss.str();
}