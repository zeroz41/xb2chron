#ifndef CLASSES_SSD_STREAMCONTROLLER_H
#define CLASSES_SSD_STREAMCONTROLLER_H

#include "classes/ssd/List.h"
namespace ssd {
// table 0x7100B82360. sizeof 0x278: VoiceHandle::DeleteStream destroys its block's instances 0x278 bytes apart.
// SystemCore links it into its stream list through the Node base at 0x0. The field names are not the original's.
class StreamController : public List<StreamController>::Node {
public:
    virtual ~StreamController();  // slot 0

    void QuitStream();
    void ResetStream();

    unsigned char pad_18[0x50];
    // SoundHandle::SetRemainLoopCount refuses (-1) while it is clear (the name is not the original's)
    bool pad_68;
    unsigned char pad_69[0x8c];
    bool streaming_;  // 0xF5: VoiceHandle::Stop clears it
    unsigned char pad_f6[0x15a];
    int remainLoopCount_;  // 0x250: VoiceHandle::GetRemainLoopCount / SetRemainLoopCount
    unsigned char pad_254[0x24];
};
}  // namespace ssd

#endif
