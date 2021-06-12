#pragma once
#include "MicroscopeApiRequest.h"
#include "MicroscopeObject.h"

#include "MicroscopeApiPostObjectRequest.generated.h"

UCLASS()
class MICROSCOPEAPI_API UMicroscopePostObjectRequest final : public UMicroscopeApiRequest {
    GENERATED_BODY()

protected:
    virtual void ProcessRequest() override;
    virtual void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) override;

public:
    /** Request object Id. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Title;

    /** Request department Id. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString DepartmentId;

    /** Request result. */
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
    FMicroscopeObject Object;
};
