#ifndef ML_DRRESMDOPOS_H
#define ML_DRRESMDOPOS_H

namespace mm { class Vec3; }

namespace ml {
class DrCalcViewWork;
class DrResMdoPos;
struct MdsPosKeepData;

// The object a position is handed to: it keeps the DrResMdoPos* at 0x28, which DrResMdoPos::release clears.
// Its class is not known yet; the name is not the original's.
struct DrResMdoPosOwner {
    unsigned char pad_0[0x28];
    DrResMdoPos* m_pos;  // 0x28
};

// One position slot of the resource; 0x28 bytes (DrResMdoPosAddList strides by 0x28). Field names are not the
// original's.
class DrResMdoPos {
public:
    // 1.0.0 has this out of line (0x710087260C); 3.0.1 only inlines it (DrResMdoPosAddList::setupBuff).
    DrResMdoPos() : m_owner(0), m_data(0), m_frame(0), m_alphaCnt(0), m_alphaMax(0xFF) {}
    DrResMdoPos(const MdsPosKeepData* data);
    ~DrResMdoPos();

    // 1.0.0 has this out of line (0x7100872660); 3.0.1 only inlines it.
    void release() {
        if (m_owner) {
            m_owner->m_pos = 0;
            m_owner = 0;
        }
    }
    void copy(DrResMdoPos* src);
    bool clipTest(DrCalcViewWork* view, const mm::Vec3& pos, float radius);
    void setAddAlphaCnt(int cnt);
    bool setSubAlphaCnt(int cnt);

    DrResMdoPosOwner* m_owner;      // 0x0
    const MdsPosKeepData* m_data;   // 0x8
    unsigned char pad_10[0x8];
    unsigned short m_id;            // 0x18 (copy takes it)
    unsigned char pad_1A[0x4];
    unsigned short m_frame;         // 0x1E (constructors and copy clear it)
    unsigned char pad_20[0x1];
    unsigned char m_alphaCnt;       // 0x21
    unsigned char m_alphaMax;       // 0x22 (0xFF from the constructors)
    unsigned char pad_23[0x5];
};

// A fixed pool of 100 DrResMdoPos in a caller's buffer. Field names are not the original's.
class DrResMdoPosAddList {
public:
    enum { ADD_MAX = 100 };
    int createBuffSize();
    int setupBuff(unsigned char* buff);
    void release();
    void begin();
    DrResMdoPos* createAdd();

    DrResMdoPos* m_buff;  // 0x0
    int m_cnt;            // 0x8
};
}  // namespace ml

#endif
