#ifndef MP3PLAYER_H
#define MP3PLAYER_H

#include "MediaPlayer.h"
#include "Equalizer.h"
#include <memory>
#include <functional>

/**
 * @brief Implementação concreta do MediaPlayer para arquivos MP3
 * 
 * Esta classe demonstra:
 * - Herança: Herda da classe abstrata MediaPlayer
 * - Polimorfismo: Implementa métodos virtuais
 * - Composição: Contém objeto Equalizer
 * - Gerenciamento de recursos: Usa smart pointers
 */
class MP3Player : public MediaPlayer {
private:
    std::unique_ptr<Equalizer> equalizer;
    std::function<void(const std::string&)> errorCallback;
    std::function<void(double)> positionCallback;
    
    // Detalhes de implementação privados
    void* audioEngine; // Ponteiro opaco para biblioteca de áudio
    bool initializeAudioEngine();
    void cleanupAudioEngine();

public:
    MP3Player();
    explicit MP3Player(std::unique_ptr<Equalizer> eq);
    ~MP3Player() override;

    // Implementação da interface MediaPlayer
    bool loadTrack(std::shared_ptr<Track> track) override;
    bool play() override;
    bool pause() override;
    bool stop() override;
    bool seek(double position) override;

    // Funcionalidade específica do MP3
    Equalizer* getEqualizer() const;
    void setEqualizer(std::unique_ptr<Equalizer> newEqualizer);

    // Gerenciamento de callbacks
    void setErrorCallback(std::function<void(const std::string&)> callback);
    void setPositionCallback(std::function<void(double)> callback);

    // Suporte a formatos de áudio
    static bool isFormatSupported(const std::string& format);
    static std::vector<std::string> getSupportedFormats();

private:
    void notifyError(const std::string& message);
    void notifyPositionChanged(double position);
};

#endif // MP3PLAYER_H