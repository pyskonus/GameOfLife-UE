
#include "GOLCell.h"

AGOLCell::AGOLCell()
{
	PrimaryActorTick.bCanEverTick = true;	/// TODO: set false

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CellRootComponent"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);
}

void AGOLCell::BeginPlay()
{
	Super::BeginPlay();
	Die();
}

void AGOLCell::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	IsAlive ? Die() : Live();
}

void AGOLCell::Live()
{
	IsAlive = true;
	MeshComp->SetMaterial(0, AliveMaterial);
}

void AGOLCell::Die()
{
	IsAlive = false;
	MeshComp->SetMaterial(0, DeadMaterial);
}

void AGOLCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGOLCell::GetIsAlive()
{
	return IsAlive;
}

