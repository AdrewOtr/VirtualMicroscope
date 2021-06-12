#include "Departments/MicroscopeApiDeleteDepartmentRequest.h"

#include "MicroscopeApi.h"

void UMicroscopeDeleteDepartmentRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Delete);
    HttpRequest->SetURL(Api::MakeGetDepartmentUrl(Id));

    Super::ProcessRequest();
}

void UMicroscopeDeleteDepartmentRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    TriggerDelegates(true);
}
