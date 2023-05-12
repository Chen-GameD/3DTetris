// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TetrisDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTetrisCoordinate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Coordinate")
	int x;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Coordinate")
	int y;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Coordinate")
	int z;
};

USTRUCT(BlueprintType)
struct FTetrisPieceShape
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTetrisCoordinate> CubeConfig;
};

UCLASS(BlueprintType)
class TETRIS_API UTetrisDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// Map size
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tetris Map Config")
	FTetrisCoordinate MapSize;

	// Cube static mesh reference
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tetris Pieces Config")
	UStaticMesh* CubeStaticMesh;

	// Tetris pieces config
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tetris Pieces Config")
	TArray<FTetrisPieceShape> TetrisShapes;
};
