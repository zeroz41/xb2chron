#ifndef CLASSES_EVENT_CAPTUREMANAGER_H
#define CLASSES_EVENT_CAPTUREMANAGER_H
#include "mm/mtl/Bitflag.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D988; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CaptureManager>
class CaptureManager : public IManager, public mm::mtl::Singleton<CaptureManager> {
public:
    virtual ~CaptureManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void ready();
    void start();
    void stop();
    void update();
    void render();

    // OnEventProc: bit 0 gates ready(), bits 0..1 == 1 gate start(), bit 1 gates stop(); the name is not the original's
    mm::mtl::Bitflag<32> m_flags;  // @0x10 (a 32-bit wrapper: start loads it on its own, not with m_type)
    // the capture's kind: start takes 0..2 for MOV_PATH, 3..5 for JPG_PATH; stop re-enables fades for 0..3 (the
    // name is not the original's)
    unsigned int m_type;  // 0x14
    // stop clears the event colour filter when it is set; the name is not the original's
    unsigned int m_colorFilter;  // 0x18
    unsigned int pad_1c;  // start zeroes it
    // names render appends (FixStr<16>: `m_nLen < LEN` asserted at +0x10 of each 0x14-byte element); the name is not
    // the original's
    mm::mtl::FixedVector<mm::mtl::FixStr<16>, 512> m_names;  // 0x20 (count at 0x2820)
    // start's paths (the names are not the original's): the device start appends ":" and JPG_PATH or MOV_PATH to
    mm::mtl::FixStr<128> m_device;  // 0x2828
    mm::mtl::FixStr<128> m_dir;     // 0x28ac m_device + ":" + JPG_PATH or MOV_PATH
    mm::mtl::FixStr<128> m_base;    // 0x2930 m_dir + "/" + Manager's m_sceneName
    mm::mtl::FixStr<128> m_rawAvi;  // 0x29b4 "%s/raw_%s.avi"
    mm::mtl::FixStr<128> m_mpg;     // 0x2a38 "%s/%s.mpg"
    mm::mtl::FixStr<128> m_halfMpg;  // 0x2abc "%s/half_%s.mpg"

    // the capture folders (.data pointers to "/MonolithSoft/BF2/jpeg" and "/MonolithSoft/BF2/movie")
    static const char* JPG_PATH;
    static const char* MOV_PATH;
};
}  // namespace event

#endif
