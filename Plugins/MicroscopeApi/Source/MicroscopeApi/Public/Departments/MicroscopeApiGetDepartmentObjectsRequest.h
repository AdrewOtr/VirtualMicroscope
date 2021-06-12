#pragma once
#include "MicroscopeApiRequest.h"
#include "MicroscopeObject.h"

#include "MicroscopeApiGetDepartmentObjectsRequest.generated.h"

UCLASS()
class MICROSCOPEAPI_API UMicroscopeGetDepartmentObjectsRequest final : public UMicroscopeApiRequest {
    GENERATED_BODY()

protected:
    virtual void ProcessRequest() override;
    virtual void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) override;

public:
    /** Request object Id. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;

    /** Request result. */
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TArray<FMicroscopeObject> Objects;
};
