#pragma once

#include "MicroscopeApiRequest.h"
#include "MicroscopeApiResponse.h"
#include "MicroscopeDepartment.h"
#include "MicroscopeObject.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "MicroscopeApiService.generated.h"


UCLASS()
class MICROSCOPEAPI_API UMicroscopeApiService final : public UGameInstanceSubsystem {
	GENERATED_BODY()

	/** Internal API request callback. */
	void OnApiRequestComplete(class UMicroscopeApiRequest* Request, bool bWasSuccessful);

public:
	/** Storage for pending requests and matching responses. */
	UPROPERTY()
	TMap<class UMicroscopeApiRequest*, FMicroscopeApiResponse> RequestMap;

#pragma region Objects
	UFUNCTION(BlueprintCallable)
	void GetObject(const FString Id, const FMicroscopeApiCallDelegate& Callback);

	UFUNCTION(BlueprintCallable)
	FMicroscopeObject GetObjectResponse(UMicroscopeApiRequest* RequestObject);

	UFUNCTION(BlueprintCallable)
	void GetObjects(const FMicroscopeApiCallDelegate& Callback);

	UFUNCTION(BlueprintCallable)
	TArray<FMicroscopeObject> GetObjectsResponse(UMicroscopeApiRequest* RequestObject);

	UFUNCTION(BlueprintCallable)
	void PostObject(const FString Title, const FString DepartmentId, const FMicroscopeApiCallDelegate& Callback);

	UFUNCTION(BlueprintCallable)
	FMicroscopeObject PostObjectResponse(UMicroscopeApiRequest* RequestObject);

	UFUNCTION(BlueprintCallable)
	void DeleteObject(const FString Id, const FMicroscopeApiCallDelegate& Callback);
#pragma endregion

#pragma region Department
	UFUNCTION(BlueprintCallable)
	void GetDepartment(const FString Id, const FMicroscopeApiCallDelegate& Callback);

	UFUNCTION(BlueprintCallable)
	FMicroscopeDepartment GetDepartmentResponse(UMicroscopeApiRequest* RequestObject);

	UFUNCTION(BlueprintCallable)
	void GetDepartmentObjects(const FString Id, const FMicroscopeApiCallDelegate& Callback);

	UFUNCTION(BlueprintCallable)
	TArray<FMicroscopeObject> GetDepartmentObjectsResponse(UMicroscopeApiRequest* RequestObject);

	UFUNCTION(BlueprintCallable)
	void GetDepartments(const FMicroscopeApiCallDelegate& Callback);

	UFUNCTION(BlueprintCallable)
	TArray<FMicroscopeDepartment> GetDepartmentsResponse(UMicroscopeApiRequest* RequestObject);

	UFUNCTION(BlueprintCallable)
	void PostDepartment(const FString Title, const FMicroscopeApiCallDelegate& Callback);

	UFUNCTION(BlueprintCallable)
	FMicroscopeDepartment PostDepartmentResponse(UMicroscopeApiRequest* RequestObject);

	UFUNCTION(BlueprintCallable)
	void DeleteDepartment(const FString Id, const FMicroscopeApiCallDelegate& Callback);
#pragma endregion
};
