#ifndef CLASSES_EVENT_MOVIEMANAGER_H
#define CLASSES_EVENT_MOVIEMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "mm/mtl/FixStr.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfMovieManager.h"

namespace event {
// table 0x7100B3D308; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::MovieManager>
class MovieManager : public IManager, public mm::mtl::Singleton<MovieManager> {
public:
    virtual ~MovieManager();  // slot 0
    // the constructor (out of line: the unit has it at its own address, Singleton<T>::getPtr calls it)
    MovieManager();
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    void update();
    void render();
    // called by the evt_movie script plugin (application/BF2/ScriptPlayText)
    void captureScreen(bool enable);
    void preload(const char* name, bool obj);
    bool isLoading() const;
    void play(const char* name, bool obj, bool arg);
    void setScriptFlag(bool enable);
    bool isLoadedAuto(const char* name, bool obj) const;
    // builds the movie's file path for name (0x71000F9EA4; isLoadedAuto passes its own path and the name in x0/x1,
    // so it takes no this); returns true (w0 = 1 on its only path)
    static bool makePath(mm::mtl::FixStr<256>& path, const char* name);
    // setScriptFlag's bit; the name is not the original's
    bool isScriptFlag() const { return (pad_10 & 0x100) != 0; }
    // 2.0.0's MovieManager::stop (0x7100111C14, 0x38 bytes); 3.0.1 inlines it everywhere (clear, update,
    // SkipManager::skip): when bit 1 or 2 is set, drops bits 3/5 (with bit 3), starts the 0x22c countdown at 2 and
    // swaps bits 1, 2, 5 for bit 6
    void stop() {
        if (pad_10 & 6) {
            if (pad_10 & 8) {
                pad_10 &= ~0x28;
            }
            pad_22c = 2;
            pad_10 = (pad_10 & ~0x66) | 0x40;
        }
    }
    // 2.0.0's MovieManager::close (stop, then the GfMovieManager movie stopped and closed when bit 0 is set, bits 0
    // and 6 dropped); 3.0.1 inlines it (clear, update)
    void close() {
        stop();
        if (pad_10 & 1) {
            mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->stop();
            mm::mtl::PtrSingleton<gf::GfMovieManager>::sys()->close();
        }
        pad_10 &= ~0x41;
    }
    // true when both names are the same path, each given a leading '/' when it has none
    static bool isSame(const char* a, const char* b);
    // fields the constructor initializes; what they hold is not known yet
    unsigned int pad_10;
    mm::mtl::FixStr<256> pad_14;
    bool pad_118;
    mm::mtl::FixStr<256> pad_11c;
    long pad_220;  // -1 at first
    int pad_228;  // update counts it down while bit 5 is set
    int pad_22c;  // stop sets it to 2; update counts it down while bit 6 is set
};
}  // namespace event

#endif
