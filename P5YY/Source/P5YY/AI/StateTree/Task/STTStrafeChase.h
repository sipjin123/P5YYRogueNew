#pragma once

#include "STTChaseTarget.h"
#include "STTStrafeChase.generated.h"

UCLASS()
class USTTStrafeChase : public USTTChaseTarget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float StrafeRadius;

protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
};
