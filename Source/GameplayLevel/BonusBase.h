#pragma once

#include "CoreMinimal.h"
#include "BallSpawner.h"
#include "BatBase.h"
#include "GameFramework/Actor.h"
#include "BonusBase.generated.h"

UCLASS(Abstract, Blueprintable)
class GAMEPLAYLEVEL_API ABonusBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABonusBase();

	void Init(float BonusFallSpeed, BallSpawner* BallSpawner, ABatBase* BatBase);
	
protected:
	virtual void BeginPlay() override;

	BallSpawner* BallSpawner;

		ABatBase* Bat;

	UPROPERTY(VisibleAnyWhere, BlueprintReadonly)
	UStaticMeshComponent* MeshComponent;

	virtual void EnableBonus();

	virtual void DisableBonus();
	
	UPROPERTY(EditAnywhere)
		float BonusFallSpeed;

public:	
	virtual void Tick(float DeltaTime) override;

	void InactivateBonus();
private:

	void Move(float DeltaTime);
	
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp
		, class AActor* OtherActor
		, class UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
		, bool bFromSweep
		, const FHitResult& SweepResult);

	void ActivateBonus();

	bool bBonusActivated;
};
