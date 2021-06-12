#pragma once
#include "MicroscopeApiRequest.h"
#include "MicroscopeDepartment.h"

#include "MicroscopeApiGetDepartmentsRequest.generated.h"

UCLASS()
class MICROSCOPEAPI_API UMicroscopeGetDepartmentsRequest final : public UMicroscopeApiRequest {
    GENERATED_BODY()

protected:
    virtual void ProcessRequest() override;
    virtual void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) override;

public:
    /** Request result. */
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    TArray<FMicroscopeDepartment> Departments;
};
