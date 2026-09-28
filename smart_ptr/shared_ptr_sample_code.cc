#include <iostream>
#include <memory>
#include <vector>
#include <string>

/*
Code Example: A Media Playlis tIn this scenario, multiple Playlists share ownership of the same Song objects. 
If a song is removed from one playlist, it should still exist if another playlist is using it. 
The song is only deleted from memory when no playlist references it anymore.
*/  
class Song {
public:
    std::string title;
    Song(std::string t) : title(t) { 
        std::cout << "Song created: " << title << "\n"; 
    }
    ~Song() { 
        std::cout << "Song destroyed: " << title << "\n"; 
    }
};

class Playlist {
public:
    std::string name;
    std::vector<std::shared_ptr<Song>> tracks;

    Playlist(std::string n) : name(n) {}

    void addSong(std::shared_ptr<Song> song) {
        tracks.push_back(song);
    }
};

int main() {
    std::cout << "--- Creating a Song ---\n";
    // Allocate the song using make_shared (Ref count = 1)
    std::shared_ptr<Song> song1 = std::make_shared<Song>("Blinding Lights");

    {
        std::cout << "\n--- Creating Playlists ---\n";
        Playlist popPlaylist("Pop Hits");
        Playlist drivingPlaylist("Driving Mix");

        // Both playlists share ownership of the same song
        popPlaylist.addSong(song1);     // Ref count = 2
        drivingPlaylist.addSong(song1);  // Ref count = 3
        
        std::cout << "Current reference count: " << song1.use_count() << "\n";
        
        std::cout << "\n--- Leaving Playlist Scope ---\n";
    } // popPlaylist and drivingPlaylist go out of scope here.
      // Their internal shared_ptrs are destroyed, dropping the ref count back to 1.

    std::cout << "Reference count after playlists destroyed: " << song1.use_count() << "\n";

    std::cout << "\n--- Ending Main Program ---\n";
    return 0; 
} // song1 goes out of scope here. Ref count hits 0, and the Song is automatically deleted.
