// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GAMEPROJECT_GameProjectCharacter_generated_h
#error "GameProjectCharacter.generated.h already included, missing '#pragma once' in GameProjectCharacter.h"
#endif
#define GAMEPROJECT_GameProjectCharacter_generated_h

#define GameProject_Source_GameProject_GameProjectCharacter_h_12_SPARSE_DATA
#define GameProject_Source_GameProject_GameProjectCharacter_h_12_RPC_WRAPPERS
#define GameProject_Source_GameProject_GameProjectCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define GameProject_Source_GameProject_GameProjectCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGameProjectCharacter(); \
	friend struct Z_Construct_UClass_AGameProjectCharacter_Statics; \
public: \
	DECLARE_CLASS(AGameProjectCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GameProject"), NO_API) \
	DECLARE_SERIALIZER(AGameProjectCharacter)


#define GameProject_Source_GameProject_GameProjectCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAGameProjectCharacter(); \
	friend struct Z_Construct_UClass_AGameProjectCharacter_Statics; \
public: \
	DECLARE_CLASS(AGameProjectCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GameProject"), NO_API) \
	DECLARE_SERIALIZER(AGameProjectCharacter)


#define GameProject_Source_GameProject_GameProjectCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AGameProjectCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AGameProjectCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGameProjectCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGameProjectCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGameProjectCharacter(AGameProjectCharacter&&); \
	NO_API AGameProjectCharacter(const AGameProjectCharacter&); \
public:


#define GameProject_Source_GameProject_GameProjectCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGameProjectCharacter(AGameProjectCharacter&&); \
	NO_API AGameProjectCharacter(const AGameProjectCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGameProjectCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGameProjectCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGameProjectCharacter)


#define GameProject_Source_GameProject_GameProjectCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AGameProjectCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__FollowCamera() { return STRUCT_OFFSET(AGameProjectCharacter, FollowCamera); }


#define GameProject_Source_GameProject_GameProjectCharacter_h_9_PROLOG
#define GameProject_Source_GameProject_GameProjectCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_SPARSE_DATA \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_RPC_WRAPPERS \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_INCLASS \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GameProject_Source_GameProject_GameProjectCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_SPARSE_DATA \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_INCLASS_NO_PURE_DECLS \
	GameProject_Source_GameProject_GameProjectCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAMEPROJECT_API UClass* StaticClass<class AGameProjectCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GameProject_Source_GameProject_GameProjectCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
