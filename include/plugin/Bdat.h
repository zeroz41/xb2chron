#ifndef PLUGIN_BDAT_H
#define PLUGIN_BDAT_H

// the BDAT tables (application/BF2/plugin/bdat.cpp)
namespace Bdat {
// a value read from a table, as the library hands it around (convertType rewrites it in place): 8 bytes, cleared
// before one value type's bytes are written (the field names are not the original's)
union uVal {
    unsigned char ubyte;
    unsigned short ushort;
    unsigned int uint;
    signed char sbyte;
    short sshort;
    int sint;
    char* str;
    unsigned long ulong;  // all 8 bytes, as the getters return them
    float real;
};
// the registered BDAT files, one per slot (regist stores, unregist clears, getFP searches them all)
extern unsigned char* m_pBin[16];
// the BDAT file in a slot (fw::BdatManager's layers 0-15): its data registered, its tables' count and names, and the
// slot released (fw::BdatManager::Impl registers a loaded file's data and indexes its tables by name)
void regist(int slot, void* data);
void unregist(int slot);
int getFileCount(int slot);
const char* getFileName(int slot, int index);
// the loaded table of that name
unsigned char* getFP(const char* name);
// the table's name, stored in the table (ui::UITextManager::registTextFile hashes it)
const char* getSheetName(unsigned char* fp);
// its first and last row ids, and how many rows there are from the first
int getIdTop(unsigned char* fp);
int getIdEnd(unsigned char* fp);
int getIdCount(unsigned char* fp);
unsigned short getMemberSize(unsigned char* fp);  // the table's number of columns
// the named member (column) of a table; null when the table has none
unsigned char* getMember(unsigned char* fp, const char* name);
// a row's value of the named column, in 64 bits: a string column's text address, a number column's value (0 when
// there is no such member; 1.0.0's ui::UIManager::createLayer tests bits of it above 16). The getters return the
// value as an integer, not a pointer: the original's getMSText/getMSLabel, GfMenuTagHomuriName::convBegin and
// GfDataBlade's getters call them without a tail call (the integer-to-pointer conversion after the call), and
// getValCheck returns all 64 bits of the converted value (ldr x0)
unsigned long getVal(unsigned char* fp, const char* column, int id);
// the index-th value of an array column (the bdat script class's getArrayVal hands it on like getVal's)
unsigned long getArrayVal(unsigned char* fp, const char* column, int id, int index);
int getArrayCount(unsigned char* fp, const char* column);
// a column's value type: 1 u8, 2 u16, 3 u32, 4 s8, 5 s16, 6 s32, 7 string, 8 float (the bdat script class's getVal
// converts by it)
int getVarType(unsigned char* fp, const char* column);
// getVal for a column of that value type (7: a string; ai::AiScriptDataManager reads its Script column so)
unsigned long getValCheck(unsigned char* fp, const char* column, int id, int type);
// getValCheck of a u8 / u16 column, narrowed by an inline callee (no copy of them exists; the names are not the
// original's). The original compares such values in 32 bits after the call (and w8, w0, #0xff / #0xffff; cmp w8):
// the narrowing done in a callee keeps the compare narrow, the same cast written at the call site widens it to
// and x8/cmp x8 (GmkCollection::BdatInfo::create, gf::npc::StateIdle::enter/leave, GfMenuObjWorldMap's shop test)
inline unsigned char getValCheckU8(unsigned char* fp, const char* column, int id) {
    return getValCheck(fp, column, id, 1);
}
inline unsigned short getValCheckU16(unsigned char* fp, const char* column, int id) {
    return getValCheck(fp, column, id, 2);
}
// a row's text in a message table
const char* getMSText(unsigned char* fp, int id);
// a row's style in a message table (its 16 bits: the code masks them into the int it returns)
int getMSStyle(unsigned char* fp, int id);
// a row's value of a member getMember found, unconverted (the value type's bytes; 0 when the id is out of range or
// the member is not a scalar)
unsigned long getVal(unsigned char* fp, unsigned char* member, int id);
// the value of the member at that index
unsigned long getVal(unsigned char* fp, int member, int id);
unsigned long getArrayVal(unsigned char* fp, unsigned char* member, int id, int index);
// the table's scramble undone in place (regist calls it on each table of a file it registers)
void decodeScramble(void* data);
// a value converted from the member's value type to another (an integer widened or narrowed, 0 for strings
// and floats)
void convertType(unsigned char* fp, unsigned char* member, int type, uVal* val);
const char* getMSLabel(unsigned char* fp, int id);
// a row's value of a member getMember found, read as the given value type (2: 16 bits, 1: 8 bits, 7: a string), in
// 64 bits (a string column's text address); 0 when the member is null
unsigned long getValCheck(unsigned char* fp, unsigned char* member, int id, int type);
// the named table when it is loaded, else null (GfFobjManager::update polls for RSC_dropitemList so)
unsigned char* isExistFP(const char* name);
// a row's value of the member at that index, as the given value type (8: a float's 32 bits)
unsigned long getValCheck(unsigned char* fp, int member, int id, int type);
// a row's flag: the flag word member's bit that the bit member names (nonzero when set)
int getFlagVal(unsigned char* fp, unsigned char* member, int id, unsigned char* bitMember);
// getFlagVal by the columns' names (gf::GfFieldMapGimmick::BdatInfo::create reads its row's "flag" bits so; the
// symbols spell this overload, 0x7100655F2C)
int getFlagVal(unsigned char* fp, const char* member, int id, const char* bitMember);
// getValCheck for an array member: element index of the row's value (1.0.0's gf::_gfbcd::getChrDrWpnType reads the
// WpnType array so, type 1, keeping the low 8 bits)
unsigned long getArrayValCheck(unsigned char* fp, unsigned char* member, int id, int index, int type);
}  // namespace Bdat

// a loaded BDAT table, as the generated column accessors take it (1.0.0's gf::_gfbbg and gf::_gfbdb functions take a
// CBdatWrapper const&); it holds the table and nothing else, and its calls are inline (no copy of them exists), so
// a column handle, an argument, is read before the table (the method names are not the original's)
class CBdatWrapper {
public:
    CBdatWrapper(unsigned char* fp) : m_fp(fp) {}
    unsigned char* getMember(const char* name) const { return Bdat::getMember(m_fp, name); }
    int getIdTop() const { return Bdat::getIdTop(m_fp); }
    int getIdCount() const { return Bdat::getIdCount(m_fp); }
    unsigned long getValCheck(unsigned char* member, int id, int type) const {
        return Bdat::getValCheck(m_fp, member, id, type);
    }
    int getFlagVal(unsigned char* member, int id, unsigned char* bitMember) const {
        return Bdat::getFlagVal(m_fp, member, id, bitMember);
    }
    unsigned long getArrayValCheck(unsigned char* member, int id, int index, int type) const {
        return Bdat::getArrayValCheck(m_fp, member, id, index, type);
    }
    unsigned char* m_fp;  // the name is not the original's
};

#endif
