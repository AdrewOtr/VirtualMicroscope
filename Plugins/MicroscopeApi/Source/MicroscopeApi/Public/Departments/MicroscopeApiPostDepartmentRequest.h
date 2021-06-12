#pragma once
#include "MicroscopeApiRequest.h"
#include "MicroscopeDepartment.h"

#include "MicroscopeApiPostDepartmentRequest.generated.h"

UCLASS()
class MICROSCOPEAPI_API UMicroscopePostDepartmentRequest final : public UMicroscopeApiRequest {
    GENERATED_BODY()

protected:
    virtual void ProcessRequest() override;
    virtual void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) override;

public:
    /** Request object Id. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Title;

    /** Request result. */
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    FMicroscopeDepartment Department;
};
