#include "Departments/MicroscopeApiGetDepartmentRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"

void UMicroscopeGetDepartmentRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Get);
    HttpRequest->SetURL(Api::MakeGetDepartmentUrl(Id));

    Super::ProcessRequest();
}

void UMicroscopeGetDepartmentRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();

    TriggerDelegates(true);
}
