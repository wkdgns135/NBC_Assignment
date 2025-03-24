// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyIDPlugin_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_MyIDPlugin;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_MyIDPlugin()
	{
		if (!Z_Registration_Info_UPackage__Script_MyIDPlugin.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/MyIDPlugin",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xD8943BCE,
				0x9165C5BC,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_MyIDPlugin.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_MyIDPlugin.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_MyIDPlugin(Z_Construct_UPackage__Script_MyIDPlugin, TEXT("/Script/MyIDPlugin"), Z_Registration_Info_UPackage__Script_MyIDPlugin, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xD8943BCE, 0x9165C5BC));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
