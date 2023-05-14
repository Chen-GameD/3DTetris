// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeBase.h"
#include "TetrisDataAsset.h"
#include "GameFramework/Actor.h"
#include "TetrisPieceBase.generated.h"

UENUM(BlueprintType)
enum ETetrisMoveDir { X_Forward, X_Backward, Y_Forward, Y_Backward, Down };

UENUM(BlueprintType)
enum ETetrisRotateDir { X_Clockwise, X_Counterclockwise, Y_Clockwise, Y_Counterclockwise, Z_Clockwise, Z_Counterclockwise };

USTRUCT(BlueprintType)
struct FCubeStruct
{
	GENERATED_BODY()

	UPROPERTY()
	ACubeBase* Cube;
	UPROPERTY()
	FTetrisCoordinate CubeRelativeCoordinates;
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

	// Move function
	UFUNCTION(BlueprintCallable)
	bool TetrisMove(ETetrisMoveDir n_Dir);
	// Rotate function
	UFUNCTION(BlueprintCallable)
	void TetrisRotate(ETetrisRotateDir n_Rot);
	// Check if can move or rotate
	UFUNCTION(BlueprintCallable)
	bool CheckIfCanMoveOrRotate();

	// Eliminate cube
	UFUNCTION(BlueprintCallable)
	void EliminateACubeFromThisPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Rotate unit
	UFUNCTION(BlueprintCallable)
	FTetrisCoordinate TetrisCubeRotate_X(bool isClockwise, FTetrisCoordinate i_OldCoordinate);
	UFUNCTION(BlueprintCallable)
	FTetrisCoordinate TetrisCubeRotate_Y(bool isClockwise, FTetrisCoordinate i_OldCoordinate);
	UFUNCTION(BlueprintCallable)
	FTetrisCoordinate TetrisCubeRotate_Z(bool isClockwise, FTetrisCoordinate i_OldCoordinate);

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

	UPROPERTY()
	int CubeNumber = 0;
};
