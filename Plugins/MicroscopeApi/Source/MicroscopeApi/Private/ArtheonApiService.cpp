#include "MicroscopeApiService.h"

#include "Departments/MicroscopeApiDeleteDepartmentRequest.h"
#include "Departments/MicroscopeApiGetDepartmentObjectsRequest.h"
#include "Departments/MicroscopeApiGetDepartmentRequest.h"
#include "Departments/MicroscopeApiGetDepartmentsRequest.h"
#include "Departments/MicroscopeApiPostDepartmentRequest.h"
#include "Objects/MicroscopeApiDeleteObjectRequest.h"
#include "Objects/MicroscopeApiGetObjectRequest.h"
#include "Objects/MicroscopeApiGetObjectsRequest.h"
#include "Objects/MicroscopeApiPostObjectRequest.h"


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

#pragma region Objects

void UMicroscopeApiService::GetObject(const FString Id, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeGetObjectRequest* Request = NewObject<UMicroscopeGetObjectRequest>(this);
	Request->Id = Id;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

FMicroscopeObject UMicroscopeApiService::GetObjectResponse(UMicroscopeApiRequest* RequestObject) {
	const auto CastedObject = Cast<UMicroscopeGetObjectRequest>(RequestObject);
	if(!CastedObject) {
		return FMicroscopeObject();
	}
	return CastedObject->Object;
}

void UMicroscopeApiService::GetObjects(const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeGetObjectsRequest* Request = NewObject<UMicroscopeGetObjectsRequest>(this);

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

TArray<FMicroscopeObject> UMicroscopeApiService::GetObjectsResponse(UMicroscopeApiRequest* RequestObject) {
	const auto CastedObject = Cast<UMicroscopeGetObjectsRequest>(RequestObject);
	if(!CastedObject) {
		return TArray<FMicroscopeObject>();
	}
	return CastedObject->Objects;
}

void UMicroscopeApiService::PostObject(const FString Title, const FString DepartmentId, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopePostObjectRequest* Request = NewObject<UMicroscopePostObjectRequest>(this);
	Request->Title = Title;
	Request->DepartmentId = DepartmentId;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

FMicroscopeObject UMicroscopeApiService::PostObjectResponse(UMicroscopeApiRequest* RequestObject) {
	const auto CastedObject = Cast<UMicroscopePostObjectRequest>(RequestObject);
	if(!CastedObject) {
		return FMicroscopeObject();
	}
	return CastedObject->Object;
}

void UMicroscopeApiService::DeleteObject(const FString Id, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeDeleteObjectRequest* Request = NewObject<UMicroscopeDeleteObjectRequest>(this);
	Request->Id = Id;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

#pragma endregion

#pragma region Departments

void UMicroscopeApiService::GetDepartment(const FString Id, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeGetDepartmentRequest* Request = NewObject<UMicroscopeGetDepartmentRequest>(this);
	Request->Id = Id;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

FMicroscopeDepartment UMicroscopeApiService::GetDepartmentResponse(UMicroscopeApiRequest* RequestObject) {
	const auto CastedObject = Cast<UMicroscopeGetDepartmentRequest>(RequestObject);
	if(!CastedObject) {
		return FMicroscopeDepartment();
	}
	return CastedObject->Department;
}

void UMicroscopeApiService::GetDepartmentObjects(const FString Id, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeGetDepartmentObjectsRequest* Request = NewObject<UMicroscopeGetDepartmentObjectsRequest>(this);
	Request->Id = Id;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

TArray<FMicroscopeObject> UMicroscopeApiService::GetDepartmentObjectsResponse(UMicroscopeApiRequest* RequestObject) {
	const auto CastedObject = Cast<UMicroscopeGetDepartmentObjectsRequest>(RequestObject);
	if(!CastedObject) {
		return TArray<FMicroscopeObject>();
	}
	return CastedObject->Objects;
}

void UMicroscopeApiService::GetDepartments(const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeGetDepartmentsRequest* Request = NewObject<UMicroscopeGetDepartmentsRequest>(this);

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

TArray<FMicroscopeDepartment> UMicroscopeApiService::GetDepartmentsResponse(UMicroscopeApiRequest* RequestObject) {
	const auto CastedObject = Cast<UMicroscopeGetDepartmentsRequest>(RequestObject);
	if(!CastedObject) {
		return TArray<FMicroscopeDepartment>();
	}
	return CastedObject->Departments;
}

void UMicroscopeApiService::PostDepartment(const FString Title, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopePostDepartmentRequest* Request = NewObject<UMicroscopePostDepartmentRequest>(this);
	Request->Title = Title;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

FMicroscopeDepartment UMicroscopeApiService::PostDepartmentResponse(UMicroscopeApiRequest* RequestObject) {
	const auto CastedObject = Cast<UMicroscopePostDepartmentRequest>(RequestObject);
	if(!CastedObject) {
		return FMicroscopeDepartment();
	}
	return CastedObject->Department;
}

void UMicroscopeApiService::DeleteDepartment(const FString Id, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeDeleteDepartmentRequest* Request = NewObject<UMicroscopeDeleteDepartmentRequest>(this);
	Request->Id = Id;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

#pragma endregion
