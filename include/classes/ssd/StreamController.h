#include "ssd/Mutex.h"

#ifndef CLASSES_SSD_STREAMCONTROLLER_H
#define CLASSES_SSD_STREAMCONTROLLER_H

#include "classes/ssd/FileStream.h"
#include "classes/ssd/List.h"
#include "classes/ssd/MemoryBuffer.h"
#include "classes/ssd/StreamBuffer.h"
#include "classes/ssd/WaveSource.h"
#include "nn/codec.h"
#include "ssd/Debug.h"

namespace ssd {
// table 0x7100B82360. sizeof 0x278: VoiceHandle::DeleteStream destroys its block's instances 0x278 bytes apart.
// SystemCore links it into its stream list through the Node base at 0x0. Streams a WaveSource's file through
// file_ into buffer_ (Opus data decoded by opusDecoder_). The field names are not the original's.
class StreamController : public List<StreamController>::Node {
public:
    StreamController();
    virtual ~StreamController();  // slot 0

    void Execution();
    void ExecCloseStream();
    void ExecOpenStream();
    void ExecReadStream(Result (StreamBuffer::*inData)(const void*, unsigned long, bool));
    Result InitStream(WaveSource* source, unsigned long bufferSize, unsigned long startPosition);
    Result QuitStream();
    Result ResetStream();
    Result CloseStream();
    void ExecAdpcmDecode();
    void ExecOpusDecode();
    Result OutData(unsigned char* data, unsigned long size, unsigned long* outSize, bool* end);
    void SetReadPosition(unsigned long position);

    // numbers each controller (the constructor takes the next one)
    static unsigned int idCounter_;

    // a copy of the source InitStream is given (its path, opened by ExecOpenStream)
    WaveSource source_;
    unsigned int id_;
    // InitStream has started the stream (ExecCloseStream clears it); a byte nothing found uses; CloseStream asks
    // Execution to close it; InitStream has run (QuitStream clears it)
    bool active_;
    bool pad_ed;
    bool closeRequested_;
    bool initialized_;
    // the file is open (ExecOpenStream opens it while clear; SetReadPosition works only while set)
    bool fileOpen_;
    // the buffer holds enough to play (0x20000 bytes) or the data has ended
    bool bufferReady_;
    // the source loops (its format's loop flag)
    bool loop_;
    // the read position reached the end; a flag set and cleared with it
    bool readEnd_;
    bool pad_f4;
    // VoiceHandle::Stop clears it
    bool streaming_;
    // SetReadPosition asks Execution to move the read position, and holds the Opus decoder meanwhile
    bool seekRequested_;
    bool seekPending_;
    // 1 closed, 3 closing, 4 opening, 6 open
    int state_;
    FileStream file_;
    // the StreamBuffer::InData* ExecReadStream fills buffer_ with, and the Exec*Decode Execution runs
    Result (StreamBuffer::*inData_)(const void*, unsigned long, bool);
    void (StreamController::*decode_)();
    StreamBuffer buffer_;
    nn::codec::OpusDecoder opusDecoder_;
    // the decoder's work buffer and the table of Opus frame offsets read from the file
    void* opusWorkBuffer_;
    unsigned int* opusFrameOffsets_;
    // OutData's output for ExecOpusDecode: where, how much room, how much was decoded, how long it took (seconds)
    unsigned char* decodeOutput_;
    unsigned long decodeOutputSize_;
    unsigned long decodedSize_;
    double decodeTime_;
    // frames decoded by the last ExecOpusDecode, the next frame, and the decode state (1 idle, 2 requested,
    // 3 decoding, 4 done)
    int decodedFrames_;
    int frameIndex_;
    int decodeState_;
    // a buffer ExecCloseStream gives back (nothing found allocates it); the position InitStream is given
    void* extraBuffer_;
    unsigned long startPosition_;
    // the position SetReadPosition asks for
    unsigned long seekPosition_;
    // the data's offset in the file, the read position in it, its size, and the loop start and end
    unsigned long dataOffset_;
    unsigned long readPosition_;
    unsigned long dataSize_;
    unsigned long loopStart_;
    unsigned long loopEnd_;
    unsigned char pad_238[0x8];
    // the Opus loop's first and end frames and the frame count
    int loopStartFrame_;
    int loopEndFrame_;
    int frameCount_;
    // the loops played, and those left (-1: endless): VoiceHandle::GetRemainLoopCount / SetRemainLoopCount
    int loopCount_;
    int remainLoopCount_;
    // the block ExecReadStream reads the file into
    MemoryBuffer readBuffer_;
};
}  // namespace ssd

#endif
