#ifndef ML_DRRESFILTERDATA_H
#define ML_DRRESFILTERDATA_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
class DrMan;
// DrMan::m_filterData. Only what DrIniSys::loadFilterLutTexture calls is declared.
class DrResFilterData {
public:
    // One per view (the constructor sets four). Field names are not the original's.
    struct Filter {
        Filter() {
            m_far = 1000.0f;
            m_angle = 60.0f;
            pad_20 = 0;
            m_rate = 1.0f;
        }
        unsigned char pad_0[0x20];
        long pad_20;      // 0x20: the constructor clears it
        unsigned char pad_28[0x4];
        float m_far;      // 0x2C: the constructor sets 1000
        float m_angle;    // 0x30: the constructor sets 60
        float m_rate;     // 0x34: the constructor sets 1
    };
    // an entry of the filter data (0x1C bytes); the name is not the original's
    struct Entry {
        unsigned char pad_0[0x8];
        unsigned int m_id;  // 0x8: findFilterTexture's key
        unsigned char pad_C[0x10];
    };
    DrResFilterData(DrMan* drMan);
    ~DrResFilterData();
    // the texture of the entry with the id, else the first texture
    grlib::CGLibTextureBuffer* findFilterTexture(unsigned int id) const;
    // takes the data of the filter LUT file DrIniSys::loadFilterLutTexture read
    void setFilterData(const void* data);

    DrMan* m_drMan;                        // 0x00
    const Entry* m_entries;                // 0x08: setFilterData's data
    Filter m_filter[4];                    // 0x10
    grlib::CGLibTextureBuffer* m_texture;  // 0xF0: m_texNum of them, one per entry
    int m_texNum;                          // 0xF8
    unsigned char pad_FC[0x4];
    int pad_100;                           // the constructor clears it
};
}  // namespace ml

#endif
