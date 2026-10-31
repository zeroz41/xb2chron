#ifndef ARC_CARCDATA_H
#define ARC_CARCDATA_H

namespace arc {
// an archive in memory: its binary and, past the header (the offset at its 0x10), its contents
class CArcData {
public:
    // the archive's header (the names are not the original's)
    struct Header {
        unsigned char pad_0[0x8];
        unsigned int m_version;  // from 0x102 the file table is sorted by name hash
        unsigned int m_files;
        unsigned int m_contentsOffset;
        unsigned char pad_14[0xC];
        char m_str[1];  // a string at 0x20 (getStr's)
    };
    // one file of the archive (the names are not the original's)
    struct File {
        unsigned int m_offset;  // from the archive's start
        unsigned int m_size;
        unsigned int m_hash;  // mm::mtl::hashStrCrc of the name
        char m_name[0x34];
    };

    // an empty one by default (Vector<CArcData>::resize constructs its new elements with none)
    CArcData(void* data = nullptr);
    void setData(void* data);
    unsigned int getFiles() const;
    const char* getStr() const;
    // the file's data in the archive, none when it has none
    void* getFileAdr(unsigned int index) const;
    // the named file's data in the archive, none when it has none
    void* getFileAdr(const char* name) const;
    // the named file's index, -1 when there is none
    int find(const char* name) const;
    unsigned int getFileSize(unsigned int index) const;
    const char* getFileName(unsigned int index) const;

    Header* m_data;
    File* m_contents;  // the name is not the original's
};
}  // namespace arc

#endif
