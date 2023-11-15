// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MergeTownPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MERGEHOUSES_API AMergeTownPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	// Store current game scores
	UPROPERTY()
		int32 PlayerScore = 0;

	UPROPERTY()
		int32 StoredScores = 0;

	UFUNCTION()
		void PrintScoresToScreen();

	UPROPERTY()
		int32 HighScore;

	class UMainWidgetBase* ScoreWidget;
	class UGameOverWidgetBase* GameOverWidget;
	class UMainMenuWidgetBase* MainMenuWidget;
	class UHowToPlayWidget* HowToPlayWidget;
	class UInformationUserWidgetBase* AuthorsWidget;

	UFUNCTION()
		void SaveHighScore();

	UFUNCTION()
		void LoadHighScore();

	bool bIsSoundOn = true;
	bool bIsMusicOn = true;

public:
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraBlendSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TSubclassOf<UUserWidget> HowToPlayWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		TSubclassOf<UInformationUserWidgetBase> AuthorsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* MoveSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* MergeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundCue* ClickSound;

	AMergeTownPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void SetMenuCameraActive();
	void SetBoardCameraActive();

	// Get player's current scores
	int32 GetScore();
	
	// Add scores to player's current scores
	void AddScores(int32 PointsToAdd);

	// Set value to player's current scores
	void SetScores(int32 PointToSet);

	// Reset player's current scores
	void ResetScores();

	void StoreScores(int32 ScoresToStore);

	void RestoreScores();

	UFUNCTION(BlueprintCallable, Category = UI)
		void ShowGameplayUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HideGameplayUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void ShowGameOverUI(bool bIsHighScore);

	UFUNCTION(BlueprintCallable, Category = UI)
		void HideGameOverUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void ShowMainMenuUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HideMainMenuUI();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void StartGameplay();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void GameOver();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void EndGameplay();

	UFUNCTION(BlueprintCallable, Category = UI)
		void ShowHowToPlayUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HideHowToPlayUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void ShowAuthorsUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		void HideAuthorsUI();

	UFUNCTION(BlueprintCallable, Category = UI)
		bool IsSoundOn();

	UFUNCTION(BlueprintCallable, Category = UI)
		bool IsMusicOn();

	UFUNCTION(BlueprintCallable, Category = UI)
		void SetSoundEnabled(bool bNewValue);

	UFUNCTION(BlueprintCallable, Category = UI)
		void SetMusicEnabled(bool bNewValue);

	UFUNCTION(BlueprintCallable, Category = UI)
		void LoadSoundSetting();

	UFUNCTION(BlueprintCallable, Category = UI)
		void LoadMusicSetting();

	UFUNCTION(BlueprintCallable, Category = "Sound")
		void PlayMoveSound();

	UFUNCTION(BlueprintCallable, Category = "Sound")
		void PlayMergeSound();

	UFUNCTION(BlueprintCallable, Category = "Sound")
		void PlayClickSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
		class USoundCue* BGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
		class USoundCue* GameOverCue;


	// BGM Private Methods
	class UAudioComponent* BGMAudioComponent;
	UFUNCTION(BlueprintCallable, Category = "Sound")
		void SetupBGM();
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
		void PlayBGM();
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
		void StopBGM();
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
		void LowerBGMVolume();
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
		void RestoreBGMVolume();

	class UAudioComponent* GameOverAudioComponent;
	UFUNCTION(BlueprintCallable, Category = "Sound")
		void SetupGameOverMusic();
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
		void PlayGameOverMusic();
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
		void StopGameOverMusic();

	UFUNCTION(BlueprintCallable, Category = "Saving")
		void SaveUndoState(bool bNewState);

	UFUNCTION(BlueprintCallable, Category = "Saving")
		void SaveRemoveState(bool bNewState);

	UFUNCTION(BlueprintCallable, Category = "Saving")
		bool LoadUndoState();

	UFUNCTION(BlueprintCallable, Category = "Saving")
		bool LoadRemoveState();
};
