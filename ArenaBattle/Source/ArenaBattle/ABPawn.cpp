// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPawn.h"
#include "ABGameInstance.h"

// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Body = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
    RootComponent = Body;
 	
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
    Mesh->SetupAttachment(Body);
 	
    Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
    Arrow->SetupAttachment(Body);
 	
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(Body);
 	
    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);
 	
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

    Body->SetCapsuleSize(34.0f, 88.0f);
    Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Warrior(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
    Mesh->SetSkeletalMesh(SK_Warrior.Object);
    SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
    SpringArm->TargetArmLength = 650.0f;
 	
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

    MaxHP = 100.0f;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, (float)_I32_MAX, FColor::Blue, TEXT("AABPawn BeginPlay - Screen"));

	Super::BeginPlay();
	CurrentHP = MaxHP;

	// 비동기 방식 리소스 로딩
	NewIndex = FMath::RandRange(0, CharacterAssets.Num() - 1);
	UABGameInstance* ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	if (ABGameInstance)
	{
		ABGameInstance->AssetLoader.RequestAsyncLoad(CharacterAssets[NewIndex], FStreamableDelegate::CreateUObject(this, &AABPawn::CharacterMeshDeferred));
	}

	// 동기방식 리소스 로딩
	// int32 NewIndex = FMath::RandRange(0, CharacterAssets.Num() - 1);
	// UABGameInstance* ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	// if (ABGameInstance)
	// {
	// 	TAssetPtr<USkeletalMesh> NewCharacter = Cast<USkeletalMesh>(ABGameInstance->AssetLoader.SynchronousLoad(CharacterAssets[NewIndex]));
	// 	if (NewCharacter)
	// 	{
	// 		Mesh->SetSkeletalMesh(NewCharacter.Get());
	// 	}
	// }
}

void AABPawn::CharacterMeshDeferred()
{
	UE_LOG(LogClass, Warning, TEXT("CharacterMeshDeferred Call!!"));
	TAssetPtr<USkeletalMesh> NewCharacter(CharacterAssets[NewIndex]);
	if (NewCharacter)
	{
		Mesh->SetSkeletalMesh(NewCharacter.Get());
	}
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector InputVector = FVector(CurrentUpDownVal, CurrentLeftRightVal, 0.0F);
	if (InputVector.SizeSquared() > 0.0F)
	{
		FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(InputVector);
		SetActorRotation(TargetRotation);
		AddMovementInput(GetActorForwardVector());
	}
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("LeftRight", this, &AABPawn::LeftRightInput);
	InputComponent->BindAxis("UpDown", this, &AABPawn::UpDownInput);
}

void AABPawn::UpDownInput(float NewInputVal)
{
	CurrentUpDownVal = NewInputVal;
}

void AABPawn::LeftRightInput(float NewInputVal)
{
	CurrentLeftRightVal = NewInputVal;
}