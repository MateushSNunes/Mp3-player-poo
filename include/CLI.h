#ifndef CLI_H
#define CLI_H

#include "MP3PlayerApp.h"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <iostream>

/**
 * @brief Interface de Linha de Comando para o MP3 Player
 * 
 * Esta classe demonstra:
 * - Classes e Objetos: Componente de interface do usuário
 * - Templates: Padrão Command com funções template
 * - STL: Uso extensivo de containers para gerenciamento de comandos
 * - Composição: Usa MP3PlayerApp para funcionalidade
 */
class CLI {
public:
    using CommandFunction = std::function<void(const std::vector<std::string>&)>;
    
    struct Command {
        std::string name;
        std::string description;
        std::string usage;
        CommandFunction function;
        size_t minArgs;
        size_t maxArgs;
        
        Command(const std::string& n, const std::string& desc, 
                const std::string& use, CommandFunction func, 
                size_t min = 0, size_t max = SIZE_MAX)
            : name(n), description(desc), usage(use), 
              function(func), minArgs(min), maxArgs(max) {}
    };

private:
    std::unique_ptr<MP3PlayerApp> app;
    std::map<std::string, Command> commands;
    bool running;
    std::string prompt;

    void initializeCommands();
    void displayWelcome();
    void displayHelp();
    void displayStatus();
    
    // Implementações de comandos
    void cmdPlay(const std::vector<std::string>& args);
    void cmdPause(const std::vector<std::string>& args);
    void cmdStop(const std::vector<std::string>& args);
    void cmdNext(const std::vector<std::string>& args);
    void cmdPrevious(const std::vector<std::string>& args);
    void cmdVolume(const std::vector<std::string>& args);
    void cmdSeek(const std::vector<std::string>& args);
    void cmdPlaylist(const std::vector<std::string>& args);
    void cmdLoad(const std::vector<std::string>& args);
    void cmdSave(const std::vector<std::string>& args);
    void cmdAdd(const std::vector<std::string>& args);
    void cmdScan(const std::vector<std::string>& args);
    void cmdList(const std::vector<std::string>& args);
    void cmdEqualizer(const std::vector<std::string>& args);
    void cmdStatus(const std::vector<std::string>& args);
    void cmdHelp(const std::vector<std::string>& args);
    void cmdQuit(const std::vector<std::string>& args);

    // Métodos utilitários
    std::vector<std::string> parseCommand(const std::string& input);
    void printError(const std::string& message);
    void printSuccess(const std::string& message);
    void printInfo(const std::string& message);
    bool validateArguments(const Command& cmd, const std::vector<std::string>& args);

public:
    CLI();
    explicit CLI(std::unique_ptr<MP3PlayerApp> application);
    ~CLI() = default;

    // Interface principal
    void run();
    void processCommand(const std::string& commandLine);
    void shutdown();

    // Configuração
    void setPrompt(const std::string& newPrompt) { prompt = newPrompt; }
    const std::string& getPrompt() const { return prompt; }

    // Registro de comandos (para extensibilidade)
    void registerCommand(const Command& command);
    void unregisterCommand(const std::string& name);
    std::vector<std::string> getAvailableCommands() const;

private:
    void setupCallbacks();
    void onTrackChanged(std::shared_ptr<Track> track);
    void onError(const std::string& message);
    void onPositionChanged(double position);
};

#endif // CLI_H