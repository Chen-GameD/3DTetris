// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisMapBase.h"

#include "TetrisPieceBase.h"

// Sets default values
ATetrisMapBase::ATetrisMapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));	
	RootMesh->SetupAttachment(RootComponent);
	RootMesh->SetCollisionProfileName(TEXT("NoCollision"));

	X_Wall_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XWall"));	
	X_Wall_StaticMesh->SetupAttachment(RootMesh);
	X_Wall_StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	X_Wall_Mirror_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XMirrorWall"));	
	X_Wall_Mirror_StaticMesh->SetupAttachment(RootMesh);
	X_Wall_Mirror_StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));

	Y_Wall_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YWall"));	
	Y_Wall_StaticMesh->SetupAttachment(RootMesh);
	Y_Wall_StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	Y_Wall_Mirror_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YMirrorWall"));	
	Y_Wall_Mirror_StaticMesh->SetupAttachment(RootMesh);
	Y_Wall_Mirror_StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));

	Floor_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorWall"));	
	Floor_StaticMesh->SetupAttachment(RootMesh);
	Floor_StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));

	Arrow_X_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowX"));	
	Arrow_X_StaticMesh->SetupAttachment(RootMesh);
	Arrow_X_StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	Arrow_Y_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowY"));	
	Arrow_Y_StaticMesh->SetupAttachment(RootMesh);
	Arrow_Y_StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	Arrow_Z_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowZ"));	
	Arrow_Z_StaticMesh->SetupAttachment(RootMesh);
	Arrow_Z_StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
}

void ATetrisMapBase::InitMap(int i_GA_X, int i_GA_Y, int i_GA_Z, FVector i_CubeSize)
{
	// Init game area
	GA_X = i_GA_X;
	GA_Y = i_GA_Y;
	GA_Z = i_GA_Z;

	// Init the threshold of a layer
	ThresholdOfALayer = i_GA_X * i_GA_Y;
	
	float meshSizeX = Floor_StaticMesh->GetStaticMesh()->GetBoundingBox().GetSize().X;
	float meshSizeY = Floor_StaticMesh->GetStaticMesh()->GetBoundingBox().GetSize().Y;

	// Arrow:
	// X
	FTransform newArrowXTransform;
	newArrowXTransform.SetLocation(FVector(-i_CubeSize.X / 2, -i_CubeSize.Y / 2, 0));
	FRotator ArrowXRotationToAdd(0, -90, 0);
	newArrowXTransform.SetRotation(ArrowXRotationToAdd.Quaternion());
	Arrow_X_StaticMesh->SetRelativeTransform(newArrowXTransform);
	// Y
	FTransform newArrowYTransform;
	newArrowYTransform.SetLocation(FVector(-i_CubeSize.X / 2, -i_CubeSize.Y / 2, 0));
	Arrow_Y_StaticMesh->SetRelativeTransform(newArrowYTransform);
	// Z
	FTransform newArrowZTransform;
	newArrowZTransform.SetLocation(FVector(-i_CubeSize.X / 2, -i_CubeSize.Y / 2, 0));
	FRotator ArrowZRotationToAdd(0, 0, -90);
	newArrowZTransform.SetRotation(ArrowZRotationToAdd.Quaternion());
	Arrow_Z_StaticMesh->SetRelativeTransform(newArrowZTransform);
	
	// Floor wall:
	FTransform newFloorTransform;
	newFloorTransform.SetLocation(FVector(-i_CubeSize.X / 2, -i_CubeSize.Y / 2, 0));
	newFloorTransform.SetScale3D(FVector(i_GA_X * i_CubeSize.X / meshSizeX, i_GA_Y * i_CubeSize.Y / meshSizeY, 1));
	Floor_StaticMesh->SetRelativeTransform(newFloorTransform);

	// X_Wall:
	FTransform newXWallTransform;
	newXWallTransform.SetLocation(FVector(-i_CubeSize.X / 2, -i_CubeSize.Y / 2, i_GA_Z * i_CubeSize.Z));
	newXWallTransform.SetScale3D(FVector(i_GA_X * i_CubeSize.X / meshSizeX, i_GA_Z * i_CubeSize.Z / meshSizeY, 1));
	FRotator XRotationToAdd(0, 0, 90);
	newXWallTransform.SetRotation(XRotationToAdd.Quaternion());
	X_Wall_StaticMesh->SetRelativeTransform(newXWallTransform);
	// X_Mirror_Wall:
	FTransform newXMirrorWallTransform;
	newXMirrorWallTransform.SetLocation(FVector(-i_CubeSize.X / 2, i_GA_Y * i_CubeSize.Y - i_CubeSize.Y / 2, 0));
	newXMirrorWallTransform.SetScale3D(FVector(i_GA_X * i_CubeSize.X / meshSizeX, i_GA_Z * i_CubeSize.Z / meshSizeY, 1));
	FRotator XMirroRotationToAdd(0, 0, -90);
	newXMirrorWallTransform.SetRotation(XMirroRotationToAdd.Quaternion());
	X_Wall_Mirror_StaticMesh->SetRelativeTransform(newXMirrorWallTransform);

	// Y_Wall:
	FTransform newYWallTransform;
	newYWallTransform.SetLocation(FVector(-i_CubeSize.X / 2, -i_CubeSize.Y / 2, i_GA_Z * i_CubeSize.Z));
	newYWallTransform.SetScale3D(FVector(i_GA_Z * i_CubeSize.Z / meshSizeX, i_GA_Y * i_CubeSize.Y / meshSizeY, 1));
	FRotator YRotationToAdd(-90, 0, 0);
	newYWallTransform.SetRotation(YRotationToAdd.Quaternion());
	Y_Wall_StaticMesh->SetRelativeTransform(newYWallTransform);
	// Y_Mirror_Wall:
	FTransform newYMirrorWallTransform;
	newYMirrorWallTransform.SetLocation(FVector(i_GA_X * i_CubeSize.X - i_CubeSize.X / 2, -i_CubeSize.Y / 2, 0));
	newYMirrorWallTransform.SetScale3D(FVector(i_GA_Z * i_CubeSize.Z / meshSizeX, i_GA_Y * i_CubeSize.Y / meshSizeY, 1));
	FRotator YMirrorRotationToAdd(90, 0, 0);
	newYMirrorWallTransform.SetRotation(YMirrorRotationToAdd.Quaternion());
	Y_Wall_Mirror_StaticMesh->SetRelativeTransform(newYMirrorWallTransform);

	// Init FillCubes
	FillCubes.Empty();
	// Init FillState
	FillState.Empty();
}

void ATetrisMapBase::AddToFillCubes(ACubeBase* i_Cube)
{
	if (i_Cube)
	{
		FillCubes.Add(i_Cube);
		if (FillState.Contains(i_Cube->CubeWorldCoordinate.z))
		{
			int cubeNumInCurrentLayer = FillState[i_Cube->CubeWorldCoordinate.z];
			cubeNumInCurrentLayer++;
			FillState[i_Cube->CubeWorldCoordinate.z] = cubeNumInCurrentLayer;
		}
		else
		{
			FillState.Add(i_Cube->CubeWorldCoordinate.z, 1);
		}
	}
}

bool ATetrisMapBase::CheckIfCubePositionIsValid(FTetrisCoordinate i_CheckCubeCoordinate)
{
	bool retValue = true;

	for (int i = 0; i < FillCubes.Num(); i++)
	{
		// Determine whether a Cube already exists at the current location
		if (FillCubes[i]->CubeWorldCoordinate == i_CheckCubeCoordinate)
		{
			retValue = false;
			break;
		}
	}

	// Determine whether the position exceeds the boundary of the game area
	if (i_CheckCubeCoordinate.x > GA_X - 1 ||
		i_CheckCubeCoordinate.y > GA_Y - 1 ||
		i_CheckCubeCoordinate.z > GA_Z - 1 ||
		i_CheckCubeCoordinate.x < 0 ||
		i_CheckCubeCoordinate.y < 0 ||
		i_CheckCubeCoordinate.z < 0)
	{
		retValue = false;
	}

	return retValue;
}

// Called when the game starts or when spawned
void ATetrisMapBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATetrisMapBase::CheckIfCubesNeedEliminate()
{
	int theLayerNeedToEliminate = -1;
	bool isNeedToEliminate = false;
	// Iterate the FillState
	for (TMap<int, int>::TIterator It(FillState); It; ++It)
	{
		if (It.Value() == ThresholdOfALayer)
		{
			theLayerNeedToEliminate = It.Key();
			isNeedToEliminate = true;
			break;
			//FillState[It.Key()] = 0;
		}
	}

	if (isNeedToEliminate && theLayerNeedToEliminate >= 0)
	{
		EliminateCubes(theLayerNeedToEliminate);
	}
}

void ATetrisMapBase::EliminateCubes(int i_TheLayerNeedToEliminate)
{
	// Destroy cubes
	TArray<ACubeBase*> newFillCubes;
	for (int i = 0; i < FillCubes.Num(); i++)
	{
		bool isNeedDestory = false;

		if (FillCubes[i]->CubeWorldCoordinate.z == i_TheLayerNeedToEliminate)
		{
			ACubeBase* currentRemoveCube = FillCubes[i];
			ATetrisPieceBase* currentCubeParent = Cast<ATetrisPieceBase>(currentRemoveCube->ParentPiece);
			if (currentCubeParent)
			{
				currentCubeParent->EliminateACubeFromThisPiece();
			}
			currentRemoveCube->Destroy();
			isNeedDestory = true;
		}
		if (!isNeedDestory)
		{
			newFillCubes.Add(FillCubes[i]);
		}
	}
	FillCubes = newFillCubes;

	// Update the rest cubes coordinate
	for (int i = 0; i < FillCubes.Num(); i++)
	{
		if (FillCubes[i]->CubeWorldCoordinate.z > i_TheLayerNeedToEliminate)
		{
			FillCubes[i]->CubeWorldCoordinate.z--;
			FillCubes[i]->UpdateCubePosition();
		}
	}

	// Reset the FillState
	FillState.Empty();
	for (int i = 0; i < FillCubes.Num(); i++)
	{
		if (!FillState.Contains(FillCubes[i]->CubeWorldCoordinate.z))
		{
			FillState.Add(FillCubes[i]->CubeWorldCoordinate.z, 1);
		}
		else
		{
			int cubeNumInCurrentLayer = FillState[FillCubes[i]->CubeWorldCoordinate.z];
			cubeNumInCurrentLayer++;
			FillState[FillCubes[i]->CubeWorldCoordinate.z] = cubeNumInCurrentLayer;
		}
	}

	// Recheck
	CheckIfCubesNeedEliminate();
}

// Called every frame
void ATetrisMapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

