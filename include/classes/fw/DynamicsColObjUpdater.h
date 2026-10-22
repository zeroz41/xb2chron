#ifndef CLASSES_FW_DYNAMICSCOLOBJUPDATER_H
#define CLASSES_FW_DYNAMICSCOLOBJUPDATER_H

namespace skd { class CollisionObject; }

namespace fw {
// what DyanmicsManager's per-layer collision lists hold (addColUpdater/removeColUpdater take one)
class DynamicsColObjUpdaterInterface {
public:
    virtual ~DynamicsColObjUpdaterInterface() {}
    virtual void update() = 0;

    unsigned char pad_8[0x10];  // a list node: addColUpdater links it into the layer's list
};

// table 0x7100B412F8; updates a collision object
class DynamicsColObjUpdater : public DynamicsColObjUpdaterInterface {
public:
    DynamicsColObjUpdater();
    virtual ~DynamicsColObjUpdater();  // slot 0
    virtual void update();  // slot 2
    void bind(skd::CollisionObject* colObj);
    void unbind();

    skd::CollisionObject* m_pColObj;  // bind's, referenced; unbind releases it (the name is not the original's)
};
}  // namespace fw

#endif
