#include "BatBase.h"
#include "BallBase.h"

ABatBase::ABatBase()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ABatBase::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
}

void ABatBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABatBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
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

