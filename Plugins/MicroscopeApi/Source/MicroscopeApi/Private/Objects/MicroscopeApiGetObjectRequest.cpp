#include "Objects/MicroscopeApiGetObjectRequest.h"

#include "MicroscopeApi.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UMicroscopeGetObjectRequest::ProcessRequest() {
    HttpRequest->SetVerb(Api::HttpMethods::Get);
    HttpRequest->SetURL(Api::MakeGetObjectUrl(Id));

    Super::ProcessRequest();
}

void UMicroscopeGetObjectRequest::OnProcessRequestComplete(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful) {
    Super::OnProcessRequestComplete(Request, Response, bWasSuccessful);

    if(!CheckResponse(Response)) {
        TriggerDelegates(false);
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();


    TriggerDelegates(true);
}
