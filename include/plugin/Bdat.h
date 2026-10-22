#ifndef PLUGIN_BDAT_H
#define PLUGIN_BDAT_H

// the BDAT tables (application/BF2/plugin/bdat.cpp)
namespace Bdat {
// the loaded table of that name
unsigned char* getFP(const char* name);
// its first and last row ids
int getIdTop(unsigned char* fp);
int getIdEnd(unsigned char* fp);
// the named member (column) of a table; null when the table has none
unsigned char* getMember(unsigned char* fp, const char* name);
// a row's value of the named column, in 64 bits: a string column's text, a number column's value (0 when there is no
// such member; 1.0.0's ui::UIManager::createLayer tests bits of it above 16)
char* getVal(unsigned char* fp, const char* column, int id);
}  // namespace Bdat

#endif
