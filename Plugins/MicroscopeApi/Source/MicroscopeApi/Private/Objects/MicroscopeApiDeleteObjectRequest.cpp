#include "Objects/MicroscopeApiDeleteObjectRequest.h"

#include "MicroscopeApi.h"

void UMicroscopeDeleteObjectRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Delete);
    HttpRequest->SetURL(Api::MakeGetObjectUrl(Id));

    Super::ProcessRequest();
}

void UMicroscopeDeleteObjectRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    TriggerDelegates(true);
}
