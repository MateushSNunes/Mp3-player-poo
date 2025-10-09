#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <chrono>
#include <memory>
#include <optional>

/**
 * @brief Representa uma faixa de mídia com metadados
 * 
 * Esta classe demonstra:
 * - Encapsulamento: Campos privados com acesso controlado
 * - Classes e Objetos: Modelo de domínio representando entidade do mundo real
 * - Sobrecarga de operadores: Operadores de comparação para ordenação
 */
class Track {
private:
    std::string filePath;
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    int year;
    std::chrono::seconds duration;
    size_t fileSize;
    std::string format; // MP3, WAV, OGG

public:
    // Construtores
    Track();
    Track(const std::string& path);
    Track(const std::string& path, const std::string& title, 
          const std::string& artist, const std::string& album);

    // Construtores de cópia e movimento/atribuição
    Track(const Track& other) = default;
    Track(Track&& other) noexcept = default;
    Track& operator=(const Track& other) = default;
    Track& operator=(Track&& other) noexcept = default;

    // Destrutor
    virtual ~Track() = default;

    // Getters (métodos const para encapsulamento)
    const std::string& getFilePath() const { return filePath; }
    const std::string& getTitle() const { return title; }
    const std::string& getArtist() const { return artist; }
    const std::string& getAlbum() const { return album; }
    const std::string& getGenre() const { return genre; }
    int getYear() const { return year; }
    std::chrono::seconds getDuration() const { return duration; }
    size_t getFileSize() const { return fileSize; }
    const std::string& getFormat() const { return format; }

    // Setters com validação
    void setTitle(const std::string& newTitle);
    void setArtist(const std::string& newArtist);
    void setAlbum(const std::string& newAlbum);
    void setGenre(const std::string& newGenre);
    void setYear(int newYear);
    void setDuration(std::chrono::seconds newDuration);
    void setFilePath(const std::string& path);

    // Sobrecarga de operadores para comparação e ordenação
    bool operator==(const Track& other) const;
    bool operator!=(const Track& other) const;
    bool operator<(const Track& other) const;  // Para ordenação por título
    bool operator>(const Track& other) const;

    // Métodos utilitários
    bool isValid() const;
    std::string getDisplayName() const;
    std::string getDurationString() const;

    // Métodos factory estáticos
    static std::shared_ptr<Track> createFromFile(const std::string& filePath);
    static std::optional<Track> loadMetadata(const std::string& filePath);
};

#endif // TRACK_H