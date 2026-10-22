#ifndef ARC_CARCDATA_H
#define ARC_CARCDATA_H

namespace arc {
// an archive in memory: its binary and, past the header (the offset at its 0x10), its contents
class CArcData {
public:
    CArcData(void* data);
    // the named file's data in the archive, none when it has none
    void* getFileAdr(const char* name) const;

    void* m_data;
    void* m_contents;  // the name is not the original's
};
}  // namespace arc

#endif
