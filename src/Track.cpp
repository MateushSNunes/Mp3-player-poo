#include "Track.h"
#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <iomanip>

Track::Track() 
    : title("Untitled"), artist("Unknown Artist"), album("Unknown Album"),
      genre("Unknown"), year(2024), duration(std::chrono::seconds(0)), 
      fileSize(0), format("MP3") {}

Track::Track(const std::string& path) 
    : filePath(path), title(""), artist(""), album(""),
      genre(""), year(2024), duration(std::chrono::seconds(0)), 
      fileSize(0), format("MP3") {
    
    if (!std::filesystem::exists(path)) {
        throw std::invalid_argument("Arquivo não encontrado: " + path);
    }
    
    // Extrair nome do arquivo como título padrão
    auto filename = std::filesystem::path(path).stem().string();
    title = filename;
    
    // Obter tamanho do arquivo
    try {
        fileSize = std::filesystem::file_size(path);
    } catch (const std::filesystem::filesystem_error&) {
        fileSize = 0;
    }
    
    // Determinar formato pela extensão
    auto extension = std::filesystem::path(path).extension().string();
    if (extension == ".mp3" || extension == ".MP3") {
        format = "MP3";
    } else if (extension == ".wav" || extension == ".WAV") {
        format = "WAV";
    } else if (extension == ".ogg" || extension == ".OGG") {
        format = "OGG";
    }
    
    // Duração padrão baseada no tamanho (estimativa)
    if (fileSize > 0) {
        // Estimativa: ~1MB por minuto para MP3 de qualidade média
        auto estimatedMinutes = fileSize / (1024 * 1024);
        duration = std::chrono::seconds(estimatedMinutes * 60);
    }
}

Track::Track(const std::string& path, const std::string& title, 
             const std::string& artist, const std::string& album)
    : filePath(path), title(title), artist(artist), album(album),
      genre("Unknown"), year(2024), duration(std::chrono::seconds(0)),
      fileSize(0), format("MP3") {
    
    if (!std::filesystem::exists(path)) {
        throw std::invalid_argument("Arquivo não encontrado: " + path);
    }
    
    try {
        fileSize = std::filesystem::file_size(path);
    } catch (const std::filesystem::filesystem_error&) {
        fileSize = 0;
    }
}

void Track::setTitle(const std::string& newTitle) {
    if (newTitle.empty()) {
        throw std::invalid_argument("Título não pode estar vazio");
    }
    title = newTitle;
}

void Track::setArtist(const std::string& newArtist) {
    if (newArtist.empty()) {
        throw std::invalid_argument("Artista não pode estar vazio");
    }
    artist = newArtist;
}

void Track::setAlbum(const std::string& newAlbum) {
    album = newAlbum;
}

void Track::setGenre(const std::string& newGenre) {
    genre = newGenre;
}

void Track::setYear(int newYear) {
    if (newYear < 1900 || newYear > 2100) {
        throw std::invalid_argument("Ano inválido para faixa musical");
    }
    year = newYear;
}

void Track::setDuration(std::chrono::seconds newDuration) {
    if (newDuration.count() < 0) {
        throw std::invalid_argument("Duração não pode ser negativa");
    }
    duration = newDuration;
}

bool Track::operator==(const Track& other) const {
    return filePath == other.filePath;
}

bool Track::operator!=(const Track& other) const {
    return !(*this == other);
}

bool Track::operator<(const Track& other) const {
    // Ordenação por artista, depois álbum, depois título
    if (artist != other.artist) return artist < other.artist;
    if (album != other.album) return album < other.album;
    return title < other.title;
}

bool Track::operator>(const Track& other) const {
    return other < *this;
}

bool Track::isValid() const {
    return !filePath.empty() && std::filesystem::exists(filePath) && 
           !title.empty() && !artist.empty();
}

std::string Track::getDisplayName() const {
    return artist + " - " + title;
}

std::string Track::getDurationString() const {
    auto totalSeconds = duration.count();
    auto minutes = totalSeconds / 60;
    auto seconds = totalSeconds % 60;
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes 
       << ":" << std::setw(2) << seconds;
    return ss.str();
}

std::shared_ptr<Track> Track::createFromFile(const std::string& filePath) {
    try {
        return std::make_shared<Track>(filePath);
    } catch (const std::exception&) {
        return nullptr;
    }
}

std::optional<Track> Track::loadMetadata(const std::string& filePath) {
    try {
        return Track(filePath);
    } catch (const std::exception&) {
        return std::nullopt;
    }
}