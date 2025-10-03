#include "Equalizer.h"
#include <stdexcept>
#include <sstream>
#include <map>
#include <vector>

// Inicialização dos presets estáticos
const std::map<std::string, std::array<double, Equalizer::NUM_BANDS>> Equalizer::presets = {
    {"flat", {0.0, 0.0, 0.0}},
    {"rock", {4.0, 2.0, 6.0}},
    {"jazz", {2.0, 0.0, 3.0}},
    {"classical", {0.0, 3.0, 2.0}},
    {"pop", {3.0, 1.0, 4.0}},
    {"bass", {8.0, 0.0, 0.0}},
    {"treble", {0.0, 0.0, 8.0}}
};

Equalizer::Equalizer() : bandGains{0.0, 0.0, 0.0}, presetName("flat"), enabled(true) {}

Equalizer::Equalizer(double lowGain, double midGain, double highGain) 
    : presetName("custom"), enabled(true) {
    setBands(lowGain, midGain, highGain);
}

Equalizer::Equalizer(const std::string& presetName) : enabled(true) {
    applyPreset(presetName);
}

void Equalizer::validateGain(double& gain) {
    if (gain < MIN_GAIN) {
        gain = MIN_GAIN;
    } else if (gain > MAX_GAIN) {
        gain = MAX_GAIN;
    }
}

void Equalizer::setBandGain(Band band, double gain) {
    validateGain(gain);
    bandGains[static_cast<size_t>(band)] = gain;
    presetName = "custom"; // Mudança manual quebra preset
}

double Equalizer::getBandGain(Band band) const {
    return bandGains[static_cast<size_t>(band)];
}

void Equalizer::setBands(double lowGain, double midGain, double highGain) {
    validateGain(lowGain);
    validateGain(midGain);
    validateGain(highGain);
    
    bandGains[static_cast<size_t>(Band::LOW)] = lowGain;
    bandGains[static_cast<size_t>(Band::MID)] = midGain;
    bandGains[static_cast<size_t>(Band::HIGH)] = highGain;
    
    presetName = "custom";
}

void Equalizer::applyPreset(const std::string& preset) {
    auto it = presets.find(preset);
    if (it == presets.end()) {
        throw std::invalid_argument("Preset não encontrado: " + preset);
    }
    
    bandGains = it->second;
    presetName = preset;
}

std::vector<std::string> Equalizer::getAvailablePresets() {
    std::vector<std::string> result;
    for (const auto& pair : presets) {
        result.push_back(pair.first);
    }
    return result;
}

void Equalizer::reset() {
    bandGains = {0.0, 0.0, 0.0};
    presetName = "flat";
}

std::string Equalizer::toString() const {
    std::stringstream ss;
    ss << "Equalizer [" << presetName << "] - ";
    ss << "Graves: " << getBandGain(Band::LOW) << "dB, ";
    ss << "Médios: " << getBandGain(Band::MID) << "dB, ";
    ss << "Agudos: " << getBandGain(Band::HIGH) << "dB";
    ss << " (" << (enabled ? "Ativo" : "Inativo") << ")";
    return ss.str();
}

bool Equalizer::operator==(const Equalizer& other) const {
    return bandGains == other.bandGains && enabled == other.enabled;
}

bool Equalizer::operator!=(const Equalizer& other) const {
    return !(*this == other);
}

std::unique_ptr<Equalizer> Equalizer::createFlat() {
    return std::make_unique<Equalizer>();
}

std::unique_ptr<Equalizer> Equalizer::createRock() {
    auto eq = std::make_unique<Equalizer>();
    eq->applyPreset("rock");
    return eq;
}

std::unique_ptr<Equalizer> Equalizer::createJazz() {
    auto eq = std::make_unique<Equalizer>();
    eq->applyPreset("jazz");
    return eq;
}

std::unique_ptr<Equalizer> Equalizer::createClassical() {
    auto eq = std::make_unique<Equalizer>();
    eq->applyPreset("classical");
    return eq;
}

std::string Equalizer::bandToString(Band band) {
    switch (band) {
        case Band::LOW: return "Graves";
        case Band::MID: return "Médios";  
        case Band::HIGH: return "Agudos";
        default: return "Desconhecido";
    }
}