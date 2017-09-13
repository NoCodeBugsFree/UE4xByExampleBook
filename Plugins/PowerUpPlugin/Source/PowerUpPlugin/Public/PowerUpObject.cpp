#include "PowerUpObject.h"

UPowerUpObject::UPowerUpObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	int iType = FMath::Rand() % 3;
	switch (iType)
	{
	case 0:
	{
		PowerUpType = EPowerUp::SPEED;
		break;
	}
	case 1:
	{
		PowerUpType = EPowerUp::SMASH;
		break;
	}
	case 2:
	{
		PowerUpType = EPowerUp::MAGNET;
		break;
	}
	default:
		break;
	}
}