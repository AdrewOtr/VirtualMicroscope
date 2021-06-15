#include "MicroscopeApiService.h"

#include "Departments/MicroscopeApiDeleteDepartmentRequest.h"
#include "Departments/MicroscopeApiGetDepartmentObjectsRequest.h"
#include "Departments/MicroscopeApiGetDepartmentRequest.h"
#include "Departments/MicroscopeApiGetDepartmentsRequest.h"
#include "Departments/MicroscopeApiPostDepartmentRequest.h"
#include "Objects/MicroscopeApiDeleteObjectRequest.h"
#include "Objects/MicroscopeApiGetObjectFilesRequest.h"
#include "Objects/MicroscopeApiGetObjectRequest.h"
#include "Objects/MicroscopeApiGetObjectsRequest.h"
#include "Objects/MicroscopeApiPostObjectRequest.h"

#include "HttpModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Engine/Texture2DDynamic.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


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

void UMicroscopeApiService::DownloadTexture(const FString Url) {
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));;
    TSharedPtr<IImageWrapper> ImageWrappers[3] =
    {
        ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG),
        ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG)
    };

    TArray64<uint8>* RawData = new TArray64<uint8>();

    const FString FilePathG = FPaths::ProjectDir() + TEXT("cache/") + Url;

    // Try to load file from the cache.
    TArray<uint8>* LoadedData = new TArray<uint8>;
    if (FFileHelper::LoadFileToArray(*LoadedData, *FilePathG)) {
        // Find a matching image wrapper for the image data.
        for (auto ImageWrapper : ImageWrappers) {
            if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(LoadedData->GetData(), LoadedData->Num())) {
                if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, *RawData)) {
                    const auto Width = ImageWrapper->GetWidth();
                    const auto Height = ImageWrapper->GetHeight();
                    Texture = UTexture2D::CreateTransient(Width, Height);
                    // Copy raw bytes to the texture.
                    if (Texture) {

                        Texture->CompressionSettings = TC_Default;
                        Texture->SRGB = true;

                        const auto TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
                        FMemory::Memcpy(TextureData, RawData->GetData(), RawData->Num());
                        Texture->PlatformData->Mips[0].BulkData.Unlock();

                        // Free memory used for temporary storage.
                        delete RawData;
                        Texture->UpdateResource();

                        OnCompleteTexture.Broadcast(Url, Texture);
                        UE_LOG(LogTemp, Log, TEXT("Loaded cache"));
                        return;
                    }
                }
            }
        }
    }
}

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

void UMicroscopeApiService::GetObjectFiles(const FString Id, const FMicroscopeApiCallDelegate& Callback) {
	UMicroscopeGetObjectFilesRequest* Request = NewObject<UMicroscopeGetObjectFilesRequest>(this);
	Request->Id = Id;

	FMicroscopeApiResponse Response;
	Response.Request = Request;
	Response.Callback = Callback;
	Response.CompleteDelegateHandle = Request->OnCppRequestComplete.AddUObject(this, &UMicroscopeApiService::OnApiRequestComplete);

	RequestMap.Add(Request, Response);

	Request->Execute();
}

TArray<FMicroscopeFile> UMicroscopeApiService::GetObjectFilesResponse(UMicroscopeApiRequest* RequestObject) {
	const auto CastedObject = Cast<UMicroscopeGetObjectFilesRequest>(RequestObject);
	if(!CastedObject) {
		return TArray<FMicroscopeFile>();
	}
	return CastedObject->Files;
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
