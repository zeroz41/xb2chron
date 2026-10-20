#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B644A0
class GfMenuObjQuestLog : public ::gf::GfMenuObject {
public:
    class CompleteListener;
    class LogListener;
    class OrderListener;
    class TitleListener;
    virtual ~GfMenuObjQuestLog();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
