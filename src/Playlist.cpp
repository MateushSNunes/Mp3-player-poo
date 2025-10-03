#include "Playlist.h"
#include <algorithm>
#include <random>
#include <stdexcept>

Playlist::Playlist() : name("Nova Playlist"), currentIndex(0), 
                       shuffleMode(false), repeatMode(false) {
    randomGenerator.seed(std::random_device{}());
}

Playlist::Playlist(const std::string& playlistName) 
    : name(playlistName), currentIndex(0), shuffleMode(false), repeatMode(false) {
    randomGenerator.seed(std::random_device{}());
}

Playlist::Playlist(const std::string& playlistName, 
                   const std::vector<std::shared_ptr<Track>>& initialTracks)
    : name(playlistName), tracks(initialTracks), currentIndex(0),
      shuffleMode(false), repeatMode(false) {
    randomGenerator.seed(std::random_device{}());
}

// Construtor de cópia
Playlist::Playlist(const Playlist& other) 
    : name(other.name), tracks(other.tracks), currentIndex(other.currentIndex),
      shuffleMode(other.shuffleMode), repeatMode(other.repeatMode),
      shuffleOrder(other.shuffleOrder) {
    randomGenerator.seed(std::random_device{}());
}

// Construtor de movimento
Playlist::Playlist(Playlist&& other) noexcept
    : name(std::move(other.name)), tracks(std::move(other.tracks)),
      currentIndex(other.currentIndex), shuffleMode(other.shuffleMode),
      repeatMode(other.repeatMode), shuffleOrder(std::move(other.shuffleOrder)) {
    randomGenerator.seed(std::random_device{}());
}

// Operador de atribuição por cópia
Playlist& Playlist::operator=(const Playlist& other) {
    if (this != &other) {
        name = other.name;
        tracks = other.tracks;
        currentIndex = other.currentIndex;
        shuffleMode = other.shuffleMode;
        repeatMode = other.repeatMode;
        shuffleOrder = other.shuffleOrder;
    }
    return *this;
}

// Operador de atribuição por movimento
Playlist& Playlist::operator=(Playlist&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        tracks = std::move(other.tracks);
        currentIndex = other.currentIndex;
        shuffleMode = other.shuffleMode;
        repeatMode = other.repeatMode;
        shuffleOrder = std::move(other.shuffleOrder);
    }
    return *this;
}

void Playlist::addTrack(std::shared_ptr<Track> track) {
    if (!track) {
        throw std::invalid_argument("Track não pode ser nula");
    }
    
    tracks.push_back(track);
    
    // Atualizar ordem shuffle se ativo
    if (shuffleMode) {
        generateShuffleOrder();
    }
}

void Playlist::addTracks(const std::vector<std::shared_ptr<Track>>& newTracks) {
    for (const auto& track : newTracks) {
        if (track) {
            tracks.push_back(track);
        }
    }
    
    if (shuffleMode) {
        generateShuffleOrder();
    }
}

bool Playlist::removeTrack(size_t index) {
    if (index >= tracks.size()) {
        return false;
    }
    
    tracks.erase(tracks.begin() + index);
    
    // Ajustar índice atual se necessário
    if (currentIndex >= tracks.size() && !tracks.empty()) {
        currentIndex = tracks.size() - 1;
    } else if (tracks.empty()) {
        currentIndex = 0;
    }
    
    if (shuffleMode) {
        generateShuffleOrder();
    }
    
    return true;
}

bool Playlist::removeTrack(std::shared_ptr<Track> track) {
    auto it = std::find(tracks.begin(), tracks.end(), track);
    if (it != tracks.end()) {
        size_t index = std::distance(tracks.begin(), it);
        return removeTrack(index);
    }
    return false;
}

void Playlist::clear() {
    tracks.clear();
    shuffleOrder.clear();
    currentIndex = 0;
}

std::shared_ptr<Track> Playlist::getTrack(size_t index) const {
    if (index >= tracks.size()) {
        return nullptr;
    }
    return tracks[index];
}

std::shared_ptr<Track> Playlist::getCurrentTrack() const {
    if (tracks.empty()) {
        return nullptr;
    }
    
    size_t actualIndex = shuffleMode && !shuffleOrder.empty() 
                        ? shuffleOrder[currentIndex % shuffleOrder.size()]
                        : currentIndex;
    
    return getTrack(actualIndex);
}

std::optional<size_t> Playlist::findTrack(std::shared_ptr<Track> track) const {
    auto it = std::find(tracks.begin(), tracks.end(), track);
    if (it != tracks.end()) {
        return std::distance(tracks.begin(), it);
    }
    return std::nullopt;
}

std::shared_ptr<Track> Playlist::operator[](size_t index) const {
    return getTrack(index);
}

Playlist& Playlist::operator+=(std::shared_ptr<Track> track) {
    addTrack(track);
    return *this;
}

Playlist& Playlist::operator+=(const Playlist& other) {
    addTracks(other.tracks);
    return *this;
}

std::shared_ptr<Track> Playlist::next() {
    if (tracks.empty()) {
        return nullptr;
    }
    
    size_t maxIndex = shuffleMode ? shuffleOrder.size() : tracks.size();
    
    currentIndex++;
    
    if (currentIndex >= maxIndex) {
        if (repeatMode) {
            currentIndex = 0;
        } else {
            currentIndex = maxIndex - 1;
            return nullptr; // Fim da playlist
        }
    }
    
    return getCurrentTrack();
}

std::shared_ptr<Track> Playlist::previous() {
    if (tracks.empty()) {
        return nullptr;
    }
    
    if (currentIndex > 0) {
        currentIndex--;
    } else if (repeatMode) {
        size_t maxIndex = shuffleMode ? shuffleOrder.size() : tracks.size();
        currentIndex = maxIndex - 1;
    }
    
    return getCurrentTrack();
}

bool Playlist::setCurrentIndex(size_t index) {
    size_t maxIndex = shuffleMode ? shuffleOrder.size() : tracks.size();
    if (index < maxIndex) {
        currentIndex = index;
        return true;
    }
    return false;
}

void Playlist::setName(const std::string& newName) {
    if (newName.empty()) {
        throw std::invalid_argument("Nome da playlist não pode estar vazio");
    }
    name = newName;
}

void Playlist::setShuffleMode(bool enabled) {
    shuffleMode = enabled;
    if (enabled) {
        generateShuffleOrder();
    } else {
        shuffleOrder.clear();
    }
}

void Playlist::setRepeatMode(bool enabled) {
    repeatMode = enabled;
}

void Playlist::generateShuffleOrder() {
    shuffleOrder.clear();
    for (size_t i = 0; i < tracks.size(); ++i) {
        shuffleOrder.push_back(i);
    }
    
    std::shuffle(shuffleOrder.begin(), shuffleOrder.end(), randomGenerator);
}

std::chrono::seconds Playlist::getTotalDuration() const {
    std::chrono::seconds total(0);
    for (const auto& track : tracks) {
        if (track) {
            total += track->getDuration();
        }
    }
    return total;
}

std::vector<std::shared_ptr<Track>> Playlist::getAllTracks() const {
    return tracks;
}

void Playlist::sortByTitle() {
    std::sort(tracks.begin(), tracks.end(),
        [](const std::shared_ptr<Track>& a, const std::shared_ptr<Track>& b) {
            return a->getTitle() < b->getTitle();
        });
    
    if (shuffleMode) {
        generateShuffleOrder();
    }
}

void Playlist::sortByArtist() {
    std::sort(tracks.begin(), tracks.end(),
        [](const std::shared_ptr<Track>& a, const std::shared_ptr<Track>& b) {
            return a->getArtist() < b->getArtist();
        });
    
    if (shuffleMode) {
        generateShuffleOrder();
    }
}

void Playlist::sortByAlbum() {
    std::sort(tracks.begin(), tracks.end(),
        [](const std::shared_ptr<Track>& a, const std::shared_ptr<Track>& b) {
            return a->getAlbum() < b->getAlbum();
        });
    
    if (shuffleMode) {
        generateShuffleOrder();
    }
}

void Playlist::sortBy(std::function<bool(const Track&, const Track&)> comparator) {
    std::sort(tracks.begin(), tracks.end(),
        [&comparator](const std::shared_ptr<Track>& a, const std::shared_ptr<Track>& b) {
            return comparator(*a, *b);
        });
    
    if (shuffleMode) {
        generateShuffleOrder();
    }
}

std::vector<std::shared_ptr<Track>> Playlist::searchByTitle(const std::string& query) const {
    std::vector<std::shared_ptr<Track>> results;
    
    for (const auto& track : tracks) {
        if (track && track->getTitle().find(query) != std::string::npos) {
            results.push_back(track);
        }
    }
    
    return results;
}

std::vector<std::shared_ptr<Track>> Playlist::searchByArtist(const std::string& query) const {
    std::vector<std::shared_ptr<Track>> results;
    
    for (const auto& track : tracks) {
        if (track && track->getArtist().find(query) != std::string::npos) {
            results.push_back(track);
        }
    }
    
    return results;
}