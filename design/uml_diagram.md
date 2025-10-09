# UML Class Diagram - MP3 Player System (v3.0 Final)

## Diagrama Completo de Classes

```
┌──────────────────────────────────────────────────────────────────────────┐
│                     MP3 PLAYER SYSTEM - UML DIAGRAM                       │
│                            Versão 3.0 Final                               │
└──────────────────────────────────────────────────────────────────────────┘

╔═══════════════════════════════════════════════════════════════════════╗
║                    HIERARQUIA PRINCIPAL - PLAYER                       ║
╚═══════════════════════════════════════════════════════════════════════╝

┌────────────────────────────────┐
│       MediaPlayer              │ ◄──── [ABSTRACT CLASS]
│       <<abstract>>             │
├────────────────────────────────┤
│ # currentTrack: shared_ptr<Track>│ ◄──── [PROTECTED - Herança]
│ # isPlaying: bool              │
│ # isPaused: bool               │
│ # volume: double               │
│ # currentPosition: double      │
├────────────────────────────────┤
│ + loadTrack(track): bool = 0   │ ◄──── [PURE VIRTUAL - Polimorfismo]
│ + play(): bool = 0             │
│ + pause(): bool = 0            │
│ + stop(): bool = 0             │
│ + seek(position): bool = 0     │
│ + setVolume(vol): bool         │
│ + getVolume(): double          │
│ + getCurrentPosition(): double │
│ + getIsPlaying(): bool         │
│ + playFromBeginning(): bool    │ ◄──── [TEMPLATE METHOD]
└────────────────────────────────┘
         △
         │ [HERANÇA - IS-A]
         │
┌────────────────────────────────┐
│         MP3Player              │
├────────────────────────────────┤
│ - equalizer: unique_ptr<Equalizer>│ ◄──── [COMPOSIÇÃO - HAS-A]
│ - errorCallback: function      │
│ - positionCallback: function   │
├────────────────────────────────┤
│ + MP3Player()                  │
│ + MP3Player(equalizer)         │
│ + ~MP3Player() override        │
│ + loadTrack(track): bool override│ ◄──── [OVERRIDE - Polimorfismo]
│ + play(): bool override        │
│ + pause(): bool override       │
│ + stop(): bool override        │
│ + seek(position): bool override│
│ + getEqualizer(): Equalizer*   │
│ + setEqualizer(eq): void       │
│ + setErrorCallback(cb): void   │ ◄──── [OBSERVER PATTERN]
│ + setPositionCallback(cb): void│
│ + isFormatSupported(): bool    │ ◄──── [STATIC]
└────────────────────────────────┘
         │
         │ [USA/CONTÉM]
         ▼
╔═══════════════════════════════════════════════════════════════════════╗
║                        MODELO DE DOMÍNIO                               ║
╚═══════════════════════════════════════════════════════════════════════╝

┌────────────────────────────────┐
│           Track                │
├────────────────────────────────┤
│ - filePath: string             │ ◄──── [ENCAPSULAMENTO - Private]
│ - title: string                │
│ - artist: string               │
│ - album: string                │
│ - genre: string                │
│ - year: int                    │
│ - duration: chrono::seconds    │
│ - fileSize: size_t             │
│ - format: string               │
├────────────────────────────────┤
│ + Track()                      │
│ + Track(path)                  │
│ + Track(path, title, artist, album)│
│ + getFilePath(): string const  │ ◄──── [GETTERS - const]
│ + getTitle(): string const     │
│ + getArtist(): string const    │
│ + getAlbum(): string const     │
│ + getDuration(): chrono::seconds const│
│ + setTitle(title): void        │ ◄──── [SETTERS com validação]
│ + setArtist(artist): void      │
│ + setAlbum(album): void        │
│ + setYear(year): void          │
│ + setFilePath(path): void      │
│ + operator==(other): bool      │ ◄──── [SOBRECARGA OPERADORES]
│ + operator!=(other): bool      │
│ + operator<(other): bool       │
│ + operator>(other): bool       │
│ + isValid(): bool              │
│ + getDisplayName(): string     │
│ + createFromFile(path): shared_ptr<Track>│ ◄──── [FACTORY]
└────────────────────────────────┘
         △
         │ [AGREGAÇÃO - 1:N]
         │
┌────────────────────────────────┐
│         Playlist               │
├────────────────────────────────┤
│ - name: string                 │
│ - tracks: vector<shared_ptr<Track>>│ ◄──── [COMPOSIÇÃO - contém]
│ - currentIndex: size_t         │
│ - shuffleMode: bool            │
│ - repeatMode: bool             │
│ - description: string          │
│ - creationDate: time_point     │
├────────────────────────────────┤
│ + Playlist(name)               │
│ + getName(): string const      │
│ + setName(name): void          │
│ + addTrack(track): void        │ ◄──── [CRUD - Create]
│ + removeTrack(index): bool     │ ◄──── [CRUD - Delete]
│ + getTracks(): vector const&   │ ◄──── [CRUD - Read]
│ + clear(): void                │
│ + size(): size_t const         │
│ + empty(): bool const          │
│ + getCurrentTrack(): shared_ptr<Track>│
│ + next(): shared_ptr<Track>    │
│ + previous(): shared_ptr<Track>│
│ + setShuffleMode(enable): void │
│ + setRepeatMode(enable): void  │
│ + search(predicate): vector    │ ◄──── [TEMPLATE METHOD]
│ + searchByTitle(title): vector │
│ + searchByArtist(artist): vector│
│ + sort(criteria): void         │
│ + getTotalDuration(): chrono::seconds│
│ + begin(): iterator            │ ◄──── [STL ITERATORS]
│ + end(): iterator              │
└────────────────────────────────┘

╔═══════════════════════════════════════════════════════════════════════╗
║                           COMPONENTES                                  ║
╚═══════════════════════════════════════════════════════════════════════╝

┌────────────────────────────────┐
│         Equalizer              │
├────────────────────────────────┤
│ - bands: map<Band, double>     │ ◄──── [STL - map]
│ - enabled: bool                │
│ + enum Band { LOW, MID, HIGH } │ ◄──── [ENUM CLASS]
├────────────────────────────────┤
│ + Equalizer()                  │
│ + setBandGain(band, gain): void│
│ + getBandGain(band): double    │
│ + setEnabled(enable): void     │
│ + isEnabled(): bool const      │
│ + reset(): void                │
│ + applyPreset(name): void      │
│ + toString(): string           │
│ + createFlat(): unique_ptr<Equalizer>│ ◄──── [FACTORY METHOD]
│ + createPreset(name): unique_ptr<Equalizer>│
│ + getAvailablePresets(): vector<string>│ ◄──── [STATIC]
└────────────────────────────────┘

╔═══════════════════════════════════════════════════════════════════════╗
║                          PERSISTÊNCIA                                  ║
╚═══════════════════════════════════════════════════════════════════════╝

┌────────────────────────────────┐
│   PlaylistPersistence          │
│      <<interface>>             │ ◄──── [INTERFACE ABSTRATA]
├────────────────────────────────┤
│ + savePlaylist(playlist, filename): bool = 0│ ◄──── [PURE VIRTUAL]
│ + loadPlaylist(filename): optional<Playlist> = 0│
│ + listSavedPlaylists(): vector<string> = 0│
└────────────────────────────────┘
         △
         │ [IMPLEMENTA]
         │
┌────────────────────────────────┐
│  JsonPlaylistPersistence       │
├────────────────────────────────┤
│ - defaultDirectory: string     │
├────────────────────────────────┤
│ + JsonPlaylistPersistence()    │
│ + savePlaylist(playlist, filename): bool override│
│ + loadPlaylist(filename): optional<Playlist> override│
│ + listSavedPlaylists(): vector<string> override│
│ - serializeTrack(track): string│ ◄──── [PRIVATE HELPER]
│ - deserializeTrack(json): optional<Track>│
│ - serializePlaylist(playlist): string│
│ - deserializePlaylist(json): optional<Playlist>│
└────────────────────────────────┘

╔═══════════════════════════════════════════════════════════════════════╗
║                         UTILITÁRIOS                                    ║
╚═══════════════════════════════════════════════════════════════════════╝

┌────────────────────────────────┐
│  DirectoryScanner<FileFilter>  │ ◄──── [TEMPLATE CLASS]
├────────────────────────────────┤
│ - supportedExtensions: set<string>│ ◄──── [STL - set]
│ - filter: FileFilter           │ ◄──── [TEMPLATE PARAMETER]
│ - recursive: bool              │
│ - maxDepth: size_t             │
│ - progressCallback: function   │
├────────────────────────────────┤
│ + DirectoryScanner()           │
│ + DirectoryScanner(extensions) │
│ + DirectoryScanner(extensions, filter)│
│ + setSupportedExtensions(ext): void│
│ + addSupportedExtension(ext): void│
│ + setRecursive(enable, maxDepth): void│
│ + setProgressCallback(cb): void│
│ + setFilter(filter): void      │
│ + scanDirectory(path): vector<string>│
│ + scanForTracks(path): vector<shared_ptr<Track>>│
│ + scanForTracksAsync(path): future<vector<shared_ptr<Track>>>│ ◄──── [ASYNC]
└────────────────────────────────┘

┌────────────────────────────────┐
│            CLI                 │
├────────────────────────────────┤
│ - player: unique_ptr<MP3Player>│
│ - persistence: unique_ptr<JsonPlaylistPersistence>│
│ - currentPlaylist: shared_ptr<Playlist>│
│ - savedPlaylists: vector<shared_ptr<Playlist>>│
│ - running: bool                │
├────────────────────────────────┤
│ + CLI()                        │
│ + run(): void                  │
│ - showMainMenu(): void         │
│ - scanDirectory(): void        │
│ - playbackControls(): void     │
│ - playlistManagement(): void   │ ◄──── [CRUD OPERATIONS]
│ - equalizerSettings(): void    │
│ - persistenceOperations(): void│
│ - clearScreen(): void          │
│ - printHeader(): void          │
│ - printStatus(): void          │
└────────────────────────────────┘
```

## Relacionamentos entre Classes

### Herança (IS-A)
```
MediaPlayer (abstract)
    ↑
    └── MP3Player (concrete implementation)

PlaylistPersistence (interface)
    ↑
    └── JsonPlaylistPersistence (concrete implementation)
```

### Composição (HAS-A / PART-OF)
```
MP3Player
    └── Equalizer (1:1) - ownership exclusivo (unique_ptr)

Playlist
    └── Track[] (1:N) - ownership compartilhado (shared_ptr)

CLI
    ├── MP3Player (1:1)
    ├── JsonPlaylistPersistence (1:1)
    └── Playlist (1:1 current)
│ + getTitle(): string            │     │ + addTrack(track): void         │
│ + getArtist(): string           │     │ + removeTrack(index): bool      │
│ + getDuration(): chrono::seconds│     │ + getCurrentTrack(): shared_ptr<Track>│
│ + setTitle(title): void         │     │ + next(): bool                  │
│ + operator==(other): bool       │     │ + previous(): bool              │
│ + createFromFile(path): shared_ptr<Track>│ + shuffle(): void           │
└─────────────────────────────────┘     │ + sortByTitle(): void           │
                 △                      └─────────────────────────────────┘
                 │ (aggregation)                       △
                 └─────────────────────────────────────┘

┌─────────────────────────────────┐     ┌─────────────────────────────────┐
│          Equalizer              │     │              CLI                │
├─────────────────────────────────┤     ├─────────────────────────────────┤
│ - bands: map<string, double>    │     │ - player: unique_ptr<MP3Player> │
│ - enabled: bool                 │     │ - scanner: unique_ptr<DirectoryScanner>│
├─────────────────────────────────┤     ├─────────────────────────────────┤
│ + setBand(freq, gain): void     │     │ + run(): void                   │
│ + getBand(freq): double         │     │ + showMenu(): void              │
│ + enable(): void                │     │ + processCommand(cmd): void     │
│ + disable(): void               │     │ + listTracks(): void            │
│ + reset(): void                 │     │ + createPlaylist(): void        │
└─────────────────────────────────┘     └─────────────────────────────────┘

┌─────────────────────────────────┐     ┌─────────────────────────────────┐
│       DirectoryScanner         │     │     PlaylistPersistence         │
├─────────────────────────────────┤     ├─────────────────────────────────┤
│ - supportedFormats: vector<string>│    │ + savePlaylist(playlist, path): bool│
├─────────────────────────────────┤     │ + loadPlaylist(path): shared_ptr<Playlist>│
│ + scanDirectory(path): vector<Track>│  │ + exportM3U(playlist, path): bool│
│ + isSupported(file): bool       │     │ + importM3U(path): shared_ptr<Playlist>│
│ + findMusicFiles(dir): vector<string>│ └─────────────────────────────────┘
└─────────────────────────────────┘

┌─────────────────────────────────┐
│         MP3PlayerApp            │
├─────────────────────────────────┤
│ - cli: unique_ptr<CLI>          │
├─────────────────────────────────┤
│ + main(): int                   │
│ + initialize(): bool            │
│ + run(): void                   │
│ + cleanup(): void               │
└─────────────────────────────────┘
```

## Relationships:
- **Inheritance**: MP3Player inherits from MediaPlayer
- **Composition**: MP3Player contains Equalizer, CLI contains MP3Player and DirectoryScanner
- **Aggregation**: Playlist contains multiple Track objects
- **Dependency**: CLI uses PlaylistPersistence for save/load operations

## Key OOP Concepts Demonstrated:
1. **Abstraction**: MediaPlayer abstract base class
2. **Encapsulation**: Private members with public interfaces
3. **Inheritance**: MP3Player extends MediaPlayer
4. **Polymorphism**: Virtual methods in MediaPlayer
5. **Composition**: Complex objects built from simpler ones
6. **Smart Pointers**: shared_ptr, unique_ptr for memory management
7. **STL Usage**: vector, map, string containers
8. **Exception Handling**: Error management throughout
9. **Templates**: STL containers and smart pointers
10. **Operator Overloading**: Track comparison operators