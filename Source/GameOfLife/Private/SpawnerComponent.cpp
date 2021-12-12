#include "SpawnerComponent.h"
#include "Engine/World.h"
#include "GameOfLife/Public/GOLCell.h"

USpawnerComponent::USpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	/// init 2D arrays
	Grid = TArray<TArray<AGOLCell*>>();
	Grid.Reserve(SizeX);
	NextStep = TArray<TArray<bool>>();
	NextStep.Reserve(SizeX);
	for (int i = 0; i < SizeX; ++i)
	{
		Grid.Add(TArray<AGOLCell*>());
		Grid[i].Reserve(SizeY);
		NextStep.Add(TArray<bool>());
		NextStep[i].Reserve(SizeY);
	}
}

void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickInterval(UpdateInterval);
}


void USpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PendingUpdate)
		Update();
}

void USpawnerComponent::InitGrid()
{
	FVector Location;
	FRotator Rotation = FRotator::ZeroRotator;

	for (int i = 0; i < SizeX; ++i)
	{
		for (int j = 0; j < SizeY; ++j)
		{
			Location = FVector((i - SizeX / 2.0 + 0.5) * CellSize, (j - SizeY / 2.0 + 0.5) * CellSize, 0);
			AActor* temp = GetWorld()->SpawnActor(CellClass, &Location, &Rotation);
			Grid[i].Add(Cast<AGOLCell>(temp));
			NextStep[i].Add(false);
		}
	}
}

void USpawnerComponent::Update()
{
	CalculateNextStep();
	RefreshGrid();
}

void USpawnerComponent::CalculateNextStep()
{
	int AliveNeighboursNum;
	for (int i = 0; i < SizeX; ++i)
	{
		for (int j = 0; j < SizeY; ++j)
		{
			AliveNeighboursNum = CalculateAliveNeighbours(i, j);
			if (Grid[i][j]->GetIsAlive())
			{
				if (AliveNeighboursNum < 2 || AliveNeighboursNum > 3)
					NextStep[i][j] = false;
				else
					NextStep[i][j] = true;
			} else
			{
				if (AliveNeighboursNum == 3)
					NextStep[i][j] = true;
				else
					NextStep[i][j] = false;
			}
		}
	}
}

void USpawnerComponent::RefreshGrid()
{
	for (int i = 0; i < SizeX; ++i)
	{
		for (int j = 0; j < SizeY; ++j)
		{
			if (NextStep[i][j])
				Grid[i][j]->Live();
			else
				Grid[i][j]->Die();
		}
	}
}

int USpawnerComponent::CalculateAliveNeighbours(const int I, const int J)
{
	int Result = 0;
	int CurrI, CurrJ;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (!(i == 0 && j == 0))
			{
				CurrI = I + i;
				CurrJ = J + j;
				if (CurrI >= 0 && CurrI < SizeX && CurrJ >= 0 && CurrJ < SizeY)
				{
					if (Grid[CurrI][CurrJ]->GetIsAlive())
						Result++;
				}
			}
		}
	}
	return Result;
}

void USpawnerComponent::TogglePendingUpdate()
{
	PendingUpdate = !PendingUpdate;
}