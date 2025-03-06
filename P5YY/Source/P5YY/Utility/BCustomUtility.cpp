#include "BCustomUtility.h"
#if WITH_EDITOR
#include "Editor.h"
#include "EditorViewportClient.h"
#endif

#include "Engine/OverlapResult.h"
#include "Kismet/KismetMathLibrary.h"


void UBCustomUtility::Test(int a, int b)
{
	
}

FVector UBCustomUtility::GetViewportCamLoc()
{
	FVector viewPos;
#if WITH_EDITOR// || !WITH_EDITOR
	//FViewport* Viewport = GEditor->GetActiveViewport();
	//FIntPoint mousePos;
	//GEditor->GetActiveViewport()->GetMousePos(mousePos, true);
	FViewport* activeViewport = GEditor->GetActiveViewport();
	FEditorViewportClient* editorViewClient = (FEditorViewportClient*)activeViewport->GetClient();
	if( editorViewClient )
	{
		viewPos = editorViewClient->GetViewLocation();
	}
	return viewPos;
#endif
	//return FVector(0.0f, 0.0f, 0.0f);
	return viewPos;
}

TArray<AActor*> UBCustomUtility::GetActorsWithinRadius(FVector Origin, float Radius, UObject* WorldContextObject)
{
	// This doesnt work for Blueprint Function Library
	//UWorld* world = GEngine->GameViewport->GetWorld();

	UWorld * world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	TArray<AActor*> OutActors;


    FCollisionShape DetectionSphere = FCollisionShape::MakeSphere(Radius);

    // Define object types to detect (only detect Pawns, like enemies)
    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

    // Store detected actors
    TArray<FOverlapResult> OverlapResults;

    // Perform Overlap
    bool bHasOverlap = world->OverlapMultiByObjectType(
        OverlapResults, 
        Origin, 
        FQuat::Identity, 
        ObjectQueryParams, 
        DetectionSphere
    );

    // Draw debug sphere (optional, for visualization)
    DrawDebugSphere(world, Origin, Radius, 16, FColor::Green, false, 2.0f);

    // Process detected actors
    if (bHasOverlap)
    {
        for (const FOverlapResult& Result : OverlapResults)
        {
            AActor* DetectedActor = Result.GetActor();
            if (DetectedActor)//&& DetectedActor->ActorHasTag("Enemy")) // Check if it's an enemy
            {
                UE_LOG(LogTemp, Warning, TEXT("Enemy detected: %s"), *DetectedActor->GetName());
            	OutActors.Add(DetectedActor);
            }
        }
    }

	return OutActors;
}

FRotator UBCustomUtility::GetViewportCamRot()
{
	FRotator viewRot;
#if WITH_EDITOR// || !WITH_EDITOR
	FViewport* activeViewport = GEditor->GetActiveViewport();
	FEditorViewportClient* editorViewClient = (FEditorViewportClient*)activeViewport->GetClient();
	if( editorViewClient )
	{
		viewRot = editorViewClient->GetViewRotation();
	}
	return viewRot;
#endif
	return viewRot;
}

FVector UBCustomUtility::GetViewportForwardVector(FRotator NewRotator)
{
	return UKismetMathLibrary::GetForwardVector(NewRotator);
}
