#pragma once
#include "MicroscopeApiRequest.h"
#include "MicroscopeObject.h"

#include "MicroscopeApiGetObjectsRequest.generated.h"

UCLASS()
class MICROSCOPEAPI_API UMicroscopeGetObjectsRequest final : public UMicroscopeApiRequest {
    GENERATED_BODY()

protected:
    virtual void ProcessRequest() override;
    virtual void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) override;

public:
    /** Request result. */
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TArray<FMicroscopeObject> Objects;
};
