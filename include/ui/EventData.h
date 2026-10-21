#ifndef UI_EVENTDATA_H
#define UI_EVENTDATA_H

namespace ui {

// what UIEventManager hands its listeners (UIManager::requestObjectEvent copies its 0x18 bytes)
struct EventData {
    // it zeroes the parameters only: senders set the type after it, and bytes 2-7 stay as they were
    EventData() : m_param0(0), m_param1(0), m_param2(0), m_param3(0) {}
    unsigned short m_type;  // what happened: 0xD, an event a UIEventCondition raised
    unsigned char pad_2[6];
    union {
        int m_param0;  // per type: the condition's event; for a fade's start (0xA) and end (0xB), its channel
        unsigned short m_param0Short;  // the same, where a type passes 16 bits: 0x21 (a menu object's open), its index
    };
    int m_param1;  // per type: the condition's first user value; for 5, 1 when the menu's layer is ready
    int m_param2;  // per type
    int m_param3;  // per type
};

}  // namespace ui

#endif
