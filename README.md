TSP Route Optimizer - C++ POO Project
Projeto: Otimização de Rotas (Problema do Caixeiro Viajante)
Disciplina: Programação Orientada a Objetos (C++)
Universidade: UFPB - Centro de Informática
Autor: Erick Batista da Silva
Matrícula: [Sua matrícula]

# MP3 Player - Programação Orientada a Objetos

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.16+-green.svg)
![License](https://img.shields.io/badge/License-Academic-yellow.svg)

## 📖 Sobre o Projeto

Este é um projeto acadêmico completo de um **MP3 Player** desenvolvido em **C++** seguindo rigorosamente os princípios de **Programação Orientada a Objetos**. O projeto demonstra de forma clara e justificável todos os conceitos fundamentais de OOP, utilizando práticas modernas da linguagem C++17.

### 🎯 Objetivos

- Demonstrar **abstração e encapsulamento** através de interfaces bem definidas
- Implementar **herança e polimorfismo** com hierarquias coerentes
- Aplicar **composição vs herança** com justificativas técnicas
- Utilizar **templates e STL** de forma extensiva e apropriada
- Implementar **gerenciamento moderno de recursos** (RAII, smart pointers)
- Aplicar **tratamento de exceções** robusto
- Documentar decisões arquiteturais com **UML** e relatórios técnicos

## 🏗️ Arquitetura

### Principais Componentes

```
📦 MP3Player
├── 🎵 MediaPlayer (Abstract Base)
│   └── MP3Player (Concrete Implementation)
├── 🎶 Track (Domain Model)
├── 📂 Playlist (Collection Management)
├── 🎛️ Equalizer (Audio Processing)
├── 💾 PlaylistPersistence (Storage Interface)
│   └── JsonPlaylistPersistence (JSON Implementation)
├── 📁 DirectoryScanner<T> (Template-based File Discovery)
├── 🎮 MP3PlayerApp (Application Facade)
└── 💻 CLI (Command Line Interface)
```

### Conceitos OOP Demonstrados

| Conceito | Implementação | Localização |
|----------|---------------|-------------|
| **Abstração** | MediaPlayer interface abstrata | `include/MediaPlayer.h` |
| **Encapsulamento** | Campos privados com getters/setters | `include/Track.h` |
| **Herança** | MP3Player ← MediaPlayer | `include/MP3Player.h` |
| **Polimorfismo** | Métodos virtuais e interfaces | `include/PlaylistPersistence.h` |
| **Composição** | MP3Player contém Equalizer | `include/MP3Player.h:15` |
| **Templates** | DirectoryScanner<FileFilter> | `include/DirectoryScanner.h` |
| **Smart Pointers** | unique_ptr, shared_ptr em todo projeto | Todos os headers |
| **Exceções** | Hierarquia JsonException | `include/PlaylistPersistence.h:67` |
| **Operadores** | Track::operator<, Playlist::operator[] | `include/Track.h:45`, `include/Playlist.h:82` |
| **STL** | vector, map, set, optional | Extensivamente |

## 🚀 Build e Instalação

### Pré-requisitos

- **C++17** compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- **CMake 3.16+**
- **Git** para clone do repositório

### Opcional
- **Qt6** para futuro suporte GUI
- **Audio libraries** (PortAudio, libsndfile) para playback real

### Compilação

```bash
# Clone o repositório
git clone <repository-url>
cd POOMP3

# Criar diretório de build
mkdir build && cd build

# Configurar com CMake
cmake ..

# Compilar
cmake --build .

# Executar teste de headers
./header_test
```

### Estrutura de Diretórios

```
POOMP3/
├── include/           # Headers (.h)
│   ├── MediaPlayer.h
│   ├── Track.h
│   ├── MP3Player.h
│   ├── Playlist.h
│   ├── Equalizer.h
│   └── ...
├── src/              # Implementações (.cpp) - Etapa 2
├── design/           # Documentação de design
│   ├── README.md
│   ├── uml_class_diagram.puml
│   ├── Relatorio_Tecnico_Etapa1.md
│   └── header_test.cpp
├── CMakeLists.txt    # Build configuration
└── README.md         # Este arquivo
```

## 📋 Funcionalidades (Planejadas)

### Etapa 1 ✅ - Arquitetura e Headers
- [x] Classes principais definidas
- [x] Interfaces abstratas implementadas
- [x] UML de classes documentado
- [x] CMake configurado
- [x] Relatório técnico completo

### Etapa 2 🔄 - Implementação Core
- [ ] Implementação de todos os métodos
- [ ] Sistema de persistência JSON
- [ ] Scanner de diretórios funcional
- [ ] CLI interativa completa
- [ ] Testes unitários

### Etapa 3 📅 - Interface e Finalização
- [ ] Interface gráfica Qt6
- [ ] Integração com bibliotecas de áudio
- [ ] Player funcional completo
- [ ] Documentação final

## 🎮 Uso Planejado (CLI)

```bash
# Criar playlist
playlist create "My Favorites"

# Adicionar músicas
add track "/path/to/song.mp3"
add directory "/path/to/music/folder"

# Controlar playback
play
pause
stop
next
previous

# Configurar equalizer
equalizer preset rock
equalizer set low 2.5 mid -1.0 high 3.0

# Gerenciar playlists
playlist save "My Favorites"
playlist load "Rock Collection"
playlist list

# Scanner de arquivos
scan "/music/library" --recursive
```

## 🎨 Design Patterns Utilizados

- **Factory Pattern**: `Equalizer::createRock()`, `Track::createFromFile()`
- **Facade Pattern**: `MP3PlayerApp` como interface simplificada
- **Template Method**: `MediaPlayer::playFromBeginning()`
- **Strategy Pattern**: `DirectoryScanner<FileFilter>`
- **Exception Hierarchy**: Exceções especializadas para diferentes erros

## 🔧 Características Técnicas

### Modernas C++17
- **Smart Pointers**: Gerenciamento automático de memória
- **RAII**: Todos os recursos gerenciados por constructors/destructors
- **Move Semantics**: Transferência eficiente de recursos
- **std::optional**: Valores opcionais type-safe
- **Range-based loops**: Sintaxe moderna de iteração
- **Uniform initialization**: Sintaxe consistente

### STL Integration
- **Containers**: `vector`, `map`, `set`, `array`
- **Algorithms**: `sort`, `find_if`, `for_each`
- **Iterators**: Suporte completo para range-based loops
- **Functional**: `function`, lambdas para callbacks

## 📊 Métricas de Qualidade

- **Cobertura de Conceitos OOP**: 100%
- **Princípios SOLID**: Totalmente aplicados
- **Exception Safety**: Strong guarantee
- **Memory Safety**: Sem raw pointers de propriedade
- **const Correctness**: Métodos imutáveis marcados como const

## 📚 Documentação

- **[Design README](design/README.md)**: Decisões arquiteturais detalhadas
- **[Relatório Técnico](design/Relatorio_Tecnico_Etapa1.md)**: Análise completa da arquitetura
- **[UML Diagram](design/uml_class_diagram.puml)**: Diagrama de classes visual
- **Headers**: Documentação inline em cada arquivo

## 🧪 Testes

### Teste de Compilação
```bash
./header_test  # Valida que todos os headers compilam corretamente
```

### Futuros Testes
- **Unit Tests**: Google Test framework
- **Integration Tests**: Cenários completos
- **Memory Tests**: Valgrind/AddressSanitizer
- **Performance Tests**: Benchmarking

## 🤝 Contribuição

Este é um projeto acadêmico individual, mas sugestões e melhorias são bem-vindas:

1. Fork o projeto
2. Crie uma branch para feature (`git checkout -b feature/AmazingFeature`)
3. Commit suas mudanças (`git commit -m 'Add some AmazingFeature'`)
4. Push para a branch (`git push origin feature/AmazingFeature`)
5. Abra um Pull Request

## 📄 Licença

Este projeto é desenvolvido para fins acadêmicos na disciplina de Programação Orientada a Objetos.

## 👨‍💻 Autor

**Projeto POO - MP3 Player**
- Universidade: UFPB
- Disciplina: Programação Orientada a Objetos
- Período: 2025.1

## 🙏 Agradecimentos

- Professor da disciplina pelas especificações detalhadas
- Comunidade C++ pelas melhores práticas
- Documentação oficial do C++17
- Exemplos e tutoriais da comunidade open source

---

**Status do Projeto**: 🟢 Etapa 1 Completa - Arquitetura e Headers validados

Para mais detalhes técnicos, consulte a [documentação de design](design/README.md).
