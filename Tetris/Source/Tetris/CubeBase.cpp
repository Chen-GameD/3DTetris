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

void ACubeBase::InitCube(UStaticMesh* i_CubeMesh)
{
	if (i_CubeMesh)
	{
		CubeMeshComponent->SetStaticMesh(i_CubeMesh);
	}
}

