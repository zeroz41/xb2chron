#ifndef CLASSES_GF_GFLAYERPAUSE_H
#define CLASSES_GF_GFLAYERPAUSE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfLayerPause; class GF_LP_HANDLE; class GfSetupParam; }

namespace gf {
// table 0x7100B547F8; 0x48 bytes (build allocates them). Counted pauses of the framework's layer groups: each
// setLayerPause hands out a handle (the layer in its low byte, its bit of the group's mask above), and the group is
// unpaused when its last handle is destroyed (the field names are not the original's)
class GfLayerPause : public ::mm::mtl::PtrSingleton< ::gf::GfLayerPause> {
public:
    GfLayerPause()
        : m_layer4Pauses(0), m_layer1Pauses(0), m_layer7Pauses(0), m_layer10Pauses(0), m_layer0Pauses(0),
          m_eventPause4(reinterpret_cast<GF_LP_HANDLE*>(-1)), m_eventPause0(reinterpret_cast<GF_LP_HANDLE*>(-1)),
          m_eventPause1(reinterpret_cast<GF_LP_HANDLE*>(-1)), m_eventPause7(reinterpret_cast<GF_LP_HANDLE*>(-1)),
          m_eventPause10(reinterpret_cast<GF_LP_HANDLE*>(-1)) {
        m_valid = true;
    }
    virtual ~GfLayerPause();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static void gevPause(unsigned int prev, unsigned int next);
    // GfGameEvent::clear hands it its handle
    static void destroyLayerPause(GF_LP_HANDLE*& handle);
    static GF_LP_HANDLE* setLayerPause(unsigned int layer);
    static void destroyLayerPause();
    static bool isLayerPause(unsigned int layer);

    bool m_valid;                  // 0x8: the constructor sets it last, destroy clears it
    unsigned int m_layer4Pauses;   // 0xC: a bit per live handle of layers 4-6
    unsigned int m_layer1Pauses;   // 0x10: layers 1-3
    unsigned int m_layer7Pauses;   // 0x14: layers 7-9
    unsigned int m_layer10Pauses;  // 0x18: layers 10-12
    unsigned int m_layer0Pauses;   // 0x1C: layer 0
    // gevPause's handles: pause bit 0 pauses layers 4, 0, 1 and 7, bit 9 layer 10 (-1 for none)
    GF_LP_HANDLE* m_eventPause4;   // 0x20
    GF_LP_HANDLE* m_eventPause0;   // 0x28
    GF_LP_HANDLE* m_eventPause1;   // 0x30
    GF_LP_HANDLE* m_eventPause7;   // 0x38
    GF_LP_HANDLE* m_eventPause10;  // 0x40
};
}  // namespace gf

#endif
