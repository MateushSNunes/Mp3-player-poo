#include <iostream>
#include <memory>
#include <exception>
#include "CLI.h"

/**
 * @file main.cpp
 * @brief Ponto de entrada da aplicação MP3 Player
 * @author MP3 Player Team
 * @date 2024
 * 
 * Este arquivo contém o ponto de entrada principal da aplicação MP3 Player,
 * demonstrando os conceitos de Programação Orientada a Objetos aplicados
 * em um sistema de reprodução de música com interface CLI.
 * 
 * Conceitos POO demonstrados:
 * - Abstração: Classes abstratas como MediaPlayer
 * - Encapsulamento: Dados privados com métodos públicos controlados
 * - Herança: MP3Player herda de MediaPlayer
 * - Polimorfismo: Uso de virtual e override
 * - Composição: MP3Player composto por Equalizer e Playlist
 * - Templates: DirectoryScanner parametrizado
 * - STL: Uso extensivo de containers e algoritmos
 * - Smart Pointers: Gerenciamento automático de memória
 * - Exception Handling: Tratamento robusto de erros
 * - Operator Overloading: Sobrecarga em classes como Track
 */

int main() {
    try {
        // Mostrar informações do sistema
        std::cout << "MP3 Player - Sistema de Música Avançado\n";
        std::cout << "Programação Orientada a Objetos - Etapa 2\n";
        std::cout << "Universidade - 2024\n";
        std::cout << "Compilado com C++17\n\n";
        
        // Criar e executar interface CLI
        auto cli = std::make_unique<CLI>();
        cli->run();
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "\n=== ERRO CRÍTICO ===\n";
        std::cerr << "Falha fatal na aplicação: " << e.what() << "\n";
        std::cerr << "A aplicação será encerrada.\n";
        std::cerr << "\nDetalhes técnicos:\n";
        std::cerr << "- Verifique se todos os arquivos necessários estão presentes\n";
        std::cerr << "- Certifique-se de que o sistema tem permissões adequadas\n";
        std::cerr << "- Confirme se as dependências estão instaladas\n\n";
        
        return 1;
        
    } catch (...) {
        std::cerr << "\n=== ERRO DESCONHECIDO ===\n";
        std::cerr << "Ocorreu um erro não identificado.\n";
        std::cerr << "A aplicação será encerrada.\n\n";
        
        return 2;
    }
}

/*
=== DEMONSTRAÇÃO DOS CONCEITOS POO ===

1. ABSTRAÇÃO:
   - MediaPlayer: classe abstrata que define interface comum
   - Métodos virtuais puros definem contrato para implementações

2. ENCAPSULAMENTO:
   - Membros privados em todas as classes
   - Acesso controlado via métodos públicos
   - Validação de dados nos setters

3. HERANÇA:
   - MP3Player herda de MediaPlayer
   - Implementa métodos virtuais da classe base
   - Especializa comportamento para formato MP3

4. POLIMORFISMO:
   - Métodos virtuais permitem comportamento dinâmico
   - Ponteiros/referências para classe base apontam para derivadas
   - Override explícito em métodos sobrescritos

5. COMPOSIÇÃO:
   - MP3Player possui Equalizer e Playlist
   - Relacionamento "tem-um" ao invés de "é-um"
   - Delegação de responsabilidades

6. TEMPLATES:
   - DirectoryScanner<FileFilter> parametrizado
   - Permite diferentes tipos de filtros
   - Reutilização de código com type safety

7. STL (Standard Template Library):
   - std::vector para coleções dinâmicas
   - std::shared_ptr para gerenciamento de memória
   - std::string para manipulação de texto
   - std::map para associações chave-valor
   - std::algorithm para operações em containers

8. SMART POINTERS:
   - std::shared_ptr para propriedade compartilhada
   - std::unique_ptr para propriedade exclusiva
   - RAII (Resource Acquisition Is Initialization)
   - Prevenção de vazamentos de memória

9. EXCEPTION HANDLING:
   - Classes de exceção customizadas
   - Hierarquia de exceções bem definida
   - Tratamento em múltiplos níveis
   - Garantia de liberação de recursos

10. OPERATOR OVERLOADING:
    - Operadores == e != em Track
    - Operador << para output streams
    - Operadores de comparação para ordenação
    - Interface natural para objetos customizados

=== ARQUITETURA DO SISTEMA ===

A aplicação segue uma arquitetura em camadas:

1. INTERFACE (CLI.h/cpp):
   - Responsável pela interação com usuário
   - Parsing de comandos e formatação de saída
   - Isolamento da lógica de negócio

2. APLICAÇÃO (MP3PlayerApp.h/cpp):
   - Coordena operações de alto nível
   - Integra componentes do sistema
   - Gerencia estado da aplicação

3. DOMÍNIO (Track.h/cpp, Playlist.h/cpp):
   - Modelos de negócio fundamentais
   - Regras e validações específicas do domínio
   - Independente de detalhes técnicos

4. SERVIÇOS (DirectoryScanner.h/cpp, PlaylistPersistence.h/cpp):
   - Funcionalidades de infraestrutura
   - Acesso a sistemas externos (filesystem, arquivos)
   - Operações especializadas

5. CORE (MP3Player.h/cpp, MediaPlayer.h/cpp):
   - Engine principal de reprodução
   - Implementação dos algoritmos centrais
   - Controle de estado do player

=== PADRÕES DE DESIGN UTILIZADOS ===

1. TEMPLATE METHOD:
   - MediaPlayer define algoritmo base
   - Subclasses implementam passos específicos

2. STRATEGY:
   - DirectoryScanner aceita diferentes filtros
   - Equalizer com diferentes presets

3. FACADE:
   - MP3PlayerApp simplifica interface complexa
   - CLI oferece interface unificada

4. FACTORY:
   - Track::createFromFile() para criação de tracks
   - createAudioScanner() para scanners

5. OBSERVER (implícito):
   - Callbacks de progresso em DirectoryScanner
   - Notificações de mudança de estado

Este projeto demonstra a aplicação prática dos conceitos de POO
em um sistema real, com ênfase na manutenibilidade, extensibilidade
e robustez do código.
*/