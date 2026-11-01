#ifndef CLASSES_GF_GFAPPENDHANDLES_H
#define CLASSES_GF_GFAPPENDHANDLES_H

#include <string.h>

#include "mm/mtl/FixedArray.h"

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
        memset(&m_handles, 0xff, sizeof(m_handles) + sizeof(m_secondHandles));
    }
    virtual ~GfAppendHandles() {}  // slot 0
    // msg handed to the appended objects, from sender
    void sendMessage(fw::MessageObject* sender, fw::Message& msg) const;
    void eraseHandle(gf::GF_OBJ_HANDLE* handle);
    // the first of handles that is handle, cleared (1.0.0 has it out of line; 3.0.1's eraseHandle inlines it)
    void eraseHandle(mm::mtl::FixedArray<gf::GF_OBJ_HANDLE*, 10>& handles, gf::GF_OBJ_HANDLE* handle);
    void setAlpha(float alpha);
    // every object of both sets destroyed and cleared
    void destroy();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads both sets and
    // m_useSecond. What it does: true when handle is in the set not in use (GfObjFactory::createComponent asks).
    bool fn_71004A38F4(gf::GF_OBJ_HANDLE* handle) const;
    void destroy(mm::mtl::FixedArray<gf::GF_OBJ_HANDLE*, 10>& handles);
    // the objects: one of the two sets of ten, by m_useSecond (inline: the name is not the original's;
    // GfTrinityAttack::isLoading waits for each that is set)
    gf::GF_OBJ_HANDLE* const* getObjHandles() const { return m_useSecond ? m_secondHandles.m_data : m_handles.m_data; }
    // the object at index of the set second picks (inline: the name is not the original's).
    // GfGameParty::buildObjWeapon selects the element (csel ..., ne on the flag): only a bool parameter keeps the
    // flag's own test in the select; written in the caller the branch is canonicalized and the select inverts
    gf::GF_OBJ_HANDLE* getObjHandle(unsigned int index, bool second) const {
        return second ? m_secondHandles[index] : m_handles[index];
    }

    // (the field names are not the original's)
    mm::mtl::FixedArray<gf::GF_OBJ_HANDLE*, 10> m_handles;        // destroy(FixedArray&)'s symbol types them
    mm::mtl::FixedArray<gf::GF_OBJ_HANDLE*, 10> m_secondHandles;
    bool m_useSecond;
};
}  // namespace gf

#endif
