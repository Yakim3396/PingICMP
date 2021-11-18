//Copyright(c) 2021 Dmitry Yakimenko

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PingICMPObject.generated.h"

struct FIcmpEchoResult;
struct FIcmpTarget;

USTRUCT(BlueprintType)
struct PINGICMP_API FPingICMPResult
{
	GENERATED_USTRUCT_BODY()

	/** Status of the final response */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PingICMP")
		FString Status;
	/** Addressed resolved by GetHostName */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PingICMP")
		FString ResolvedAddress;
	/** Reply received from this address */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PingICMP")
		FString ReplyFrom;
	/** Total round trip time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PingICMP")
		float Time;
};

DECLARE_DELEGATE_OneParam(FIcmpEchoResultDelegate, FIcmpEchoResult Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPingICMPDelegate, FPingICMPResult, Result);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PINGICMP_API UPingICMPObject : public UObject
{
	GENERATED_BODY()
public:

	UPingICMPObject();
	~UPingICMPObject();

	UPROPERTY(BlueprintAssignable)
		FPingICMPDelegate OnPingCompleted;

	UFUNCTION(BlueprintCallable)
		void Ping(FString IP);

private:

		FIcmpEchoResultDelegate IcmpEchoResult;

		void OnServerCheckFinished(FIcmpEchoResult Result);
		
		FPingICMPResult ICMPResult;
};
