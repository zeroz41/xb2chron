#ifndef NN_ACCOUNT_H
#define NN_ACCOUNT_H

#include "nn/result.h"

namespace nn { namespace account {
// the SDK's account library setup (ml::DeviceNx::initializeSDK calls it)
void Initialize();

// a user's identity (0x10 bytes; zero is no user)
struct Uid {
    unsigned long _data[2];
};
// an opened user (0x18 bytes; ml::DevFileNxTh::m_appuser)
struct UserHandle {
    unsigned long _data[3];
};
// opens the user chosen at launch (ml::DevFileNxTh::initializeSave)
Result OpenPreselectedUser(UserHandle* handle);
Result GetUserId(Uid* uid, const UserHandle& handle);
// writes up to `count` users' identities; how many in *actual
Result ListAllUsers(int* actual, Uid* uids, int count);
void CloseUser(const UserHandle& handle);
}}  // namespace nn::account

#endif
