#ifndef CLASSES_EVENT_PARAMVARIABLE_H
#define CLASSES_EVENT_PARAMVARIABLE_H

namespace event {
// table 0x7100B3C018
class ParamVariable {
public:
    ParamVariable() : m_type(0) {
        m_value.s32 = 0;
    }
    virtual ~ParamVariable();  // slot 0

    // what the value holds: setS32 makes it 1, setF32 2, setBool 3, setStr 4 (0 for nothing, clear())
    int m_type;
    union {
        int s32;
        float f32;
        bool b;
        const char* str;
        void* userdata;
    } m_value;
};
}  // namespace event

#endif
