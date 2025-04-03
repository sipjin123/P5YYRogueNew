#include "STTStrafeChase.h"

EStateTreeRunStatus USTTStrafeChase::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	float distance = GetDistanceFromTarget();
	
	if(distance < StrafeRadius)
	{
		UE_LOG(LogTemp, Log, TEXT("CHASE COMPLETED"));
		return EStateTreeRunStatus::Succeeded;
	}		
	
	return Super::EnterState(Context, Transition);
}
