#pragma once
#include "GTASA/CTimer.h"
#include "GTASA/CObject.h"
#include <unordered_map>
#include <map>
#include <unordered_set>

using namespace plugin;

class COpenDoorAnim
{
public:
	static void OpenDoorAnim(CObject* obj);
	static bool IsOnDoorPos(CVector pPos, CVector oPos, float radius);
};

extern bool (*GetTaskUseGun)(CPedIntelligence *pInt);
extern bool (*GetTaskFighting)(CPedIntelligence *pInt);
extern bool (*GetTaskHold)(CPedIntelligence *pInt, bool yes);
extern bool (*GetTaskInAir)(CPedIntelligence *pInt);
extern bool (*GetTaskDuck)(CPedIntelligence *pInt, bool yes);
extern bool (*GetTaskSwim)(CPedIntelligence *pInt);
extern CAnimBlendAssociation* (*BlendAnimation)(RpClump* clump, int AssocGroupId, int AnimationId, float clumpAssocBlendData);

