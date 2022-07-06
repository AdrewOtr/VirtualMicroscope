#include "MicroscopeApi/Public/MicroscopeApiRequest.h"

#include "MicroscopeApi/Public/MicroscopeApi.h"
#include "Engine/World.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

/** Each request gets a header with request id which simplifies debugging requests between api and the server. */
static int64 RequestId = -1;

void UMicroscopeApiRequest::ProcessRequest() {
    const auto World = GetWorld();
    if (World == nullptr) {
        UE_LOG(LogMicroscopeApi, Warning, TEXT("Unable to get world"));
        return;
    }

    const auto GameInstance = World->GetGameInstance();
    if (GameInstance == nullptr) {
        UE_LOG(LogMicroscopeApi, Warning, TEXT("Unable to get game instance"));
        return;
    }

    // HttpRequest->SetHeader(Api::Headers::Referer, GMicroscope_Build_Version);
    HttpRequest->SetHeader(Api::Headers::RequestId, FString::Printf(TEXT("%lld"), ++RequestId));

    UE_LOG(LogMicroscopeApi, Warning, TEXT("Sending request {%s} {#%lld} from client to {%s}."), *GetClass()->GetName(), RequestId, *HttpRequest->GetURL());

    if (HttpRequest->GetHeader(Api::Headers::ContentType).IsEmpty()) {
        HttpRequest->SetHeader(Api::Headers::ContentType, Api::ContentTypes::ApplicationJson);
    }

    //! Bind the parent class virtual function, required overriding function will be called automatically. 
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UMicroscopeApiRequest::OnProcessRequestComplete);

    const bool bStarted = HttpRequest->ProcessRequest();

    if (!bStarted) {
        OnRequestComplete.Broadcast(this, false);
        OnCppRequestComplete.Broadcast(this, false);
    }
}

void UMicroscopeApiRequest::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
    UE_LOG(LogMicroscopeApi, Verbose, TEXT("Received response {%s} {#%s} from {%s}."), *GetClass()->GetName(), *Request->GetHeader(Api::Headers::RequestId), *HttpRequest->GetURL());
    HttpRequest->OnRequestProgress().Unbind();
    HttpRequest->OnProcessRequestComplete().Unbind();
}

bool UMicroscopeApiRequest::CheckResponse(const FHttpResponsePtr Response) {
    if (!Response.IsValid()) {
        return false;
    }

    if (!EHttpResponseCodes::IsOk(Response->GetResponseCode())) {
        UE_LOG(LogMicroscopeApi, Warning, TEXT("Received response has bad code:{%d} in {%s}"), Response->GetResponseCode(), *Response->GetURL());
        return false;
    }

    return true;
}

void UMicroscopeApiRequest::TriggerDelegates(const bool bSuccessful) {
    OnRequestComplete.Broadcast(this, bSuccessful);
    OnCppRequestComplete.Broadcast(this, bSuccessful);
}
