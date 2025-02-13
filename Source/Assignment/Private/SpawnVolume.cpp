#include "SpawnVolume.h"
#include "Components/BoxComponent.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	PositiveItemDataTable = nullptr;
	NegativeItemDataTable = nullptr;
}

ABaseItem* ASpawnVolume::SpawnRandomItem(bool bIsSpawnPositiveItem)
{
	FItemSpawnRow* SelectedRow = GetRandomItem(bIsSpawnPositiveItem ? PositiveItemDataTable : NegativeItemDataTable);
	if (SelectedRow)
	{
		return SpawnItem(SelectedRow->ItemClass);
	}

	return nullptr;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem(UDataTable* ItemDataTable) const
{
	if (!ItemDataTable) return nullptr;

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnRow"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);

	float AccumulateChance = 0.0f;

	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

ABaseItem* ASpawnVolume::GetObject(TSubclassOf<ABaseItem> ItemClass)
{
	ABaseItem* NewItem = nullptr;
	if (ObjectPools.Contains(ItemClass)) {
		if (!ObjectPools[ItemClass]->IsEmpty())
		{
			ObjectPools[ItemClass]->Dequeue(NewItem);
			return NewItem;
		}
	}
	else {
		ObjectPools.Add(ItemClass, new TQueue<ABaseItem*>());
	}

	NewItem = GetWorld()->SpawnActor<ABaseItem>(ItemClass);
	if (NewItem) {
		NewItem->Activate();
		NewItem->SetPool(ObjectPools[ItemClass]);
	}
	return NewItem;
}

void ASpawnVolume::ReturnObject(ABaseItem* Object)
{
	if (Object)
	{
		Object->Deactivate();
	}
}

ABaseItem* ASpawnVolume::SpawnItem(TSubclassOf<ABaseItem> ItemClass)
{
	if (!ItemClass) return nullptr;

	// 풀에서 오브젝트를 가져옴
	ABaseItem* BaseItem = GetObject(ItemClass);
	BaseItem->Initialize(GetRandomPointInVolume(), FRotator::ZeroRotator);

	return BaseItem;
}
