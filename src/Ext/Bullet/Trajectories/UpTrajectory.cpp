#include "UpTrajectory.h"
#include <Ext/BulletType/Body.h>

bool UpTrajectoryType::Load(PhobosStreamReader& Stm, bool RegisterForChange)
{
	this->PhobosTrajectoryType::Load(Stm, false);
	return true;
}

bool UpTrajectoryType::Save(PhobosStreamWriter& Stm) const
{
	this->PhobosTrajectoryType::Save(Stm);
	return true;
}


void UpTrajectoryType::Read(CCINIClass* const pINI, const char* pSection)
{	
}

bool UpTrajectory::Load(PhobosStreamReader& Stm, bool RegisterForChange)
{
	return true;
}

bool UpTrajectory::Save(PhobosStreamWriter& Stm) const
{
	return true;
}

void UpTrajectory::OnUnlimbo(BulletClass* pBullet, CoordStruct* pCoord, BulletVelocity* pVelocity)
{
	pBullet->Velocity.X = 0;
	pBullet->Velocity.Y = 0;
	pBullet->Velocity.Z = 1;
	pBullet->Velocity *= this->GetTrajectorySpeed(pBullet) / pBullet->Velocity.Magnitude();
}

void UpTrajectory::OnAI(BulletClass* pBullet)
{
	if (pBullet->TargetCoords.DistanceFrom(pBullet->Location) < 100)
	{
		pBullet->Explode(true);
		pBullet->UnInit();
		pBullet->LastMapCoords = CellClass::Coord2Cell(pBullet->Location);
	}
	
}

void UpTrajectory::OnAIVelocity(BulletClass* pBullet, BulletVelocity* pSpeed, BulletVelocity* pPosition)
{
	pSpeed->Z += BulletTypeExt::GetAdjustedGravity(pBullet->Type); // We don't want to take the gravity into account
}

TrajectoryCheckReturnType UpTrajectory::OnAITargetCoordCheck(BulletClass* pBullet)
{
	return TrajectoryCheckReturnType::ExecuteGameCheck; // Execute game checks.
}

TrajectoryCheckReturnType UpTrajectory::OnAITechnoCheck(BulletClass* pBullet, TechnoClass* pTechno)
{
	return TrajectoryCheckReturnType::SkipGameCheck; // Bypass game checks entirely.
}

