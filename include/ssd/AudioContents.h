#ifndef SSD_AUDIOCONTENTS_H
#define SSD_AUDIOCONTENTS_H

namespace ssd {

// an audio file's contents header: AudioFileSadf::PreLoad constructs one on its stack and reads 0x80 bytes
// into it (the size is from that read)
class AudioContents {
public:
    AudioContents();

    unsigned char pad_0[0x80];
};

}  // namespace ssd

#endif
