// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBase.h"

// Sets default values
ACubeBase::ACubeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMeshComponent->SetupAttachment(RootComponent);
	CubeMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ACubeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeBase::InitCube(UStaticMesh* i_CubeMesh, AActor* i_ParentPiece)
{
	if (i_CubeMesh && i_ParentPiece)
	{
		CubeMeshComponent->SetStaticMesh(i_CubeMesh);

		// Init CubeStaticMeshRef's length, width and height;
		CubeRef_X = i_CubeMesh->GetBounds().BoxExtent.X * 2;
		CubeRef_Y = i_CubeMesh->GetBounds().BoxExtent.Y * 2;
		CubeRef_Z = i_CubeMesh->GetBounds().BoxExtent.Z * 2;

		// Set the parent piece
		ParentPiece = i_ParentPiece;
	}
}

void ACubeBase::UpdateCubePosition()
{
	// Calculate the real world location
	FVector CurrentCubeWorldLocation = FVector(CubeWorldCoordinate.x * CubeRef_X, CubeWorldCoordinate.y * CubeRef_Y, CubeWorldCoordinate.z * CubeRef_Z);
	this->SetActorLocation(CurrentCubeWorldLocation);
}

