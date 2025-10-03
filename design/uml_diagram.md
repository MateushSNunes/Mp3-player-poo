# UML Class Diagram - MP3 Player System

```
┌─────────────────────────────────────────────────────────────┐
│                     MP3 Player System                       │
│                    UML Class Diagram                        │
└─────────────────────────────────────────────────────────────┘

┌─────────────────────────────────┐
│          MediaPlayer            │
│        <<abstract>>             │
├─────────────────────────────────┤
│ # currentTrack: shared_ptr<Track>│
│ # isPlaying: bool               │
│ # isPaused: bool                │
│ # volume: double                │
├─────────────────────────────────┤
│ + play(): bool                  │
│ + pause(): bool                 │
│ + stop(): bool                  │
│ + setVolume(vol: double): void  │
│ + getVolume(): double           │
└─────────────────────────────────┘
                 △
                 │ (inheritance)
                 │
┌─────────────────────────────────┐
│           MP3Player             │
├─────────────────────────────────┤
│ - equalizer: unique_ptr<Equalizer>│
│ - currentPlaylist: shared_ptr<Playlist>│
├─────────────────────────────────┤
│ + loadTrack(track): bool        │
│ + playCurrentTrack(): bool      │
│ + nextTrack(): bool             │
│ + previousTrack(): bool         │
│ + getEqualizer(): Equalizer*    │
└─────────────────────────────────┘
                 │
                 │ (composition)
                 ▽
┌─────────────────────────────────┐     ┌─────────────────────────────────┐
│             Track               │     │           Playlist              │
├─────────────────────────────────┤     ├─────────────────────────────────┤
│ - filePath: string              │     │ - name: string                  │
│ - title: string                 │     │ - tracks: vector<shared_ptr<Track>>│
│ - artist: string                │     │ - currentIndex: size_t          │
│ - album: string                 │     │ - description: string           │
│ - duration: chrono::seconds     │     │ - creationDate: chrono::time_point│
├─────────────────────────────────┤     ├─────────────────────────────────┤
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