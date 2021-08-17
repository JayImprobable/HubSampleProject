// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponStation.h"
#include "HitscanArea.h"
#include "NetContentCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHitscanShootDelegate, FVector, Location, FRotator, Rotation, float, time);
DECLARE_DELEGATE_RetVal(float, FFloatReturnDelegate);

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ANetContentCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Pawn mesh: 3st person view (Fullbody) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh3P;


	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* L_MotionController;

	

protected: 
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* VR_Gun;

	FHitscanShootDelegate OnShoot;

	FFloatReturnDelegate GetTimeWhenShoot;

	uint8 bInsideHitscanVolume:1;

public:
	ANetContentCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ANetContentProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	UFUNCTION()
	void FireLocal(FVector Location, FRotator Direction);

	UFUNCTION(Server, Reliable)
	void Fire(FVector Location, FRotator Direction);

	UFUNCTION(NetMulticast, Reliable)
	void FireOthers(FVector Location, FRotator Direction);

	UFUNCTION()
	void ShootBullet(FVector Location, FRotator Direction);

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;


protected: 
	UPROPERTY(ReplicatedUsing= OnRep_CurrentWeapon, BlueprintReadOnly)
	TEnumAsByte<EWeaponType> currentWeapon;

public: 
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SwitchWeapon(EWeaponType newType);
	virtual void SwitchWeapon_Implementation(EWeaponType newType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateWeaponVisuals();
	virtual void UpdateWeaponVisuals_Implementation();

	UFUNCTION()
	void OnRep_CurrentWeapon();

	UFUNCTION()
	void EnterHitscanArea(AHitscanArea* area);

	UFUNCTION()
	void LeaveHitscanArea();

protected:

	UFUNCTION(Server, Reliable)
	void FireHitscan(FVector SpawnLocation, FRotator SpawnDirection, float Time);
	virtual void FireHitscan_Implementation(FVector SpawnLocation, FRotator SpawnDirection, float Time);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

