#ifndef CLASSES_CMOVIENX_CMOVIE_H
#define CLASSES_CMOVIENX_CMOVIE_H

namespace mm { namespace mtl { class IAllocator; }}

namespace CMovieNX {
// table none (its derived classes')
class CMovie {
public:
    virtual ~CMovie();  // slot 0
    virtual void initialize(mm::mtl::IAllocator*);  // slot 2
    virtual void finalize();  // slot 3
    virtual void update(unsigned char*, int, int, int);  // slot 4
    virtual void set_file(char const*);  // slot 5
    virtual void get_length();  // slot 6
    virtual void pos();  // slot 7
    virtual void play();  // slot 8
    virtual void pause();  // slot 9
    virtual void stop();  // slot 10
    virtual bool isstandby();  // slot 11
    virtual void ispause();  // slot 12
    virtual bool isplaying();  // slot 13
    virtual void doHomeMenu(bool);  // slot 14
};
}  // namespace CMovieNX

#endif
