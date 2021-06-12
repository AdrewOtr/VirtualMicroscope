#include "Departments/MicroscopeApiGetDepartmentObjectsRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"

void UMicroscopeGetDepartmentObjectsRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Get);
    HttpRequest->SetURL(Api::MakeGetDepartmentObjectsUrl(Id));

    Super::ProcessRequest();
}

void UMicroscopeGetDepartmentObjectsRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();

    TriggerDelegates(true);
}
