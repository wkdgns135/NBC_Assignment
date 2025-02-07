#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

UCLASS()
class ASSIGNMENT_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:
    ABaseItem();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemType;
    // 씬 컴포넌트 (루트)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    USceneComponent* Scene;
    // 충돌 컴포넌트 (플레이어 진입 범위 감지)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    class USphereComponent* Collision;
    // 아이템의 시각적 표현을 담당하는 스태틱 메시
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
    UStaticMeshComponent* StaticMesh;

    virtual void OnItemOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult) override;
    virtual void OnItemEndOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex) override;
    virtual void ActivateItem(AActor* Activator) override;
    virtual FName GetItemType() const override;

    void DestroyItem();
};
