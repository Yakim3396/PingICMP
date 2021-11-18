//Copyright(c) 2021 Dmitry Yakimenko

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FPingICMPModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
