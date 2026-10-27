#ifndef NN_CODEC_H
#define NN_CODEC_H

// NintendoSDK's nn::codec, as far as the module imports it. The size is the one ssd::StreamController's layout
// shows (its next field follows 0x30 bytes later).
namespace nn { namespace codec {

class OpusDecoder {
public:
    OpusDecoder();
    ~OpusDecoder();

    unsigned long GetWorkBufferSize(int sampleRate, int channelCount) const;
    int Initialize(int sampleRate, int channelCount, void* workBuffer, unsigned long workBufferSize);
    int DecodeInterleaved(unsigned long* outSize, int* outSampleCount, short* outBuffer, unsigned long outBufferSize,
                          const void* inBuffer, unsigned long inBufferSize);

    unsigned char storage_[0x30];
};

}}  // namespace nn::codec

#endif
