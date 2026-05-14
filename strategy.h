// Sort strategies and filter callbacks for MusicLibrary.
// Author: Matas Jasiūnas
// Developed with the assistance of Claude Sonnet 4.6 by Anthropic.
#ifndef STRATEGY_H
#define STRATEGY_H
#include "track.h"
#include <vector>

enum class TrackType { Song, Podcast, Ringtone };

// Strategy pattern: interchangeable sorting algorithms for MusicLibrary.
// Set the desired strategy via MusicLibrary::setStrategy(), then call sort().
class SortStrategy {
public:
    SortStrategy() = default;
    SortStrategy(const SortStrategy&) = delete;
    SortStrategy& operator=(const SortStrategy&) = delete;
    virtual ~SortStrategy();
    virtual void sort(std::vector<Track*>& tracks) const = 0;
};

// Sorts tracks alphabetically by title.
class SortByTitle : public SortStrategy {
public:
    void sort(std::vector<Track*>& tracks) const override;
};

// Sorts tracks by duration, shortest first.
class SortByDuration : public SortStrategy {
public:
    void sort(std::vector<Track*>& tracks) const override;
};

// Sorts tracks by rating, highest first.
class SortByRating : public SortStrategy {
public:
    void sort(std::vector<Track*>& tracks) const override;
};

// Shuffles tracks into a random order.
class SortByRandom : public SortStrategy {
public:
    void sort(std::vector<Track*>& tracks) const override;
};

// Callback pattern: passed to MusicLibrary::filter() to select tracks by arbitrary criteria.
class FilterCallback {
public:
    FilterCallback() = default;
    FilterCallback(const FilterCallback&) = delete;
    FilterCallback& operator=(const FilterCallback&) = delete;
    virtual ~FilterCallback();
    virtual bool operator()(const Track* track) const = 0;
};

// Keeps only tracks with duration >= minDuration (seconds).
class FilterByMinDuration : public FilterCallback {
    double minDuration;
public:
    FilterByMinDuration(double minDuration);
    bool operator()(const Track* track) const override;
};

// Keeps only tracks with rating >= minRating.
class FilterByMinRating : public FilterCallback {
    double minRating;
public:
    FilterByMinRating(double minRating);
    bool operator()(const Track* track) const override;
};

// Keeps only tracks of the specified concrete type.
class FilterByType : public FilterCallback {
    TrackType type;
public:
    FilterByType(TrackType type);
    bool operator()(const Track* track) const override;
};
#endif
