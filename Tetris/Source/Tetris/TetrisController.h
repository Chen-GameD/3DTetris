// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TetrisPieceBase.h"
#include "GameFramework/PlayerController.h"
#include "TetrisController.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SignNewPieceToCurrentControlledPiece(ATetrisPieceBase* n_ControlledPiece);

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void GameOver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	// Movement control
	// X
	DECLARE_DELEGATE_OneParam(FMoveXDelegate, int);
	UFUNCTION()
	void MoveOnTheXAxis(int Dir); // If Dir == 1, move along the positive x-axis; If Dir == -1, move along the negative x-axis
	// Y
	DECLARE_DELEGATE_OneParam(FMoveYDelegate, int);
	UFUNCTION()
	void MoveOnTheYAxis(int Dir); // If Dir == 1, move along the positive y-axis; If Dir == -1, move along the negative y-axis
	// Z (Down)
	UFUNCTION()
	void MoveDown();

	// Rotate control
	// X
	DECLARE_DELEGATE_OneParam(FRotateXDelegate, int);
	UFUNCTION()
	void RotateOnTheXAxis(int Dir); // If Dir == 1, rotate clockwise along the x-axis; If Dir == -1, rotate counterclockwise along the x-axis
	// Y
	DECLARE_DELEGATE_OneParam(FRotateYDelegate, int);
	UFUNCTION()
	void RotateOnTheYAxis(int Dir); // If Dir == 1, rotate clockwise along the y-axis; If Dir == -1, rotate counterclockwise along the y-axis
	// Z (Down)
	DECLARE_DELEGATE_OneParam(FRotateZDelegate, int);
	UFUNCTION()
	void RotateOnTheZAxis(int Dir); // If Dir == 1, rotate clockwise along the z-axis; If Dir == -1, rotate counterclockwise along the z-axis

private:
	UPROPERTY()
	ATetrisPieceBase* CurrentControlledPiece;
};
