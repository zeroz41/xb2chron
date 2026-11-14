#ifndef PTLIB_PARTICLESYSTEM_H
#define PTLIB_PARTICLESYSTEM_H

#include "mm/Mat34.h"
#include "mm/Mat44.h"

namespace mtl { class ALLOC_HANDLE; }
namespace mm { class Vec3; class Col4; }
namespace ptlib { namespace emitter { class EmitterParam; class EmitterObj; class EmitterArg; class ParticleObj; } }

namespace ptlib {
class DrDrawWorkInfoEF;

// the camera of the view being drawn, as effect::SystemManager::updateCam stores it from the draw info
// (ParticleManager::getCamParam's; the type and field names are not the original's)
struct CamParam {
    mm::Mat44 m_viewMtx;      // the draw info's view matrix
    mm::Mat44 m_cameraMtx;    // the draw info's camera matrix
    mm::Mat44 m_viewProjMtx;  // view * projection
    mm::Mat34 m_billboard;    // the camera matrix's first two rows, transposed
    unsigned char pad_f0[0x30];
    float m_pitch;  // atan2 of the view direction's height over its ground length
    float m_yaw;    // -atan2(x, -z) of the view direction
    float m_height;  // the camera matrix's m[3][1]
    int m_view;     // the draw info's view
};

// one entry of an effect resource's material table (the names are not the original's:
// ParticleManager::convert_key_by_material_index reads the key of entry <index>)
class FxMaterialEntry {
public:
    int m_key;
    unsigned char pad_4[0xc];
};

// an effect resource's material table: a count, then the entries (the names are not the original's)
class FxMaterialTable {
public:
    const FxMaterialEntry* getEntry(unsigned int index) const { return index < m_count ? &m_entries[index] : nullptr; }

    unsigned int m_count;
    FxMaterialEntry m_entries[1];  // m_count of them
};

// an effect resource's header, as effect::SystemManager::es_regist hands it out (the names are not the original's:
// es_is_loop and es_contais_cam_axis read the flags)
class FxHeader {
public:
    // the texture table of a type 'P' file: m_num entries; each entry's data lies m_offset bytes after the table
    // (the names are not the original's)
    struct TexTable {
        struct Entry {
            int m_key;
            int m_format;
            int m_size;
            unsigned int m_offset;
        };
        void* getData(const Entry& entry) {
            return entry.m_offset != 0 ? reinterpret_cast<unsigned char*>(this) + entry.m_offset : nullptr;
        }
        unsigned int m_num;
        Entry m_entries[1];
    };

    // the block at m_materialTableOffset whatever the file's type (parseEfb: 'Q' and 'P' files)
    void* getBlock() {
        return m_materialTableOffset != 0 ? reinterpret_cast<unsigned char*>(this) + m_materialTableOffset : nullptr;
    }

    // the file m_nextOffset names, or null
    FxHeader* getNext() {
        return m_nextOffset != 0 ? reinterpret_cast<FxHeader*>(reinterpret_cast<unsigned char*>(this) + m_nextOffset)
                                 : nullptr;
    }

    unsigned int m_magic;  // "efb0" (parseEfb; the name is not the original's)
    unsigned char pad_4[0x4];
    unsigned char m_type;  // 0x8: 1 an effect, 'P' textures, 'Q' ParticleManager::m_pReserved (the name is not the original's)
    unsigned char m_loop;
    unsigned char m_containsCamAxis;
    unsigned char m_nameLength;  // 0xB: m_name's (EmitterManager::emitter_set_search; the name is not the original's)
    // 0xC: of a pack ('a'), its first file; of a file in a pack, the next one; relative to the header, 0 for none
    // (parse_efs; the name is not the original's)
    unsigned int m_nextOffset;
    unsigned int m_materialTableOffset;  // from the header; 0 for none (the name is not the original's)
    char m_name[0x34];  // 0x14: m_nameLength characters, not terminated (emitter_set_search; the name is not the original's)
    unsigned long m_userParam;  // 0x48: parseEfb's third argument for a type-1 file (the name is not the original's)

    const FxMaterialTable* getMaterialTable() const {
        return m_materialTableOffset != 0
                   ? reinterpret_cast<const FxMaterialTable*>(reinterpret_cast<const unsigned char*>(this) +
                                                              m_materialTableOffset)
                   : nullptr;
    }
};

// the library's state that the renderer shares (RenderManager::init takes it; ParticleManager::getFxParam)
class FxParam {
public:
    // what ParticleManager::init sets (the name is not the original's)
    void reset() {
        m_paused = false;
        m_pause = false;
        m_flagF = true;
        m_flag10 = false;
        m_flag11 = false;
        m_flag12 = false;
        m_value14 = 1;
    }

    unsigned char pad_0[0x4];
    int m_drawCount;  // 0x4: RenderGrObj::draw counts the view-0 draws (the name is not the original's)
    unsigned char pad_8[0x5];
    bool m_paused;  // the pause state update_pause applied (the name is not the original's)
    bool m_pause;   // set_pause's request (the name is not the original's)
    bool m_flagF;
    bool m_flag10;  // move does nothing while it is set
    bool m_flag11;
    bool m_flag12;
    unsigned char pad_13[0x1];
    int m_value14;
};

// reports a failed check of the effect library with a printf-style message; the expression comes first
void efAstMsg(const char* expression, const char* format, ...);
// prints a printf-style message of the effect library
void efMsg(const char* format, ...);
// prints a printf-style warning of the effect library
void efWng(const char* format, ...);

// the game's drawing hooks, as setUserDrFunc stores them; ParticleManager's forwarders of the same names call
// them (the type's name is not the original's; the members are named after 1.0.0's forwarders)
struct DrFunc {
    void* (*createMdl)(const void*, const char*, int, const void*, int);
    void (*deleteMdl)(void*);
    void* (*createLgt)(unsigned int, int);
    void (*deleteLgt)(unsigned int, void*);
    void (*setMdlPos)(void*, void*);
    void (*setMdlMatrix)(void*, void*);
    void (*setMdlColor)(void*, void*);
    void (*setMdlAlpha)(void*, float);
    void (*setMdlSpd)(void*, void*);
    void (*setLgtPos)(unsigned int, void*, void*);
    void (*setLgtMatrix)(unsigned int, void*, void*);
    void (*setLgtParam)(unsigned int, void*, void*);
    void* (*createGrp)(int, int);
    void (*destroyGrp)(void*);
    void (*debugRenderer)(void*);
    void* pad_78;
};

// the effect library's manager (particle_system.cpp)
class ParticleManager {
public:
    static void* (*s_pAllocFuncSys)(void*, unsigned int, unsigned int, const char*, unsigned int);
    static void (*s_pFreeFuncSys)(void*, void*);
    static void* (*s_pAllocFuncRes)(void*, unsigned int, unsigned int, const char*, unsigned int);
    static void (*s_pFreeFuncRes)(void*, void*);
    static mtl::ALLOC_HANDLE (*s_pGetSysHandle)();
    static mtl::ALLOC_HANDLE (*s_pGetResHandle)();
    static void* (*s_pReadFunc)(const char*, int&);
    static void (*s_pReadEndFunc)(void*);
    static void (*s_pOutputDebugStringFunc)(const char*);
    static void (*s_pOutputWarnStringFunc)(const char*);
    static DrFunc s_pDrFunc;

    static void resFree(void* p);
    static void* readFileBlock(const char* path, int& size);
    static void* createMdl(const void* a, const char* b, int c, const void* d, int e);
    static void deleteMdl(void* pMdl);
    static void* createLgt(unsigned int a, int b);
    static void deleteLgt(unsigned int a, void* pLgt);
    static void debugRenderer(void* p);
    // 1.0.0 has these two out of line; 3.0.1 only inlines them (init, term)
    static void* createGrp(int index, int a) { return s_pDrFunc.createGrp(index, a); }
    static void destroyGrp(void* pGrp) { s_pDrFunc.destroyGrp(pGrp); }
    // the draw group <index> (0..3) init made, or null
    static void* getGrp(int index);
    // checks an effect file's header and takes it in by its type; the file, or null when it is not one
    unsigned char* parseEfb(unsigned char* pData, const char* name, unsigned long param);
    void parse_efb_type0001(unsigned char* pData);
    // parseEfb of an effect file, or of every file of a pack ('a'); null when it is not one
    unsigned char* parse_efs(const char* name, void* pData, unsigned int size);
    // what it returns is not known yet (EmitterManager's callers drop it)
    void update_model_spd(emitter::EmitterObj* pEmitter, float speed);
    // per-frame update of a particle's model or light (EmitterObj::move01_type_model / move01_type5; what they
    // return is not known yet)
    void update_model(emitter::ParticleObj* pParticle, emitter::EmitterObj* pEmitter, emitter::EmitterArg* pArg);
    void update_plight(emitter::ParticleObj* pParticle, emitter::EmitterObj* pEmitter);
    // applies set_pause's request to the models (update_model_spd of every emitter at speed 1)
    void update_pause();
    FxParam* getFxParam();
    CamParam* getCamParam();
    void set_pause(bool pause);
    int convert_key_by_material_index(int index, FxHeader* pHeader) const;

    void emitter_set_search(int a, const char* b, void* c, unsigned int d);
    void emitter_set_param_pos_only(unsigned int handle, emitter::EmitterParam* pParam);
    void emitter_set_param_pos_only2(unsigned int handle, emitter::EmitterParam* pParam);
    void emitter_set_param(unsigned int handle, emitter::EmitterParam* pParam);
    void emitter_set_param(FxHeader* pHeader, emitter::EmitterParam* pParam);
    void emitter_set_casname(unsigned int handle, const void* a, const char* b, int c, float d, int e);
    void emitter_set_casparam(unsigned int handle, const void* a, emitter::EmitterParam* pParam);
    void emitter_set_disp(unsigned int handle, int disp);
    void emitter_set_alpha(unsigned int handle, float alpha);
    void emitter_set_speed(unsigned int handle, float speed);
    void emitter_set_category(unsigned int handle, unsigned int category);
    void emitter_set_viewnum(unsigned int handle, int view);
    void emitter_set_nowait(unsigned int handle, int nowait);
    void emitter_set_fadeout(unsigned int handle, int frames);
    void emitter_set_fadeout(FxHeader* pHeader, int frames);
    void emitter_set_fadeout(void* p, int frames);
    void emitter_pack_free(unsigned long pack);
    void emitter_alloc01_set_draw(emitter::EmitterObj* pObj, emitter::EmitterArg* pArg);

    // the library's own memory: size bytes on an align boundary, cited with the requesting file and line
    static void* sysAlloc(unsigned int size, unsigned int align, const char* file, unsigned int line);
    static void sysFree(void* p);

    static ParticleManager* get();
    static ParticleManager*& getPtr();
    static void init(const DrDrawWorkInfoEF* pDrInfo);
    void term();
    void move();
    void tail();
    void setDrInfo(const DrDrawWorkInfoEF* pDrInfo);
    void draw(const DrDrawWorkInfoEF* pDrInfo, int view, bool blur);
    // the ground under a ray or a line (idcoli::IDColiDef), false while m_initFlags[1] is set
    bool testRayGround(mm::Vec3& outNormal, mm::Vec3& outPos, const mm::Vec3& pos, const mm::Vec3& dir, float, float);
    bool testLineGround(mm::Vec3& outNormal, mm::Vec3& outPos, const mm::Vec3& start, const mm::Vec3& end);
    void emitter_set_free(FxHeader* pHeader, int frames);
    void emitter_set_free_all(bool flag);

    // the game's hooks (effect::SystemManager passes them on; setUserFuncClear clears them all)
    static void setUserAllocFunc(void* (*alloc)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                 void (*free)(void*, void*),
                                 void* (*alloc2)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                 void (*free2)(void*, void*), mtl::ALLOC_HANDLE (*handle)(),
                                 mtl::ALLOC_HANDLE (*handle2)());
    static void setUserFileFunc(void* (*load)(const char*, int&), void (*release)(void*));
    static void setUserOutputString(void (*print)(const char*), void (*warn)(const char*));
    static void setUserDrFunc(void* (*a)(const void*, const char*, int, const void*, int), void (*b)(void*),
                              void* (*c)(unsigned int, int), void (*d)(unsigned int, void*), void (*e)(void*, void*),
                              void (*f)(void*, void*), void (*g)(void*, void*), void (*h)(void*, float),
                              void (*i)(void*, void*), void (*j)(unsigned int, void*, void*),
                              void (*k)(unsigned int, void*, void*), void (*l)(unsigned int, void*, void*),
                              void (*m)(void*), void* (*n)(int, int), void (*o)(void*));

    // 1.0.0's clear(), which 3.0.1 only inlines into init
    void clear() {
        m_pReserved = nullptr;
        m_frame = 0.0f;
        m_param0 = 0.25f;
        m_param1 = 0.0f;
        m_param2 = 1.0f;
        m_param3 = 1.0f;
        m_param4 = 1.0f;
        m_pGrp[0] = nullptr;
        m_pGrp[1] = nullptr;
        m_pGrp[2] = nullptr;
        m_pGrp[3] = nullptr;
    }

    CamParam m_camParam;  // getCamParam returns it (at 0: its code is a bare ret)
    FxParam m_fxParam;
    // clear() sets them to 0.25, 0, 1, 1, 1; what they are is not known yet (separate members: as an array the
    // stores do not pair the way the original's do)
    float m_param0;
    float m_param1;
    float m_param2;
    float m_param3;
    float m_param4;
    float m_frame;      // move's frame accumulator (the name is not the original's)
    void* m_pReserved;  // clear() nulls it; nothing in this unit is known to read it yet
    bool m_initFlags[2];  // init sets {true, false}; what they are is not known yet
    unsigned char pad_16a[0x6];
    void* m_pGrp[4];  // the draw groups (the name is not the original's)
};

// the live effects' handles (searchDead is -1 for an unknown handle)
class HashManager {
public:
    // one live handle, with the name 1.0.0's add_core could give it
    struct Entry {
        const char* m_name;
        unsigned int m_handle;
    };
    // a handle that died, with what it died with
    struct Dead {
        unsigned int m_handle;
        int m_value;
    };

    static void init();
    static void term();
    static HashManager* get();
    static HashManager*& getPtr();
    void reset() {
        Entry* pEntry = m_entries;
        long count = 4000;
        while (count--) {
            pEntry->m_name = nullptr;
            pEntry->m_handle = 0;
            pEntry++;
        }
        m_count = 0;
    }
    // rebuilds the entries from the active emitters (tail passes it an emitter it never sets; build does not use it)
    void build(emitter::EmitterObj* pEmitter);
    void add(unsigned int handle);
    bool check(unsigned int handle);
    unsigned int get_create_key();
    int searchDead(unsigned int handle);

    void add_core(unsigned int handle, const char* name) {
        m_entries[m_count].m_handle = handle;
        m_entries[m_count].m_name = name;
        m_count++;
        m_entries[m_count].m_handle = 0;
        m_entries[m_count].m_name = nullptr;
    }
    unsigned int check_core(unsigned int handle) {
        for (unsigned int i = 0; i < m_count; i++) {
            if (m_entries[i].m_handle == handle) {
                return i;
            }
        }
        return 0;
    }

    Entry m_entries[4000];
    Dead m_dead[4000];
    unsigned int m_deadCount;
    unsigned int m_count;
    unsigned int m_createKey;
};

}  // namespace ptlib

#endif
