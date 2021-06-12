#include "Departments/MicroscopeApiPostDepartmentRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"

void UMicroscopePostDepartmentRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Post);
    HttpRequest->SetURL(Api::MakePostDepartmentUrl(Title));

    Super::ProcessRequest();
}

void UMicroscopePostDepartmentRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();

    TriggerDelegates(true);
}
