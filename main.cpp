#include "library.h"
#include "mod/amlmod.h"
#include "mod/config.h"
#include "mod/logger.h"
#include "GTASA/common.h"
#include "shared/CEvents.h"
#include "GTASA/CTimer.h"

MYMODCFG(OpenDoorAnim, GTASa, 1.0, PandaGaming)
NEEDGAME(com.rockstargames.gtasa)

using namespace plugin;

bool (*GetTaskUseGun)(CPedIntelligence *pInt);
bool (*GetTaskFighting)(CPedIntelligence *pInt);
bool (*GetTaskHold)(CPedIntelligence *pInt, bool yes);
bool (*GetTaskInAir)(CPedIntelligence *pInt);
bool (*GetTaskDuck)(CPedIntelligence *pInt, bool yes);
bool (*GetTaskSwim)(CPedIntelligence *pInt);
CAnimBlendAssociation* (*BlendAnimation)(RpClump* clump, int AssocGroupId, int AnimationId, float clumpAssocBlendData);

#include "COpenDoorAnim.h"

objectPreRenderEvent = [](CObject* obj)
{
    COpenDoorAnim::OpenDoorAnim(obj);
};

extern "C" void OnModLoad()
{
	SET_TO(GetTaskUseGun, libs.GetSym("_ZNK16CPedIntelligence13GetTaskUseGunEv"));
	SET_TO(GetTaskFighting, libs.GetSym("_ZNK16CPedIntelligence15GetTaskFightingEv"));
	SET_TO(GetTaskInAir, libs.GetSym("_ZNK16CPedIntelligence12GetTaskInAirEv"));
	SET_TO(GetTaskDuck, libs.GetSym("_ZNK16CPedIntelligence11GetTaskDuckEb"));
	SET_TO(GetTaskSwim, libs.GetSym("_ZNK16CPedIntelligence11GetTaskSwimEv"));
	SET_TO(GetTaskHold, libs.GetSym("_ZNK16CPedIntelligence11GetTaskHoldEb"));
	SET_TO(BlendAnimation, libs.GetSym("_ZN12CAnimManager14BlendAnimationEP7RpClump12AssocGroupId11AnimationIdf"));
	SetEventBefore(objectPreRender);
}
