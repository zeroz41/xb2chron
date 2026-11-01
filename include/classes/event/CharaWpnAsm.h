#ifndef CLASSES_EVENT_CHARAWPNASM_H
#define CLASSES_EVENT_CHARAWPNASM_H

#include "mm/mtl/FixedVector.h"

namespace gf { class GfEvtModel; }

namespace event {
// table 0x7100B3CB18
class CharaWpnAsm {
public:
    virtual ~CharaWpnAsm();  // slot 0
    // the weapon command execCmd runs (its values are not known yet)
    enum CMD : int;
    // 0x71000E0928: pushes the command's motion numbers (CharaEvaPlayer::setBattleWeapon passes weapon - 1)
    void execCmd(gf::GfEvtModel* model, CMD cmd, bool left, void* param);
    // 1.0.0's CharaWpnAsm::mount (0x71000C8F98, out of line there; 3.0.1's CharaEvaPlayer::setMountWeapon inlines
    // it): one motion (the mount flag), bit 1 = mounted, bit 2 = left, bit 0 cleared; the parameter names are not
    // the original's
    void mount(gf::GfEvtModel* model, bool mounted, bool left) {
        m_mots.clear();
        m_mots.push_back(mounted);
        pad_50 = m_mots[m_mots.size() - 1];
        unsigned int flags = pad_8 & ~1u;
        flags = mounted ? (flags | 2) : (flags & ~2u);
        flags = left ? (flags | 4) : (flags & ~4u);
        m_model = model;
        pad_8 = flags;
    }
    unsigned int pad_8;  // 0x8: flags update tests
    unsigned char pad_c[0x4];
    // the model mount() stores (the name is not the original's)
    gf::GfEvtModel* m_model;  // 0x10
    unsigned char pad_18[0x10];
    // execCmd (0x71000E0928) pushes motion numbers, update clears them (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 8> m_mots;  // 0x28 (count at 0x48)
    unsigned int pad_50;  // 0x50: update sets 1
};
}  // namespace event

#endif
