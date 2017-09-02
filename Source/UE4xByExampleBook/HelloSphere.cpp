// Fill out your copyright notice in the Description page of Project Settings.

#include "HelloSphere.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AHelloSphere::AHelloSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if(Sphere.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(Sphere.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01'"));
	if (Material.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, Material.Object);
	}

	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(100.f);

	CharText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Char Text"));
	CharText->SetupAttachment(RootComponent);
	CharText->SetHorizontalAlignment(EHTA_Center);
	CharText->SetTextRenderColor(FColor::Blue);
	CharText->SetRelativeLocation(FVector(0, 0, 100));

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Engine/Tutorial/SubEditors/TutorialAssets/TutorialParticleSystem.TutorialParticleSystem'"));
	if (ParticleSystem.Succeeded())
	{
		ParticleSystemComponent->SetTemplate(ParticleSystem.Object);
	}


}

// Called when the game starts or when spawned
void AHelloSphere::BeginPlay()
{
	Super::BeginPlay();

	// OnComponentBeginOverlap
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHelloSphere::OnOverlapBegin);
	// OnComponentEndOverlap
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AHelloSphere::OnOverlapEnd);
}

void AHelloSphere::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (APawn* Pawn = Cast<APawn>(OtherActor))
		{
			CharText->SetText(FText::FromString("NEWText"));
		}
	}
}

void AHelloSphere::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (APawn* Pawn = Cast<APawn>(OtherActor))
		{
			CharText->SetText(FText::FromString("Text"));
		}
	}
}

// Called every frame
void AHelloSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

