#pragma once

#include "..\..\Intermediate\ProjectFiles\Delegates.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, int, NewHealth);

UCLASS()
class GAMEPLAYLEVEL_API ABlockBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlockBase();

	UPROPERTY(VisibleAnyWhere, BlueprintReadonly)
		UStaticMeshComponent* MeshComponent;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
		void SetHealth(int value);

	BlockBaseDelegate OnDestroyBlock;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
		FOnHealthChanged OnHealthChanged;

	virtual void Destroyed() override;

public:	
	virtual void Tick(float DeltaTime) override;
private:
	void Damage();		
	
	int Health;
};
