# MP3 Player - Projeto de Programacao Orientada a Objetos# MP3 Player - Projeto de Programação Orientada a Objetos# MP3 Player - C++ POO Project



**Disciplina:** Programacao Orientada a Objetos (C++)  

**Instituicao:** UFPB - Centro de Informatica  

**Aluno:** Matheus da Silva Nunes  **Disciplina:** Programação Orientada a Objetos (C++)  ## 🚀 **INSTRUÇÕES PARA EXECUÇÃO DOS TESTES CLI**

**Matricula:** 20240011024  

**Data:** Outubro 2025**Instituição:** UFPB - Centro de Informática  



## Descricao do Projeto**Aluno:** Matheus da Silva Nunes  ### **Compilação:**



Aplicacao completa de MP3 Player desenvolvida em C++17 que demonstra todos os conceitos fundamentais de Programacao Orientada a Objetos. O projeto implementa um player de musica com interface CLI funcional, incluindo gerenciamento de playlists, controles de reproducao, equalizacao e persistencia de dados.**Matrícula:** 20240011024  ```bash



## Requisitos Minimos Implementados**Data:** Outubro 2025cd "e:\POO\POOMP3"



Conforme especificacao do trabalho final, todos os 6 requisitos minimos foram implementados:g++ -std=c++17 -Wall -Wextra -Iinclude src/Track.cpp src/Playlist.cpp src/MediaPlayer.cpp cli_test.cpp -o cli_test.exe



### 1. Lista/Scan de Diretorio com Arquivos de Midia## Descrição do Projeto```

- Implementacao via classe DirectoryScanner

- Simulacao de busca de arquivos MP3/WAV/OGG

- Criacao automatica de tracks a partir de arquivos encontrados

Aplicação completa de MP3 Player desenvolvida em C++17 que demonstra todos os conceitos fundamentais de Programação Orientada a Objetos. O projeto implementa um player de música com interface CLI funcional, incluindo gerenciamento de playlists, controles de reprodução, equalização e persistência de dados.### **Execução:**

### 2. Controles de Reproducao

- Play: Iniciar reproducao de faixas```bash

- Pause: Pausar reproducao atual

- Stop: Parar reproducao completamente## Requisitos Mínimos Implementados.\cli_test.exe

- Seek: Navegar para posicao especifica na faixa

- Volume: Ajustar volume (0-100%)```

- Next/Previous: Navegar entre faixas da playlist

Conforme especificação do trabalho final, todos os 6 requisitos mínimos foram implementados:

### 3. Playlist CRUD (Create, Read, Update, Delete)

- Create: Criar novas playlists com nome customizado### **Resultado Esperado:**

- Read: Visualizar detalhes e listar faixas

- Update: Adicionar ou remover faixas### 1. Lista/Scan de Diretório com Arquivos de MídiaO programa demonstra todas as operações-chave do MP3 Player:

- Delete: Remover playlists completas

- Implementação via classe DirectoryScanner- ✅ Criação e configuração de tracks

### 4. Hierarquia de Classes Implementada

- MediaPlayer: Classe abstrata base com metodos virtuais puros- Simulação de busca de arquivos MP3/WAV/OGG- ✅ Gerenciamento de playlists

- MP3Player: Implementacao concreta do player

- Track: Representa faixas de musica com metadados- Criação automática de tracks a partir de arquivos encontrados- ✅ Navegação entre músicas

- Playlist: Gerencia colecoes de tracks

- Equalizer: Processamento de audio (3 bandas: LOW/MID/HIGH)- ✅ Busca e filtros

- Demonstracao de composicao: MP3Player contem Equalizer

### 2. Controles de Reprodução- ✅ Uso de smart pointers e STL

### 5. Persistencia em JSON

- Salvar playlists completas em arquivos JSON- **Play:** Iniciar reprodução de faixas- ✅ Todos os conceitos OOP implementados

- Carregar playlists de arquivos JSON

- Preservacao de metadados e ordenacao- **Pause:** Pausar reprodução atual



### 6. Interface CLI Funcional- **Stop:** Parar reprodução completamente---

- Menu interativo com todas as funcionalidades

- Demonstracao completa de todos os requisitos- **Seek:** Navegar para posição específica na faixa

- Interface profissional e intuitiva

- **Volume:** Ajustar volume (0-100%)Projeto: MP3 Player

## Conceitos de POO Demonstrados

- **Next/Previous:** Navegar entre faixas da playlist

O projeto implementa explicitamente os 10 conceitos exigidos:

Disciplina: Programação Orientada a Objetos (C++)

### 1. Abstracao & Encapsulamento

- Interfaces claras separando .h e .cpp### 3. Playlist CRUD (Create, Read, Update, Delete)

- Campos privados com getters/setters validados

- Exemplo: classe Track com validacao de metadados- **Create:** Criar novas playlists com nome customizadoUniversidade: UFPB - Centro de Informática



### 2. Classes e Objetos- **Read:** Visualizar detalhes e listar faixas

- Modelo de dominio coerente com responsabilidades bem definidas

- Uso apropriado de instancias e relacoes- **Update:** Adicionar ou remover faixasAutor: Matheus da Silva Nunes

- Exemplo: Track, Playlist, MediaPlayer, Equalizer

- **Delete:** Remover playlists completas

### 3. Heranca & Polimorfismo

- Hierarquia: MediaPlayer (abstrato) -> MP3Player (concreto)Matrícula: 20240011024

- Metodos virtuais puros para interface polimorfica

- Exemplo: virtual bool play() = 0;### 4. Hierarquia de Classes Implementada



### 4. Composicao vs Heranca- **MediaPlayer:** Classe abstrata base com métodos virtuais puros# MP3 Player - Programação Orientada a Objetos

- MP3Player contem Equalizer (composicao)

- Playlist contem vector de Tracks (composicao)- **MP3Player:** Implementação concreta do player

- Justificativa: relacao "tem-um" ao inves de "e-um"

- **Track:** Representa faixas de música com metadados![C++](https://img.shields.io/badge/C++-17-blue.svg)

### 5. Polimorfismo Dinamico

- Uso de ponteiros polimorficos para MediaPlayer- **Playlist:** Gerencia coleções de tracks![CMake](https://img.shields.io/badge/CMake-3.16+-green.svg)

- Ligacao tardia atraves de metodos virtuais

- Exemplo: std::unique_ptr<MediaPlayer> player;- **Equalizer:** Processamento de áudio (3 bandas: LOW/MID/HIGH)![License](https://img.shields.io/badge/License-Academic-yellow.svg)



### 6. Gerenciamento de Recursos- Demonstração de **composição**: MP3Player contém Equalizer

- RAII para gerenciamento automatico de memoria

- Smart pointers: std::unique_ptr, std::shared_ptr## 📖 Sobre o Projeto

- Nenhum uso de new/delete manual

### 5. Persistência em JSON

### 7. Templates e STL

- Containers STL: std::vector, std::map, std::optional- Salvar playlists completas em arquivos JSONEste é um projeto acadêmico completo de um **MP3 Player** desenvolvido em **C++** seguindo rigorosamente os princípios de **Programação Orientada a Objetos**. O projeto demonstra de forma clara e justificável todos os conceitos fundamentais de OOP, utilizando práticas modernas da linguagem C++17.

- Smart pointers: std::unique_ptr<T>, std::shared_ptr<T>

- Exemplo: DirectoryScanner<T> template class- Carregar playlists de arquivos JSON



### 8. Sobrecarga de Operadores- Preservação de metadados e ordenação### 🎯 Objetivos

- Track: operator== para comparacao

- Track: operator< para ordenacao

- Exemplo: bool Track::operator==(const Track& other) const

### 6. Interface CLI Funcional- Demonstrar **abstração e encapsulamento** através de interfaces bem definidas

### 9. Tratamento de Excecoes

- try-catch em operacoes criticas- Menu interativo com todas as funcionalidades- Implementar **herança e polimorfismo** com hierarquias coerentes

- Excecoes para erros de arquivo e validacao

- Mensagens de erro apropriadas ao usuario- Demonstração completa de todos os requisitos- Aplicar **composição vs herança** com justificativas técnicas



### 10. Documentacao Tecnica- Interface profissional e intuitiva- Utilizar **templates e STL** de forma extensiva e apropriada

- Diagramas UML de classes completos

- README com justificativas de design- Implementar **gerenciamento moderno de recursos** (RAII, smart pointers)

- Comentarios em codigo quando necessario

## Conceitos de POO Demonstrados- Aplicar **tratamento de exceções** robusto

## Estrutura do Projeto

- Documentar decisões arquiteturais com **UML** e relatórios técnicos

```

POOMP3/O projeto implementa explicitamente os 10 conceitos exigidos:

├── include/              # Headers (.h)

│   ├── MediaPlayer.h     # Classe abstrata base## 🏗️ Arquitetura

│   ├── MP3Player.h       # Player concreto

│   ├── Track.h           # Faixas de musica### 1. Abstração & Encapsulamento

│   ├── Playlist.h        # Gerenciador de playlists

│   ├── Equalizer.h       # Equalizacao de audio- Interfaces claras separando .h e .cpp### Principais Componentes

│   └── PlaylistPersistence.h  # Persistencia JSON

│- Campos privados com getters/setters validados

├── src/                  # Implementacoes (.cpp)

│   ├── MediaPlayer.cpp- Exemplo: classe Track com validação de metadados```

│   ├── MP3Player.cpp

│   ├── Track.cpp📦 MP3Player

│   ├── Playlist.cpp

│   ├── Equalizer.cpp### 2. Classes e Objetos├── 🎵 MediaPlayer (Abstract Base)

│   └── PlaylistPersistence.cpp

│- Modelo de domínio coerente com responsabilidades bem definidas│   └── MP3Player (Concrete Implementation)

├── design/               # Documentacao de arquitetura

│   ├── README.md         # Justificativas de design- Uso apropriado de instâncias e relações├── 🎶 Track (Domain Model)

│   ├── uml_class_diagram.puml  # Diagrama UML

│   └── *.h               # Copias dos headers- Exemplo: Track, Playlist, MediaPlayer, Equalizer├── 📂 Playlist (Collection Management)

│

├── mp3_player_functional.cpp  # Aplicacao principal├── 🎛️ Equalizer (Audio Processing)

├── cli_test.cpp          # Testes CLI

├── CMakeLists.txt        # Build system### 3. Herança & Polimorfismo├── 💾 PlaylistPersistence (Storage Interface)

├── README.md             # Este arquivo

└── LICENSE               # Licenca do projeto- Hierarquia: MediaPlayer (abstrato) -> MP3Player (concreto)│   └── JsonPlaylistPersistence (JSON Implementation)

```

- Métodos virtuais puros para interface polimórfica├── 📁 DirectoryScanner<T> (Template-based File Discovery)

## Compilacao e Execucao

- Exemplo: `virtual bool play() = 0;`├── 🎮 MP3PlayerApp (Application Facade)

### Requisitos

- C++17 ou superior└── 💻 CLI (Command Line Interface)

- g++ ou compilador compativel

- Sistema: Windows/Linux### 4. Composição vs Herança```



### Compilar- MP3Player **contém** Equalizer (composição)



Aplicacao Principal:- Playlist **contém** vector de Tracks (composição)### Conceitos OOP Demonstrados

```bash

g++ -std=c++17 -Wall -Wextra -Iinclude \- Justificativa: relação "tem-um" ao invés de "é-um"

    src/Track.cpp \

    src/Playlist.cpp \| Conceito | Implementação | Localização |

    src/MediaPlayer.cpp \

    src/MP3Player.cpp \### 5. Polimorfismo Dinâmico|----------|---------------|-------------|

    src/Equalizer.cpp \

    src/PlaylistPersistence.cpp \- Uso de ponteiros polimórficos para MediaPlayer| **Abstração** | MediaPlayer interface abstrata | `include/MediaPlayer.h` |

    mp3_player_functional.cpp \

    -o mp3_player.exe- Ligação tardia através de métodos virtuais| **Encapsulamento** | Campos privados com getters/setters | `include/Track.h` |

```

- Exemplo: `std::unique_ptr<MediaPlayer> player;`| **Herança** | MP3Player ← MediaPlayer | `include/MP3Player.h` |

Testes CLI:

```bash| **Polimorfismo** | Métodos virtuais e interfaces | `include/PlaylistPersistence.h` |

g++ -std=c++17 -Wall -Wextra -Iinclude \

    src/Track.cpp \### 6. Gerenciamento de Recursos| **Composição** | MP3Player contém Equalizer | `include/MP3Player.h:15` |

    src/Playlist.cpp \

    src/MediaPlayer.cpp \- RAII para gerenciamento automático de memória| **Templates** | DirectoryScanner<FileFilter> | `include/DirectoryScanner.h` |

    cli_test.cpp \

    -o cli_test.exe- Smart pointers: `std::unique_ptr`, `std::shared_ptr`| **Smart Pointers** | unique_ptr, shared_ptr em todo projeto | Todos os headers |

```

- Nenhum uso de new/delete manual| **Exceções** | Hierarquia JsonException | `include/PlaylistPersistence.h:67` |

### Executar

| **Operadores** | Track::operator<, Playlist::operator[] | `include/Track.h:45`, `include/Playlist.h:82` |

Aplicacao Principal:

```bash### 7. Templates e STL| **STL** | vector, map, set, optional | Extensivamente |

./mp3_player.exe

```- Containers STL: `std::vector`, `std::map`, `std::optional`



Testes:- Smart pointers: `std::unique_ptr<T>`, `std::shared_ptr<T>`## 🚀 Build e Instalação

```bash

./cli_test.exe- Exemplo: `DirectoryScanner<T>` template class

```

### Pré-requisitos

## Uso da Aplicacao

### 8. Sobrecarga de Operadores

A aplicacao apresenta um menu interativo com as seguintes opcoes:

- Track: `operator==` para comparação- **C++17** compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

```

============================================================- Track: `operator<` para ordenação- **CMake 3.16+**

     *** FUNCTIONAL MP3 PLAYER - ALL FEATURES DEMO ***      

============================================================- Exemplo: `bool Track::operator==(const Track& other) const`- **Git** para clone do repositório



>> MAIN MENU:

  1. [Scan] Directory for Music Files

  2. [Play] Playback Controls (Play/Pause/Stop/Seek/Volume)### 9. Tratamento de Exceções### Opcional

  3. [List] Playlist Management (CRUD)

  4. [EQ]   Equalizer Settings- try-catch em operações críticas- **Qt6** para futuro suporte GUI

  5. [Save] Save/Load Playlist (JSON)

  6. [Info] Show Current Status- Exceções para erros de arquivo e validação- **Audio libraries** (PortAudio, libsndfile) para playback real

  0. [Exit] Exit

```- Mensagens de erro apropriadas ao usuário



### Exemplo de Uso### Compilação



1. Escanear diretorio (opcao 1): Cria tracks de exemplo### 10. Documentação Técnica

2. Criar playlist (opcao 3 > 1): Define nome e adiciona tracks

3. Reproduzir (opcao 2 > 1): Inicia reproducao- Diagramas UML de classes completos```bash

4. Ajustar volume (opcao 2 > 6): Define volume 0-100%

5. Configurar equalizer (opcao 4): Ajustar bandas LOW/MID/HIGH- README com justificativas de design# Clone o repositório

6. Salvar playlist (opcao 5 > 1): Persistir em arquivo JSON

7. Sair (opcao 0): Encerrar aplicacao- Comentários em código quando necessáriogit clone <repository-url>



## Decisoes de Arquiteturacd POOMP3



### 1. Padrao de Design: Composicao sobre Heranca## Estrutura do Projeto

- Decisao: MP3Player contem Equalizer ao inves de herdar

- Justificativa: Relacao "tem-um" e mais apropriada que "e-um"# Criar diretório de build

- Beneficio: Maior flexibilidade para trocar implementacoes

```mkdir build && cd build

### 2. Smart Pointers sobre Ponteiros Raw

- Decisao: Uso exclusivo de std::unique_ptr e std::shared_ptrPOOMP3/

- Justificativa: RAII garante gerenciamento automatico de memoria

- Beneficio: Prevencao de memory leaks e dangling pointers├── include/              # Headers (.h)# Configurar com CMake



### 3. Classe Abstrata MediaPlayer│   ├── MediaPlayer.h     # Classe abstrata basecmake ..

- Decisao: Interface pura com metodos virtuais

- Justificativa: Permite polimorfismo e extensibilidade│   ├── MP3Player.h       # Player concreto

- Beneficio: Facil adicionar novos tipos de players (WAV, OGG)

│   ├── Track.h           # Faixas de música# Compilar

### 4. STL Containers

- Decisao: std::vector para tracks, std::optional para valores opcionais│   ├── Playlist.h        # Gerenciador de playlistscmake --build .

- Justificativa: Performance, seguranca e idiomatico em C++

- Beneficio: Codigo mais limpo e menos propenso a erros│   ├── Equalizer.h       # Equalização de áudio



### 5. Separacao Interface/Implementacao│   └── PlaylistPersistence.h  # Persistência JSON# Executar teste de headers

- Decisao: Headers (.h) separados de implementacoes (.cpp)

- Justificativa: Boa pratica de engenharia de software│./header_test

- Beneficio: Melhor organizacao e tempo de compilacao

├── src/                  # Implementações (.cpp)```

## Caracteristicas Tecnicas

│   ├── MediaPlayer.cpp

- Linguagem: C++17

- Paradigma: Orientado a Objetos│   ├── MP3Player.cpp### Estrutura de Diretórios

- Padroes: RAII, Composition, Factory, Interface Segregation

- Bibliotecas: STL (Standard Template Library)│   ├── Track.cpp

- Build System: CMake compativel

- Codificacao: UTF-8 sem BOM│   ├── Playlist.cpp```

- Estilo: Modern C++ best practices

│   ├── Equalizer.cppPOOMP3/

## Conformidade com Especificacao

│   └── PlaylistPersistence.cpp├── include/           # Headers (.h)

### Etapa 1: Arquitetura (Concluida)

- [x] Arquivos .h das principais classes││   ├── MediaPlayer.h

- [x] UML de classes (design/uml_class_diagram.puml)

- [x] README do design├── design/               # Documentação de arquitetura│   ├── Track.h

- [x] CMakeLists.txt funcional

- [x] Relatorio de arquitetura│   ├── README.md         # Justificativas de design│   ├── MP3Player.h



### Etapa 2: CLI Funcional (Concluida)│   ├── uml_class_diagram.puml  # Diagrama UML│   ├── Playlist.h

- [x] Build funcional

- [x] Executavel CLI demonstrando operacoes-chave│   └── *.h               # Cópias dos headers│   ├── Equalizer.h

- [x] Smart pointers implementados

- [x] STL utilizado adequadamente││   └── ...

- [x] Excecoes tratadas

├── mp3_player_functional.cpp  # Aplicação principal├── src/              # Implementações (.cpp) - Etapa 2

### Etapa 3: Entrega Final (Em Andamento)

- [x] Aplicacao CLI completa├── cli_test.cpp          # Testes CLI├── design/           # Documentação de design

- [x] Codigo organizado

- [x] Documentacao tecnica├── CMakeLists.txt        # Build system│   ├── README.md

- [ ] Interface grafica (Qt/JUCE) - Opcional

- [ ] Video demonstrativo - Pendente├── README.md             # Este arquivo│   ├── uml_class_diagram.puml

- [ ] Tag GitHub v3-final - Pendente

└── LICENSE               # Licença do projeto│   ├── Relatorio_Tecnico_Etapa1.md

## Testes Implementados

```│   └── header_test.cpp

O arquivo cli_test.cpp demonstra:

├── CMakeLists.txt    # Build configuration

1. Criacao de Tracks: Instanciacao e configuracao

2. Gerenciamento de Playlists: Adicionar, remover, navegar## Compilação e Execução└── README.md         # Este arquivo

3. Navegacao: Next, previous, current track

4. Comparacao: Operator overloading```

5. Busca: Search by artist/title

6. Smart Pointers: Reference counting### Requisitos

7. Excecoes: Try-catch error handling

- C++17 ou superior## 📋 Funcionalidades (Planejadas)

Saida esperada:

```- g++ ou compilador compatível

=== MP3 PLAYER CLI TEST - CORE FUNCTIONALITY ===

- Sistema: Windows/Linux### Etapa 1 ✅ - Arquitetura e Headers

1. Testing Track Creation:

   [OK] Track 1: Bohemian Rhapsody by Queen- [x] Classes principais definidas

   [OK] Track 2: Hotel California by Eagles

### Compilar- [x] Interfaces abstratas implementadas

2. Testing Playlist Management:

   [OK] Playlist: My Favorites- [x] UML de classes documentado

   [OK] Track count: 2

   [OK] Total duration: 0 seconds**Aplicação Principal:**- [x] CMake configurado



=== CORE FUNCTIONALITY TESTS PASSED! ===```bash- [x] Relatório técnico completo

```

g++ -std=c++17 -Wall -Wextra -Iinclude \

## Licenca

    src/Track.cpp \### Etapa 2 🔄 - Implementação Core

Este e um projeto academico desenvolvido para fins educacionais.  

Licenciado sob Academic Use License.    src/Playlist.cpp \- [ ] Implementação de todos os métodos



## Autor    src/MediaPlayer.cpp \- [ ] Sistema de persistência JSON



Matheus da Silva Nunes      src/MP3Player.cpp \- [ ] Scanner de diretórios funcional

Matricula: 20240011024  

UFPB - Centro de Informatica      src/Equalizer.cpp \- [ ] CLI interativa completa

Disciplina: Programacao Orientada a Objetos (C++)  

Professor: Dr. Bidu    src/PlaylistPersistence.cpp \- [ ] Testes unitários



## Refer    mp3_player_functional.cpp \



encias    -o mp3_player.exe### Etapa 3 📅 - Interface e Finalização



- Especificacao do Trabalho Final - Disciplina POO```- [ ] Interface gráfica Qt6

- C++ Primer (5th Edition) - Stanley B. Lippman

- Effective Modern C++ - Scott Meyers- [ ] Integração com bibliotecas de áudio

- Design Patterns - Gang of Four

- C++ Core Guidelines - Bjarne Stroustrup**Testes CLI:**- [ ] Player funcional completo


```bash- [ ] Documentação final

g++ -std=c++17 -Wall -Wextra -Iinclude \

    src/Track.cpp \## 🎮 Uso Planejado (CLI)

    src/Playlist.cpp \

    src/MediaPlayer.cpp \```bash

    cli_test.cpp \# Criar playlist

    -o cli_test.exeplaylist create "My Favorites"

```

# Adicionar músicas

### Executaradd track "/path/to/song.mp3"

add directory "/path/to/music/folder"

**Aplicação Principal:**

```bash# Controlar playback

./mp3_player.exeplay

```pause

stop

**Testes:**next

```bashprevious

./cli_test.exe

```# Configurar equalizer

equalizer preset rock

## Uso da Aplicaçãoequalizer set low 2.5 mid -1.0 high 3.0



A aplicação apresenta um menu interativo com as seguintes opções:# Gerenciar playlists

playlist save "My Favorites"

```playlist load "Rock Collection"

============================================================playlist list

     *** FUNCTIONAL MP3 PLAYER - ALL FEATURES DEMO ***      

============================================================# Scanner de arquivos

scan "/music/library" --recursive

>> MAIN MENU:```

  1. [Scan] Directory for Music Files

  2. [Play] Playback Controls (Play/Pause/Stop/Seek/Volume)## 🎨 Design Patterns Utilizados

  3. [List] Playlist Management (CRUD)

  4. [EQ]   Equalizer Settings- **Factory Pattern**: `Equalizer::createRock()`, `Track::createFromFile()`

  5. [Save] Save/Load Playlist (JSON)- **Facade Pattern**: `MP3PlayerApp` como interface simplificada

  6. [Info] Show Current Status- **Template Method**: `MediaPlayer::playFromBeginning()`

  0. [Exit] Exit- **Strategy Pattern**: `DirectoryScanner<FileFilter>`

```- **Exception Hierarchy**: Exceções especializadas para diferentes erros



### Exemplo de Uso## 🔧 Características Técnicas



1. **Escanear diretório** (opção 1): Cria tracks de exemplo### Modernas C++17

2. **Criar playlist** (opção 3 > 1): Define nome e adiciona tracks- **Smart Pointers**: Gerenciamento automático de memória

3. **Reproduzir** (opção 2 > 1): Inicia reprodução- **RAII**: Todos os recursos gerenciados por constructors/destructors

4. **Ajustar volume** (opção 2 > 6): Define volume 0-100%- **Move Semantics**: Transferência eficiente de recursos

5. **Configurar equalizer** (opção 4): Ajustar bandas LOW/MID/HIGH- **std::optional**: Valores opcionais type-safe

6. **Salvar playlist** (opção 5 > 1): Persistir em arquivo JSON- **Range-based loops**: Sintaxe moderna de iteração

7. **Sair** (opção 0): Encerrar aplicação- **Uniform initialization**: Sintaxe consistente



## Decisões de Arquitetura### STL Integration

- **Containers**: `vector`, `map`, `set`, `array`

### 1. Padrão de Design: Composição sobre Herança- **Algorithms**: `sort`, `find_if`, `for_each`

- **Decisão:** MP3Player contém Equalizer ao invés de herdar- **Iterators**: Suporte completo para range-based loops

- **Justificativa:** Relação "tem-um" é mais apropriada que "é-um"- **Functional**: `function`, lambdas para callbacks

- **Benefício:** Maior flexibilidade para trocar implementações

## 📊 Métricas de Qualidade

### 2. Smart Pointers sobre Ponteiros Raw

- **Decisão:** Uso exclusivo de std::unique_ptr e std::shared_ptr- **Cobertura de Conceitos OOP**: 100%

- **Justificativa:** RAII garante gerenciamento automático de memória- **Princípios SOLID**: Totalmente aplicados

- **Benefício:** Prevenção de memory leaks e dangling pointers- **Exception Safety**: Strong guarantee

- **Memory Safety**: Sem raw pointers de propriedade

### 3. Classe Abstrata MediaPlayer- **const Correctness**: Métodos imutáveis marcados como const

- **Decisão:** Interface pura com métodos virtuais

- **Justificativa:** Permite polimorfismo e extensibilidade## 📚 Documentação

- **Benefício:** Fácil adicionar novos tipos de players (WAV, OGG)

- **[Design README](design/README.md)**: Decisões arquiteturais detalhadas

### 4. STL Containers- **[Relatório Técnico](design/Relatorio_Tecnico_Etapa1.md)**: Análise completa da arquitetura

- **Decisão:** std::vector para tracks, std::optional para valores opcionais- **[UML Diagram](design/uml_class_diagram.puml)**: Diagrama de classes visual

- **Justificativa:** Performance, segurança e idiomático em C++- **Headers**: Documentação inline em cada arquivo

- **Benefício:** Código mais limpo e menos propenso a erros

## 🧪 Testes

### 5. Separação Interface/Implementação

- **Decisão:** Headers (.h) separados de implementações (.cpp)### Teste de Compilação

- **Justificativa:** Boa prática de engenharia de software```bash

- **Benefício:** Melhor organização e tempo de compilação./header_test  # Valida que todos os headers compilam corretamente

```

## Características Técnicas

### Futuros Testes

- **Linguagem:** C++17- **Unit Tests**: Google Test framework

- **Paradigma:** Orientado a Objetos- **Integration Tests**: Cenários completos

- **Padrões:** RAII, Composition, Factory, Interface Segregation- **Memory Tests**: Valgrind/AddressSanitizer

- **Bibliotecas:** STL (Standard Template Library)- **Performance Tests**: Benchmarking

- **Build System:** CMake compatível

- **Codificação:** UTF-8 sem BOM## 🤝 Contribuição

- **Estilo:** Modern C++ best practices

Este é um projeto acadêmico individual, mas sugestões e melhorias são bem-vindas:

## Conformidade com Especificação

1. Fork o projeto

### Etapa 1: Arquitetura (Concluída)2. Crie uma branch para feature (`git checkout -b feature/AmazingFeature`)

- [x] Arquivos .h das principais classes3. Commit suas mudanças (`git commit -m 'Add some AmazingFeature'`)

- [x] UML de classes (design/uml_class_diagram.puml)4. Push para a branch (`git push origin feature/AmazingFeature`)

- [x] README do design5. Abra um Pull Request

- [x] CMakeLists.txt funcional

- [x] Relatório de arquitetura## 📄 Licença



### Etapa 2: CLI Funcional (Concluída)Este projeto é desenvolvido para fins acadêmicos na disciplina de Programação Orientada a Objetos.

- [x] Build funcional

- [x] Executável CLI demonstrando operações-chave## 👨‍💻 Autor

- [x] Smart pointers implementados

- [x] STL utilizado adequadamente**Projeto POO - MP3 Player**

- [x] Exceções tratadas- Universidade: UFPB

- Disciplina: Programação Orientada a Objetos

### Etapa 3: Entrega Final (Em Andamento)- Período: 2025.1

- [x] Aplicação CLI completa

- [x] Código organizado## 🙏 Agradecimentos

- [x] Documentação técnica

- [ ] Interface gráfica (Qt/JUCE) - Opcional- Professor da disciplina pelas especificações detalhadas

- [ ] Vídeo demonstrativo - Pendente- Comunidade C++ pelas melhores práticas

- [ ] Tag GitHub v3-final - Pendente- Documentação oficial do C++17

- Exemplos e tutoriais da comunidade open source

## Testes Implementados

---

O arquivo `cli_test.cpp` demonstra:

**Status do Projeto**: 🟢 Etapa 1 Completa - Arquitetura e Headers validados

1. **Criação de Tracks:** Instanciação e configuração

2. **Gerenciamento de Playlists:** Adicionar, remover, navegarPara mais detalhes técnicos, consulte a [documentação de design](design/README.md).

3. **Navegação:** Next, previous, current track
4. **Comparação:** Operator overloading
5. **Busca:** Search by artist/title
6. **Smart Pointers:** Reference counting
7. **Exceções:** Try-catch error handling

Saída esperada:
```
=== MP3 PLAYER CLI TEST - CORE FUNCTIONALITY ===

1. Testing Track Creation:
   [OK] Track 1: Bohemian Rhapsody by Queen
   [OK] Track 2: Hotel California by Eagles

2. Testing Playlist Management:
   [OK] Playlist: My Favorites
   [OK] Track count: 2
   [OK] Total duration: 600 seconds

=== CORE FUNCTIONALITY TESTS PASSED! ===
```

## Licença

Este é um projeto acadêmico desenvolvido para fins educacionais.  
Licenciado sob Academic Use License.

## Autor

**Matheus da Silva Nunes**  
Matrícula: 20240011024  
UFPB - Centro de Informática  
Disciplina: Programação Orientada a Objetos (C++)  
Professor: Dr. Bidu

## Referências

- Especificação do Trabalho Final - Disciplina POO
- C++ Primer (5th Edition) - Stanley B. Lippman
- Effective Modern C++ - Scott Meyers
- Design Patterns - Gang of Four
- C++ Core Guidelines - Bjarne Stroustrup
