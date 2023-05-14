// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Windows.UI.Input.h>

#include "CoreMinimal.h"
#include "CubeBase.h"
#include "GameFramework/Actor.h"
#include "TetrisMapBase.generated.h"

UCLASS()
class TETRIS_API ATetrisMapBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisMapBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Init
	UFUNCTION(BlueprintCallable)
	void InitMap(int i_GA_X, int i_GA_Y, int i_GA_Z, FVector i_CubeSize);

	// Add cube in FillCubes
	UFUNCTION(BlueprintCallable)
	void AddToFillCubes(ACubeBase* i_Cube);

	// Check if a cube position is valid
	UFUNCTION(BlueprintCallable)
	bool CheckIfCubePositionIsValid(FTetrisCoordinate i_CheckCubeCoordinate);

	// Check if Cube needs to be eliminated
	UFUNCTION(BlueprintCallable)
	void CheckIfCubesNeedEliminate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Eliminate cubes
	UFUNCTION(BlueprintCallable)
	void EliminateCubes(int i_TheLayerNeedToEliminate);

public:
	// Map Area
	// The entire game area is a box,
	// and the wall on the X axis is called X_Wall_StaticMesh;
	// The other wall parallel to the x-axis is called X_Wall_Mirror_StaticMesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* X_Wall_StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* X_Wall_Mirror_StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Y_Wall_StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Y_Wall_Mirror_StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Floor_StaticMesh;
	// X, Y, Z Arrow
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Arrow_X_StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Arrow_Y_StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Arrow_Z_StaticMesh;

	// Game area
	UPROPERTY()
	int GA_X = 10;
	UPROPERTY()
	int GA_Y = 10;
	UPROPERTY()
	int GA_Z = 20;

private:
	UPROPERTY()
	UStaticMeshComponent* RootMesh;

	UPROPERTY()
	TArray<ACubeBase*> FillCubes;

	// Use FillState to detect if a layer completely filled
	// Key is a integer to indicate the layer (z-axis)
	// Value is a number of how may cube it has in this layer
	UPROPERTY()
	TMap<int, int> FillState;
	UPROPERTY()
	int ThresholdOfALayer = 0;

};
