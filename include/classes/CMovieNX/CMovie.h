#ifndef CLASSES_CMOVIENX_CMOVIE_H
#define CLASSES_CMOVIENX_CMOVIE_H

#include "classes/ICMovie.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace CMovieNX {
// table none (its derived classes'): ::CMovie's destructor goes straight to PtrSingleton<ICMovie>'s, so this one is
// inline and empty
class CMovie : public ::ICMovie {
public:
    virtual ~CMovie() {}  // slot 0
    virtual void initialize(mm::mtl::IAllocator*);  // slot 2
    virtual void finalize();  // slot 3
    virtual void update(unsigned char*, int, int, int);  // slot 4
    virtual int set_file(char const*);  // slot 5
    virtual float get_length();  // slot 6
    virtual float pos();  // slot 7
    virtual void play();  // slot 8
    virtual void pause();  // slot 9
    virtual void stop();  // slot 10
    virtual bool isstandby();  // slot 11
    virtual bool ispause();  // slot 12
    virtual bool isplaying();  // slot 13
    virtual void doHomeMenu(bool);  // slot 14
    unsigned char pad_8[0x20];  // fields: fw::MovieManager::open makes it 0x28 bytes
};
}  // namespace CMovieNX

#endif
