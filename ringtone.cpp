#include "track.h"
/*
 * Ringtone – to be implemented by you!
 *
 * Ringtone represents a short audio clip used as a phone ringtone.
 * It inherits from Track and adds one field:
 *   bool loopable – true if the ringtone should repeat continuously.
 *
 * Include:
 *
 * Constructor – Ringtone(string title, double duration, double rating, string filename, bool loopable):
 *   Call Track(title, duration, rating, filename) in the initializer list.
 *
 * clone() – Ringtone* clone() const override:
 *   Return: new Ringtone object.
 *
 * getInfo() – string getInfo() const override:
 *   Use ostringstream to build and return a formatted string (see other classes for examples).
 *   Do NOT throw NotImplementedException – Track's base already does that as a placeholder; override this method with a real implementation.
 *
 * isLoopable() – bool isLoopable() const:
 *   Return: loopable
 *
 * Might come in handy:
 *   – Do not add a copy constructor or assignment operator (inherited = delete).
 *   – Do not add an explicit destructor (Track's virtual destructor is enough).
 *   – The order of method definitions in this file must match the declaration
 *     order in track.h: constructor, clone, isLoopable, then getInfo if added.
 */
