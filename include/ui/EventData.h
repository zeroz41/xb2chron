#ifndef UI_EVENTDATA_H
#define UI_EVENTDATA_H

namespace ui {

// what UIEventManager hands its listeners (UIManager::requestObjectEvent copies its 0x18 bytes)
struct EventData {
    // it zeroes the parameters only: senders set the type after it, and bytes 2-7 stay as they were. m_param2 and
    // m_param3 go first: a sender that sets m_param0 stores the zeroed pair before m_param1 (GfMenuObjFade::dispLoading,
    // GfMenuCallManager::reciveUIEvent), and the members of the union below are not merged into one block
    EventData() : m_param2(0), m_param3(0) {
        m_param0 = 0;
        m_param1 = 0;
    }
    unsigned short m_type;  // what happened: 0xD, an event a UIEventCondition raised
    unsigned char pad_2[6];
    // the parameters share their bytes with 8-byte and 16-bit views. The 8-byte member makes the event 8-aligned:
    // listeners read two neighbouring parameters with one 8-byte load (GfMenuObjNameSelect's reads m_param0 with
    // m_param1 and m_param2 with m_param3), which the compiler only does for an 8-aligned first one
    union {
        struct {
            union {
                struct {
                    union {
                        int m_param0;  // per type: the condition's event; for a fade's start (0xA) and end (0xB), its channel
                        unsigned short m_param0Short;  // the same, where a type passes 16 bits: 0x21 (a menu object's open), its index
                    };
                    int m_param1;  // per type: the condition's first user value; for 5, 1 when the menu's layer is ready
                };
                unsigned long m_param01;  // the two as one (the name is not the original's; no code reads it)
            };
            int m_param2;  // per type
            int m_param3;  // per type
        };
        // the parameters as 16-bit values: GfMenuObjFade's fade (0x100) passes its frames, colour, alpha and channel
        // (the name is not the original's)
        unsigned short m_paramShort[8];
    };
};

}  // namespace ui

#endif
