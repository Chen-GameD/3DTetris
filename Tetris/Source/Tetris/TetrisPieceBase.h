// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TetrisDataAsset.h"
#include "GameFramework/Actor.h"
#include "TetrisPieceBase.generated.h"

USTRUCT(BlueprintType)
struct FCubeStruct
{
	GENERATED_BODY()

	UPROPERTY()
	UStaticMeshComponent* CubeMesh;
	UPROPERTY()
	FTetrisCoordinate CubeCoordinates;
};

UCLASS()
class TETRIS_API ATetrisPieceBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisPieceBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Init actor by config file
	UFUNCTION(BlueprintCallable)
	void InitPiece(TArray<FTetrisCoordinate> i_PiecesCoordinates, FTetrisCoordinate i_BaseCoordinate, UStaticMesh* i_CubeMesh);

	// Update all pieces world position
	UFUNCTION(BlueprintCallable)
	void UpdatePiecesWorldPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	// TSubclassOf<UStaticMesh> CubeStaticMeshRef;

	// Root
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RootMesh;

	UPROPERTY(BlueprintReadWrite)
	TArray<FCubeStruct> Cubes;

	// This is the base coordinate, the Cubes[i]'s world coordinate = BaseCoordinate + Cubes[i].CubeCoordinates;
	UPROPERTY(BlueprintReadWrite)
	FTetrisCoordinate BaseCoordinate;

private:
	UPROPERTY()
	bool IsFinishedInit = false;

	// CubeStaticMeshRef's length, width and height;
	UPROPERTY()
	float CubeRef_X;
	UPROPERTY()
	float CubeRef_Y;
	UPROPERTY()
	float CubeRef_Z;
};
