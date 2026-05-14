// MusicLibrary — polymorphic container for audio tracks.
// Author: Matas Jasiūnas
// Developed with the assistance of Claude Sonnet 4.6 by Anthropic.
#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H
#include "track.h"
#include "strategy.h"
#include <cstddef>
#include <iterator>
#include <string>
#include <stdexcept>

// Thrown by sort() when no strategy has been set via setStrategy().
struct StrategyNotSet : public std::runtime_error {
    StrategyNotSet();
};

// Container for polymorphic Track objects. Owns all added pointers (deletes them on removal/destruction).
// Deep copy is performed via Track::clone() (Prototype pattern).
// Sorting is delegated to a SortStrategy (Strategy pattern). filter() accepts a FilterCallback object.
class MusicLibrary {
    struct Impl;
    Impl* impl;
public:
    // RandomAccess iterator over Track* elements. Supports all operations required by std::sort.
    class RandomAccessIterator {
        Track** ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Track*;
        using difference_type = std::ptrdiff_t;
        using pointer = Track**;
        using reference = Track*&;

        RandomAccessIterator(Track** ptr);
        Track*& operator*() const;
        Track** operator->() const;
        RandomAccessIterator& operator++();
        RandomAccessIterator operator++(int);
        RandomAccessIterator& operator--();
        RandomAccessIterator operator--(int);
        RandomAccessIterator& operator+=(difference_type n);
        RandomAccessIterator& operator-=(difference_type n);
        RandomAccessIterator operator+(difference_type n) const;
        RandomAccessIterator operator-(difference_type n) const;
        difference_type operator-(const RandomAccessIterator& other) const;
        Track*& operator[](difference_type n) const;
        bool operator==(const RandomAccessIterator& other) const;
        bool operator!=(const RandomAccessIterator& other) const;
        bool operator<(const RandomAccessIterator& other) const;
        bool operator>(const RandomAccessIterator& other) const;
        bool operator<=(const RandomAccessIterator& other) const;
        bool operator>=(const RandomAccessIterator& other) const;
    };

    MusicLibrary();
    MusicLibrary(const MusicLibrary& other);
    MusicLibrary& operator=(const MusicLibrary& other);
    ~MusicLibrary();

    void add(Track* track);
    Track* get(int index) const;
    Track* find(const std::string& query) const; // returns first track whose searchable fields contain query (case-insensitive partial)
    void remove(int index);
    void update(int index, Track* track);
    int size() const;

    void setStrategy(SortStrategy* strategy); // does not take ownership of the pointer
    void sort(); // throws StrategyNotSet if no strategy is set

    MusicLibrary filter(const FilterCallback& callback) const; // returns a new library with cloned matching tracks
    std::string getAllInfo() const; // calls getInfo() on each track and returns the concatenated result

    RandomAccessIterator begin();
    RandomAccessIterator end();
    RandomAccessIterator begin() const;
    RandomAccessIterator end() const;
};
#endif
