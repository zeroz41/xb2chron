#ifndef CLASSES_FW_MOVIEMANAGER_H
#define CLASSES_FW_MOVIEMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/ml/IWorkBackground.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class MovieManager; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B422C0; the base at 0x10 is mm::mtl::PtrSingleton<fw::MovieManager> (1.0.0's destructor stores its
// table there and clears its instance)
class MovieManager : public ::fw::ManagerObject,
                     public ::mm::mtl::PtrSingleton< ::fw::MovieManager>,
                     public ::ml::IWorkBackground {
public:
    virtual ~MovieManager();  // slot 0
    virtual void getName() const;  // slot 5
    virtual void bkgHomeMenu(bool);  // slot 8
    void open(mm::mtl::IAllocator* allocator, unsigned int layer);
    void close();
    void open(mm::mtl::IAllocator* allocator, int width, int height, unsigned int layer);
    void stop();
    void set_file(const char* file);
    float get_length();
    void play();
    void pause();
    bool isstandby();
    bool ispause();
    bool isplaying();
};
}  // namespace fw

#endif
