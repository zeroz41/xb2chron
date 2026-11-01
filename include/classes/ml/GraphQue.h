#ifndef CLASSES_ML_GRAPHQUE_H
#define CLASSES_ML_GRAPHQUE_H

namespace ml { class DevGraphQue; }

namespace ml {
// table 0x7100B77548; one queue of a DevGraphQue (createQue allocates 0x50 bytes; the field names are not the
// original's)
class GraphQue {
public:
    // a queue of two halves of size bytes for owner (DevGraphQue::createQue inlines it; defined in DevGraphQue.h)
    inline GraphQue(DevGraphQue* owner, unsigned int size);
    virtual ~GraphQue();  // slot 0
    // points the queue at its owner's current half and empties it (createQue and DevGraph::wkTail inline it; the
    // name is not the original's). Defined in DevGraphQue.h
    inline void reset();

    DevGraphQue* m_owner;     // 0x08 createQue stores its DevGraphQue
    char* m_buf[2];           // 0x10 one allocation of twice the size, the second half at 0x18
    unsigned int m_size;      // 0x20 the size of a half
    char* m_cur;              // 0x28
    char* m_end;              // 0x30
    unsigned short pad_38;
    unsigned char pad_3a[0x6];
    unsigned long pad_40;
    unsigned int pad_48;
    unsigned char pad_4c[0x4];
};
}  // namespace ml

#endif
