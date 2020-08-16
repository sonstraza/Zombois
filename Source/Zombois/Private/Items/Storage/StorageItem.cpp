// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Storage/StorageItem.h"

AStorageItem::AStorageItem()
{

}

void AStorageItem::BeginPlay()
{
}

void AStorageItem::Tick(float DeltaTime)
{
}

void AStorageItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	//TODO: 
}

void AStorageItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);


}
