// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisController.h"

void ATetrisController::SignNewPieceToCurrentControlledPiece(ATetrisPieceBase* n_ControlledPiece)
{
	CurrentControlledPiece = n_ControlledPiece;
}

void ATetrisController::StartGame()
{
	// Set the input mode
	FInputModeGameOnly inputMode;
	inputMode.SetConsumeCaptureMouseDown(false);
	SetInputMode(inputMode);
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATetrisController::BeginPlay()
{
	Super::BeginPlay();

	// Set input mode
	//FInputModeUIOnly inputMode;
	FInputModeUIOnly inputMode;
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	this->SetInputMode(inputMode);
	this->SetShowMouseCursor(true);
}

void ATetrisController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ATetrisController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Movement
	// Single Click
	InputComponent->BindAction<FMoveXDelegate>("X_Forward", IE_Pressed, this, &ATetrisController::MoveOnTheXAxis, 1);
	InputComponent->BindAction<FMoveXDelegate>("X_Backward", IE_Pressed, this, &ATetrisController::MoveOnTheXAxis, -1);
	InputComponent->BindAction<FMoveYDelegate>("Y_Forward", IE_Pressed, this, &ATetrisController::MoveOnTheYAxis, 1);
	InputComponent->BindAction<FMoveYDelegate>("Y_Backward", IE_Pressed, this, &ATetrisController::MoveOnTheYAxis, -1);
	InputComponent->BindAction("Z_Down", IE_Pressed, this, &ATetrisController::MoveDown);
	// Keep Press
	InputComponent->BindAction<FMoveXDelegate>("X_Forward", IE_Repeat, this, &ATetrisController::MoveOnTheXAxis, 1);
	InputComponent->BindAction<FMoveXDelegate>("X_Backward", IE_Repeat, this, &ATetrisController::MoveOnTheXAxis, -1);
	InputComponent->BindAction<FMoveYDelegate>("Y_Forward", IE_Repeat, this, &ATetrisController::MoveOnTheYAxis, 1);
	InputComponent->BindAction<FMoveYDelegate>("Y_Backward", IE_Repeat, this, &ATetrisController::MoveOnTheYAxis, -1);
	InputComponent->BindAction("Z_Down", IE_Repeat, this, &ATetrisController::MoveDown);

	// Rotate
	// Single Click
	InputComponent->BindAction<FRotateXDelegate>("X_Clockwise", IE_Pressed, this, &ATetrisController::RotateOnTheXAxis, 1);
	InputComponent->BindAction<FRotateXDelegate>("X_Counterclockwise", IE_Pressed, this, &ATetrisController::RotateOnTheXAxis, -1);
	InputComponent->BindAction<FRotateYDelegate>("Y_Clockwise", IE_Pressed, this, &ATetrisController::RotateOnTheYAxis, 1);
	InputComponent->BindAction<FRotateYDelegate>("Y_Counterclockwise", IE_Pressed, this, &ATetrisController::RotateOnTheYAxis, -1);
	InputComponent->BindAction<FRotateZDelegate>("Z_Clockwise", IE_Pressed, this, &ATetrisController::RotateOnTheZAxis, 1);
	InputComponent->BindAction<FRotateZDelegate>("Z_Counterclockwise", IE_Pressed, this, &ATetrisController::RotateOnTheZAxis, -1);
	// Keep Press
	InputComponent->BindAction<FRotateXDelegate>("X_Clockwise", IE_Repeat, this, &ATetrisController::RotateOnTheXAxis, 1);
	InputComponent->BindAction<FRotateXDelegate>("X_Counterclockwise", IE_Repeat, this, &ATetrisController::RotateOnTheXAxis, -1);
	InputComponent->BindAction<FRotateYDelegate>("Y_Clockwise", IE_Repeat, this, &ATetrisController::RotateOnTheYAxis, 1);
	InputComponent->BindAction<FRotateYDelegate>("Y_Counterclockwise", IE_Repeat, this, &ATetrisController::RotateOnTheYAxis, -1);
	InputComponent->BindAction<FRotateZDelegate>("Z_Clockwise", IE_Repeat, this, &ATetrisController::RotateOnTheZAxis, 1);
	InputComponent->BindAction<FRotateZDelegate>("Z_Counterclockwise", IE_Repeat, this, &ATetrisController::RotateOnTheZAxis, -1);
}

void ATetrisController::MoveOnTheXAxis(int Dir)
{
	if (CurrentControlledPiece)
	{
		if (Dir == 1)
		{
			CurrentControlledPiece->TetrisMove(ETetrisMoveDir::X_Forward);
		}
		else if (Dir == -1)
		{
			CurrentControlledPiece->TetrisMove(ETetrisMoveDir::X_Backward);
		}
	}
	
}

void ATetrisController::MoveOnTheYAxis(int Dir)
{
	if (CurrentControlledPiece)
	{
		if (Dir == 1)
		{
			CurrentControlledPiece->TetrisMove(ETetrisMoveDir::Y_Forward);
		}
		else if (Dir == -1)
		{
			CurrentControlledPiece->TetrisMove(ETetrisMoveDir::Y_Backward);
		}
	}
}

void ATetrisController::MoveDown()
{
	if (CurrentControlledPiece)
	{
		CurrentControlledPiece->TetrisMove(ETetrisMoveDir::Down);
	}
}

void ATetrisController::RotateOnTheXAxis(int Dir)
{
	if (CurrentControlledPiece)
	{
		if (Dir == 1)
		{
			CurrentControlledPiece->TetrisRotate(ETetrisRotateDir::X_Clockwise);
		}
		else
		{
			CurrentControlledPiece->TetrisRotate(ETetrisRotateDir::X_Counterclockwise);
		}
	}
}

void ATetrisController::RotateOnTheYAxis(int Dir)
{
	if (CurrentControlledPiece)
	{
		if (Dir == 1)
		{
			CurrentControlledPiece->TetrisRotate(ETetrisRotateDir::Y_Clockwise);
		}
		else
		{
			CurrentControlledPiece->TetrisRotate(ETetrisRotateDir::Y_Counterclockwise);
		}
	}
}

void ATetrisController::RotateOnTheZAxis(int Dir)
{
	if (CurrentControlledPiece)
	{
		if (Dir == 1)
		{
			CurrentControlledPiece->TetrisRotate(ETetrisRotateDir::Z_Clockwise);
		}
		else
		{
			CurrentControlledPiece->TetrisRotate(ETetrisRotateDir::Z_Counterclockwise);
		}
	}
}
