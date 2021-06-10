#pragma once

#include "MicroscopeApiRequest.h"
#include "MicroscopeApiResponse.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "MicroscopeApiService.generated.h"


UCLASS()
class MICROSCOPEAPI_API UMicroscopeApiService final : public UGameInstanceSubsystem {
	GENERATED_BODY()

	/** Internal API request callback. */
	void OnApiRequestComplete(class UMicroscopeApiRequest* Request, bool bWasSuccessful);

public:
	/** Storage for pending requests and matching responses. */
	UPROPERTY()
	TMap<class UMicroscopeApiRequest*, FMicroscopeApiResponse> RequestMap;

	UFUNCTION(BlueprintCallable)
	void GetObjects(const FString Id, const FMicroscopeApiCallDelegate& Callback);
};
