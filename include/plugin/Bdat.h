#ifndef PLUGIN_BDAT_H
#define PLUGIN_BDAT_H

// the BDAT tables (application/BF2/plugin/bdat.cpp)
namespace Bdat {
// the loaded table of that name
unsigned char* getFP(const char* name);
// its first and last row ids, and how many rows there are from the first
int getIdTop(unsigned char* fp);
int getIdEnd(unsigned char* fp);
int getIdCount(unsigned char* fp);
unsigned short getMemberSize(unsigned char* fp);  // the table's number of columns
// the named member (column) of a table; null when the table has none
unsigned char* getMember(unsigned char* fp, const char* name);
// a row's value of the named column, in 64 bits: a string column's text, a number column's value (0 when there is no
// such member; 1.0.0's ui::UIManager::createLayer tests bits of it above 16)
char* getVal(unsigned char* fp, const char* column, int id);
// getVal for a column of that value type (7: a string; ai::AiScriptDataManager reads its Script column so)
char* getValCheck(unsigned char* fp, const char* column, int id, int type);
// a row's text in a message table
const char* getMSText(unsigned char* fp, int id);
// a row's value of a member getMember found, read as the given value type (2: 16 bits, 1: 8 bits, 7: a string), in
// 64 bits (a string column's text address); 0 when the member is null
unsigned long getValCheck(unsigned char* fp, unsigned char* member, int id, int type);
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
    unsigned char* m_fp;  // the name is not the original's
};

#endif
