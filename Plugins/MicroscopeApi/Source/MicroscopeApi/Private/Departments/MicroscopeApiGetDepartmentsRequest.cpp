#include "Departments/MicroscopeApiGetDepartmentsRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"

void UMicroscopeGetDepartmentsRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Get);
    HttpRequest->SetURL(Api::MakeGetDepartmentsUrl());

    Super::ProcessRequest();
}

void UMicroscopeGetDepartmentsRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();

    TriggerDelegates(true);
}
