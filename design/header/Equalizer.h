#ifndef EQUALIZER_H
#define EQUALIZER_H

#include <array>
#include <string>
#include <memory>
#include <map>

/**
 * @brief Equalizador de 3 bandas para processamento de áudio
 * 
 * Esta classe demonstra:
 * - Composição: Será composta no MP3Player
 * - Encapsulamento: Controles de banda privados com interface pública
 * - Templates e STL: Usa std::array, std::map
 * - Classes e Objetos: Representa componente de áudio do mundo real
 */
class Equalizer {
public:
    enum class Band {
        LOW = 0,    // Graves (20Hz - 250Hz)
        MID = 1,    // Médios (250Hz - 4kHz)
        HIGH = 2    // Agudos (4kHz - 20kHz)
    };

    static constexpr size_t NUM_BANDS = 3;
    static constexpr double MIN_GAIN = -12.0; // dB
    static constexpr double MAX_GAIN = 12.0;  // dB
    static constexpr double DEFAULT_GAIN = 0.0;

private:
    std::array<double, NUM_BANDS> bandGains;
    std::string presetName;
    bool enabled;
    
    // Presets predefinidos
    static const std::map<std::string, std::array<double, NUM_BANDS>> presets;

    void validateGain(double& gain);

public:
    // Construtores
    Equalizer();
    explicit Equalizer(double lowGain, double midGain, double highGain);
    explicit Equalizer(const std::string& presetName);

    // Semântica de cópia
    Equalizer(const Equalizer& other) = default;
    Equalizer& operator=(const Equalizer& other) = default;

    // Semântica de movimento
    Equalizer(Equalizer&& other) noexcept = default;
    Equalizer& operator=(Equalizer&& other) noexcept = default;

    // Destrutor
    ~Equalizer() = default;

    // Controle de bandas
    void setBandGain(Band band, double gain);
    double getBandGain(Band band) const;
    void setBands(double lowGain, double midGain, double highGain);

    // Gerenciamento de presets
    void applyPreset(const std::string& preset);
    const std::string& getCurrentPreset() const { return presetName; }
    static std::vector<std::string> getAvailablePresets();

    // Controle global
    void setEnabled(bool enable) { enabled = enable; }
    bool isEnabled() const { return enabled; }
    void reset(); // Resetar todas as bandas para 0dB

    // Métodos utilitários
    std::array<double, NUM_BANDS> getAllGains() const { return bandGains; }
    std::string toString() const;

    // Sobrecarga de operadores para comparação fácil
    bool operator==(const Equalizer& other) const;
    bool operator!=(const Equalizer& other) const;

    // Método factory para configurações comuns
    static std::unique_ptr<Equalizer> createFlat();
    static std::unique_ptr<Equalizer> createRock();
    static std::unique_ptr<Equalizer> createJazz();
    static std::unique_ptr<Equalizer> createClassical();

private:
    void initializePresets();
    static std::string bandToString(Band band);
};

#endif // EQUALIZER_H