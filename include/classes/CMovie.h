#ifndef CLASSES_CMOVIE_H
#define CLASSES_CMOVIE_H

#include "classes/CMovieNX/CMovie.h"

// table 0x7100B42368
class CMovie : public ::CMovieNX::CMovie {
public:
    virtual ~CMovie() {}  // slot 0: inline (its table and D0 are emitted where fw::MovieManager makes it)
};

#endif
