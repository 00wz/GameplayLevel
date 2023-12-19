// Fill out your copyright notice in the Description page of Project Settings.


#include "StartCallingWidget.h"

void UStartCallingWidget::StartGame()
{
	OnPressStart.ExecuteIfBound();
}
