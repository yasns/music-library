#include "track.h"
#include "strategy.h"
#include "musiclibrary.h"
#include <cassert>
#include <iostream>
using namespace std;

void testCRUD()
{
    cout << "Testing CRUD...\n";
    MusicLibrary lib;
    lib.add(new Song("A", 120.0, 4.0, "a.mp3", "Artist", "Album", 2020, "Pop", 100));
    lib.add(new Podcast("B", 3600.0, 4.5, "b.mp3", "Host", 1, "2024-01-01"));
    assert(lib.size() == 2);

    assert(lib.get(0)->getTitle() == "A");
    assert(lib.get(1)->getTitle() == "B");

    lib.update(0, new Song("C", 90.0, 3.5, "c.mp3", "X", "Y", 2019, "Rock", 50));
    assert(lib.get(0)->getTitle() == "C");
    assert(lib.size() == 2);

    lib.remove(1);
    assert(lib.size() == 1);
    assert(lib.get(0)->getTitle() == "C");
}

void testDeepCopy()
{
    cout << "Testing deep copy...\n";
    MusicLibrary lib;
    lib.add(new Song("Original", 200.0, 4.0, "original.mp3", "A", "B", 2000, "C", 10));

    MusicLibrary copy = lib;
    assert(copy.size() == 1);
    assert(copy.get(0)->getTitle() == "Original");
    assert(copy.get(0) != lib.get(0));

    lib.update(0, new Song("Modified", 200.0, 4.0, "modified.mp3", "A", "B", 2000, "C", 10));
    assert(copy.get(0)->getTitle() == "Original");

    MusicLibrary assigned;
    assigned = lib;
    assert(assigned.size() == 1);
    assert(assigned.get(0)->getTitle() == "Modified");
    assert(assigned.get(0) != lib.get(0));
}

void testStrategy()
{
    cout << "Testing sorting...\n";
    MusicLibrary lib;
    lib.add(new Song("Zebra", 100.0, 3.0, "zebra.mp3", "A", "B", 2000, "C", 0));
    lib.add(new Song("Apple", 300.0, 5.0, "apple.mp3", "A", "B", 2000, "C", 0));
    lib.add(new Song("Mango", 200.0, 4.0, "mango.mp3", "A", "B", 2000, "C", 0));

    SortByTitle byTitle;
    lib.setStrategy(&byTitle);
    lib.sort();
    assert(lib.get(0)->getTitle() == "Apple");
    assert(lib.get(1)->getTitle() == "Mango");
    assert(lib.get(2)->getTitle() == "Zebra");

    SortByDuration byDuration;
    lib.setStrategy(&byDuration);
    lib.sort();
    assert(lib.get(0)->getDuration() == 100.0);
    assert(lib.get(2)->getDuration() == 300.0);

    SortByRating byRating;
    lib.setStrategy(&byRating);
    lib.sort();
    assert(lib.get(0)->getRating() == 5.0);
    assert(lib.get(2)->getRating() == 3.0);

    SortByRandom byRandom;
    lib.setStrategy(&byRandom);
    lib.sort();
    assert(lib.size() == 3);
    assert(lib.find("Zebra") != nullptr);
    assert(lib.find("Apple") != nullptr);
    assert(lib.find("Mango") != nullptr);

    try {
        MusicLibrary unset;
        unset.add(new Song("X", 60.0, 3.0, "x.mp3", "A", "B", 2000, "C", 0));
        unset.sort();
        assert(false);
    } catch (const StrategyNotSet&) {
    }
}

void testFilter()
{
    cout << "Testing filtering...\n";
    MusicLibrary lib;
    lib.add(new Song("Short", 60.0, 3.0, "short.mp3", "A", "B", 2000, "C", 0));
    lib.add(new Song("Long", 400.0, 4.5, "long.mp3", "A", "B", 2000, "C", 0));
    lib.add(new Podcast("P", 3600.0, 4.8, "p.mp3", "H", 1, "2024-01-01"));

    FilterByMinDuration longFilter(300.0);
    MusicLibrary longTracks = lib.filter(longFilter);
    assert(longTracks.size() == 2);
    assert(longTracks.get(0) != lib.get(1));

    FilterByMinRating topFilter(4.5);
    MusicLibrary topTracks = lib.filter(topFilter);
    assert(topTracks.size() == 2);

    FilterByType songFilter(TrackType::Song);
    MusicLibrary songs = lib.filter(songFilter);
    assert(songs.size() == 2);

    FilterByType podcastFilter(TrackType::Podcast);
    MusicLibrary podcasts = lib.filter(podcastFilter);
    assert(podcasts.size() == 1);
    assert(podcasts.get(0)->getTitle() == "P");
}

void testGetAllInfo()
{
    cout << "Testing getAllInfo...\n";
    MusicLibrary lib;
    lib.add(new Song("S", 120.0, 4.0, "s.mp3", "A", "B", 2000, "C", 10));
    lib.add(new Podcast("P", 3600.0, 4.5, "p.mp3", "H", 1, "2024-01-01"));

    string info = lib.getAllInfo();
    assert(info.find("Song:") != string::npos);
    assert(info.find("Podcast:") != string::npos);
}

void testIterator()
{
    cout << "Testing iterator...\n";
    MusicLibrary lib;
    lib.add(new Song("A", 100.0, 5.0, "a.mp3", "X", "Y", 2000, "Z", 0));
    lib.add(new Song("B", 200.0, 3.0, "b.mp3", "X", "Y", 2000, "Z", 0));
    lib.add(new Song("C", 150.0, 4.0, "c.mp3", "X", "Y", 2000, "Z", 0));

    int count = 0;
    for (MusicLibrary::RandomAccessIterator it = lib.begin(); it != lib.end(); ++it) {
        count++;
    }
    assert(count == 3);

    assert(lib.end() - lib.begin() == 3);
    assert(lib.begin()[1]->getTitle() == "B");

    const MusicLibrary& clib = lib;
    int ccount = 0;
    for (MusicLibrary::RandomAccessIterator it = clib.begin(); it != clib.end(); ++it) {
        ccount++;
    }
    assert(ccount == 3);
}

void testPolymorphism()
{
    cout << "Testing polymorphism...\n";
    MusicLibrary lib;
    lib.add(new Song("S", 200.0, 4.0, "s.mp3", "A", "B", 2000, "Pop", 5));
    lib.add(new Podcast("P", 3600.0, 4.5, "p.mp3", "H", 1, "2024-01-01"));

    for (int i = 0; i < lib.size(); i++) {
        Track* t = lib.get(i);
        string info = t->getInfo();
        assert(!info.empty());
    }

    Song* s = dynamic_cast<Song*>(lib.get(0));
    assert(s != nullptr);
    s->incrementPlayCount();
    assert(s->getPlayCount() == 6);

    Podcast* p = dynamic_cast<Podcast*>(lib.get(1));
    assert(p != nullptr);
    assert(p->getHost() == "H");
    assert(p->getPublishDate() == "2024-01-01");

    assert(dynamic_cast<Song*>(lib.get(1)) == nullptr);
}

void testPrototype()
{
    cout << "Testing prototype...\n";
    Song* original = new Song("X", 100.0, 4.0, "x.mp3", "A", "B", 2000, "C", 1);
    Track* cloned = original->clone();

    assert(cloned != original);
    assert(cloned->getTitle() == original->getTitle());
    assert(cloned->getDuration() == original->getDuration());
    assert(cloned->getRating() == original->getRating());
    assert(cloned->getFilename() == original->getFilename());

    Song* clonedSong = dynamic_cast<Song*>(cloned);
    assert(clonedSong != nullptr);
    assert(clonedSong->getPlayCount() == 1);
    assert(clonedSong->getYear() == 2000);

    delete original;
    delete cloned;
}

void testFind()
{
    cout << "Testing find...\n";
    MusicLibrary lib;
    lib.add(new Song("Imagine", 187.0, 4.9, "imagine.mp3", "John Lennon", "Imagine", 1971, "Rock", 0));
    lib.add(new Podcast("Lex Fridman #400", 7200.0, 4.7, "lex_fridman_400.mp3", "Lex Fridman", 400, "2024-03-15"));

    Track* found = lib.find("Imagine");
    assert(found != nullptr);
    assert(found->getTitle() == "Imagine");

    assert(lib.find("mag") != nullptr);
    assert(lib.find("john lennon") != nullptr);
    assert(lib.find("Fridman") != nullptr);
    assert(lib.find("Nonexistent") == nullptr);
}

void testRingtone()
{
    std::cout << "Testing ringtone...\n";
    MusicLibrary lib;
    lib.add(new Ringtone("Nokia Tune", 5.0, 3.5, "nokia_tune.mp3", true));
    lib.add(new Ringtone("Marimba", 3.0, 4.0, "marimba.mp3", false));
    assert(lib.size() == 2);

    Ringtone* r = dynamic_cast<Ringtone*>(lib.get(0));
    assert(r != nullptr);
    assert(r->isLoopable() == true);
    assert(r->getTitle() == "Nokia Tune");

    Track* cloned = lib.get(0)->clone();
    assert(cloned != lib.get(0));
    assert(cloned->getTitle() == "Nokia Tune");
    Ringtone* clonedR = dynamic_cast<Ringtone*>(cloned);
    assert(clonedR != nullptr);
    assert(clonedR->isLoopable() == true);
    delete cloned;

    string info = lib.get(0)->getInfo();
    assert(!info.empty());
    assert(info.find("Ringtone") != string::npos);
    assert(info.find("Nokia Tune") != string::npos);
    assert(info.find("nokia_tune.mp3") != string::npos);
    assert(info.find("5") != string::npos);   // duration
    assert(info.find("3.5") != string::npos); // rating
    assert(info.find("true") != string::npos); // loopable

    string info2 = lib.get(1)->getInfo();
assert(!info2.empty());
    assert(info2.find("Ringtone") != string::npos);
    assert(info2.find("Marimba") != string::npos);
    assert(info2.find("marimba.mp3") != string::npos);
    assert(info2.find("4") != string::npos);  // rating
    assert(info2.find("false") != string::npos); // loopable

    MusicLibrary copy = lib;
    assert(copy.size() == 2);
    assert(copy.get(0) != lib.get(0));
    assert(copy.get(0)->getTitle() == "Nokia Tune");
}

int main()
{
    try {
        testCRUD();
        testDeepCopy();
        testStrategy();
        testFilter();
        testGetAllInfo();
        testIterator();
        testPolymorphism();
        testPrototype();
        testFind();
        testRingtone();
        cout << "all tests passed\n";
    } catch (...) {
        cout << "unexpected exception\n";
        return 1;
    }
    assert(Track::getCount() == 0);
    return 0;
}