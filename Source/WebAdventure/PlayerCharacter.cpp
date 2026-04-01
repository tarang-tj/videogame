#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnemyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HealthComponent.h"
#include "Interactable.h"
#include "ProgressionComponent.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set sensible defaults
	WalkSpeed = 500.f;
	SprintSpeed = 800.f;
	bIsSprinting = false;
	CollectibleCount = 0;
	MeleeDamage = 25.f;
	InteractionRange = 350.f;

	// Configure character rotation – orient to movement by default
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	// Create camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	ProgressionComponent = CreateDefaultSubobject<UProgressionComponent>(TEXT("ProgressionComponent"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Ensure we start at walk speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis mappings – set up in Project Settings → Input
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);

	// Action mappings
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &APlayerCharacter::StopJump);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerCharacter::StopSprint);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerCharacter::TryInteract);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &APlayerCharacter::TryAttack);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator ControlRot = Controller->GetControlRotation();
		const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		const FRotator ControlRot = Controller->GetControlRotation();
		const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void APlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::StartSprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::AddCollectibles(int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}

	CollectibleCount += Amount;
	if (ProgressionComponent)
	{
		ProgressionComponent->AddCurrency(Amount);
		ProgressionComponent->AddExperience(Amount * 10);
	}
}

void APlayerCharacter::TryInteract()
{
	if (!FollowCamera || !GetWorld())
	{
		return;
	}

	const FVector Start = FollowCamera->GetComponentLocation();
	const FVector End = Start + FollowCamera->GetForwardVector() * InteractionRange;

	FHitResult Hit;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(PlayerInteract), false, this);
	Params.AddIgnoredActor(this);

	if (!GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		return;
	}

	AActor* HitActor = Hit.GetActor();
	if (!HitActor || !HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		return;
	}

	IInteractable::Execute_Interact(HitActor, this);
}

void APlayerCharacter::TryAttack()
{
	if (!FollowCamera || !GetWorld())
	{
		return;
	}

	const FVector Start = FollowCamera->GetComponentLocation();
	const FVector End = Start + FollowCamera->GetForwardVector() * InteractionRange;

	FHitResult Hit;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(PlayerMelee), false, this);
	Params.AddIgnoredActor(this);

	if (!GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params))
	{
		return;
	}

	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Hit.GetActor()))
	{
		Enemy->ApplyDamage(MeleeDamage);
	}
}

