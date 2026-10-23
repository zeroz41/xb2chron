#ifndef FW_PADRELAY_H
#define FW_PADRELAY_H

#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Map.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {

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
    void bind(int padNo, int, mm::mtl::IAllocator* allocator);  // the middle argument's role is not known
    void unbind();
    void update();

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

    int pad_0;  // the constructor stores -1
    int pad_4;  // the constructor stores -1
    ActionMap m_actions;  // bindAction's handlers by name (the name is not the original's)
    AxisMap m_axes;  // bindAxis's handlers by name (the name is not the original's)
};

}  // namespace fw

#endif
