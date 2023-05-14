// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TetrisDataAsset.generated.h"

/**
 * 
 */

UENUM()
enum ETetrisLevelUpgradeTypeEnum { Time, Score };

USTRUCT(BlueprintType)
struct FTimerStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timer")
	float TickTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timer")
	TEnumAsByte<ETetrisLevelUpgradeTypeEnum> UpgradeLevelType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timer")
	float KeyValueToTheNewLevel;
};

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

	// Override the == operator
	bool operator==(const FTetrisCoordinate& Other) const
	{
		return x == Other.x && y == Other.y && z == Other.z;
	}

	// Override the + operator
	FTetrisCoordinate operator+(const FTetrisCoordinate& Other) const
	{
		FTetrisCoordinate Result;
		Result.x = x + Other.x;
		Result.y = y + Other.y;
		Result.z = z + Other.z;
		return Result;
	}
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

	// Timer Level
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tetris Pieces Config")
	TArray<FTimerStruct> TimerLevel;
};
