#ifndef CLASSES_GF_GFMENUPOSADAPTER_H
#define CLASSES_GF_GFMENUPOSADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "gf/MenuOffset.h"
#include "mm/Pnt.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B5D7E0; a menu object placed on the screen where an object (or a bone of it, or a fixed point) is
class GfMenuPosAdapter : public ::gf::GfMenuAdapter {
public:
    // where update takes its object from instead of m_handle (1.0.0's PartyDriverConverter derives from it; it has
    // no virtual destructor: the adapter frees it with operator delete); the name is not the original's
    class IConverter {
    public:
        virtual GF_OBJ_HANDLE* getGfObjHandle() = 0;  // slot 0
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuPosAdapter(ui::UIObjectPlugin* plugin)
        : GfMenuAdapter(plugin, false, true), m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_bone(), m_world(false),
          m_fixedPoint(false), m_diffOffset(false), m_screenOffset(0, 0), m_converter(nullptr) {}
    virtual ~GfMenuPosAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuPosAdapter* create(unsigned int handle, GF_OBJ_HANDLE* object, const MenuOffset* offset);
    // inline: 1.0.0 has it out of line, 3.0.1 none
    void setup(GF_OBJ_HANDLE* object, const MenuOffset* offset) {
        m_handle = object;
        m_offset = mm::Vec3(0.0f, 0.0f, 0.0f);
        m_bone.m_nLen = 0;
        m_bone.m_str[0] = '\0';
        if (offset != nullptr) {
            m_offset = offset->m_offset;
            m_pos = offset->m_offset;
            if (offset->m_bone != nullptr && offset->m_bone[0] != '\0') {
                m_bone = offset->m_bone;
            }
        }
    }
    static GfMenuPosAdapter* createDiffOffset(unsigned int handle, GF_OBJ_HANDLE* object, const MenuOffset* offset,
                                              unsigned short limitX, unsigned short limitY);
    static GfMenuPosAdapter* createFixedPoint(unsigned int handle, const mm::Vec3& pos, bool world);
    void changeReference(GF_OBJ_HANDLE* object, const MenuOffset* offset);
    GF_OBJ_HANDLE* m_handle;  // the object shown at; -1 for none (a fixed point)
    unsigned char pad_38[8];
    mm::Vec3 m_offset;  // from the object (or its bone), turned with it
    mm::mtl::FixStr<16> m_bone;  // empty: the object's own transform
    mm::Vec3 m_pos;  // the world position update shows at
    // the names are not the original's: a position plugin in the world (createFixedPoint's), a fixed m_pos shown
    // without an object, an offset plugin moved to the position (createDiffOffset's)
    bool m_world;
    bool m_fixedPoint;
    bool m_diffOffset;
    mm::Pnt<short> m_screenOffset;  // added to the screen position; the name is not the original's
    IConverter* m_converter;  // owned
};
}  // namespace gf

#endif
