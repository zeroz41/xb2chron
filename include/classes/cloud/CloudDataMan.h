#ifndef CLASSES_CLOUD_CLOUDDATAMAN_H
#define CLASSES_CLOUD_CLOUDDATAMAN_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }
namespace ml { class FileHandleTh; }

namespace cloud {
// table 0x7100B7A2A0: reads the cloud's shader package and textures (the constructor starts the reads)
class CloudDataMan : public ::ml::IWorkEvent {
public:
    CloudDataMan();
    virtual ~CloudDataMan();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    bool isReadOk() const;

    // the names below are not the original's
    // 0 shd_cloud.wishp, 1 volume.witex, 2 volume2.witex, 3 pnoise.witex, 4 tg_smoke_01_n.witex
    void* m_pData[5];                 // 0x8, each file's data once read
    unsigned int m_size[5];           // 0x30, the event's m_result for it
    ml::FileHandleTh* m_hFile[5];     // 0x48, the reads still going
};
}  // namespace cloud

#endif
