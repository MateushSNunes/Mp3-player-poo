#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <string>
#include <memory>
#include "Track.h"

/**
 * @brief Classe base abstrata para players de mídia
 * 
 * Esta classe demonstra:
 * - Abstração: Define interface para todos os players de mídia
 * - Polimorfismo: Métodos virtuais para diferentes implementações
 * - Encapsulamento: Membros privados com interface pública
 */
class MediaPlayer {
protected:
    std::shared_ptr<Track> currentTrack;
    bool isPlaying;
    bool isPaused;
    double volume;
    double currentPosition;

public:
    MediaPlayer();
    virtual ~MediaPlayer() = default;

    // Métodos virtuais puros - demonstram interface abstrata
    virtual bool loadTrack(std::shared_ptr<Track> track) = 0;
    virtual bool play() = 0;
    virtual bool pause() = 0;
    virtual bool stop() = 0;
    virtual bool seek(double position) = 0;

    // Métodos de interface comum
    virtual void setVolume(double vol);
    virtual double getVolume() const;
    virtual double getCurrentPosition() const;
    virtual bool getIsPlaying() const;
    virtual bool getIsPaused() const;
    virtual std::shared_ptr<Track> getCurrentTrack() const;

    // Padrão template method - comportamento comum
    virtual bool playFromBeginning();
};

#endif // MEDIAPLAYER_H