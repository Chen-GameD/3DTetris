// Copyright Epic Games, Inc. All Rights Reserved.


#include "TetrisGameModeBase.h"

void ATetrisGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ATetrisGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (!MyController)
	{
		// Sign playercontroller
		MyController = Cast<ATetrisController>(GetWorld()->GetFirstPlayerController());
	}

	// if (TetrisDataConfig && SpawnTetrisPieceRef && MyController)
	// {
	// 	// Init game area
	// 	// GA_X = TetrisDataConfig->MapSize.x;
	// 	// GA_Y = TetrisDataConfig->MapSize.y;
	// 	// GA_Z = TetrisDataConfig->MapSize.z;
	//
	// 	/// Calculate spawn coordinate :
	// 	/// Need to notice coordinate (0, 0, 0) is in the upper left corner of the entire game area
	// 	/// The piece we want to spawn is in the middle of the top of the entire game, so the coordinate should be (GA_X/2, GA_Y/2, GA_Z)
	// 	TetrisSpawnCoordinate.x = TetrisDataConfig->MapSize.x / 2;
	// 	TetrisSpawnCoordinate.y = TetrisDataConfig->MapSize.y / 2;
	// 	TetrisSpawnCoordinate.z = TetrisDataConfig->MapSize.z;
	//
	// 	// Init Cube Size
	// 	CubeSize.X = TetrisDataConfig->CubeStaticMesh->GetBounds().BoxExtent.X * 2;
	// 	CubeSize.Y = TetrisDataConfig->CubeStaticMesh->GetBounds().BoxExtent.Y * 2;
	// 	CubeSize.Z = TetrisDataConfig->CubeStaticMesh->GetBounds().BoxExtent.Z * 2;
	//
	// 	// Init Map
	// 	if (MapRef)
	// 	{
	// 		FTransform spawnTransform;
	// 		spawnTransform.SetLocation(FVector(0, 0, 0));
	// 		spawnTransform.SetScale3D(FVector(1, 1, 1));
	// 		ATetrisMapBase* newMap = GetWorld()->SpawnActor<ATetrisMapBase>(MapRef, spawnTransform);
	// 		if (newMap)
	// 		{
	// 			GameMap = newMap;
	// 			GameMap->InitMap(TetrisDataConfig->MapSize.x, TetrisDataConfig->MapSize.y, TetrisDataConfig->MapSize.z, CubeSize);
	// 		}
	// 	}
	//
	// 	//////////////////////////////// Test //////////////////////////////////
	// 	// Spawn a piece
	// 	// FTransform spawnTransform;
	// 	// FVector spawnLocation = FVector(TetrisSpawnCoordinate.x * 100, TetrisSpawnCoordinate.y * 100, TetrisSpawnCoordinate.z * 100);
	// 	// spawnTransform.SetLocation(spawnLocation);
	// 	// ATetrisPieceBase* NewTetrisPiece = GetWorld()->SpawnActor<ATetrisPieceBase>(SpawnTetrisPieceRef, spawnTransform);
	// 	// if (NewTetrisPiece)
	// 	// {
	// 	// 	CurrentControlledTetrisPiece = NewTetrisPiece;
	// 	// 	CurrentControlledTetrisPiece->InitPiece(TetrisDataConfig->TetrisShapes[0].CubeConfig, TetrisSpawnCoordinate, TetrisDataConfig->CubeStaticMesh);
	// 	// }
	// 	//
	// 	// FTimerHandle TestTimerHandle;
	// 	// //GetWorldTimerManager().SetTimer(TestTimerHandle, this, &ATetrisGameModeBase::Timer_AutoUpdatePieceCoordinate, 2.0f, true);
	// 	//
	// 	// MyController->SignNewPieceToCurrentControlledPiece(CurrentControlledTetrisPiece);
	// 	// SpawnANewPiece();
	// 	// GetWorldTimerManager().SetTimer(AutoUpdateTimerHandle, this, &ATetrisGameModeBase::Timer_AutoUpdatePieceCoordinate, 1.0f, true);
	//
	// 	// FTimerHandle TestTimerHandle;
	// 	// GetWorldTimerManager().SetTimer(TestTimerHandle, this, &ATetrisGameModeBase::AddCurrentPieceToFillCubes, 10.0f, true);
	// 	//////////////////////////////// Test //////////////////////////////////
	// 	
	// }
}

void ATetrisGameModeBase::SpawnANewPiece()
{
	// Spawn a piece
	// Set mutex
	IsSpawn = true;
	FTransform spawnTransform;
	FVector spawnLocation = FVector(TetrisSpawnCoordinate.x * CubeSize.X, TetrisSpawnCoordinate.y * CubeSize.Y, TetrisSpawnCoordinate.z * CubeSize.Z);
	spawnTransform.SetLocation(spawnLocation);
	ATetrisPieceBase* NewTetrisPiece = GetWorld()->SpawnActor<ATetrisPieceBase>(SpawnTetrisPieceRef, spawnTransform);
	if (NewTetrisPiece)
	{
		CurrentControlledTetrisPiece = NewTetrisPiece;
		// Random to spawn a piece
		int CurrentSpawnPieceIndex = FMath::RandRange(0, TetrisDataConfig->TetrisShapes.Num() - 1);
		CurrentControlledTetrisPiece->InitPiece(TetrisDataConfig->TetrisShapes[CurrentSpawnPieceIndex].CubeConfig, TetrisSpawnCoordinate, TetrisDataConfig->CubeStaticMesh);
	}
	
	MyController->SignNewPieceToCurrentControlledPiece(CurrentControlledTetrisPiece);

	// Release mutex
	IsSpawn = false;
}

void ATetrisGameModeBase::AddCurrentPieceToFillCubes()
{
	if (CurrentControlledTetrisPiece)
	{
		// Release control
		MyController->SignNewPieceToCurrentControlledPiece(nullptr);

		for (int i = 0; i < CurrentControlledTetrisPiece->Cubes.Num(); i++)
		{
			// Convert the relative coordinates in CurrentControlledTetrisPiece->Cubes[i].CubeRelativeCoordinates into absolute coordinates
			CurrentControlledTetrisPiece->Cubes[i].CubeRelativeCoordinates.x += CurrentControlledTetrisPiece->BaseCoordinate.x;
			CurrentControlledTetrisPiece->Cubes[i].CubeRelativeCoordinates.y += CurrentControlledTetrisPiece->BaseCoordinate.y;
			CurrentControlledTetrisPiece->Cubes[i].CubeRelativeCoordinates.z += CurrentControlledTetrisPiece->BaseCoordinate.z;

			// Assign them to FillCubes
			//FillCubes.Add(CurrentControlledTetrisPiece->Cubes[i]);
			GameMap->AddToFillCubes(CurrentControlledTetrisPiece->Cubes[i].Cube);
		}
		// Check if need to Eliminate'
		GameMap->CheckIfCubesNeedEliminate();

		// Clean CurrentControlledTetrisPiece
		CurrentControlledTetrisPiece = nullptr;
		// Spawn a new piece
		SpawnANewPiece();
	}
}

bool ATetrisGameModeBase::CheckIfCubePositionIsValid(FTetrisCoordinate i_CheckCubeCoordinate)
{
	return GameMap->CheckIfCubePositionIsValid(i_CheckCubeCoordinate);
}

void ATetrisGameModeBase::StartGame()
{
	if (TetrisDataConfig && SpawnTetrisPieceRef && MyController)
	{
		// Init game area
		// GA_X = TetrisDataConfig->MapSize.x;
		// GA_Y = TetrisDataConfig->MapSize.y;
		// GA_Z = TetrisDataConfig->MapSize.z;

		/// Calculate spawn coordinate :
		/// Need to notice coordinate (0, 0, 0) is in the upper left corner of the entire game area
		/// The piece we want to spawn is in the middle of the top of the entire game, so the coordinate should be (GA_X/2, GA_Y/2, GA_Z)
		TetrisSpawnCoordinate.x = TetrisDataConfig->MapSize.x / 2;
		TetrisSpawnCoordinate.y = TetrisDataConfig->MapSize.y / 2;
		TetrisSpawnCoordinate.z = TetrisDataConfig->MapSize.z - 1;

		// Init Cube Size
		CubeSize.X = TetrisDataConfig->CubeStaticMesh->GetBounds().BoxExtent.X * 2;
		CubeSize.Y = TetrisDataConfig->CubeStaticMesh->GetBounds().BoxExtent.Y * 2;
		CubeSize.Z = TetrisDataConfig->CubeStaticMesh->GetBounds().BoxExtent.Z * 2;

		// Init Map
		if (MapRef)
		{
			FTransform spawnTransform;
			spawnTransform.SetLocation(FVector(0, 0, 0));
			spawnTransform.SetScale3D(FVector(1, 1, 1));
			ATetrisMapBase* newMap = GetWorld()->SpawnActor<ATetrisMapBase>(MapRef, spawnTransform);
			if (newMap)
			{
				GameMap = newMap;
				GameMap->InitMap(TetrisDataConfig->MapSize.x, TetrisDataConfig->MapSize.y, TetrisDataConfig->MapSize.z, CubeSize);
			}
		}

		// Init Score
		Score = 0;

		BPF_StartGame();

		SpawnANewPiece();
		if (TetrisDataConfig->TimerLevel.Num() > 0)
		{
			CurrentTimerLevel = 0;
		}
		else
		{
			CurrentTimerLevel = -1;
		}
		SetTimerToCurrentLevel();
	}
}

void ATetrisGameModeBase::GameOver()
{
	MyController->GameOver();
	BPF_GameOver();
}

void ATetrisGameModeBase::Timer_AutoUpdatePieceCoordinate()
{
	if (CurrentControlledTetrisPiece && !IsSpawn)
	{
		if (!CurrentControlledTetrisPiece->TetrisMove(ETetrisMoveDir::Down))
		{
			AddCurrentPieceToFillCubes();
		}
	}
}

void ATetrisGameModeBase::SetTimerToCurrentLevel()
{
	if (CurrentTimerLevel >= 0)
	{
		// Set tick timer
		if (TetrisDataConfig->TimerLevel.IsValidIndex(CurrentTimerLevel))
		{
			GetWorldTimerManager().ClearTimer(AutoUpdateTimerHandle);
			GetWorldTimerManager().SetTimer(AutoUpdateTimerHandle, this, &ATetrisGameModeBase::Timer_AutoUpdatePieceCoordinate, TetrisDataConfig->TimerLevel[CurrentTimerLevel].TickTime, true);
			// Set upgrade level timer
			switch (TetrisDataConfig->TimerLevel[CurrentTimerLevel].UpgradeLevelType)
			{
				case ETetrisLevelUpgradeTypeEnum::Time:
            		if (TetrisDataConfig->TimerLevel[CurrentTimerLevel].KeyValueToTheNewLevel > 0)
            		{
            			// Need to set a timer for upgrade level
            			GetWorldTimerManager().ClearTimer(AutoUpgradeTimerLevelHandle);
            			GetWorldTimerManager().SetTimer(AutoUpgradeTimerLevelHandle, this, &ATetrisGameModeBase::UpgradeTimerLevel, TetrisDataConfig->TimerLevel[CurrentTimerLevel].KeyValueToTheNewLevel, true);
            		}
                    else
                    {
                    	// If KeyValueToTheNewLevel <= 0, means it will not increase level anymore
                    	GetWorldTimerManager().ClearTimer(AutoUpgradeTimerLevelHandle);
                    }
            		break;
            	case ETetrisLevelUpgradeTypeEnum::Score:
            		if (TetrisDataConfig->TimerLevel[CurrentTimerLevel].KeyValueToTheNewLevel > 0)
            		{
            			// Need to set a timer for upgrade level
            			GetWorldTimerManager().ClearTimer(AutoUpgradeTimerLevelHandle);
            			GetWorldTimerManager().SetTimer(AutoUpgradeTimerLevelHandle, this, &ATetrisGameModeBase::CheckIfScoreMeetTheUpgradeRequire, 2.0f, true);
            		}
            		else
            		{
            			// If KeyValueToTheNewLevel <= 0, means it will not increase level anymore
            			GetWorldTimerManager().ClearTimer(AutoUpgradeTimerLevelHandle);
            		}
            		break;
            	default:
            		break;
			}
		}
		else
		{
			// If the index is not valid, need to keep game running,
			// Normally we need to output a log message to notice the designer here has a potential problem.
			GetWorldTimerManager().ClearTimer(AutoUpgradeTimerLevelHandle);
		}
	}
	else
	{
		// Set the InRate to a default value
		GetWorldTimerManager().SetTimer(AutoUpdateTimerHandle, this, &ATetrisGameModeBase::Timer_AutoUpdatePieceCoordinate, 1.0f, true);
	}
}

void ATetrisGameModeBase::UpgradeTimerLevel()
{
	CurrentTimerLevel++;
	SetTimerToCurrentLevel();
}

void ATetrisGameModeBase::CheckIfScoreMeetTheUpgradeRequire()
{
	if (Score >= TetrisDataConfig->TimerLevel[CurrentTimerLevel].KeyValueToTheNewLevel)
	{
		// Need to upgrade
		UpgradeTimerLevel();
	}
}
