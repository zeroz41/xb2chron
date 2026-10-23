#ifndef CLASSES_ICMOVIE_H
#define CLASSES_ICMOVIE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace mm { namespace mtl { class IAllocator; } }

// table none (its derived classes': CMovie's at 0x7100B42368 holds PtrSingleton<ICMovie>'s destructor in slot 0);
// the movie player interface fw::MovieManager calls, the one mm::mtl::PtrSingleton<ICMovie> holds
class ICMovie : public ::mm::mtl::PtrSingleton< ::ICMovie> {
public:
    virtual ~ICMovie() {}  // slot 0
    virtual void initialize(mm::mtl::IAllocator*) = 0;  // slot 2
    virtual void finalize() = 0;  // slot 3
    virtual void update(unsigned char*, int, int, int) = 0;  // slot 4: the buffer, its width and height, pixel size
    virtual int set_file(char const*) = 0;  // slot 5: 0 when it succeeds (MovieManager::set_file's)
    virtual float get_length() = 0;  // slot 6
    virtual float pos() = 0;  // slot 7
    virtual void play() = 0;  // slot 8
    virtual void pause() = 0;  // slot 9
    virtual void stop() = 0;  // slot 10
    virtual bool isstandby() = 0;  // slot 11
    virtual bool ispause() = 0;  // slot 12
    virtual bool isplaying() = 0;  // slot 13
    virtual void doHomeMenu(bool) = 0;  // slot 14
};

#endif
