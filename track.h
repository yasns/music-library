// Track hierarchy — Song, Podcast, Ringtone (described, not implemented).
// Author: Matas Jasiūnas
// Developed with the assistance of Claude Sonnet 4.6 by Anthropic.
#ifndef TRACK_H
#define TRACK_H
#include <string>
#include <stdexcept>

// Thrown by methods that are declared but not yet implemented (e.g. Ringtone).
struct NotImplementedException : public std::runtime_error {
    NotImplementedException();
};

// Abstract base for all audio tracks. Concrete type is preserved via clone() (Prototype pattern).
// Subclasses override getInfo() to describe themselves, the base implementation throws NotImplementedException.
class Track {
    std::string title;
    double duration;
    double rating;
    std::string filename;
    static int count;
public:
    Track(std::string title, double duration, double rating, std::string filename); // duration in seconds; rating in [0.0, 5.0]
    Track(const Track&) = delete;
    Track& operator=(const Track&) = delete;
    virtual Track* clone() const = 0; // returns a heap-allocated copy preserving the concrete type
    virtual ~Track();
    virtual std::string getInfo() const; // returns a formatted one-line description of this track
    virtual bool matches(const std::string& query) const; // case-insensitive partial match against searchable fields
    std::string getTitle() const;
    double getDuration() const; // seconds
    double getRating() const; // 0.0–5.0
    std::string getFilename() const;
    bool operator<(const Track& other) const; // compares by title
    static int getCount(); // number of Track instances currently alive (for leak detection)
protected:
    static bool containsInsensitive(const std::string& s, const std::string& q);
};

// A music track with artist, album, year, genre, and play count.
class Song : public Track {
    std::string artist;
    std::string album;
    int year;
    std::string genre;
    int playCount;
public:
    Song(std::string title, double duration, double rating, std::string filename,
         std::string artist, std::string album, int year, std::string genre, int playCount);
    Song(const Song&) = delete;
    Song& operator=(const Song&) = delete;
    Song* clone() const override;
    ~Song() override;
    bool matches(const std::string& query) const override;
    std::string getInfo() const override;
    void incrementPlayCount();
    int getPlayCount() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    int getYear() const;
    std::string getGenre() const;
};

// A podcast episode with host, episode number, and publish date.
class Podcast : public Track {
    std::string host;
    int episodeNumber;
    std::string publishDate;
public:
    Podcast(std::string title, double duration, double rating, std::string filename,
            std::string host, int episodeNumber, std::string publishDate);
    Podcast(const Podcast&) = delete;
    Podcast& operator=(const Podcast&) = delete;
    Podcast* clone() const override;
    ~Podcast() override;
    bool matches(const std::string& query) const override;
    std::string getInfo() const override;
    std::string getHost() const;
    int getEpisodeNumber() const;
    std::string getPublishDate() const;
};

#endif
