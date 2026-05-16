#include "track.h"
/*
 * Ringtone – to be implemented by you!
 * When done, define RINGTONE_IMPLEMENTED or compile with -DRINGTONE_IMPLEMENTED to run test.cpp for this class (make it pass).
 *
 * Ringtone represents a short audio clip used as a phone ringtone.
 * It inherits from Track and adds one field:
 *   bool loopable – true if the ringtone should repeat continuously.
 *
 * Include:
 *
 * Constructor – Ringtone(string title, double duration, double rating, string filename, bool loopable)
 *
 * clone() – Ringtone* clone() const override:
 *   Return: new Ringtone object.
 *
 * getInfo() – string getInfo() const override.
 *   Use ostringstream to build and return a formatted string (see other classes for examples). Must include loopable field (and others).
 *
 * isLoopable() – bool isLoopable() const:
 *   Return: loopable
 */