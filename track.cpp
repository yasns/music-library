#include "track.h"
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

int Track::count = 0;

NotImplementedException::NotImplementedException()
    : runtime_error("not implemented")
{
}

Track::Track(string title, double duration, double rating, string filename)
    : title(title), duration(duration), rating(rating), filename(filename)
{
    count++;
}

Track::~Track()
{
    count--;
}

string Track::getInfo() const
{
    throw NotImplementedException();
}

bool Track::matches(const string& query) const
{
    return containsInsensitive(title, query);
}

string Track::getTitle() const
{
    return title;
}

double Track::getDuration() const
{
    return duration;
}

double Track::getRating() const
{
    return rating;
}

string Track::getFilename() const
{
    return filename;
}

bool Track::operator<(const Track& other) const
{
    return title < other.title;
}

int Track::getCount()
{
    return count;
}
