// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusBase.h"

#include <string>

// Sets default values
ABonusBase::ABonusBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	bBonusActivated=false;
}

void ABonusBase::Init(float BonusFallSpeed_, ::BallSpawner* BallSpawner_, ABatBase* BatBase_)
{
	BonusFallSpeed=BonusFallSpeed_;
	BallSpawner=BallSpawner_;
	Bat=BatBase_;
}

// Called when the game starts or when spawned
void ABonusBase::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this,&ABonusBase::OnOverlapBegin);
}

void ABonusBase::EnableBonus()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	FString::Printf(TEXT("Bonus  ACTIVATED")));
}

void ABonusBase::DisableBonus()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
		FString::Printf(TEXT("Bonus INACTIVATED")));
}

// Called every frame
void ABonusBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void ABonusBase::Move(float DeltaTime)
{
	FVector deltaPosition{ -BonusFallSpeed*DeltaTime,0,0 };
	AddActorWorldOffset(deltaPosition);
}

void ABonusBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto BatBase = Cast<ABatBase>(OtherActor);
	if (BatBase)
	{
		ActivateBonus();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}

void ABonusBase::ActivateBonus()
{
	if(!bBonusActivated)
	{
		EnableBonus();
		bBonusActivated=true;
	}
}

void ABonusBase::InactivateBonus()
{
	if(bBonusActivated)
	{
		DisableBonus();
		bBonusActivated=false;
	}
}


