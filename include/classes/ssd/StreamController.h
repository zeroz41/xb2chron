#ifndef CLASSES_SSD_STREAMCONTROLLER_H
#define CLASSES_SSD_STREAMCONTROLLER_H

namespace ssd {
// table 0x7100B82360. sizeof 0x278: VoiceHandle::DeleteStream destroys its block's instances 0x278 bytes apart.
// The field names are not the original's.
class StreamController {
public:
    virtual ~StreamController();  // slot 0

    void QuitStream();
    void ResetStream();

    unsigned char pad_8[0xed];
    bool streaming_;  // 0xF5: VoiceHandle::Stop clears it
    unsigned char pad_f6[0x15a];
    int remainLoopCount_;  // 0x250: VoiceHandle::GetRemainLoopCount / SetRemainLoopCount
    unsigned char pad_254[0x24];
};
}  // namespace ssd

#endif
