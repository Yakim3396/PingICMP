//Copyright(c) 2021 Dmitry Yakimenko

#include "PingICMPObject.h"
#include "Icmp.h"

UPingICMPObject::UPingICMPObject()
{

}

UPingICMPObject::~UPingICMPObject()
{
	IcmpEchoResult.Unbind();
	OnPingCompleted.Clear();
}

void UPingICMPObject::Ping(FString IP)
{
	IcmpEchoResult.BindUObject(this, &UPingICMPObject::OnServerCheckFinished);
	FIcmp::IcmpEcho(IP, 1.f, IcmpEchoResult);
}

void UPingICMPObject::OnServerCheckFinished(FIcmpEchoResult Result)
{
	IcmpEchoResult.Unbind();

	FString PingStatus = "Failed";
	switch (Result.Status)
	{
	case EIcmpResponseStatus::Success:
		PingStatus = "Success";
		break;
	case EIcmpResponseStatus::Timeout:
		PingStatus = "Timeout";
		break;
	case EIcmpResponseStatus::Unreachable:
		PingStatus = "Unreachable";
		break;
	case EIcmpResponseStatus::Unresolvable:
		PingStatus = "Unresolvable";
		break;
	case EIcmpResponseStatus::InternalError:
		PingStatus = "Internal Error";
		break;
	default:
		PingStatus = "Unknown Error";
		break;
	}

	if (OnPingCompleted.IsBound())
	{
		ICMPResult.Status = PingStatus;// StaticEnum<EIcmpResponseStatus>()->GetValueAsString(Result.Status);
		ICMPResult.ResolvedAddress = Result.ResolvedAddress;
		ICMPResult.ReplyFrom = Result.ReplyFrom;
		ICMPResult.Time = Result.Time;
		OnPingCompleted.Broadcast(ICMPResult);
	}

	UE_LOG(LogTemp, Display, TEXT("Ping Result is %s"), *PingStatus);
}