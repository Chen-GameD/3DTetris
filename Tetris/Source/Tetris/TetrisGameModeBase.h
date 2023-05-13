// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TetrisController.h"
#include "TetrisPieceBase.h"
#include "GameFramework/GameModeBase.h"
#include "TetrisGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void Timer_AutoUpdatePieceCoordinate();

public:
	// Config table
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTetrisDataAsset* TetrisDataConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ATetrisPieceBase> SpawnTetrisPieceRef;

private:
	// Game area
	UPROPERTY()
	int GA_X = 10;
	UPROPERTY()
	int GA_Y = 10;
	UPROPERTY()
	int GA_Z = 20;

	// Current controlled tetris piece
	UPROPERTY()
	ATetrisPieceBase* CurrentControlledTetrisPiece;

	// Spawn piece coordinate
	FTetrisCoordinate TetrisSpawnCoordinate;

	UPROPERTY()
	ATetrisController* MyController;
};
