#include "DirectoryScanner.h"
#include <filesystem>
#include <algorithm>

// Implementação dos construtores de template
template<typename FileFilter>
DirectoryScanner<FileFilter>::DirectoryScanner() 
    : recursive(false), maxDepth(10) {
    supportedExtensions = {".mp3", ".wav", ".ogg"};
}

template<typename FileFilter>
DirectoryScanner<FileFilter>::DirectoryScanner(const std::set<std::string>& extensions)
    : supportedExtensions(extensions), recursive(false), maxDepth(10) {}

template<typename FileFilter>
DirectoryScanner<FileFilter>::DirectoryScanner(const std::set<std::string>& extensions, 
                                               FileFilter customFilter)
    : supportedExtensions(extensions), filter(customFilter), 
      recursive(false), maxDepth(10) {}

template<typename FileFilter>
void DirectoryScanner<FileFilter>::setSupportedExtensions(const std::set<std::string>& extensions) {
    supportedExtensions = extensions;
}

template<typename FileFilter>
void DirectoryScanner<FileFilter>::addSupportedExtension(const std::string& extension) {
    supportedExtensions.insert(extension);
}

template<typename FileFilter>
void DirectoryScanner<FileFilter>::setRecursive(bool enable, size_t maxDepth) {
    recursive = enable;
    this->maxDepth = maxDepth;
}

template<typename FileFilter>
void DirectoryScanner<FileFilter>::setProgressCallback(std::function<void(const std::string&)> callback) {
    progressCallback = callback;
}

template<typename FileFilter>
void DirectoryScanner<FileFilter>::setFilter(FileFilter customFilter) {
    filter = customFilter;
}

template<typename FileFilter>
std::vector<std::string> DirectoryScanner<FileFilter>::scanDirectory(const std::string& directoryPath) const {
    std::vector<std::string> results;
    
    try {
        if (!std::filesystem::exists(directoryPath)) {
            throw ScanException("Diretório não encontrado: " + directoryPath);
        }
        
        if (!std::filesystem::is_directory(directoryPath)) {
            throw ScanException("Caminho não é um diretório: " + directoryPath);
        }
        
        if (recursive) {
            scanRecursive(directoryPath, results, 0);
        } else {
            for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
                if (entry.is_regular_file()) {
                    std::string filePath = entry.path().string();
                    if (isSupported(filePath) && passesFilter(filePath)) {
                        results.push_back(filePath);
                        notifyProgress(filePath);
                    }
                }
            }
        }
        
        std::sort(results.begin(), results.end());
    } catch (const std::filesystem::filesystem_error& e) {
        throw ScanException("Erro ao acessar sistema de arquivos: " + std::string(e.what()));
    }
    
    return results;
}

template<typename FileFilter>
std::vector<std::shared_ptr<Track>> DirectoryScanner<FileFilter>::scanForTracks(const std::string& directoryPath) const {
    std::vector<std::shared_ptr<Track>> tracks;
    
    try {
        auto filePaths = scanDirectory(directoryPath);
        
        for (const auto& filePath : filePaths) {
            auto track = Track::createFromFile(filePath);
            if (track) {
                tracks.push_back(track);
            }
        }
    } catch (const ScanException&) {
        // Re-lançar exceções de scan
        throw;
    } catch (const std::exception& e) {
        throw ScanException("Erro ao criar tracks: " + std::string(e.what()));
    }
    
    return tracks;
}

template<typename FileFilter>
std::future<std::vector<std::shared_ptr<Track>>> 
DirectoryScanner<FileFilter>::scanForTracksAsync(const std::string& directoryPath) const {
    return std::async(std::launch::async, [this, directoryPath]() {
        return scanForTracks(directoryPath);
    });
}

template<typename FileFilter>
bool DirectoryScanner<FileFilter>::isSupported(const std::string& filePath) const {
    auto extension = std::filesystem::path(filePath).extension().string();
    
    // Converter para minúsculo para comparação case-insensitive
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    return supportedExtensions.find(extension) != supportedExtensions.end();
}

template<typename FileFilter>
size_t DirectoryScanner<FileFilter>::countSupportedFiles(const std::string& directoryPath) const {
    try {
        auto files = scanDirectory(directoryPath);
        return files.size();
    } catch (const ScanException&) {
        return 0;
    }
}

template<typename FileFilter>
void DirectoryScanner<FileFilter>::scanRecursive(const std::string& path, 
                                                 std::vector<std::string>& results, 
                                                 size_t currentDepth) const {
    if (currentDepth >= maxDepth) {
        return;
    }
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::string filePath = entry.path().string();
                if (isSupported(filePath) && passesFilter(filePath)) {
                    results.push_back(filePath);
                    notifyProgress(filePath);
                }
            } else if (entry.is_directory()) {
                scanRecursive(entry.path().string(), results, currentDepth + 1);
            }
        }
    } catch (const std::filesystem::filesystem_error&) {
        // Ignorar diretórios que não podem ser acessados
    }
}

template<typename FileFilter>
bool DirectoryScanner<FileFilter>::passesFilter(const std::string& filePath) const {
    if constexpr (std::is_same_v<FileFilter, std::function<bool(const std::string&)>>) {
        return !filter || filter(filePath);
    } else {
        return true; // Sem filtro customizado
    }
}

template<typename FileFilter>
void DirectoryScanner<FileFilter>::notifyProgress(const std::string& currentFile) const {
    if (progressCallback) {
        progressCallback(currentFile);
    }
}

// Instanciacao explicita do template
template class DirectoryScanner<std::function<bool(const std::string&)>>;

// Implementacao das funcoes factory
std::unique_ptr<MediaScanner> createMP3Scanner() {
    return std::make_unique<MediaScanner>(std::set<std::string>{".mp3"});
}

std::unique_ptr<MediaScanner> createAudioScanner() {
    return std::make_unique<MediaScanner>(std::set<std::string>{".mp3", ".wav", ".ogg"});
}

std::unique_ptr<CustomMediaScanner> createCustomScanner(
    const std::set<std::string>& extensions,
    std::function<bool(const std::string&)> filter) {
    return std::make_unique<CustomMediaScanner>(extensions, filter);
}