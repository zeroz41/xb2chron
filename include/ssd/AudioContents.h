#ifndef SSD_AUDIOCONTENTS_H
#define SSD_AUDIOCONTENTS_H

namespace ssd {

// an audio file's contents header: AudioFileSadf::PreLoad constructs one on its stack and reads 0x80 bytes
// into it (the size is from that read)
class AudioContents {
public:
    AudioContents();

    unsigned char pad_0[0x34];
    // the size of the audio data and each channel's data offset from it (WaveSource::GetDataSize and
    // GetDataAddress read them for format 3; the names are not the original's)
    unsigned int dataSize;
    unsigned char pad_38[0x28];
    unsigned int channelDataOffset[8];
};

}  // namespace ssd

#endif
