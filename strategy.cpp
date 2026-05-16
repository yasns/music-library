#include "strategy.h"
#include <algorithm>
#include <random>
using namespace std;

SortStrategy::SortStrategy() = default;

SortStrategy::~SortStrategy()
{
}

SortByTitle::~SortByTitle() = default;

void SortByTitle::sort(vector<Track*>& tracks) const
{
    std::sort(tracks.begin(), tracks.end(), [](Track* a, Track* b) {
        return a->getTitle() < b->getTitle();
    });
}

SortByDuration::~SortByDuration() = default;

void SortByDuration::sort(vector<Track*>& tracks) const
{
    std::sort(tracks.begin(), tracks.end(), [](Track* a, Track* b) {
        return a->getDuration() < b->getDuration();
    });
}

SortByRating::~SortByRating() = default;

void SortByRating::sort(vector<Track*>& tracks) const
{
    std::sort(tracks.begin(), tracks.end(), [](Track* a, Track* b) {
        return a->getRating() > b->getRating();
    });
}

SortByRandom::~SortByRandom() = default;

void SortByRandom::sort(vector<Track*>& tracks) const
{
    std::shuffle(tracks.begin(), tracks.end(),
                 std::default_random_engine{std::random_device{}()});
}

FilterCallback::FilterCallback() = default;

FilterCallback::~FilterCallback()
{
}

FilterByMinDuration::FilterByMinDuration(double minDuration)
    : minDuration(minDuration)
{
}

FilterByMinDuration::~FilterByMinDuration() = default;

bool FilterByMinDuration::operator()(const Track* track) const
{
    return track->getDuration() >= minDuration;
}

FilterByMinRating::FilterByMinRating(double minRating)
    : minRating(minRating)
{
}

FilterByMinRating::~FilterByMinRating() = default;

bool FilterByMinRating::operator()(const Track* track) const
{
    return track->getRating() >= minRating;
}

FilterByType::FilterByType(TrackType type)
    : type(type)
{
}

FilterByType::~FilterByType() = default;

bool FilterByType::operator()(const Track* track) const
{
    switch (type) {
        case TrackType::Song:     return dynamic_cast<const Song*>(track)     != nullptr;
        case TrackType::Podcast:  return dynamic_cast<const Podcast*>(track)  != nullptr;
#ifdef RINGTONE_IMPLEMENTED
        case TrackType::Ringtone: return dynamic_cast<const Ringtone*>(track) != nullptr;
#else
        case TrackType::Ringtone: return false;
#endif
    }
    return false;
}
