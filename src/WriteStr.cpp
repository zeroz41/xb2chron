#include "ml/font/WriteStr.h"

WriteStr::WriteStr() : m_limitWidth(0.0f), m_drawFlag(0x111) {}

WriteStr::~WriteStr() {}

// print (0x71006F44F4), fn_71006F4790, calc_string_width (0x71006F48E4), calc_string_width_to_new_line
// (0x71006F4A24) and calc_string_height (0x71006F4B4C) are not here yet: the Shift-JIS lead-byte test's blocks are
// laid out differently, and fn_71006F4790's UTF-16 value is built differently
