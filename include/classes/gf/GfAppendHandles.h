#ifndef CLASSES_GF_GFAPPENDHANDLES_H
#define CLASSES_GF_GFAPPENDHANDLES_H

#include <string.h>

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B3FBE8: the objects appended to a mount (gf::GfWeapon derives from it: its table's slot 0 is this
// class's destructor, and GfMountManager::removeMountHandle hands a mount's weapon to eraseHandle)
class GfAppendHandles {
public:
    // GfMountManager::createMount's weapon: none set in either set, the first in use (inline: the name of no
    // out-of-line copy survives)
    GfAppendHandles() : m_useSecond(false) {
        memset(m_handles, 0xff, sizeof(m_handles) + sizeof(m_secondHandles));
    }
    virtual ~GfAppendHandles() {}  // slot 0
    // msg handed to the appended objects, from sender
    void sendMessage(fw::MessageObject* sender, fw::Message& msg) const;
    void eraseHandle(gf::GF_OBJ_HANDLE* handle);
    // the objects: one of the two sets of ten, by m_useSecond (inline: the name is not the original's;
    // GfTrinityAttack::isLoading waits for each that is set)
    gf::GF_OBJ_HANDLE* const* getObjHandles() const { return m_useSecond ? m_secondHandles : m_handles; }

    // (the field names are not the original's)
    gf::GF_OBJ_HANDLE* m_handles[10];
    gf::GF_OBJ_HANDLE* m_secondHandles[10];
    bool m_useSecond;
};
}  // namespace gf

#endif
