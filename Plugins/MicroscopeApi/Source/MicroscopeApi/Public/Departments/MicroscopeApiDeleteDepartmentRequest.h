#pragma once
#include "MicroscopeApiRequest.h"

#include "MicroscopeApiDeleteDepartmentRequest.generated.h"

UCLASS()
class MICROSCOPEAPI_API UMicroscopeDeleteDepartmentRequest final : public UMicroscopeApiRequest {
    GENERATED_BODY()

protected:
    virtual void ProcessRequest() override;
    virtual void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) override;

public:
    /** Request object Id. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;
};
