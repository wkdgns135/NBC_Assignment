// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MyIDPluginBPLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MYIDPLUGIN_MyIDPluginBPLibrary_generated_h
#error "MyIDPluginBPLibrary.generated.h already included, missing '#pragma once' in MyIDPluginBPLibrary.h"
#endif
#define MYIDPLUGIN_MyIDPluginBPLibrary_generated_h

#define FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h_28_RPC_WRAPPERS \
	DECLARE_FUNCTION(execGetUserName); \
	DECLARE_FUNCTION(execSetUserName); \
	DECLARE_FUNCTION(execMyIDPluginSampleFunction);


#define FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h_28_INCLASS \
private: \
	static void StaticRegisterNativesUMyIDPluginBPLibrary(); \
	friend struct Z_Construct_UClass_UMyIDPluginBPLibrary_Statics; \
public: \
	DECLARE_CLASS(UMyIDPluginBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MyIDPlugin"), NO_API) \
	DECLARE_SERIALIZER(UMyIDPluginBPLibrary)


#define FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h_28_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyIDPluginBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyIDPluginBPLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyIDPluginBPLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyIDPluginBPLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UMyIDPluginBPLibrary(UMyIDPluginBPLibrary&&); \
	UMyIDPluginBPLibrary(const UMyIDPluginBPLibrary&); \
public: \
	NO_API virtual ~UMyIDPluginBPLibrary();


#define FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h_25_PROLOG
#define FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h_28_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h_28_RPC_WRAPPERS \
	FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h_28_INCLASS \
	FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h_28_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MYIDPLUGIN_API UClass* StaticClass<class UMyIDPluginBPLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NBC_NBC_Assignment_Build_MyIDPlugin_HostProject_Plugins_MyIDPlugin_Source_MyIDPlugin_Public_MyIDPluginBPLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
