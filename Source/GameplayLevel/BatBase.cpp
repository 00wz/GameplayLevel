// Fill out your copyright notice in the Description page of Project Settings.


#include "BatBase.h"
#include "BallBase.h"

// Sets default values
ABatBase::ABatBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	//BallSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallSpawnPoint"));
	//BallSpawnPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//BallSpawnPoint->SetupAttachment(RootComponent);
	//BallSpawnPoint->SetRelativeLocation({ 3,3,3 });
	//BallSpawnPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//IsConstructorWorked = true;
}

// Called when the game starts or when spawned
void ABatBase::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	//SpawnBall();
	//IsBeginPlayWorked = true;
}

// Called every frame
void ABatBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABatBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SetupPlayerInputComponent"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Horizontal", this, &ABatBase::MoveRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABatBase::ThrowBall);
}

void ABatBase::MoveRight(float Value)
{
	FVector deltaPosition{ 0,MoveSpeed * World->GetDeltaSeconds() * Value,0 };
	AddActorWorldOffset(deltaPosition,true);
}

ABallBase* ABatBase::SpawnBall()
{
	/*
	if (IsConstructorWorked)
	{
		UE_LOG(LogTemp, Warning, TEXT("IsConstructorWorked = true"));
	}
	if (IsBeginPlayWorked)
	{
		UE_LOG(LogTemp, Warning, TEXT("IsBeginPlayWorked = true"));
	}
	*/
	//if(IsValid(ReadyBall))return;
	auto ReadyBall = World->SpawnActor<ABallBase>(BallClass
		, GetBallSpawnPoint()->GetComponentTransform().GetLocation(), FRotator{});
	ReadyBall->AttachToActor(this,FAttachmentTransformRules::KeepWorldTransform);
	ReadyBalls.Add(ReadyBall);
	return ReadyBall;
}

void ABatBase::ThrowBall()
{
	if (ReadyBalls.Num()>0)
	{
		auto ReadyBall = ReadyBalls.Pop();
		ReadyBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		ReadyBall->SetMoveSpeed(GetBallSpawnPoint()->GetForwardVector()* BallSpeed);
		ReadyBall = NULL;
	}
}

