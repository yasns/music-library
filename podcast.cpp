#include "track.h"
#include <sstream>
using namespace std;

Podcast::Podcast(string title, double duration, double rating, string filename,
                 string host, int episodeNumber, string publishDate)
    : Track(title, duration, rating, filename), host(host), episodeNumber(episodeNumber), publishDate(publishDate)
{
}

Podcast* Podcast::clone() const
{
    return new Podcast(getTitle(), getDuration(), getRating(), getFilename(), host, episodeNumber, publishDate);
}

Podcast::~Podcast() = default;

bool Podcast::matches(const string& query) const
{
    return Track::matches(query) || Track::containsInsensitive(host, query);
}

string Podcast::getInfo() const
{
    ostringstream oss;
    oss << "Podcast: " << getTitle() << " | " << getFilename() << " | host:" << host
        << " | ep:" << episodeNumber << " | " << publishDate
        << " | " << getRating();
    return oss.str();
}

string Podcast::getHost() const
{
    return host;
}

int Podcast::getEpisodeNumber() const
{
    return episodeNumber;
}

string Podcast::getPublishDate() const
{
    return publishDate;
}