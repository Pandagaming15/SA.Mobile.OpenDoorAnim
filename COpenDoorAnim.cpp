#include "COpenDoorAnim.h"

bool load = false;

// Global map to store the last animation time for each ped
std::unordered_map<CPed*, unsigned int> pedAnimDoorLastTimeMap;
bool COpenDoorAnim::IsOnDoorPos(CVector pedPos, CVector objectPos, float radius)
{
	float xOffset = fabs(pedPos.x - objectPos.x); // Calculate the x-offset
	return xOffset <= radius;
}

void COpenDoorAnim::OpenDoorAnim(CObject* obj)
{
    if (obj->m_pObjectInfo->m_nSpecialColResponseCase == 6) // SWINGDOOR
    {
        obj->m_nPhysicalFlags.bUsesCollisionRecords = true; // record collisions
		
		for (int i = 0; i < 6; ++i)
        {
			CVector oPos = obj->GetPosition();
			if(obj->m_nNoOfCollisionRecords > 0)
			{
					CEntity *entity = obj->m_aCollisionRecordPtrs[i];
                    if (entity && entity->m_info.m_nType == ENTITY_TYPE_PED)
                    {
						CPed *ped = reinterpret_cast<CPed*>(entity);
						//PedExtended &xdata = extData.Get(ped);
                        CVector pPos = ped->GetPosition();
                        if (pedAnimDoorLastTimeMap.find(ped) == pedAnimDoorLastTimeMap.end())
                        {
                            pedAnimDoorLastTimeMap[ped] = 0;//CTimer::m_snTimeInMilliseconds;
                        }

                        unsigned int &animDoorLastTime = pedAnimDoorLastTimeMap[ped]; // Get entry in map*/
						if ((CTimer::m_snTimeInMilliseconds - animDoorLastTime) > 1700)
                        {
							if (!ped->m_pIntelligence->GetTaskUseGun() &&
                            !ped->m_pIntelligence->GetTaskHold(true) &&
                            !ped->m_pIntelligence->GetTaskFighting() &&
                            !ped->m_pIntelligence->GetTaskInAir() &&
                            !ped->m_pIntelligence->GetTaskDuck(true) &&
                            !ped->m_pIntelligence->GetTaskSwim() && // maybe some map mod is using doors underwater...
                            ped->m_nHealth > 0.0f) // Ensure animation is not played again
							{
								if(IsOnDoorPos(pPos, oPos, 0.5f))
								{
									if(!load)
									{
										BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_DEFAULT_WALK_DOORPARTIAL, 4.0);
                                        animDoorLastTime = CTimer::m_snTimeInMilliseconds;
										load = true;
									}
								}
								else{
									load = false;
								}
							}
						}
					}
			}
			
		}
    }
}
