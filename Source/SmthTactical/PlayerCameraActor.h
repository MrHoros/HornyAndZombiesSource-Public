#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCameraActor.generated.h"

UCLASS()
class SMTHTACTICAL_API APlayerCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCameraActor();

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	FVector BaseLocation = FVector(0,0,0);
	UPROPERTY(EditAnywhere, Category = "Components")
	float YBorderOffset = 300;
	UPROPERTY(EditAnywhere, Category = "Components")
	float XBorderOffset = 300;
	
	UFUNCTION(BlueprintCallable, meta = (Tooltip = "Clamps given location within set boundaries."))
	FVector ClampLocation(FVector NewLocation);

	UFUNCTION(BlueprintCallable)
	void SetBaseLocation(FVector NewLocation);

	UFUNCTION(BlueprintPure)
	FVector GetBaseLocation();

public:

};
