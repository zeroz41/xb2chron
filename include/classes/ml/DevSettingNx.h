#ifndef CLASSES_ML_DEVSETTINGNX_H
#define CLASSES_ML_DEVSETTINGNX_H

namespace ml { class SleepExtendType; }

namespace ml {
// table 0x7100B769C8
class DevSettingNx {
public:
    virtual ~DevSettingNx();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void vf4();  // slot 4
    virtual void vf5();  // slot 5
    virtual void setAutoSleepExtended(ml::SleepExtendType);  // slot 6
    virtual void isAutoSleepExtended() const;  // slot 7
};
}  // namespace ml

#endif
