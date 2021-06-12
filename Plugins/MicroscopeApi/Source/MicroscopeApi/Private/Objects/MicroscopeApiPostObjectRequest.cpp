#include "Objects/MicroscopeApiPostObjectRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UMicroscopePostObjectRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Post);
    HttpRequest->SetURL(Api::MakePostObjectUrl(DepartmentId));

    Super::ProcessRequest();
}

void UMicroscopePostObjectRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();


    TriggerDelegates(true);
}
