#ifndef DIRECTORYSCANNER_H
#define DIRECTORYSCANNER_H

#include "Track.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <set>
#include <future>

/**
 * @brief Scanner de diretório baseado em template para arquivos de mídia
 * 
 * Esta classe demonstra:
 * - Templates: Filtragem e processamento genérico
 * - STL: Uso extensivo de containers e algoritmos
 * - Gerenciamento de recursos: Smart pointers e RAII
 * - Tratamento de exceções: Tratamento de erros do sistema de arquivos
 */
template<typename FileFilter = std::function<bool(const std::string&)>>
class DirectoryScanner {
private:
    std::set<std::string> supportedExtensions;
    FileFilter filter;
    bool recursive;
    size_t maxDepth;
    std::function<void(const std::string&)> progressCallback;

public:
    // Construtores
    DirectoryScanner();
    explicit DirectoryScanner(const std::set<std::string>& extensions);
    DirectoryScanner(const std::set<std::string>& extensions, FileFilter customFilter);

    // Configuração
    void setSupportedExtensions(const std::set<std::string>& extensions);
    void addSupportedExtension(const std::string& extension);
    void setRecursive(bool enable, size_t maxDepth = 10);
    void setProgressCallback(std::function<void(const std::string&)> callback);
    void setFilter(FileFilter customFilter);

    // Operações de varredura
    std::vector<std::string> scanDirectory(const std::string& directoryPath) const;
    std::vector<std::shared_ptr<Track>> scanForTracks(const std::string& directoryPath) const;
    
    // Varredura assíncrona
    std::future<std::vector<std::shared_ptr<Track>>> scanForTracksAsync(const std::string& directoryPath) const;

    // Métodos utilitários
    bool isSupported(const std::string& filePath) const;
    size_t countSupportedFiles(const std::string& directoryPath) const;

    // Tratamento de exceções
    class ScanException : public std::exception {
    private:
        std::string message;
    public:
        explicit ScanException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
    };

private:
    void scanRecursive(const std::string& path, std::vector<std::string>& results, 
                      size_t currentDepth) const;
    bool passesFilter(const std::string& filePath) const;
    void notifyProgress(const std::string& currentFile) const;
};

// Aliases de tipo comuns
using MediaScanner = DirectoryScanner<>;
using CustomMediaScanner = DirectoryScanner<std::function<bool(const std::string&)>>;

// Funções factory para configurações comuns
std::unique_ptr<MediaScanner> createMP3Scanner();
std::unique_ptr<MediaScanner> createAudioScanner(); // MP3, WAV, OGG
std::unique_ptr<CustomMediaScanner> createCustomScanner(
    const std::set<std::string>& extensions,
    std::function<bool(const std::string&)> filter
);

#endif // DIRECTORYSCANNER_H