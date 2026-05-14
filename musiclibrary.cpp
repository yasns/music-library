#include "musiclibrary.h"
#include <vector>
#include <sstream>
using namespace std;

StrategyNotSet::StrategyNotSet()
    : runtime_error("strategy not set")
{
}

struct MusicLibrary::Impl {
    vector<Track*> tracks;
    SortStrategy* strategy;

    Impl()
        : strategy(nullptr)
    {
    }
};

MusicLibrary::RandomAccessIterator::RandomAccessIterator(Track** ptr)
    : ptr(ptr)
{
}

Track*& MusicLibrary::RandomAccessIterator::operator*() const
{
    return *ptr;
}

Track** MusicLibrary::RandomAccessIterator::operator->() const
{
    return ptr;
}

MusicLibrary::RandomAccessIterator& MusicLibrary::RandomAccessIterator::operator++()
{
    ptr++;
    return *this;
}

MusicLibrary::RandomAccessIterator MusicLibrary::RandomAccessIterator::operator++(int)
{
    RandomAccessIterator tmp = *this;
    ptr++;
    return tmp;
}

MusicLibrary::RandomAccessIterator& MusicLibrary::RandomAccessIterator::operator--()
{
    ptr--;
    return *this;
}

MusicLibrary::RandomAccessIterator MusicLibrary::RandomAccessIterator::operator--(int)
{
    RandomAccessIterator tmp = *this;
    ptr--;
    return tmp;
}

MusicLibrary::RandomAccessIterator& MusicLibrary::RandomAccessIterator::operator+=(difference_type n)
{
    ptr += n;
    return *this;
}

MusicLibrary::RandomAccessIterator& MusicLibrary::RandomAccessIterator::operator-=(difference_type n)
{
    ptr -= n;
    return *this;
}

MusicLibrary::RandomAccessIterator MusicLibrary::RandomAccessIterator::operator+(difference_type n) const
{
    return RandomAccessIterator(ptr + n);
}

MusicLibrary::RandomAccessIterator MusicLibrary::RandomAccessIterator::operator-(difference_type n) const
{
    return RandomAccessIterator(ptr - n);
}

MusicLibrary::RandomAccessIterator::difference_type MusicLibrary::RandomAccessIterator::operator-(const RandomAccessIterator& other) const
{
    return ptr - other.ptr;
}

Track*& MusicLibrary::RandomAccessIterator::operator[](difference_type n) const
{
    return ptr[n];
}

bool MusicLibrary::RandomAccessIterator::operator==(const RandomAccessIterator& other) const
{
    return ptr == other.ptr;
}

bool MusicLibrary::RandomAccessIterator::operator!=(const RandomAccessIterator& other) const
{
    return ptr != other.ptr;
}

bool MusicLibrary::RandomAccessIterator::operator<(const RandomAccessIterator& other) const
{
    return ptr < other.ptr;
}

bool MusicLibrary::RandomAccessIterator::operator>(const RandomAccessIterator& other) const
{
    return ptr > other.ptr;
}

bool MusicLibrary::RandomAccessIterator::operator<=(const RandomAccessIterator& other) const
{
    return ptr <= other.ptr;
}

bool MusicLibrary::RandomAccessIterator::operator>=(const RandomAccessIterator& other) const
{
    return ptr >= other.ptr;
}

MusicLibrary::MusicLibrary()
    : impl(new Impl())
{
}

MusicLibrary::MusicLibrary(const MusicLibrary& other)
    : impl(new Impl())
{
    impl->strategy = other.impl->strategy;
    for (Track* t : other.impl->tracks) {
        impl->tracks.push_back(t->clone());
    }
}

MusicLibrary& MusicLibrary::operator=(const MusicLibrary& other)
{
    if (this == &other) {
        return *this;
    }
    for (Track* t : impl->tracks) {
        delete t;
    }
    impl->tracks.clear();
    impl->strategy = other.impl->strategy;
    for (Track* t : other.impl->tracks) {
        impl->tracks.push_back(t->clone());
    }
    return *this;
}

MusicLibrary::~MusicLibrary()
{
    for (Track* t : impl->tracks) {
        delete t;
    }
    delete impl;
}

void MusicLibrary::add(Track* track)
{
    impl->tracks.push_back(track);
}

Track* MusicLibrary::get(int index) const
{
    return impl->tracks[index];
}

Track* MusicLibrary::find(const std::string& query) const
{
    for (Track* t : impl->tracks) {
        if (t->matches(query)) {
            return t;
        }
    }
    return nullptr;
}

void MusicLibrary::remove(int index)
{
    delete impl->tracks[index];
    impl->tracks.erase(impl->tracks.begin() + index);
}

void MusicLibrary::update(int index, Track* track)
{
    delete impl->tracks[index];
    impl->tracks[index] = track;
}

int MusicLibrary::size() const
{
    return static_cast<int>(impl->tracks.size());
}

void MusicLibrary::setStrategy(SortStrategy* strategy)
{
    impl->strategy = strategy;
}

void MusicLibrary::sort()
{
    if (impl->strategy == nullptr) {
        throw StrategyNotSet();
    }
    impl->strategy->sort(impl->tracks);
}

MusicLibrary MusicLibrary::filter(const FilterCallback& callback) const
{
    MusicLibrary result;
    result.impl->strategy = impl->strategy;
    for (Track* t : impl->tracks) {
        if (callback(t)) {
            result.impl->tracks.push_back(t->clone());
        }
    }
    return result;
}

string MusicLibrary::getAllInfo() const
{
    ostringstream oss;
    for (Track* t : impl->tracks) {
        oss << t->getInfo() << "\n";
    }
    return oss.str();
}

MusicLibrary::RandomAccessIterator MusicLibrary::begin()
{
    return RandomAccessIterator(impl->tracks.data());
}

MusicLibrary::RandomAccessIterator MusicLibrary::end()
{
    return RandomAccessIterator(impl->tracks.data() + impl->tracks.size());
}

MusicLibrary::RandomAccessIterator MusicLibrary::begin() const
{
    return RandomAccessIterator(impl->tracks.data());
}

MusicLibrary::RandomAccessIterator MusicLibrary::end() const
{
    return RandomAccessIterator(impl->tracks.data() + impl->tracks.size());
}
