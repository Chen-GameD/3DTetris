// Copyright Epic Games, Inc. All Rights Reserved.


#include "TetrisGameModeBase.h"

void ATetrisGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	
}

void ATetrisGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (TetrisDataConfig && SpawnTetrisPieceRef)
	{
		// Init game area
		GA_X = TetrisDataConfig->MapSize.x;
		GA_Y = TetrisDataConfig->MapSize.y;
		GA_Z = TetrisDataConfig->MapSize.z;

		/// Calculate spawn coordinate :
		/// Need to notice coordinate (0, 0, 0) is in the lower left corner of the entire game area
		/// The piece we want to spawn is in the middle of the top of the entire game, so the coordinate should be (GA_X/2, GA_Y/2, GA_Z)
		TetrisSpawnCoordinate.x = GA_X / 2;
		TetrisSpawnCoordinate.y = GA_Y / 2;
		TetrisSpawnCoordinate.z = GA_Z;

		//////////////////////////////// Test //////////////////////////////////
		// Spawn a piece
		FTransform spawnTransform;
		FVector spawnLocation = FVector(TetrisSpawnCoordinate.x * 100, TetrisSpawnCoordinate.y * 100, TetrisSpawnCoordinate.z * 100);
		spawnTransform.SetLocation(spawnLocation);
		ATetrisPieceBase* NewTetrisPiece = GetWorld()->SpawnActor<ATetrisPieceBase>(SpawnTetrisPieceRef, spawnTransform);
		if (NewTetrisPiece)
		{
			CurrentControlledTetrisPiece = NewTetrisPiece;
			CurrentControlledTetrisPiece->InitPiece(TetrisDataConfig->TetrisShapes[0].CubeConfig, TetrisSpawnCoordinate, TetrisDataConfig->CubeStaticMesh);
		}
	}
}
