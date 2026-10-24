#ifndef BTL_UTILITY_H
#define BTL_UTILITY_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace btl { namespace Utility {
enum CHECK_CHR_NUM_MODE : int;
bool IsEnableDeadSequence();
// fills the list with the indices of the characters the handle's character sees (EnemyParameter::CheckChangeAttr
// passes mode 0 and 0x23, AngryInfection mode 1 and 0x62) and returns how many
int GetCharacterList(mm::mtl::FixedVector<unsigned char, 90>& list, gf::GF_OBJ_HANDLE* handle,
                     CHECK_CHR_NUM_MODE mode, unsigned int flags);
}}  // namespace btl::Utility

#endif
