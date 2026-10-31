#ifndef LAYER_LAYERACCFORMAT_H
#define LAYER_LAYERACCFORMAT_H

namespace layer {
// the header LayerAccFormat's constructor reads (the names are not the original's)
struct LyrFormatHeader {
    unsigned int m_magic;  // "LAHD", "LAPS", "LAFT" or "LATS" in the file (types 1-4)
    unsigned int m_version;  // LayerAccFormat knows 10001
    unsigned char m_flags;  // 0x8: a type 1 header's bit 5 sets m_flag
    unsigned char pad_9[0xF];
    unsigned int m_entryOfs;  // 0x18: the offset of a type 1 header's entry count (a u16)
    unsigned char pad_1C[0x8];
    unsigned int m_data;  // 0x24: non-zero when a type 1 header names data
};
// what a layer resource's header says it is (the constructor reads it); the names are not the original's
class LayerAccFormat {
public:
    LayerAccFormat(const void* data);
    unsigned int m_type;  // 0: none it knows; 1-4: by the header's magic
    bool m_hasData;       // its type 1 header names data (or type 3)
    bool m_flag;          // bit 5 of a type 1 header's flags: UIPolygonObject takes no texture with it set
    bool m_multi;         // a type 1 header with more than one entry
};
}  // namespace layer

#endif
