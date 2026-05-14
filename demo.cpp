#include "track.h"
#include "strategy.h"
#include "musiclibrary.h"
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    try {
        MusicLibrary library;
        library.add(new Song("Bohemian Rhapsody", 354.0, 5.0, "bohemian_rhapsody.mp3", "Queen", "A Night at the Opera", 1975, "Rock", 1200000));
        library.add(new Song("Billie Jean", 294.0, 4.8, "billie_jean.mp3", "Michael Jackson", "Thriller", 1982, "Pop", 800000));
        library.add(new Song("Imagine", 187.0, 4.9, "imagine.mp3", "John Lennon", "Imagine", 1971, "Rock", 600000));
        library.add(new Podcast("Lex Fridman #400", 7200.0, 4.7, "lex_fridman_400.mp3", "Lex Fridman", 400, "2024-03-15"));
        library.add(new Podcast("Huberman Lab #100", 5400.0, 4.6, "huberman_lab_100.mp3", "Andrew Huberman", 100, "2023-09-10"));

        SortByTitle sortByTitle;
        SortByDuration sortByDuration;
        SortByRating sortByRating;

        // strategy
        library.setStrategy(&sortByTitle);
        library.sort();

        // deep copy
        MusicLibrary copy = library;

        // iterator
        std::sort(library.begin(), library.end(), [](Track* a, Track* b) {
            return a->getRating() > b->getRating();
        });

        cout << "=== by rating ===\n";
        for (MusicLibrary::RandomAccessIterator it = library.begin(); it != library.end(); ++it) {
            // polymorphism
            cout << (*it)->getInfo() << "\n";
        }

        cout << "\n=== dynamic_cast: increment play count for Songs ===\n";
        for (int i = 0; i < library.size(); i++) {
            if (Song* s = dynamic_cast<Song*>(library.get(i))) {
                s->incrementPlayCount();
                cout << s->getTitle() << " plays: " << s->getPlayCount() << "\n";
            }
        }

        cout << "\n=== filter: longer than 5 minutes ===\n";
        FilterByMinDuration longFilter(300.0);
        // callback
        MusicLibrary longTracks = library.filter(longFilter);
        cout << longTracks.getAllInfo();

        cout << "\n=== filter: rating >= 4.9 ===\n";
        FilterByMinRating topFilter(4.9);
        MusicLibrary topRated = library.filter(topFilter);
        cout << topRated.getAllInfo();

        cout << "\n=== filter: by type ===\n";
        FilterByType songFilter(TrackType::Song);
        MusicLibrary songs = library.filter(songFilter);
        cout << songs.size() << " songs\n";
        FilterByType podcastFilter(TrackType::Podcast);
        MusicLibrary podcasts = library.filter(podcastFilter);
        cout << podcasts.size() << " podcasts\n";

        cout << "\n=== find ===\n";
        Track* found = library.find("Imagine");
        if (found) {
            cout << found->getInfo() << "\n";
        }
        cout << (library.find("queen") != nullptr ? "found by artist: ok" : "ERROR") << "\n";
        cout << (library.find("Thrill") != nullptr ? "found partial album: ok" : "ERROR") << "\n";
        cout << (library.find("Fridman") != nullptr ? "found by host: ok" : "ERROR") << "\n";
        cout << (library.find("Nonexistent") == nullptr ? "not found: ok" : "ERROR") << "\n";

        cout << "\n=== copy is independent (sorted by title, unaffected by later re-sort) ===\n";
        library.setStrategy(&sortByDuration);
        library.sort();
        cout << "copy:\n" << copy.getAllInfo();

        cout << "\n=== shuffle ===\n";
        SortByRandom sortByRandom;
        library.setStrategy(&sortByRandom);
        library.sort();
        cout << library.getAllInfo();

        cout << "\n=== StrategyNotSet ===\n";
        try {
            MusicLibrary unset;
            unset.add(new Song("Test", 60.0, 3.0, "test.mp3", "A", "B", 2000, "C", 0));
            unset.sort();
        } catch (const StrategyNotSet& e) {
            cout << e.what() << "\n";
        }

    } catch (...) {
        cout << "unexpected exception\n";
        return 1;
    }
    assert(Track::getCount() == 0);
    return 0;
}
