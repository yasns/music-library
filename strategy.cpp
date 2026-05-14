#include "strategy.h"
#include <algorithm>
#include <random>
using namespace std;

SortStrategy::~SortStrategy()
{
}

void SortByTitle::sort(vector<Track*>& tracks) const
{
    std::sort(tracks.begin(), tracks.end(), [](Track* a, Track* b) {
        return a->getTitle() < b->getTitle();
    });
}

void SortByDuration::sort(vector<Track*>& tracks) const
{
    std::sort(tracks.begin(), tracks.end(), [](Track* a, Track* b) {
        return a->getDuration() < b->getDuration();
    });
}

void SortByRating::sort(vector<Track*>& tracks) const
{
    std::sort(tracks.begin(), tracks.end(), [](Track* a, Track* b) {
        return a->getRating() > b->getRating();
    });
}

void SortByRandom::sort(vector<Track*>& tracks) const
{
    std::shuffle(tracks.begin(), tracks.end(),
                 std::default_random_engine{std::random_device{}()});
}

FilterCallback::~FilterCallback()
{
}

FilterByMinDuration::FilterByMinDuration(double minDuration)
    : minDuration(minDuration)
{
}

bool FilterByMinDuration::operator()(const Track* track) const
{
    return track->getDuration() >= minDuration;
}

FilterByMinRating::FilterByMinRating(double minRating)
    : minRating(minRating)
{
}

bool FilterByMinRating::operator()(const Track* track) const
{
    return track->getRating() >= minRating;
}

FilterByType::FilterByType(TrackType type)
    : type(type)
{
}

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
