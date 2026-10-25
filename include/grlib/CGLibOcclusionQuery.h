#ifndef GRLIB_CGLIBOCCLUSIONQUERY_H
#define GRLIB_CGLIBOCCLUSIONQUERY_H

namespace grlib {

// an occlusion query reporting into two alternating report slots of the context's CGLibBuffOcclusion
// (0x14 bytes used; the field names are not the original's)
class CGLibOcclusionQuery {
public:
    CGLibOcclusionQuery();
    void release();
    void beginQuery();
    void endQuery();
    // the samples passed by the last finished query (0 before one finished)
    unsigned int getQueryPixel();

    unsigned char* m_pReport;     // 0x00: the reports, 0 until endQuery allocates them
    unsigned int m_id;            // 0x08: the CGLibBuffFixAlloc id
    unsigned int m_ofs;           // 0x0C: the reports' offset in the report pool
    unsigned short m_validMask;   // 0x10: the reports written
    unsigned char m_writeIdx;     // 0x12: the report endQuery writes next
    unsigned char m_readIdx;      // 0x13: the report getQueryPixel reads
};

}  // namespace grlib

#endif
