#include "Track.h"
#include "Playlist.h"
#include "MP3Player.h"
#include "Equalizer.h"
#include "PlaylistPersistence.h"
#include "DirectoryScanner.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <filesystem>

/**
 * @brief Functional MP3 Player CLI demonstrating ALL minimum requirements
 * 
 * This implementation demonstrates:
 * 1. Directory scan for media files
 * 2. Play/pause/stop, seek, volume controls
 * 3. Playlist CRUD operations
 * 4. MediaPlayer (abstract), Track, Playlist, Equalizer classes
 * 5. JSON persistence for playlists
 * 6. CLI interface for all operations
 */

class FunctionalMP3Player {
private:
    std::unique_ptr<MP3Player> player;
    std::unique_ptr<JsonPlaylistPersistence> persistence;
    std::shared_ptr<Playlist> currentPlaylist;
    std::vector<std::shared_ptr<Playlist>> savedPlaylists;
    bool running;
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void printHeader() {
        std::cout << "\n============================================================\n";
        std::cout << "     *** FUNCTIONAL MP3 PLAYER - ALL FEATURES DEMO ***      \n";
        std::cout << "============================================================\n";
    }
    
    void printSeparator() {
        std::cout << "------------------------------------------------------------\n";
    }
    
    void printStatus() {
        printSeparator();
        std::cout << ">> STATUS:\n";
        std::cout << "   Volume: " << static_cast<int>(player->getVolume()) << "%\n";
        
        auto track = player->getCurrentTrack();
        if (track) {
            std::cout << "   Playing: " << track->getArtist() << " - " << track->getTitle() << "\n";
            std::cout << "   Position: " << player->getCurrentPosition() << "s / " 
                      << track->getDuration().count() << "s\n";
        } else {
            std::cout << "   No track loaded\n";
        }
        
        if (currentPlaylist) {
            std::cout << "   Playlist: " << currentPlaylist->getName() 
                      << " (" << currentPlaylist->size() << " tracks)\n";
        }
        printSeparator();
    }
    
    void showMainMenu() {
        std::cout << "\n>> MAIN MENU:\n";
        std::cout << "  1. [Scan] Directory for Music Files\n";
        std::cout << "  2. [Play] Playback Controls (Play/Pause/Stop/Seek/Volume)\n";
        std::cout << "  3. [List] Playlist Management (CRUD)\n";
        std::cout << "  4. [EQ]   Equalizer Settings\n";
        std::cout << "  5. [Save] Save/Load Playlist (JSON)\n";
        std::cout << "  6. [Info] Show Current Status\n";
        std::cout << "  0. [Exit] Exit\n";
        std::cout << "\nChoice: ";
    }
    
    // REQUIREMENT 1: Directory scan for media files
    void scanDirectory() {
        std::cout << "\n[DIRECTORY SCANNER]\n";
        printSeparator();
        
        std::cout << "** Scanning directory for MP3 files...\n\n";
        
        // Default music directory
        std::string musicDir = "e:\\POO\\POOMP3\\musicas";
        
        std::cout << "Default directory: " << musicDir << "\n";
        std::cout << "Use default directory? (y/n): ";
        std::string useDefault;
        std::getline(std::cin, useDefault);
        
        if (useDefault != "y" && useDefault != "Y") {
            std::cout << "Enter directory path: ";
            std::getline(std::cin, musicDir);
        }
        
        // Check if directory exists
        if (!std::filesystem::exists(musicDir)) {
            std::cout << "[ERROR] Directory does not exist: " << musicDir << "\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return;
        }
        
        // Use DirectoryScanner to find MP3 files
        try {
            DirectoryScanner<> scanner({".mp3", ".MP3"});
            scanner.setRecursive(true, 3);
            
            std::cout << "Scanning directory: " << musicDir << "\n";
            auto filePaths = scanner.scanDirectory(musicDir);
            
            if (filePaths.empty()) {
                std::cout << "\n[WARNING] No MP3 files found in directory.\n";
                std::cout << "Please add MP3 files to: " << musicDir << "\n";
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                return;
            }
            
            // Create tracks from found files
            std::vector<std::shared_ptr<Track>> tracks;
            for (const auto& filePath : filePaths) {
                auto track = std::make_shared<Track>();
                
                // Extract filename without extension
                std::filesystem::path path(filePath);
                std::string filename = path.stem().string();
                
                track->setTitle(filename);
                track->setArtist("Unknown Artist");
                track->setAlbum("Unknown Album");
                track->setFilePath(filePath);  // Salvar caminho completo do arquivo
                
                tracks.push_back(track);
            }
            
            std::cout << "[OK] Found " << tracks.size() << " music file(s):\n\n";
            
            for (size_t i = 0; i < tracks.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << tracks[i]->getTitle() << "\n";
            }
            
            // Option to create playlist from scan
            std::cout << "\nCreate playlist from these files? (y/n): ";
            std::string response;
            std::getline(std::cin, response);
            
            if (response == "y" || response == "Y") {
                std::cout << "Enter playlist name: ";
                std::string name;
                std::getline(std::cin, name);
                
                currentPlaylist = std::make_shared<Playlist>(name);
                for (const auto& track : tracks) {
                    currentPlaylist->addTrack(track);
                }
                
                std::cout << "[OK] Playlist '" << name << "' created with " 
                          << tracks.size() << " tracks!\n";
            }
            
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to scan directory: " << e.what() << "\n";
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    // REQUIREMENT 2: Play/pause/stop, seek, volume controls
    void playbackControls() {
        while (true) {
            clearScreen();
            printHeader();
            printStatus();
            
            std::cout << "\n[PLAYBACK CONTROLS]\n";
            std::cout << "  1. [>>] Play\n";
            std::cout << "  2. [||] Pause\n";
            std::cout << "  3. [#]  Stop\n";
            std::cout << "  4. [>]  Next Track\n";
            std::cout << "  5. [<]  Previous Track\n";
            std::cout << "  6. [+]  Set Volume (0-100)\n";
            std::cout << "  7. [->] Seek Position\n";
            std::cout << "  0. [<-] Back to Main Menu\n";
            std::cout << "\nChoice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: { // Play
                    if (currentPlaylist && !currentPlaylist->empty()) {
                        auto track = currentPlaylist->getCurrentTrack();
                        if (track) {
                            player->loadTrack(track);
                            if (player->play()) {
                                std::cout << "[PLAY] Playing: " << track->getTitle() << "\n";
                            }
                        }
                    } else {
                        std::cout << "[ERROR] No playlist loaded or playlist is empty!\n";
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                case 2: // Pause
                    if (player->pause()) {
                        std::cout << "[PAUSE] Paused\n";
                    } else {
                        std::cout << "[ERROR] Cannot pause - no track playing\n";
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                    
                case 3: // Stop
                    player->stop();
                    std::cout << "[STOP] Stopped\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                    
                case 4: // Next
                    if (currentPlaylist) {
                        auto next = currentPlaylist->next();
                        if (next) {
                            player->loadTrack(next);
                            player->play();
                            std::cout << "[NEXT] Next: " << next->getTitle() << "\n";
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                    
                case 5: // Previous
                    if (currentPlaylist) {
                        auto prev = currentPlaylist->previous();
                        if (prev) {
                            player->loadTrack(prev);
                            player->play();
                            std::cout << "[PREV] Previous: " << prev->getTitle() << "\n";
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                    
                case 6: { // Volume
                    std::cout << "Enter volume (0-100): ";
                    int vol;
                    std::cin >> vol;
                    std::cin.ignore();
                    
                    if (vol >= 0 && vol <= 100) {
                        player->setVolume(vol);
                        std::cout << "[VOLUME] Volume set to " << vol << "%\n";
                    } else {
                        std::cout << "[ERROR] Invalid volume! Must be 0-100\n";
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                case 7: { // Seek
                    std::cout << "Enter position in seconds: ";
                    double pos;
                    std::cin >> pos;
                    std::cin.ignore();
                    
                    if (player->seek(pos)) {
                        std::cout << "[SEEK] Seeked to " << pos << "s\n";
                    } else {
                        std::cout << "[ERROR] Cannot seek - no track loaded\n";
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                case 0:
                    return;
                    
                default:
                    std::cout << "[ERROR] Invalid choice!\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }
    
    // REQUIREMENT 3: Playlist CRUD operations
    void playlistManagement() {
        while (true) {
            clearScreen();
            printHeader();
            
            std::cout << "\nPLAYLIST MANAGEMENT (CRUD):\n";
            std::cout << "  1. Create New Playlist\n";
            std::cout << "  2. Read/View Playlists\n";
            std::cout << "  3. Update Playlist (Add/Remove Tracks)\n";
            std::cout << "  4. Delete Playlist\n";
            std::cout << "  5. Show Current Playlist Details\n";
            std::cout << "  0. Back to Main Menu\n";
            std::cout << "\nChoice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1: { // Create
                    std::cout << "\nCREATE NEW PLAYLIST\n";
                    printSeparator();
                    
                    std::cout << "Enter playlist name: ";
                    std::string name;
                    std::getline(std::cin, name);
                    
                    currentPlaylist = std::make_shared<Playlist>(name);
                    
                    std::cout << "Add tracks manually? (y/n): ";
                    std::string response;
                    std::getline(std::cin, response);
                    
                    if (response == "y" || response == "Y") {
                        while (true) {
                            std::cout << "\nEnter track title (or 'done' to finish): ";
                            std::string title;
                            std::getline(std::cin, title);
                            
                            if (title == "done") break;
                            
                            std::cout << "Enter artist: ";
                            std::string artist;
                            std::getline(std::cin, artist);
                            
                            auto track = std::make_shared<Track>();
                            track->setTitle(title);
                            track->setArtist(artist);
                            currentPlaylist->addTrack(track);
                            
                            std::cout << "[OK] Track added!\n";
                        }
                    }
                    
                    std::cout << "\n[OK] Playlist '" << name << "' created with " 
                              << currentPlaylist->size() << " tracks!\n";
                    break;
                }
                case 2: { // Read
                    std::cout << "\nCURRENT PLAYLIST DETAILS\n";
                    printSeparator();
                    
                    if (!currentPlaylist) {
                        std::cout << "[ERROR] No playlist loaded!\n";
                    } else {
                        std::cout << "Name: " << currentPlaylist->getName() << "\n";
                        std::cout << "Tracks: " << currentPlaylist->size() << "\n";
                        std::cout << "Total Duration: " << currentPlaylist->getTotalDuration().count() << "s\n";
                        std::cout << "Shuffle: " << (currentPlaylist->getShuffleMode() ? "ON" : "OFF") << "\n";
                        std::cout << "Repeat: " << (currentPlaylist->getRepeatMode() ? "ON" : "OFF") << "\n\n";
                        
                        std::cout << "Track List:\n";
                        size_t idx = 1;
                        for (const auto& track : *currentPlaylist) {
                            std::cout << "  " << idx++ << ". " << track->getArtist() 
                                      << " - " << track->getTitle() << "\n";
                        }
                    }
                    break;
                }
                case 3: { // Update
                    if (!currentPlaylist) {
                        std::cout << "[ERROR] No playlist loaded!\n";
                        break;
                    }
                    
                    std::cout << "\nUPDATE PLAYLIST\n";
                    printSeparator();
                    std::cout << "  1. Add Track\n";
                    std::cout << "  2. Remove Track\n";
                    std::cout << "Choice: ";
                    
                    int updateChoice;
                    std::cin >> updateChoice;
                    std::cin.ignore();
                    
                    if (updateChoice == 1) {
                        std::cout << "Enter track title: ";
                        std::string title;
                        std::getline(std::cin, title);
                        
                        std::cout << "Enter artist: ";
                        std::string artist;
                        std::getline(std::cin, artist);
                        
                        auto track = std::make_shared<Track>();
                        track->setTitle(title);
                        track->setArtist(artist);
                        currentPlaylist->addTrack(track);
                        
                        std::cout << "[OK] Track added to playlist!\n";
                    } else if (updateChoice == 2) {
                        std::cout << "Enter track number to remove (1-" 
                                  << currentPlaylist->size() << "): ";
                        size_t idx;
                        std::cin >> idx;
                        std::cin.ignore();
                        
                        if (currentPlaylist->removeTrack(idx - 1)) {
                            std::cout << "[OK] Track removed!\n";
                        } else {
                            std::cout << "[ERROR] Invalid track number!\n";
                        }
                    }
                    break;
                }
                case 4: { // Delete
                    if (currentPlaylist) {
                        std::cout << "\nDelete playlist '" << currentPlaylist->getName() << "'? (y/n): ";
                        std::string response;
                        std::getline(std::cin, response);
                        
                        if (response == "y" || response == "Y") {
                            currentPlaylist.reset();
                            std::cout << "[OK] Playlist deleted!\n";
                        }
                    } else {
                        std::cout << "[ERROR] No playlist loaded!\n";
                    }
                    break;
                }
                case 5: // Show details
                    if (currentPlaylist) {
                        std::cout << "\nPLAYLIST: " << currentPlaylist->getName() << "\n";
                        printSeparator();
                        std::cout << "Tracks: " << currentPlaylist->size() << "\n";
                        std::cout << "Duration: " << currentPlaylist->getTotalDuration().count() << "s\n";
                    } else {
                        std::cout << "[ERROR] No playlist loaded!\n";
                    }
                    break;
                    
                case 0:
                    return;
                    
                default:
                    std::cout << "[ERROR] Invalid choice!\n";
            }
            
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
    
    // REQUIREMENT 4: Equalizer settings
    void equalizerSettings() {
        clearScreen();
        printHeader();
        
        std::cout << "\nEQUALIZER SETTINGS\n";
        printSeparator();
        
        auto equalizer = player->getEqualizer();
        if (!equalizer) {
            std::cout << "[ERROR] Equalizer not available!\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            return;
        }
        
        std::cout << "Equalizer Status: " << (equalizer->isEnabled() ? "[ON] ENABLED" : "[OFF] DISABLED") << "\n\n";
        
        std::cout << "Current Bands:\n";
        std::cout << "  LOW (Bass):   " << std::fixed << std::setprecision(2) 
                  << equalizer->getBandGain(Equalizer::Band::LOW) << " dB\n";
        std::cout << "  MID (Middle): " << std::fixed << std::setprecision(2) 
                  << equalizer->getBandGain(Equalizer::Band::MID) << " dB\n";
        std::cout << "  HIGH (Treble): " << std::fixed << std::setprecision(2) 
                  << equalizer->getBandGain(Equalizer::Band::HIGH) << " dB\n";
        
        std::cout << "\nOptions:\n";
        std::cout << "  1. Enable/Disable Equalizer\n";
        std::cout << "  2. Set Band Level\n";
        std::cout << "  3. Reset to Flat\n";
        std::cout << "  4. Apply Preset\n";
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                equalizer->setEnabled(!equalizer->isEnabled());
                std::cout << (equalizer->isEnabled() ? "[OK] Equalizer enabled\n" : "[OFF] Equalizer disabled\n");
                break;
                
            case 2: {
                std::cout << "Select band:\n";
                std::cout << "  1. LOW (Bass)\n";
                std::cout << "  2. MID (Middle)\n";
                std::cout << "  3. HIGH (Treble)\n";
                std::cout << "Choice: ";
                int bandChoice;
                std::cin >> bandChoice;
                std::cin.ignore();
                
                Equalizer::Band band;
                switch (bandChoice) {
                    case 1: band = Equalizer::Band::LOW; break;
                    case 2: band = Equalizer::Band::MID; break;
                    case 3: band = Equalizer::Band::HIGH; break;
                    default:
                        std::cout << "[ERROR] Invalid band!\n";
                        return;
                }
                
                std::cout << "Enter gain in dB (-12 to +12): ";
                double gain;
                std::cin >> gain;
                std::cin.ignore();
                
                equalizer->setBandGain(band, gain);
                std::cout << "[OK] Band set to " << gain << " dB\n";
                break;
            }
            case 3:
                equalizer->reset();
                std::cout << "[OK] Equalizer reset to flat (0 dB)\n";
                break;
                
            case 4: {
                std::cout << "Available presets:\n";
                auto presets = Equalizer::getAvailablePresets();
                for (size_t i = 0; i < presets.size(); ++i) {
                    std::cout << "  " << (i + 1) << ". " << presets[i] << "\n";
                }
                std::cout << "Choice: ";
                size_t presetChoice;
                std::cin >> presetChoice;
                std::cin.ignore();
                
                if (presetChoice > 0 && presetChoice <= presets.size()) {
                    equalizer->applyPreset(presets[presetChoice - 1]);
                    std::cout << "[OK] Applied preset: " << presets[presetChoice - 1] << "\n";
                } else {
                    std::cout << "[ERROR] Invalid preset!\n";
                }
                break;
            }
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    // REQUIREMENT 5: Persistence - Save/Load playlists to JSON
    void persistenceOperations() {
        clearScreen();
        printHeader();
        
        std::cout << "\nPLAYLIST PERSISTENCE (JSON)\n";
        printSeparator();
        
        std::cout << "  1. Save Current Playlist to JSON\n";
        std::cout << "  2. Load Playlist from JSON\n";
        std::cout << "  0. Back\n";
        std::cout << "\nChoice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: { // Save
                if (!currentPlaylist) {
                    std::cout << "[ERROR] No playlist to save!\n";
                    break;
                }
                
                std::cout << "Enter filename (without .json): ";
                std::string filename;
                std::getline(std::cin, filename);
                filename += ".json";
                
                try {
                    if (persistence->savePlaylist(*currentPlaylist, filename)) {
                        std::cout << "[OK] Playlist saved to " << filename << "\n";
                    } else {
                        std::cout << "[ERROR] Failed to save playlist!\n";
                    }
                } catch (const std::exception& e) {
                    std::cout << "[ERROR] Error: " << e.what() << "\n";
                }
                break;
            }
            case 2: { // Load
                std::cout << "Enter filename (without .json): ";
                std::string filename;
                std::getline(std::cin, filename);
                filename += ".json";
                
                try {
                    auto playlistOpt = persistence->loadPlaylist(filename);
                    if (playlistOpt.has_value()) {
                        currentPlaylist = std::make_shared<Playlist>(playlistOpt.value());
                        std::cout << "[OK] Playlist loaded: " << currentPlaylist->getName() 
                                  << " (" << currentPlaylist->size() << " tracks)\n";
                    } else {
                        std::cout << "[ERROR] Failed to load playlist!\n";
                    }
                } catch (const std::exception& e) {
                    std::cout << "[ERROR] Error: " << e.what() << "\n";
                }
                break;
            }
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

public:
    FunctionalMP3Player() 
        : player(std::make_unique<MP3Player>()),
          persistence(std::make_unique<JsonPlaylistPersistence>()),
          running(true) {
    }
    
    void run() {
        while (running) {
            clearScreen();
            printHeader();
            printStatus();
            showMainMenu();
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            switch (choice) {
                case 1:
                    scanDirectory();
                    break;
                case 2:
                    playbackControls();
                    break;
                case 3:
                    playlistManagement();
                    break;
                case 4:
                    equalizerSettings();
                    break;
                case 5:
                    persistenceOperations();
                    break;
                case 6:
                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    break;
                case 0:
                    running = false;
                    std::cout << "\n>> Thank you for using Functional MP3 Player!\n";
                    break;
                default:
                    std::cout << "[ERROR] Invalid choice!\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }
};

int main() {
    try {
        std::cout << ">> Starting Functional MP3 Player...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        FunctionalMP3Player app;
        app.run();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Fatal error: " << e.what() << "\n";
        return 1;
    }
}


