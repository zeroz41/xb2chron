#include "fw/ParamBuilder.h"
#include "gf/GfParamIkReflection.h"
#include "gf/GfStaticRes.h"
#include "arc/CArcData.h"
#include "classes/fw/CommonResource.h"

namespace gf {

void createGfParameter() {
    if (fw::CommonResource* resource = GfStaticRes::search("/param/common.prm")) {
        arc::CArcData arc(resource->getAssetData());
        fw::ParamBuilder::create(arc.getFileAdr("common_target.param"), 0,
                                 "T:/BF2/param/param/common/common_target.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_look_at_ik.param"), 1,
                                 "T:/BF2/param/param/common/common_look_at_ik.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_spine_ik.param"), 2,
                                 "T:/BF2/param/param/common/common_spine_ik.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_spc_ik.param"), 3,
                                 "T:/BF2/param/param/common/common_spc_ik.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_foot_ik.param"), 4,
                                 "T:/BF2/param/param/common/common_foot_ik.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_access.param"), 5,
                                 "T:/BF2/param/param/common/common_access.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_battle.param"), 10,
                                 "T:/BF2/param/param/common/common_battle.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_formation.param"), 6,
                                 "T:/BF2/param/param/common/common_formation.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_lure.param"), 7, "T:/BF2/param/param/common/common_lure.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_env_sensor.param"), 8,
                                 "T:/BF2/param/param/common/common_env_sensor.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_spine_rotate_ik.param"), 9,
                                 "T:/BF2/param/param/common/common_spine_rotate_ik.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_eye.param"), 11, "T:/BF2/param/param/common/common_eye.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_unique_motion.param"), 12,
                                 "T:/BF2/param/param/common/common_unique_motion.xml");
        fw::ParamBuilder::create(arc.getFileAdr("common_enemy.param"), 21,
                                 "T:/BF2/param/param/common/common_enemy.xml");
    }
    if (fw::CommonResource* resource = GfStaticRes::search("/param/pc.prm")) {
        arc::CArcData arc(resource->getAssetData());
        fw::ParamBuilder::create(arc.getFileAdr("pc_common.param"), 13, "T:/BF2/param/param/pc/pc_common.xml");
        fw::ParamBuilder::create(arc.getFileAdr("pc_act_field.param"), 14, "T:/BF2/param/param/pc/pc_act_field.xml");
        fw::ParamBuilder::create(arc.getFileAdr("pc_act_ai_field.param"), 15,
                                 "T:/BF2/param/param/pc/pc_act_ai_field.xml");
        fw::ParamBuilder::create(arc.getFileAdr("pc_ai_field.param"), 16, "T:/BF2/param/param/pc/pc_ai_field.xml");
        fw::ParamBuilder::create(arc.getFileAdr("pc_coli.param"), 17, "T:/BF2/param/param/pc/pc_coli.xml");
        fw::ParamBuilder::create(arc.getFileAdr("pc_sound.param"), 18, "T:/BF2/param/param/pc/pc_sound.xml");
    }
    if (fw::CommonResource* resource = GfStaticRes::search("/param/camera.prm")) {
        arc::CArcData arc(resource->getAssetData());
        fw::ParamBuilder::create(arc.getFileAdr("camera.param"), 19, "T:/BF2/param/param/camera/camera.xml");
    }
    if (fw::CommonResource* resource = GfStaticRes::search("/param/menu.prm")) {
        arc::CArcData arc(resource->getAssetData());
        fw::ParamBuilder::create(arc.getFileAdr("menu.param"), 20, "T:/BF2/param/param/menu/menu.xml");
    }
    if (fw::CommonResource* resource = GfStaticRes::search("/param/event.prm")) {
        arc::CArcData arc(resource->getAssetData());
        fw::ParamBuilder::create(arc.getFileAdr("ev_look_at_ik.param"), 22,
                                 "T:/BF2/param/param/event/ev_look_at_ik.xml");
        fw::ParamBuilder::create(arc.getFileAdr("ev_spine_ik.param"), 23, "T:/BF2/param/param/event/ev_spine_ik.xml");
    }
    if (fw::CommonResource* resource = GfStaticRes::search("/param/effect.prm")) {
        arc::CArcData arc(resource->getAssetData());
        fw::ParamBuilder::create(arc.getFileAdr("eff_footstep.param"), 24,
                                 "T:/BF2/param/param/effect/eff_footstep.xml");
    }
}

void destroyGfParameter() {
    for (unsigned int i = 0; i < 25; i++) {
        fw::ParamBuilder::destroy(i);
    }
}

}  // namespace gf
