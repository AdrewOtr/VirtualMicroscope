#pragma once
#include "MicroscopeApiRequest.h"
#include "MicroscopeFile.h"

#include "MicroscopeApiGetObjectFilesRequest.generated.h"

UCLASS()
class MICROSCOPEAPI_API UMicroscopeGetObjectFilesRequest final : public UMicroscopeApiRequest {
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
    TArray<FMicroscopeFile> Files;
};
