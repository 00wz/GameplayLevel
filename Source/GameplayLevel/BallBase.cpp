// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBase.h"

// Sets default values
ABallBase::ABallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	MoveSpeed = { 0,0,0 };
}

// Called when the game starts or when spawned
void ABallBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABallBase::Destroyed()
{
	OnDestroyBall.ExecuteIfBound(this);
}

// Called every frame
void ABallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void ABallBase::Move(float DeltaTime)
{
	FVector deltaPosition{ MoveSpeed.X*DeltaTime,MoveSpeed.Y * DeltaTime,0 };
	FHitResult* OutSweepHitResult=new FHitResult();
	AddActorWorldOffset(deltaPosition, true, OutSweepHitResult);
	if(OutSweepHitResult->bBlockingHit)
	{
		SetMoveSpeed(MoveSpeed.MirrorByVector(OutSweepHitResult->ImpactNormal));
	}
	delete OutSweepHitResult;
}

void ABallBase::SetMoveSpeed(FVector NewSpeed)
{
	MoveSpeed = { NewSpeed.X,NewSpeed.Y,0 };
}

