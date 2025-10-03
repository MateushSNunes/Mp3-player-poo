#include "MediaPlayer.h"
#include <stdexcept>

MediaPlayer::MediaPlayer() 
    : currentTrack(nullptr), isPlaying(false), isPaused(false), 
      volume(0.7), currentPosition(0.0) {}

void MediaPlayer::setVolume(double vol) {
    if (vol < 0.0 || vol > 1.0) {
        throw std::invalid_argument("Volume deve estar entre 0.0 e 1.0");
    }
    volume = vol;
}

double MediaPlayer::getVolume() const {
    return volume;
}

double MediaPlayer::getCurrentPosition() const {
    return currentPosition;
}

bool MediaPlayer::getIsPlaying() const {
    return isPlaying;
}

bool MediaPlayer::getIsPaused() const {
    return isPaused;
}

std::shared_ptr<Track> MediaPlayer::getCurrentTrack() const {
    return currentTrack;
}

bool MediaPlayer::playFromBeginning() {
    if (!currentTrack) {
        return false;
    }
    
    stop();
    seek(0.0);
    return play();
}