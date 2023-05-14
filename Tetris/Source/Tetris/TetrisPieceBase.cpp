// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisPieceBase.h"

#include "TetrisGameModeBase.h"

// Sets default values
ATetrisPieceBase::ATetrisPieceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));	
	RootMesh->SetupAttachment(RootComponent);
	RootMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ATetrisPieceBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATetrisPieceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATetrisPieceBase::InitPiece(TArray<FTetrisCoordinate> i_PiecesCoordinates, FTetrisCoordinate i_BaseCoordinate, UStaticMesh* i_CubeMesh)
{
	if (i_PiecesCoordinates.Num() > 0 && i_CubeMesh)
	{
		// Init CubeStaticMeshRef's length, width and height;
		// CubeRef_X = i_CubeMesh->GetBounds().BoxExtent.X * 2;
		// CubeRef_Y = i_CubeMesh->GetBounds().BoxExtent.Y * 2;
		// CubeRef_Z = i_CubeMesh->GetBounds().BoxExtent.Z * 2;

		// Init all pieces
		CubeNumber = i_PiecesCoordinates.Num();
		for (int i = 0; i < i_PiecesCoordinates.Num(); i++)
		{
			// New a cube and attach to RootMesh component
			ACubeBase* NewCube = GetWorld()->SpawnActor<ACubeBase>(ACubeBase::StaticClass(), FVector(0, 0, 0), FRotator::ZeroRotator);
			NewCube->InitCube(i_CubeMesh, this);
			NewCube->AttachToComponent(RootMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);

			// Calculate relative coordinate of this cube
			FTetrisCoordinate NewCubeRelativeCoordinate = i_PiecesCoordinates[i];
			FCubeStruct NewCubeStruct;
			NewCubeStruct.Cube = NewCube;
			NewCubeStruct.CubeRelativeCoordinates = NewCubeRelativeCoordinate;
			
			// Add new cube to the array
			Cubes.Add(NewCubeStruct);
		}

		// Init Base Coordinate
		BaseCoordinate = i_BaseCoordinate;

		// Finished Init
		IsFinishedInit = true;

		// When finished Init, should update all pieces world position once
		UpdatePiecesWorldPosition();

		// Check if this meet game over
		if (!CheckIfCanMoveOrRotate())
		{
			ATetrisGameModeBase* MyGameMode = Cast<ATetrisGameModeBase>(GetWorld()->GetAuthGameMode());
			if (MyGameMode)
			{
				MyGameMode->GameOver();
			}
		}
	}
	else
	{
		// Input Error
		// TODO
	}
}

void ATetrisPieceBase::UpdatePiecesWorldPosition()
{
	if (IsFinishedInit)
	{
		for (int i = 0; i < Cubes.Num(); i++)
		{
			// Cubes[i]'s world coordinate = BaseCoordinate + Cubes[i].CubeCoordinates
			// FTetrisCoordinate CurrentCubeWorldCoordinate;
			// CurrentCubeWorldCoordinate.x = BaseCoordinate.x + Cubes[i].CubeRelativeCoordinates.x;
			// CurrentCubeWorldCoordinate.y = BaseCoordinate.y + Cubes[i].CubeRelativeCoordinates.y;
			// CurrentCubeWorldCoordinate.z = BaseCoordinate.z + Cubes[i].CubeRelativeCoordinates.z;
			
			Cubes[i].Cube->CubeWorldCoordinate = BaseCoordinate + Cubes[i].CubeRelativeCoordinates;
			Cubes[i].Cube->UpdateCubePosition();

			// Calculate the real world location
			// FVector CurrentCubeWorldLocation = FVector(CurrentCubeWorldCoordinate.x * CubeRef_X, CurrentCubeWorldCoordinate.y * CubeRef_Y, CurrentCubeWorldCoordinate.z * CubeRef_Z);
			// Cubes[i].Cube->SetActorLocation(CurrentCubeWorldLocation);
		}
	}
}

bool ATetrisPieceBase::TetrisMove(ETetrisMoveDir n_Dir)
{
	bool retValue = true;
	FTetrisCoordinate oldCoordinate = BaseCoordinate;
	switch (n_Dir)
	{
	case ETetrisMoveDir::X_Forward:
		BaseCoordinate.x++;
		break;
	case ETetrisMoveDir::X_Backward:
		BaseCoordinate.x--;
		break;
	case ETetrisMoveDir::Y_Forward:
		BaseCoordinate.y++;
		break;
	case ETetrisMoveDir::Y_Backward:
		BaseCoordinate.y--;
		break;
	case ETetrisMoveDir::Down:
		BaseCoordinate.z--;
		break;
		default:
			break;
	}

	// If cannot move, restore the BaseCoordinate
	if (!CheckIfCanMoveOrRotate())
	{
		BaseCoordinate = oldCoordinate;
		retValue = false;
	}

	// Update world position
	UpdatePiecesWorldPosition();

	return retValue;
}

//////////////////////////////////////////////////////////////////////////////////////
/// Here I need to apply the relevant knowledge of rotation matrix in linear algebra.
/// Suppose the rotation angle is A:
/// //////////////////////////////////////////////////////////////////////////////////
/// If rotate along X-axis:
/// new_x = old_x;
/// new_y = old_y * cosA + old_z * sinA;
/// new_z = -(old_y * sinA) + old_z * cosA;
///========================================================
/// If rotate along Y-axis:
/// new_x = old_x * cosA - old_z * sinA;
/// new_y = old_y;
/// new_z = old_x * sinA + old_z * cosA;
///=========================================================
/// If rotate along Z_axis:
/// new_x = old_x * cosA + old_y * sinA;
/// new_y = -(old_x * sinA) + old_y * cosA;
/// new_z = old_z;
/////////////////////////////////////////////////////////////////////////////////////
void ATetrisPieceBase::TetrisRotate(ETetrisRotateDir n_Rot)
{
	TArray<FCubeStruct> oldCubes = Cubes;
	switch (n_Rot)
	{
	case ETetrisRotateDir::X_Clockwise:
		for (int i = 0; i < Cubes.Num(); i++)
		{
			Cubes[i].CubeRelativeCoordinates = TetrisCubeRotate_X(true, Cubes[i].CubeRelativeCoordinates);
		}
		break;
	case ETetrisRotateDir::X_Counterclockwise:
		for (int i = 0; i < Cubes.Num(); i++)
		{
			Cubes[i].CubeRelativeCoordinates = TetrisCubeRotate_X(false, Cubes[i].CubeRelativeCoordinates);
		}
		break;
	case ETetrisRotateDir::Y_Clockwise:
		for (int i = 0; i < Cubes.Num(); i++)
		{
			Cubes[i].CubeRelativeCoordinates = TetrisCubeRotate_Y(true, Cubes[i].CubeRelativeCoordinates);
		}
		break;
	case ETetrisRotateDir::Y_Counterclockwise:
		for (int i = 0; i < Cubes.Num(); i++)
		{
			Cubes[i].CubeRelativeCoordinates = TetrisCubeRotate_Y(false, Cubes[i].CubeRelativeCoordinates);
		}
		break;
	case ETetrisRotateDir::Z_Clockwise:
		for (int i = 0; i < Cubes.Num(); i++)
		{
			Cubes[i].CubeRelativeCoordinates = TetrisCubeRotate_Z(true, Cubes[i].CubeRelativeCoordinates);
		}
		break;
	case ETetrisRotateDir::Z_Counterclockwise:
		for (int i = 0; i < Cubes.Num(); i++)
		{
			Cubes[i].CubeRelativeCoordinates = TetrisCubeRotate_Z(false, Cubes[i].CubeRelativeCoordinates);
		}
		break;
		default:
			break;
	}

	// If cannot rotate, restore the previous value
	if (!CheckIfCanMoveOrRotate())
	{
		Cubes = oldCubes;
	}

	// Update world position
	UpdatePiecesWorldPosition();
}

bool ATetrisPieceBase::CheckIfCanMoveOrRotate()
{
	bool retValue = true;

	ATetrisGameModeBase* MyGameMode = Cast<ATetrisGameModeBase>(GetWorld()->GetAuthGameMode());
	if (MyGameMode)
	{
		for (int i = 0; i < Cubes.Num(); i++)
		{
			if (!MyGameMode->CheckIfCubePositionIsValid(BaseCoordinate + Cubes[i].CubeRelativeCoordinates))
			{
				retValue = false;
				break;
			}
		}
	}
	
	return  retValue;
}

void ATetrisPieceBase::EliminateACubeFromThisPiece()
{
	CubeNumber--;
	if (CubeNumber <= 0)
	{
		this->Destroy();
	}
}

FTetrisCoordinate ATetrisPieceBase::TetrisCubeRotate_X(bool isClockwise, FTetrisCoordinate i_OldCoordinate)
{
	int cosA = -2;
	int sinA = -2;
	if (isClockwise)
	{
		cosA = 0;
		sinA = 1;
	}
	else
	{
		cosA = 0;
		sinA = -1;
	}

	// Calculate
	FTetrisCoordinate NewCoordinate;
	NewCoordinate.x = i_OldCoordinate.x;
	NewCoordinate.y = i_OldCoordinate.y * cosA + i_OldCoordinate.z * sinA;
	NewCoordinate.z = -(i_OldCoordinate.y * sinA) + i_OldCoordinate.z * cosA;

	return  NewCoordinate;
}

FTetrisCoordinate ATetrisPieceBase::TetrisCubeRotate_Y(bool isClockwise, FTetrisCoordinate i_OldCoordinate)
{
	int cosA = -2;
	int sinA = -2;
	if (isClockwise)
	{
		cosA = 0;
		sinA = 1;
	}
	else
	{
		cosA = 0;
		sinA = -1;
	}

	// Calculate
	FTetrisCoordinate NewCoordinate;
	NewCoordinate.x = i_OldCoordinate.x * cosA - i_OldCoordinate.z * sinA;
	NewCoordinate.y = i_OldCoordinate.y;
	NewCoordinate.z = i_OldCoordinate.x * sinA + i_OldCoordinate.z * cosA;

	return  NewCoordinate;
}

FTetrisCoordinate ATetrisPieceBase::TetrisCubeRotate_Z(bool isClockwise, FTetrisCoordinate i_OldCoordinate)
{
	int cosA = -2;
	int sinA = -2;
	if (isClockwise)
	{
		cosA = 0;
		sinA = 1;
	}
	else
	{
		cosA = 0;
		sinA = -1;
	}

	// Calculate
	FTetrisCoordinate NewCoordinate;
	NewCoordinate.x = i_OldCoordinate.x * cosA + i_OldCoordinate.y * sinA;
	NewCoordinate.y = -(i_OldCoordinate.x * sinA) + i_OldCoordinate.y * cosA;
	NewCoordinate.z = i_OldCoordinate.z;

	return  NewCoordinate;
}

