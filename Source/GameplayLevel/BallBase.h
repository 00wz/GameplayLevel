// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\..\Intermediate\ProjectFiles\Delegates.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallBase.generated.h"

UCLASS()
class GAMEPLAYLEVEL_API ABallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallBase();

	UPROPERTY(VisibleAnyWhere, BlueprintReadonly)
		UStaticMeshComponent* MeshComponent;

	BallBaseDelegate OnDestroyBall;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly)
		FVector MoveSpeed;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetMoveSpeed(FVector NewSpeed);
	
	FVector GetMoveSpeed();
	
private:
	void Move(float DeltaTime);
};
