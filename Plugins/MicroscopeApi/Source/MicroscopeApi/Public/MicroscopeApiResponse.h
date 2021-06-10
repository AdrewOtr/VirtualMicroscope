#pragma once
#include "MicroscopeApiRequest.h"

#include "MicroscopeApiResponse.generated.h"

/** Used as a callback for API requests. */
DECLARE_DYNAMIC_DELEGATE_TwoParams(FMicroscopeApiCallDelegate, class UMicroscopeApiRequest*, Request, bool, bWasSuccessful);

/** Generic API response. */
USTRUCT()
struct FMicroscopeApiResponse {
    GENERATED_BODY()

    /** Related API request. */
    UPROPERTY()
    class UMicroscopeApiRequest* Request = nullptr;

    /** Callback the request was called with. */
    UPROPERTY()
    FMicroscopeApiCallDelegate Callback;

    /** Complete delegate handle. */
    FDelegateHandle CompleteDelegateHandle;
};
