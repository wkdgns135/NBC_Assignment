#include "BaseItem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

ABaseItem::ABaseItem()
{
    PrimaryActorTick.bCanEverTick = false;

    // 루트 컴포넌트 생성 및 설정
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    // 충돌 컴포넌트 생성 및 설정
    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    // 겹침만 감지하는 프로파일 설정
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    // 루트 컴포넌트로 설정
    Collision->SetupAttachment(Scene);

    // 스태틱 메시 컴포넌트 생성 및 설정
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);

    // 이벤트 바인딩
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
    Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);
}

void ABaseItem::OnItemOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    // 플레이어와의 충돌 확인
    if (OtherActor && OtherActor->ActorHasTag("Player"))
    {
        // 아이템 활성화
        ActivateItem(OtherActor);
    }
}

void ABaseItem::OnItemEndOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
}

void ABaseItem::ActivateItem(AActor* Activator)
{
    TWeakObjectPtr<UParticleSystemComponent> Particle = nullptr;

    if (PickupParticle)
    {
        Particle = UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            PickupParticle,
            GetActorLocation(),
            GetActorRotation(),
            true
        );
    }

    if (Particle != nullptr)
    {
        FTimerHandle DestroyParticleTimerHandle;

        GetWorld()->GetTimerManager().SetTimer(
            DestroyParticleTimerHandle,
            [Particle]()
            {
                if (Particle != nullptr) 
                {
                    Particle->DestroyComponent();
                }
            },
            2.0f,
            false
        );
    }
}

FName ABaseItem::GetItemType() const
{
    return ItemType;
}

void ABaseItem::Activate()
{
    IsActive = true;
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);
}

void ABaseItem::Deactivate()
{
    IsActive = false;
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
    _Pool->Enqueue(this);
}

void ABaseItem::Initialize(FVector Pos, FRotator Rotation)
{
    SetActorLocation(Pos);
    SetActorRotation(Rotation);
}
