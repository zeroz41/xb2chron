#ifndef CLASSES_CMOVIENX_CMOVIE_H
#define CLASSES_CMOVIENX_CMOVIE_H

#include "classes/ICMovie.h"

namespace mm { namespace mtl { class IAllocator; }}
class MovieDecoderPlayer;

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
    // fields: fw::MovieManager::open makes it 0x28 bytes (the names are not the original's)
    MovieDecoderPlayer* m_player;
    unsigned char* m_frame;  // a 1280x720 NV12 frame (initialize fills it, finalize frees it)
    unsigned long m_frameSize;
    mm::mtl::IAllocator* m_allocator;
};
}  // namespace CMovieNX

#endif
