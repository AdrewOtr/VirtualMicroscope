#pragma once
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "MicroscopeApiRequest.generated.h"

/** Called when an API request completes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnApiRequestComplete, class UMicroscopeApiRequest*, Request, bool, bWasSuccessfu);

/** Called when an API request completes. */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCppApiRequestComplete, class UMicroscopeApiRequest*, bool);

/** Generic API request. */
UCLASS(Abstract)
class MICROSCOPEAPI_API UMicroscopeApiRequest : public UObject {
    GENERATED_BODY()

protected:
    /** Initiates request processing. */
    virtual void ProcessRequest();

    /** Http request complete callback. Clears internal Http request delegates. */
    virtual void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    /** Internal helper used to simplify response validity check. */
    static bool CheckResponse(const FHttpResponsePtr Response);

    /** Internal helper to call both blueprint and code delegates. */
    void TriggerDelegates(const bool bSuccessful);

public:
    /** Called to process the request. */
    UFUNCTION(BlueprintCallable)
    void Execute() { ProcessRequest(); }

    /** Internal Http request. */
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    /** Delegate called when the request completes. */
    UPROPERTY(BlueprintAssignable, Category = "Microscope")
    FOnApiRequestComplete OnRequestComplete;

    /** Delegate called when the request completes. */
    FOnCppApiRequestComplete OnCppRequestComplete;
};
