#ifndef CLASSES_FW_DYNAMICSCOLOBJUPDATER_H
#define CLASSES_FW_DYNAMICSCOLOBJUPDATER_H

namespace fw {
// table 0x7100B412F8
class DynamicsColObjUpdater {
public:
    virtual ~DynamicsColObjUpdater();  // slot 0
    virtual void update();  // slot 2
};
}  // namespace fw

#endif
