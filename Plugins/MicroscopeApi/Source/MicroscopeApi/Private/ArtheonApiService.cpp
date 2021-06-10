#include "MicroscopeApiGetObjectsRequest.h"

#include "MicroscopeApi/Public/MicroscopeApiService.h"


void UMicroscopeApiService::OnApiRequestComplete(UMicroscopeApiRequest* Request, bool bWasSuccessful) {
	if (!RequestMap.Contains(Request)) {
		return;
	}

	const auto Response = RequestMap.Find(Request);
	Request->OnCppRequestComplete.Remove(Response->CompleteDelegateHandle);

	Response->Callback.ExecuteIfBound(Request, bWasSuccessful);
	Response->Request = nullptr;
	RequestMap.Remove(Request);
}

void UMicroscopeApiService::GetObjects(const FString Id, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeGetObjectsRequest* Request = NewObject<UMicroscopeGetObjectsRequest>(this);
	Request->Id = Id;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}
