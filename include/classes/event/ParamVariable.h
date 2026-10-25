#ifndef CLASSES_EVENT_PARAMVARIABLE_H
#define CLASSES_EVENT_PARAMVARIABLE_H

#include "mm/mtl/FixStr.h"

namespace event {
// table 0x7100B3C018
class ParamVariable {
public:
    ParamVariable() : m_type(0) {
        m_value.intValue = 0;
    }
    virtual ~ParamVariable();  // slot 0

    void setS32(int value);
    void setF32(float value);
    void setBool(bool value);
    void setStr(const char* value);
    void setUserdata(void* value);
    // 1.0.0 has them out of line (0x7100097270, 0x71000972A0); 3.0.1 inlines them: the value converted when it
    // holds the other number type
    int getS32() const { return m_type == 2 ? (int)m_value.floatValue : m_value.intValue; }
    float getF32() const { return m_type == 1 ? (float)m_value.intValue : m_value.floatValue; }
    // the value as text ("%d", "%f", "true"/"false", the string, "%lld"); empty for nothing
    void createString(mm::mtl::FixStr<256>& str);

    // what the value holds: setS32 makes it 1, setF32 2, setBool 3, setStr 4, setUserdata 5 (0 for nothing, clear())
    int m_type;
    union {
        int intValue;
        float floatValue;
        bool boolValue;
        const char* strValue;
        void* userdata;
    } m_value;
};
}  // namespace event

#endif
