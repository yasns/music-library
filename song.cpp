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

Song::Song(string title, double duration, double rating, string filename,
           string artist, string album, int year, string genre, int playCount)
    : Track(title, duration, rating, filename), artist(artist), album(album), year(year), genre(genre), playCount(playCount)
{
}

Song* Song::clone() const
{
    return new Song(getTitle(), getDuration(), getRating(), getFilename(), artist, album, year, genre, playCount);
}

bool Song::matches(const string& query) const
{
    return Track::matches(query)
        || containsInsensitive(artist, query)
        || containsInsensitive(album, query)
        || containsInsensitive(genre, query);
}

string Song::getInfo() const
{
    ostringstream oss;
    oss << "Song: " << getTitle() << " | " << getFilename() << " | " << artist
        << " | " << album << " | " << year << " | " << genre
        << " | plays:" << playCount << " | " << getDuration() << "s | " << getRating();
    return oss.str();
}

void Song::incrementPlayCount()
{
    playCount++;
}

int Song::getPlayCount() const
{
    return playCount;
}

string Song::getArtist() const
{
    return artist;
}

string Song::getAlbum() const
{
    return album;
}

int Song::getYear() const
{
    return year;
}

string Song::getGenre() const
{
    return genre;
}