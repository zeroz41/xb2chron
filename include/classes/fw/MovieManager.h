#ifndef CLASSES_FW_MOVIEMANAGER_H
#define CLASSES_FW_MOVIEMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/IWorkBackground.h"
#include "classes/mm/mtl/PtrSingleton.h"

class ICMovie;
namespace fw { class MovieManager; }
namespace layer { class LayerBase; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B422C0; the base at 0x10 is mm::mtl::PtrSingleton<fw::MovieManager> (1.0.0's destructor stores its
// table there and clears its instance)
class MovieManager : public ::fw::ManagerObject,
                     public ::mm::mtl::PtrSingleton< ::fw::MovieManager>,
                     public ::ml::IWorkBackground {
public:
    // inline: Framework::createManager inlines it (the module has no copy); it listens to the background work
    MovieManager() : m_layer(0), m_layerObj(nullptr), m_movie(nullptr), m_playing(false), m_pixelSize(3), m_frame(0) {
        ml::WorkCpu::addBackgroundListener(this);
    }
    virtual ~MovieManager();  // slot 0
    virtual const char* getName() const;  // slot 5
    virtual void bkgHomeMenu(bool);  // slot 8
    void open(mm::mtl::IAllocator* allocator, unsigned int layer);
    void close();
    void open(mm::mtl::IAllocator* allocator, int width, int height, unsigned int layer);
    void stop();
    void update();
    bool set_file(const char* file);  // true when the movie takes the file
    float get_length();
    void play();
    void pause();
    bool isstandby();
    bool ispause();
    bool isplaying();
    // the UI object the movie is drawn into (its on-memory buffer); 0: a memory layer object of its own
    unsigned int m_layer;
    unsigned char pad_24[0x4];
    // the memory layer object the movie is drawn into (made by the second open, or the UI object's)
    layer::LayerBase* m_layerObj;
    ICMovie* m_movie;  // open makes it, close finalizes and deletes it
    bool m_playing;  // play sets it once the movie plays, stop clears it; update shows the UI object by it
    unsigned char pad_39[0x3];
    unsigned int m_pixelSize;  // update's last argument to the movie (the buffer's pixel size; 1 for its own)
    unsigned int m_frame;  // update counts its calls (the name is not the original's)
    unsigned char pad_44[0x4];
};
}  // namespace fw

#endif
