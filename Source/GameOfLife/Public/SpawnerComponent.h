#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnerComponent.generated.h"

class AGOLCell;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFLIFE_API USpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USpawnerComponent();

protected:
	virtual void BeginPlay() override;

	void Update();
	void CalculateNextStep();
	void RefreshGrid();

	int CalculateAliveNeighbours(const int I, const int J);

	UFUNCTION(BlueprintCallable)
	void InitGrid();

	TArray<TArray<AGOLCell*>> Grid;
	TArray<TArray<bool>> NextStep;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGOLCell> CellClass;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float CellSize = 200.f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	int SizeX = 10;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	int SizeY = 10;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.1", ClampMax = "5.0"))
	float UpdateInterval = 0.7f;

	bool PendingUpdate = false;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TogglePendingUpdate();
};
