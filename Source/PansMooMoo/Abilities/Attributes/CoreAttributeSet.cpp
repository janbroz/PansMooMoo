// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreAttributeSet.h"
#include "PansMooMoo.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Player/Hero.h"

UCoreAttributeSet::UCoreAttributeSet()
	: Health(10.f)
	, MaxHealth(10.f)
	, MovementSpeed(1.f)
	, Strength(1.f)
	, Intellect(1.f)
	, Agility(1.f)
	, Stamina(1.f)
{
}

void UCoreAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCoreAttributeSet, Health);
	DOREPLIFETIME(UCoreAttributeSet, MaxHealth);
	DOREPLIFETIME(UCoreAttributeSet, HealthPerSecond);
	DOREPLIFETIME(UCoreAttributeSet, MovementSpeed);
	DOREPLIFETIME(UCoreAttributeSet, Strength);
	DOREPLIFETIME(UCoreAttributeSet, Stamina);
	DOREPLIFETIME(UCoreAttributeSet, Agility);
	DOREPLIFETIME(UCoreAttributeSet, Intellect);
	DOREPLIFETIME(UCoreAttributeSet, AttackDamage);
	DOREPLIFETIME(UCoreAttributeSet, SpellDamage);
	DOREPLIFETIME(UCoreAttributeSet, Armor);
	DOREPLIFETIME(UCoreAttributeSet, Fortitude);
}

void UCoreAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Maintain the current max / val percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;
		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}

}

void UCoreAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UCoreAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	AHero* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<AHero>(TargetActor);
	}


	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp the health value to avoid negative values.
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetBaseValue()));
		if (TargetCharacter)
		{
			//TargetCharacter->HandleHealthChanged(0.f, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		if (TargetCharacter)
		{
			//TargetCharacter->HandleHealthChanged(0.f, SourceTags);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not a valid target to do this"));

		}
		
	}
}

void UCoreAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCoreAttributeSet, Health);
}

void UCoreAttributeSet::OnRep_MaxHealth()
{
}

void UCoreAttributeSet::OnRep_HealthPerSecond()
{
}

void UCoreAttributeSet::OnRep_MovementSpeed()
{}

void UCoreAttributeSet::OnRep_Strength()
{}

void UCoreAttributeSet::OnRep_Agility()
{}

void UCoreAttributeSet::OnRep_Intellect()
{}

void UCoreAttributeSet::OnRep_Stamina()
{}

void UCoreAttributeSet::OnRep_AttackDamage()
{
}

void UCoreAttributeSet::OnRep_SpellDamage()
{
}

void UCoreAttributeSet::OnRep_Armor()
{
}

void UCoreAttributeSet::OnRep_Fortitude()
{
}