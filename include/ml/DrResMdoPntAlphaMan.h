#ifndef ML_DRRESMDOPNTALPHAMAN_H
#define ML_DRRESMDOPNTALPHAMAN_H

namespace ml {
// A work-buffer manager of per-object alpha fades: getAlphaObj finds or claims an entry for an object, update fades
// each entry touched since the last update and frees the rest. Field names are not the original's.
class DrResMdoPntAlphaMan {
public:
    // one object's fade (0x10 bytes)
    struct Entry {
        union {
            unsigned int m_flags;  // 0x0: FLAG_* (update tests FLAG_TOUCHED by byte, then rewrites the word)
            struct {
                unsigned char m_used : 1;     // FLAG_USED
                unsigned char m_touched : 1;  // FLAG_TOUCHED
                unsigned char m_fadeIn : 1;   // FLAG_FADEIN
            };
        };
        float m_alpha;         // 0x4
        const void* m_obj;     // 0x8: the object the entry belongs to
    };
    enum {
        FLAG_USED = 1,     // claimed by an object
        FLAG_TOUCHED = 2,  // asked for since the last update
        FLAG_FADEIN = 4,   // fading in (else out)
    };

    static int getWrkSize(int num);
    static int setWrk(DrResMdoPntAlphaMan*& man, int num, unsigned char* work);
    void update(float delta);
    float getAlphaObj(const void* obj, bool fadeIn);
    void setAlphaReset(const void* obj, bool fadeIn);

    Entry* m_entry;    // 0x0: m_entryNum entries after the object
    Entry** m_active;  // 0x8: the entries in use, after the entries
    int m_entryNum;    // 0x10
    int m_activeNum;   // 0x14
};
}  // namespace ml

#endif
