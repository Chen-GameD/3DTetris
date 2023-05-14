// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TetrisDataAsset.h"
#include "GameFramework/Actor.h"
#include "CubeBase.generated.h"

UCLASS()
class TETRIS_API ACubeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Init
	UFUNCTION(BlueprintCallable)
	void InitCube(UStaticMesh* i_CubeMesh, AActor* i_ParentPiece);

	// Update position
	UFUNCTION(BlueprintCallable)
	void UpdateCubePosition();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite)
	FTetrisCoordinate CubeWorldCoordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CubeMeshComponent;

	UPROPERTY(BlueprintReadOnly)
	AActor* ParentPiece;

private:
	// CubeStaticMeshRef's length, width and height;
	UPROPERTY()
	float CubeRef_X;
	UPROPERTY()
	float CubeRef_Y;
	UPROPERTY()
	float CubeRef_Z;

};
