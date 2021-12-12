// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GOLCell.generated.h"

UCLASS()
class GAMEOFLIFE_API AGOLCell : public AActor
{
	GENERATED_BODY()
	
public:
	AGOLCell();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterial* AliveMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* DeadMaterial;

	bool IsAlive;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	bool GetIsAlive();

	void Live();
	void Die();
};
