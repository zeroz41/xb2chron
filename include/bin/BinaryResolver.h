#ifndef BIN_BINARYRESOLVER_H
#define BIN_BINARYRESOLVER_H

namespace bin {
// a binary resource's pointers, kept in the file as offsets from its start: resolve turns them into addresses
// (once: the header remembers it), restore back into offsets
class BinaryResolver {
public:
    // the head of a binary resource
    struct Header {
        char m_magic[2];               // "BC"
        unsigned short m_flags;        // bit 0: the pointers are resolved
        unsigned int m_version;        // 0x10000
        unsigned int pad_8;
        unsigned int m_pointerCount;   // the entries of the pointer table
        unsigned long m_rootOffset;    // where the resource's root object starts
        unsigned long m_pointerTable;  // where the table starts: per pointer, the offset of the pointer
    };

    // the root object of `binary` with its pointers resolved, or null when it is not a binary resource
    static void* resolve(void* binary);
    // turns the pointers of `binary` back into offsets; false when it is not a binary resource
    static bool restore(void* binary);
};
}  // namespace bin

#endif
