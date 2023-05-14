// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TetrisController.h"
#include "TetrisMapBase.h"
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

	// Spawn a new Tetris Piece
	UFUNCTION(BlueprintCallable)
	void SpawnANewPiece();

	UFUNCTION(BlueprintCallable)
	void AddCurrentPieceToFillCubes();

	UFUNCTION(BlueprintCallable)
	bool CheckIfCubePositionIsValid(FTetrisCoordinate i_CheckCubeCoordinate);

	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void GameOver();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BPF_GameOver();

	UFUNCTION(BlueprintImplementableEvent)
	void BPF_StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void BPF_UpdateScore();

private:
	UFUNCTION(BlueprintCallable)
	void Timer_AutoUpdatePieceCoordinate();

	UFUNCTION(BlueprintCallable)
	void SetTimerToCurrentLevel();

	UFUNCTION(BlueprintCallable)
	void UpgradeTimerLevel();

	UFUNCTION(BlueprintCallable)
	void CheckIfScoreMeetTheUpgradeRequire();

public:
	// Config table
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTetrisDataAsset* TetrisDataConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ATetrisPieceBase> SpawnTetrisPieceRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ATetrisMapBase> MapRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score;

	// Map coordinate fill state
	//TArray<FCubeStruct> FillCubes;

private:
	// Game area
	// UPROPERTY()
	// int GA_X = 10;
	// UPROPERTY()
	// int GA_Y = 10;
	// UPROPERTY()
	// int GA_Z = 20;
	UPROPERTY()
	ATetrisMapBase* GameMap;

	// Tetris Cube Size
	UPROPERTY()
	FVector CubeSize;

	// Current controlled tetris piece
	UPROPERTY()
	ATetrisPieceBase* CurrentControlledTetrisPiece;

	// Spawn piece coordinate
	FTetrisCoordinate TetrisSpawnCoordinate;

	UPROPERTY()
	ATetrisController* MyController;

	FTimerHandle AutoUpdateTimerHandle;
	FTimerHandle AutoUpgradeTimerLevelHandle;
	bool IsSpawn = false;

	int CurrentTimerLevel;
};
