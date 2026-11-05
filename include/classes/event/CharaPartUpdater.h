#ifndef CLASSES_EVENT_CHARAPARTUPDATER_H
#define CLASSES_EVENT_CHARAPARTUPDATER_H

namespace event {
// table 0x7100B3CAB8
class CharaPartUpdater {
public:
    virtual ~CharaPartUpdater();  // slot 0
    void setExtDisp(const char* name, bool disp);
    void setExtParam(const char* name, float value);
    void updateRequest();
};
}  // namespace event

#endif
