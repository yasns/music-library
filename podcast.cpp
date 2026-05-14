#include "track.h"
#include <sstream>
#include <cctype>
using namespace std;

static bool containsInsensitive(const string& s, const string& q)
{
    if (q.empty()) return true;
    string sl = s, ql = q;
    for (char& c : sl) c = tolower((unsigned char)c);
    for (char& c : ql) c = tolower((unsigned char)c);
    return sl.find(ql) != string::npos;
}

Podcast::Podcast(string title, double duration, double rating, string filename,
                 string host, int episodeNumber, string publishDate)
    : Track(title, duration, rating, filename), host(host), episodeNumber(episodeNumber), publishDate(publishDate)
{
}

Podcast* Podcast::clone() const
{
    return new Podcast(getTitle(), getDuration(), getRating(), getFilename(), host, episodeNumber, publishDate);
}

bool Podcast::matches(const string& query) const
{
    return Track::matches(query) || containsInsensitive(host, query);
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