#ifndef CLASSES_EVENT_MOVIEMANAGER_H
#define CLASSES_EVENT_MOVIEMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "mm/mtl/FixStr.h"

namespace event {
// a base of event::MovieManager no evidence names yet
class TUnk_B3D308 {
public:
    virtual ~TUnk_B3D308() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MovieManager no evidence names yet
class TUnk_B3D330 {
public:
    virtual ~TUnk_B3D330() {}
};
// table 0x7100B3D308; base at 0x0 unknown (TUnk_B3D308), base at 0x8 unknown (TUnk_B3D330)
class MovieManager : public TUnk_B3D308, public TUnk_B3D330 {
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
    // setScriptFlag's bit; the name is not the original's
    bool isScriptFlag() const { return (pad_10 & 0x100) != 0; }
    // fields the constructor initializes; what they hold is not known yet
    unsigned int pad_10;
    mm::mtl::FixStr<256> pad_14;
    bool pad_118;
    mm::mtl::FixStr<256> pad_11c;
    long pad_220;  // -1 at first
    unsigned char pad_228[0x8];
};
}  // namespace event

#endif
