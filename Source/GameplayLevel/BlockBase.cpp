// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockBase.h"
#include "BallBase.h"
// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	//MeshComponent->OnComponentHit.__Internal_AddDynamic(this,)
}

void ABlockBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto ball = Cast<ABallBase>(OtherActor);
	if (ball)
	{
		Damage();
	}
}

void ABlockBase::SetHealth(int value)
{
	Health = value;
	OnHealthChanged.Broadcast(Health);
}

// Called when the game starts or when spawned
void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentHit.AddDynamic(this, &ABlockBase::OnHit);
	
}

// Called every frame
void ABlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockBase::Damage()
{
	Health--;
	if (Health <= 0)
	{
		Destroy();
		return;
	}
	OnHealthChanged.Broadcast(Health);
}

void ABlockBase::Destroyed()
{
	OnDestroyBlock.ExecuteIfBound(this);
}

