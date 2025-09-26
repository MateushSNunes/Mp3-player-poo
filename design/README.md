# MP3 Player - Design Documentation

## Project Overview

This MP3 Player project demonstrates comprehensive Object-Oriented Programming concepts in C++ through a complete media player application. The architecture follows SOLID principles and modern C++ best practices.

## Architecture Decisions

### 1. Abstração & Encapsulamento

**MediaPlayer Abstract Base Class** (`include/MediaPlayer.h`)
- Defines pure virtual interface for all media players
- Encapsulates common state (volume, position, playing status)
- Protected members allow derived classes controlled access
- Public interface hides implementation details

**Track Class** (`include/Track.h`)
- Private fields with controlled access through getters/setters
- Validation in setters prevents invalid state
- Const methods for read-only operations
- Clear separation of interface and implementation

### 2. Herança & Polimorfismo

**MediaPlayer → MP3Player Hierarchy**
- `MediaPlayer` as abstract base with pure virtual methods
- `MP3Player` provides concrete implementation
- Virtual destructor ensures proper cleanup
- Polymorphic behavior through virtual method calls

**PlaylistPersistence → JsonPlaylistPersistence**
- Abstract persistence interface allows multiple storage formats
- JSON implementation demonstrates concrete behavior
- Virtual methods enable runtime polymorphism
- Future extensibility for XML, binary formats

### 3. Composição vs Herança

**Composition Examples:**
- `MP3Player` **contains** `Equalizer` (has-a relationship)
- `Playlist` **contains** `Track` objects via smart pointers
- `MP3PlayerApp` **aggregates** all components

**Design Rationale:**
- Composition chosen over inheritance for loose coupling
- Components can be replaced/modified independently
- Follows "favor composition over inheritance" principle
- Enables runtime configuration and dependency injection

### 4. Polimorfismo Dinâmico

**Runtime Polymorphism Implementation:**
- Virtual method dispatch in `MediaPlayer` hierarchy
- `PlaylistPersistence` interface with multiple implementations
- Smart pointer usage with polymorphic types
- Dynamic behavior based on concrete type instantiation

### 5. Gerenciamento de Recursos

**RAII and Smart Pointers:**
- `std::unique_ptr` for exclusive ownership (Equalizer in MP3Player)
- `std::shared_ptr` for shared ownership (Track objects)
- Automatic cleanup prevents memory leaks
- Exception safety through RAII pattern

**Resource Management Examples:**
```cpp
std::unique_ptr<Equalizer> equalizer;          // Exclusive ownership
std::shared_ptr<Track> tracks;                 // Shared ownership
std::unique_ptr<PlaylistPersistence> persistence; // Interface pointer
```

### 6. Templates e STL

**Template Usage:**
- `DirectoryScanner<FileFilter>` - Generic file filtering
- Template factory functions for common configurations
- STL containers throughout: `std::vector`, `std::map`, `std::set`
- `std::optional` for optional return values

**STL Integration:**
- Iterator support in Playlist for range-based loops
- Algorithm usage for sorting and searching
- Container adaptors for specialized behavior

### 7. Sobrecarga de Operadores

**Track Class Operators:**
```cpp
bool operator==(const Track& other) const;    // Equality comparison
bool operator<(const Track& other) const;     // Sorting support
```

**Playlist Class Operators:**
```cpp
std::shared_ptr<Track> operator[](size_t index);  // Subscript access
Playlist& operator+=(std::shared_ptr<Track>);     // Add track
```

### 8. Tratamento de Exceções

**Custom Exception Hierarchy:**
- `JsonPlaylistPersistence::JsonException` base class
- `FileException` and `ParseException` derived classes
- `DirectoryScanner::ScanException` for file system errors
- Proper exception handling in public interfaces

### 9. Design Patterns Applied

**Factory Pattern:**
- `Equalizer::createFlat()`, `createRock()` etc.
- `Track::createFromFile()` static factory
- Scanner factory functions

**Facade Pattern:**
- `MP3PlayerApp` provides simplified interface to complex subsystem
- Hides complexity of player, playlist, persistence coordination

**Template Method Pattern:**
- `MediaPlayer::playFromBeginning()` defines algorithm skeleton
- Derived classes implement specific steps

## Class Relationships

### Core Hierarchy
```
MediaPlayer (abstract)
└── MP3Player (concrete)
    └── contains Equalizer

PlaylistPersistence (abstract)
└── JsonPlaylistPersistence (concrete)

DirectoryScanner<FilterType> (template)
```

### Composition Structure
```
MP3PlayerApp
├── MP3Player
│   └── Equalizer
├── Playlist
│   └── vector<shared_ptr<Track>>
├── PlaylistPersistence
└── DirectoryScanner
```

## Memory Management Strategy

1. **Smart Pointers Only** - No raw pointers for ownership
2. **RAII Everywhere** - All resources managed by constructors/destructors
3. **Exception Safety** - Strong exception guarantee where possible
4. **Const Correctness** - Immutable operations marked const

## Modern C++ Features Used

- **C++17 Standard** - std::optional, structured bindings
- **Smart Pointers** - unique_ptr, shared_ptr
- **Move Semantics** - Move constructors and assignment
- **Range-based Loops** - Iterator support in containers
- **Lambda Functions** - Callback mechanisms
- **Auto Type Deduction** - Where type is obvious
- **Uniform Initialization** - Consistent syntax

## Build System

**CMake Configuration:**
- Modern CMake 3.16+ with target-based approach
- Interface libraries for header-only components
- Package discovery for Qt6 and audio libraries
- Cross-platform compiler configuration
- Installation and packaging support

## Extensibility Points

1. **New Media Formats** - Inherit from MediaPlayer
2. **Storage Formats** - Implement PlaylistPersistence
3. **UI Frameworks** - Add GUI components via composition
4. **Audio Effects** - Extend Equalizer or add new components
5. **File Filters** - Template specialization in DirectoryScanner

## Testing Strategy

- **Header Compilation Test** - Ensures all headers compile independently
- **Unit Test Framework** - Ready for Google Test integration
- **Integration Testing** - CLI provides manual testing interface
- **Exception Testing** - Error paths validated

This architecture demonstrates mastery of OOP principles while maintaining practical applicability and extensibility for a real-world application.