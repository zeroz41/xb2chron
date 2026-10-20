#ifndef UI_EVENTDATA_H
#define UI_EVENTDATA_H

namespace ui {

// what UIEventManager hands its listeners
struct EventData {
    unsigned short m_type;  // what happened: 0xD, an event a UIEventCondition raised
    unsigned char pad_2[6];
    int m_param0;  // per type: the condition's event; for a fade's start (0xA) and end (0xB), its channel
    int m_param1;  // per type: the condition's first user value; for 5, 1 when the menu's layer is ready
};

}  // namespace ui

#endif
