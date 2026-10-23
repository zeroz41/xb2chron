#ifndef FW_PADRELAY_H
#define FW_PADRELAY_H

#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Map.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace fw { class PadResEvent; struct ResAction; struct ResActionInfo; struct ResAxisInfo; }

namespace fw {

// a pad action key (PadResEvent's ResKey::m_key): the name is the original's (getPadKey's static's symbol); the
// keys' own names are not known
enum PadActKey : unsigned int {};

// the fw::PadData bit of a pad action key
inline unsigned int getPadKey(PadActKey key) {
    static const unsigned int PAD_RAW_KEY[] = {
        0x1000,    0x2000,    0x4000,    0x8000,     0x8,        0x4,        0x2,        0x1,        0x20,
        0x80,      0x800,     0x10,      0x40,       0x400,      0x200,      0x100,      0x40000,    0x1000000,
        0x2000000, 0x4000000, 0x8000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000,
    };
    return PAD_RAW_KEY[key];
}

// (functions, by its symbols)
class PadEventImporter {
public:
    // the pad event resource of a "PADD" binary of version 1 (only its table installed), none for another
    static PadResEvent* create(void* binary, const char* name);
};

// (functions, by its symbols)
class PadRelayUtil {
public:
    // the framework pad key a named input is bound to on a pad: whether it is bound (StateUtil asks pads 0-4; it
    // passes 0 for the two middle arguments, whose roles are not known)
    static bool getFwPadKey(unsigned int pad, const char* name, unsigned int, unsigned int, unsigned int* pKey);
};

// a pad's named actions and axes, bound to handlers (no table): PadBattle holds two, PadField one
class PadRelay {
public:
    typedef mm::mtl::Delegate<void()> ActionDelegate;
    typedef mm::mtl::Delegate<void(float)> AxisDelegate;

    PadRelay();
    ~PadRelay();
    void bind(int padNo, int eventNo, mm::mtl::IAllocator* allocator);
    void unbind();
    void update();
    bool checkAction(const ResAction& action);
    void invokeAction(const ResActionInfo& info);
    void invokeAxis(const ResAxisInfo& info);

    // the action named name calls object's func (the instances are the binding classes' units': CameraPadData's,
    // GfGamePad's, GfGameTarget's, PadField's, PadBattle's). The key is made, an empty handler inserted under it,
    // then the node found again and its handler set
    template <typename T, typename F>
    void bindAction(const char* name, T* object, F func) {
        mm::mtl::FixStr<32> key(name);
        m_actions.insert(mm::mtl::MapPair<mm::mtl::FixStr<32>, ActionDelegate>(key, ActionDelegate()));
        if (ActionMap::node* n = m_actions.find(key)) {
            n->value.second.set(object, func);
        }
    }
    // the axis named name calls object's func with its value (as bindAction)
    template <typename T, typename F>
    void bindAxis(const char* name, T* object, F func) {
        mm::mtl::FixStr<32> key(name);
        m_axes.insert(mm::mtl::MapPair<mm::mtl::FixStr<32>, AxisDelegate>(key, AxisDelegate()));
        if (AxisMap::node* n = m_axes.find(key)) {
            n->value.second.set(object, func);
        }
    }

    typedef mm::mtl::Map<mm::mtl::FixStr<32>, ActionDelegate> ActionMap;
    typedef mm::mtl::Map<mm::mtl::FixStr<32>, AxisDelegate> AxisMap;

    int m_padNo;    // bind's first argument: the control pad checkAction and invokeAxis read; the constructor stores
                    // -1 (the name is not the original's)
    int m_eventNo;  // bind's second argument: the PadResEventManager resource update runs; the constructor stores -1
                    // (the name is not the original's)
    ActionMap m_actions;  // bindAction's handlers by name (the name is not the original's)
    AxisMap m_axes;  // bindAxis's handlers by name (the name is not the original's)
};

}  // namespace fw

#endif
