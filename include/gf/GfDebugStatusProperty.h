#ifndef GF_GFDEBUGSTATUSPROPERTY_H
#define GF_GFDEBUGSTATUSPROPERTY_H

namespace gf {

// an object's debug switches (GfComProperty owns one by UniquePtr; no table)
class GfDebugStatusProperty {
public:
    bool m_noDamage;  // GfComProperty::procMsgObjectDamage deals no damage while it is set
    bool m_noDeath;   // FallDamagePlugin::onDeactivate leaves 1 hit point after a fall that would kill
};

}  // namespace gf

#endif
