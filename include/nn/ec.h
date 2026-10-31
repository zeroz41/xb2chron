#ifndef NN_EC_H
#define NN_EC_H

namespace nn {

// the SDK's application (title) id, passed by value in one register
struct ApplicationId {
    unsigned long value;
};

namespace ec {

// the SDK's shop applet: an application's add-on content list, its information page
void ShowShopAddOnContentList(ApplicationId id);
void ShowShopApplicationInformation(ApplicationId id);

}  // namespace ec
}  // namespace nn

#endif
