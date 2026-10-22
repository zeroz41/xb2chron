#ifndef CLASSES_FW_SCRIPTINFO_H
#define CLASSES_FW_SCRIPTINFO_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace fw {
// table 0x7100B42B78; 0x240 bytes (mm::mtl::Array<ScriptInfo>::reserve's stride)
class ScriptInfo : public ::ml::IWorkEvent {
public:
    virtual ~ScriptInfo();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7
    void start();
    bool isLoadErr() const;
    bool isFinish() const;
    bool isActive() const;

    unsigned char pad_8[0x238];
};
}  // namespace fw

#endif
