// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisPieceBase.h"

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
		CubeRef_X = i_CubeMesh->GetBounds().BoxExtent.X * 2;
		CubeRef_Y = i_CubeMesh->GetBounds().BoxExtent.Y * 2;
		CubeRef_Z = i_CubeMesh->GetBounds().BoxExtent.Z * 2;

		// Init all pieces
		for (int i = 0; i < i_PiecesCoordinates.Num(); i++)
		{
			UStaticMeshComponent* NewCubeComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
			// Set the static mesh for the component
			NewCubeComponent->SetStaticMesh(i_CubeMesh);
			NewCubeComponent->SetupAttachment(RootMesh);

			//UStaticMesh* NewCube = GetWorld()->SpawnActor<UStaticMesh>(i_CubeMesh->GetClass(), )
			
			FTetrisCoordinate NewCubeCoordinate = i_PiecesCoordinates[i];
			FCubeStruct NewCubeStruct;
			NewCubeStruct.CubeMesh = NewCubeComponent;
			NewCubeStruct.CubeCoordinates = NewCubeCoordinate;
			Cubes.Add(NewCubeStruct);
		}

		// Init Base Coordinate
		BaseCoordinate = i_BaseCoordinate;

		// Finished Init
		IsFinishedInit = true;

		// When finished Init, should update all pieces world position once
		//UpdatePiecesWorldPosition();
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
			FTetrisCoordinate CurrentCubeWorldCoordinate;
			CurrentCubeWorldCoordinate.x = BaseCoordinate.x + Cubes[i].CubeCoordinates.x;
			CurrentCubeWorldCoordinate.y = BaseCoordinate.y + Cubes[i].CubeCoordinates.y;
			CurrentCubeWorldCoordinate.z = BaseCoordinate.z + Cubes[i].CubeCoordinates.z;

			// Calculate the real world location
			FVector CurrentCubeWorldLocation = FVector(CurrentCubeWorldCoordinate.x * CubeRef_X, CurrentCubeWorldCoordinate.y * CubeRef_Y, CurrentCubeWorldCoordinate.z * CubeRef_Z);
			Cubes[i].CubeMesh->SetWorldLocation(CurrentCubeWorldLocation);
		}
	}
}

