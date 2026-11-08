#ifndef CLASSES_GF_GFDATAZLIB_H
#define CLASSES_GF_GFDATAZLIB_H

namespace gf {
// compresses a save as GfGameSave writes it and decompresses one as GfGameLoad reads it, each on its own thread
// ("CompressThread", "DecompressThread") while a micro-thread runs, else in place
class GfDataZlib {
public:
    // one direction's input and output (the name and the member names are not the original's)
    struct Buffer {
        Buffer() : m_src(nullptr), m_srcSize(0), m_out(nullptr), m_outSize(0) {}
        ~Buffer() { setOut(nullptr); }

        void setOut(unsigned char* out) {
            unsigned char* old = m_out;
            m_out = out;
            if (old != nullptr) {
                delete old;
            }
        }
        void clear() {
            m_src = nullptr;
            m_srcSize = 0;
            setOut(nullptr);
            m_outSize = 0;
        }

        const void* m_src;
        unsigned long m_srcSize;
        unsigned char* m_out;  // allocated from the temporary memory, freed with delete
        unsigned long m_outSize;
    };

    Buffer* execForSave(const void* src, unsigned long size);
    Buffer* execForLoad(const void* src, unsigned long size);
    static unsigned int fnThreadSave(void* argument);
    static unsigned int fnThreadLoad(void* argument);
    void execCompress();
    void execDecompress();

    Buffer m_compress;    // 0x0: execForSave's
    Buffer m_decompress;  // 0x20: execForLoad's
};
}  // namespace gf

#endif
