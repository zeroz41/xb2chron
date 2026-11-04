#ifndef CLASSES_GF_GFMENUFIELDPOSADAPTER_H
#define CLASSES_GF_GFMENUFIELDPOSADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/Vec3.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5BD30; a position plugin placed on the screen where a fixed world position is, its UI object kept
// on the screen
class GfMenuFieldPosAdapter : public ::gf::GfMenuAdapter {
public:
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuFieldPosAdapter(ui::UIObjectPlugin* plugin)
        : GfMenuAdapter(plugin, false, true), m_offScreen(false), m_handle(0), m_first(true), m_keepAdjusted(false),
          m_adjusted(false) {}
    virtual ~GfMenuFieldPosAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    // 3.0.1 added the flag (the two-parameter create below passes false to it)
    static GfMenuFieldPosAdapter* create(unsigned int handle, const mm::Vec3& pos, bool keepAdjusted);
    // 1.0.0's create: 1.0.0's GfMenuObjChainIcon::open, GfMenuObjDamageBuff::openUniteCombo and
    // GfMenuObjDropItem::open call create(unsigned int, mm::Vec3 const&) where 3.0.1's call 0x710033D504, which
    // passes false as the flag
    static GfMenuFieldPosAdapter* create(unsigned int handle, const mm::Vec3& pos);
    // inline: 3.0.1 has no copy (create's stores)
    void setup(unsigned int handle, const mm::Vec3& pos, bool keepAdjusted) {
        m_pos = pos;
        m_handle = handle;
        m_offScreen = false;
        m_first = true;
        m_keepAdjusted = keepAdjusted;
        m_adjusted = false;
    }
    // 2.0.0's symbols name it. What it does: with the flag false, gf::util::getScreenPos(screen, world) (tail call);
    // with it true, the same projection through GfInfo::m_viewProj and GfInfo::m_camSize but without getScreenPos's
    // test that the depth (row 2) is at least 1e-6, so a position behind the camera still projects; false when |w| is
    // at most 1e-6. update passes m_keepAdjusted && !m_offScreen as the flag.
    bool getScreenPos(mm::Vec3& screen, const mm::Vec3& world, bool behind);
    // the field names are not the original's
    mm::Vec3 m_pos;  // the world position shown at
    bool m_offScreen;  // set when the object could not be kept on the screen: update stops adjusting it
    unsigned char pad_41[3];
    unsigned int m_handle;  // the UI object kept on the screen
    bool m_first;  // the first update puts the object at 10000, 10000
    bool m_keepAdjusted;  // create's flag: once adjusted, the position stays while GfGameManager::isGameTypeIra
    bool m_adjusted;
    unsigned char pad_4B[5];
};


}  // namespace gf

#endif
