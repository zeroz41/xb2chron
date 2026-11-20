#ifndef CLASSES_EVENT_ALPHAMANAGER_H
#define CLASSES_EVENT_ALPHAMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; class AlphaObj; }
namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// the alpha kinds setAlpha takes (1.0.0's symbols name the type)
enum ALPHA_ATTR : int {};
// table 0x7100B3C120; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::AlphaManager>
class AlphaManager : public IManager, public mm::mtl::Singleton<AlphaManager> {
public:
    // inline: getPtr's static is built in its callers (CharaFade::update)
    AlphaManager() : m_flags(0), m_debugFlags(0) {}
    // out of line (0x71000BA2B8); CharaFade::update sets a character's alpha with attribute 1
    void setAlpha(gf::GF_OBJ_HANDLE* handle, ALPHA_ATTR attr, float alpha, float time);
    // deletes every object (1.0.0 symbol; 3.0.1 keeps only OnEventProc's inlined copy)
    void clear();
    // drops the objects that are gone or opaque again
    void update();
    // the debug list (while m_debugFlags bit 0 is set)
    void render();
    virtual ~AlphaManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

private:
    unsigned int m_flags;  // 0x10 bit 0: update walks the objects (the name is not the original's)
    unsigned int m_debugFlags;  // 0x14 bit 0: render draws the list (the name is not the original's)
    // update and render walk it; render deletes (slot 1) and erases each finished one; the name is not the original's
    mm::mtl::FixedVector<AlphaObj*, 256> m_objs;  // 0x18 (count at 0x818)
};
}  // namespace event

#endif
