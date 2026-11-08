#ifndef CLASSES_EVENT_CHARAPARTUPDATER_H
#define CLASSES_EVENT_CHARAPARTUPDATER_H
#include "mm/mtl/FixedVector.h"

namespace event {
// table 0x7100B3CAB8
class CharaPartUpdater {
public:
    // one queued part change: type 0 setExtDisp, 1 setExtDispWeapon, 2 setExtParam (the setters store these values;
    // the names are not the original's)
    struct Request {
        int m_type;          // 0x0
        const char* m_name;  // 0x8
        float m_value;       // 0x10 setExtDisp(Weapon) store 1 or 0
    };

    virtual ~CharaPartUpdater();  // slot 0
    void setExtDisp(const char* name, bool disp);
    void setExtDispWeapon(const char* name, bool disp);
    void setExtParam(const char* name, float value);
    void updateRequest();

    unsigned char pad_8[0x10];
    // the queued changes, oldest first; a new one drops the oldest when full and the older one of its kind and
    // name (the name is not the original's)
    mm::mtl::FixedVector<Request, 8> m_requests;  // 0x18
};
}  // namespace event

#endif
