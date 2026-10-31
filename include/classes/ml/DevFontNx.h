#ifndef CLASSES_ML_DEVFONTNX_H
#define CLASSES_ML_DEVFONTNX_H

#include "classes/ml/DevFont.h"

namespace ml {
// table 0x7100B77240
class DevFontNx : public ::ml::DevFont {
public:
    // createFont declared first: the key function (the destructor and releaseFont are inline: 0x71006BDA04,
    // 0x71006BDA28)
    // inline: WorkUtil::createWork<DevFontNx> inlines it
    DevFontNx(const char* name, WorkObj* parent) : DevFont(name, parent) {}
    virtual bool createFont();  // slot 6
    virtual ~DevFontNx() {}  // slot 0
    virtual void wkUpdate();  // slot 4
    virtual bool releaseFont() { return true; }  // slot 7
};
}  // namespace ml

#endif
