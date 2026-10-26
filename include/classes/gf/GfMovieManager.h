#ifndef CLASSES_GF_GFMOVIEMANAGER_H
#define CLASSES_GF_GFMOVIEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMovieManager; }
namespace gf { class GfSetupParam; }
namespace mm { namespace mtl { class IAllocator; } }

namespace gf {
// table 0x7100B654C8: the game's side of fw::MovieManager, which plays a movie into a movie layer it makes
class GfMovieManager : public ::mm::mtl::PtrSingleton< ::gf::GfMovieManager> {
public:
    virtual ~GfMovieManager() {}  // slot 0: inline (its table's slot is the singleton's destructor)
    static void build(const GfSetupParam& param);
    static void destroy();
    void close();  // fw::MovieManager's close
    // a 1280x720 movie layer
    void open(mm::mtl::IAllocator* allocator);
    void open(mm::mtl::IAllocator* allocator, int width, int height);
    bool set_file(const char* file);  // fw::MovieManager::set_file's: true when the movie takes the file
    float get_length();
    void play();
    void pause();
    void stop();
    bool isstandby();
    bool ispause();
    bool isplaying();
};
}  // namespace gf

#endif
