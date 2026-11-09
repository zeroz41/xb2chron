#ifndef MM_VAL64_H
#define MM_VAL64_H

namespace mm {

// a 64-bit value: ml::DevFileTh::readFileBlock returns the file's time stamp through one, which
// fw::CommonResource::updateBlock hands to fw::AssetData::AssignFromMemory (its first 8 bytes). 0x18 bytes: the room
// updateBlock's frame gives it below its DevFileParamTh (what follows the value is not known). The field names are
// not the original's.
class VAL64 {
public:
    unsigned long m_value;
    unsigned char pad_8[0x10];
};

}  // namespace mm

#endif
