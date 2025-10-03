#include "MP3Player.h"
#include <iostream>
#include <algorithm>

MP3Player::MP3Player() : audioEngine(nullptr) {
    equalizer = Equalizer::createFlat();
    initializeAudioEngine();
}

MP3Player::MP3Player(std::unique_ptr<Equalizer> eq) : audioEngine(nullptr) {
    equalizer = std::move(eq);
    initializeAudioEngine();
}

MP3Player::~MP3Player() {
    cleanupAudioEngine();
}

bool MP3Player::initializeAudioEngine() {
    // Simulação de inicialização de engine de áudio
    audioEngine = reinterpret_cast<void*>(0x12345678); // Mock pointer
    return audioEngine != nullptr;
}

void MP3Player::cleanupAudioEngine() {
    if (audioEngine) {
        // Simulação de limpeza
        audioEngine = nullptr;
    }
}

bool MP3Player::loadTrack(std::shared_ptr<Track> track) {
    if (!track || !track->isValid()) {
        notifyError("Track inválida ou arquivo não encontrado");
        return false;
    }
    
    // Verificar se formato é suportado
    if (!isFormatSupported(track->getFormat())) {
        notifyError("Formato não suportado: " + track->getFormat());
        return false;
    }
    
    stop(); // Parar reprodução atual
    currentTrack = track;
    currentPosition = 0.0;
    
    std::cout << "Track carregada: " << track->getDisplayName() << std::endl;
    return true;
}

bool MP3Player::play() {
    if (!currentTrack) {
        notifyError("Nenhuma track carregada");
        return false;
    }
    
    if (!audioEngine) {
        notifyError("Engine de áudio não inicializada");
        return false;
    }
    
    isPlaying = true;
    isPaused = false;
    
    std::cout << "▶️ Reproduzindo: " << currentTrack->getDisplayName() 
              << " [" << currentTrack->getDurationString() << "]" << std::endl;
    
    // Simular progresso da reprodução
    notifyPositionChanged(currentPosition);
    
    return true;
}

bool MP3Player::pause() {
    if (!isPlaying) {
        return false;
    }
    
    isPaused = true;
    isPlaying = false;
    
    std::cout << "⏸️ Pausado em " << static_cast<int>(currentPosition) << "s" << std::endl;
    return true;
}

bool MP3Player::stop() {
    if (!isPlaying && !isPaused) {
        return true;
    }
    
    isPlaying = false;
    isPaused = false;
    currentPosition = 0.0;
    
    std::cout << "⏹️ Parado" << std::endl;
    return true;
}

bool MP3Player::seek(double position) {
    if (!currentTrack) {
        return false;
    }
    
    double maxPosition = static_cast<double>(currentTrack->getDuration().count());
    if (position < 0.0 || position > maxPosition) {
        return false;
    }
    
    currentPosition = position;
    notifyPositionChanged(currentPosition);
    
    std::cout << "⏭️ Posição: " << static_cast<int>(position) << "s" << std::endl;
    return true;
}

Equalizer* MP3Player::getEqualizer() const {
    return equalizer.get();
}

void MP3Player::setEqualizer(std::unique_ptr<Equalizer> newEqualizer) {
    if (newEqualizer) {
        equalizer = std::move(newEqualizer);
        std::cout << "🎛️ Equalizer atualizado: " << equalizer->toString() << std::endl;
    }
}

void MP3Player::setErrorCallback(std::function<void(const std::string&)> callback) {
    errorCallback = callback;
}

void MP3Player::setPositionCallback(std::function<void(double)> callback) {
    positionCallback = callback;
}

bool MP3Player::isFormatSupported(const std::string& format) {
    static const std::vector<std::string> supportedFormats = {"MP3", "WAV", "OGG"};
    return std::find(supportedFormats.begin(), supportedFormats.end(), format) 
           != supportedFormats.end();
}

std::vector<std::string> MP3Player::getSupportedFormats() {
    return {"MP3", "WAV", "OGG"};
}

void MP3Player::notifyError(const std::string& message) {
    if (errorCallback) {
        errorCallback(message);
    } else {
        std::cerr << "❌ Erro: " << message << std::endl;
    }
}

void MP3Player::notifyPositionChanged(double position) {
    if (positionCallback) {
        positionCallback(position);
    }
}