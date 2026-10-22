#ifndef CLASSES_GF_GFWEAPON_H
#define CLASSES_GF_GFWEAPON_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B54DE8
class GfWeapon {
public:
    virtual ~GfWeapon();  // slot 0
    // the objects of the weapon: one of its two sets of ten, by m_useSecond (inline: the name is not the original's;
    // GfTrinityAttack::isLoading waits for each that is set)
    gf::GF_OBJ_HANDLE* const* getObjHandles() const { return m_useSecond ? m_secondHandles : m_handles; }

    // (the field names are not the original's)
    gf::GF_OBJ_HANDLE* m_handles[10];
    gf::GF_OBJ_HANDLE* m_secondHandles[10];
    bool m_useSecond;
};
}  // namespace gf

#endif
