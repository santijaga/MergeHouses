// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoard.h"
#include "ABoardElement.h"
#include "MergeTownPlayerController.h"
#include "MergeHousesGameModeBase.h"
#include "EngineUtils.h"

// Sets default values
AGameBoard::AGameBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
}

// Function to start gameplay or reset board
void AGameBoard::ResetBoard()
{
    CleanBoard();

    // Comment this after debug
    // Debug Board
    // PopulateDebugBoard(16);
    //

    // Actual Gameplay board
    for (int32 times = 0; times < 2; ++times)
    {
        AddRandomCell();
    }
}

// Function to print the board to the screen
void AGameBoard::PrintBoardToScreen()
{
    // Create a string to store the board representation
    FString BoardString = "2048 Board:\n";

    for (int32 Row = 0; Row < BoardSize; ++Row)
    {
        for (int32 Col = 0; Col < BoardSize; ++Col)
        {
            // Append each cell's value to the string
            BoardString += FString::Printf(TEXT("%d|%d "), Board[Row][Col].Value, Board[Row][Col].ModelID);
        }
        // Add a newline character for the next row
        BoardString += "\n";
    }

    // Display the board on the screen using OnScreenDebugMessages
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, BoardString);
    }
}

void AGameBoard::TurnOnEditMode()
{
    UE_LOG(LogTemp, Warning, TEXT("[AGameBoard] About to turn on edit mode."));
    bIsInEditMode = true;
    UE_LOG(LogTemp, Warning, TEXT("[AGameBoard] Edit mode ON."));
}

void AGameBoard::TurnOffEditMode()
{
    UE_LOG(LogTemp, Warning, TEXT("[AGameBoard] About to turn off edit mode."));
    bIsInEditMode = false;
    UE_LOG(LogTemp, Warning, TEXT("[AGameBoard] Edit mode OFF."));
}

void AGameBoard::RemoveElement(int ID)
{
    for (int x = 0; x < BoardSize; x++)
    {
        for (int y = 0; y < BoardSize; y++)
        {
            if (Board[x][y].ModelID == ID)
            {
                Board[x][y].Value = 0;
                Board[x][y].ModelID = 0;
            }
        }
    }
}

void AGameBoard::PopulateDebugBoard(int32 Elements)
{
    CleanBoard();
    int32 Value = 1;

    for (int x = 0; x < BoardSize; x++)
    {
        for (int y = 0; y < BoardSize; y++)
        {
            if (Value < Elements)
            {
                Board[x][y].Value = Value++;
                Board[x][y].ModelID = ++nextModelID;

                SpawnBoardElement(x, y, Board[x][y].Value, Board[x][y].ModelID);
            }
        }
    }
}

bool AGameBoard::IsGameOver()
{
    for (int x = 0; x < BoardSize; x++)
    {
        for (int y = 0; y < BoardSize; y++)
        {
            if (Board[x][y].Value == 0)  // Assuming 0 represents an empty tile
                return false;

            // Check tile above
            if (x > 0 && Board[x][y].Value == Board[x - 1][y].Value)
                return false;

            // Check tile to the left
            if (y > 0 && Board[x][y].Value == Board[x][y - 1].Value)
                return false;
        }
    }
    return true;
}

// Called every frame
void AGameBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AGameBoard::MakeMove(float x, float y)
{
    bool success = false;

    if (bIsGameOver)
    {
        return false;
    }

    if (IsInEditMode())
    {
        return false;
    }

    TempBoard = Board;
    if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        TempScores = PlayerController->GetScore();
    }

    if (x > 0)
    {
        success = MoveRight();
    }
    
    if (x < 0)
    {
        success = MoveLeft();
    }

    if (y > 0)
    {
        success = MoveUp();
    }

    if (y < 0)
    {
        success = MoveDown();
    }

    if (success)
    {
        success = AddRandomCell();

        PreviousBoard = TempBoard;
        if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
        {
            PlayerController->StoreScores(TempScores);
        }
        bCanUndo = true;
    }

    bIsGameOver = IsGameOver();

    if (bIsGameOver)
    {
        if (AMergeHousesGameModeBase* GameMode = Cast<AMergeHousesGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->GameOver();
        }
    }

    return success;
}

void AGameBoard::CleanBoard()
{
    InitializeBoard();
}

bool AGameBoard::UndoMove()
{
    if (bCanUndo && !IsInEditMode())
    {
        Board = PreviousBoard;

        UWorld* World = GetWorld();  // Assuming this is being called from within an actor or actor component.
        if (World)
        {
            for (TActorIterator<AABoardElement> It(World); It; ++It)
            {
                AABoardElement* BoardElement = *It;
                if (BoardElement)
                {
                    BoardElement->Destroy();
                }
            }
        }

        for (int x = 0; x < BoardSize; x++)
        {
            for (int y = 0; y < BoardSize; y++)
            {
                Board[x][y].ModelID = ++nextModelID;

                if (Board[x][y].Value > 0)
                {
                    SpawnBoardElement(x, y, Board[x][y].Value, Board[x][y].ModelID);
                }
            }
        }

        if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
        {
            PlayerController->RestoreScores();
        }
        bCanUndo = false;
        return true;
    }

    return false;
}

bool AGameBoard::GetCanUndoMove()
{
    return bCanUndo;
}

bool AGameBoard::IsInEditMode()
{
    return bIsInEditMode;
}

// Function to initialize the game board with zeros
void AGameBoard::InitializeBoard()
{
    Board.Empty();
    Board.SetNum(BoardSize);

    for (int32 Row = 0; Row < BoardSize; ++Row)
    {
        Board[Row].Init(FBoardCell(), BoardSize);  // Use FBoardCell() as the default value
    }

    if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        PlayerController->ResetScores();
    }

    bIsGameOver = false;
    TurnOffEditMode();
}

// Function to generate a random position (row, col) for a new cell
FVector2D AGameBoard::GenerateRandomPosition()
{
    TArray<FVector2D> EmptyCells;

    for (int32 Row = 0; Row < BoardSize; ++Row)
    {
        for (int32 Col = 0; Col < BoardSize; ++Col)
        {
            if (Board[Row][Col].Value == 0)
            {
                EmptyCells.Add(FVector2D(Row, Col));
            }
        }
    }

    if (EmptyCells.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, EmptyCells.Num() - 1);
        return EmptyCells[RandomIndex];
    }

    return FVector2D(-1, -1); // No empty cells
}

// Function to add a new random cell (either 1 or 2) to the board
bool AGameBoard::AddRandomCell()
{
    bool addedSuccessfully = false;
    FVector2D Position = GenerateRandomPosition();
    if (Position.X != -1 && Position.Y != -1)
    {
        int32 Value = FMath::RandRange(1, 2);
        Board[Position.X][Position.Y].Value = Value;
        Board[Position.X][Position.Y].ModelID = ++nextModelID;

        SpawnBoardElement(Position.X, Position.Y, Board[Position.X][Position.Y].Value, Board[Position.X][Position.Y].ModelID);

        addedSuccessfully = true;
    }

    return addedSuccessfully;
}

// Function to move cells to the left
bool AGameBoard::MoveLeft()
{
    bool Moved = false;

    for (int row = 0; row < BoardSize; ++row) {
        int index = 0;
        for (int col = 0; col < BoardSize; ++col) {
            if (Board[row][col].Value != 0) {
                // Find a matching cell to merge with
                for (int mergeCol = col + 1; mergeCol < BoardSize; ++mergeCol) {
                    if (Board[row][mergeCol].Value != 0) {
                        if (Board[row][col].Value == Board[row][mergeCol].Value) {
                            // Merge cells
                            Board[row][col].Value += 1;
                            Board[row][col].ModelID = Board[row][mergeCol].ModelID;
                            Board[row][mergeCol].Value = 0;
                            Board[row][mergeCol].ModelID = 0;

                            if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
                            {
                                PlayerController->AddScores(Board[row][col].Value);
                            }

                            Moved = true;
                        }
                        break;
                    }
                }
                // Shift cell to the left
                if (index != col) {
                    Board[row][index].Value = Board[row][col].Value;
                    Board[row][index].ModelID = Board[row][col].ModelID;
                    Board[row][col].Value = 0;
                    Board[row][col].ModelID = 0;
                    Moved = true;
                }
                index++;
            }
        }
    }

    return Moved;
}

// Function to move cells to the right
bool AGameBoard::MoveRight()
{
    bool Moved = false;

    for (int row = 0; row < BoardSize; ++row) {
        int index = BoardSize - 1;
        for (int col = BoardSize - 1; col >= 0; --col) {
            if (Board[row][col].Value != 0) {
                // Find a matching cell to merge with
                for (int mergeCol = col - 1; mergeCol >= 0; --mergeCol) {
                    if (Board[row][mergeCol].Value != 0) {
                        if (Board[row][col].Value == Board[row][mergeCol].Value) {
                            // Merge cells
                            Board[row][col].Value += 1;
                            Board[row][col].ModelID = Board[row][mergeCol].ModelID;
                            Board[row][mergeCol].Value = 0;
                            Board[row][mergeCol].ModelID = 0;

                            if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
                            {
                                PlayerController->AddScores(Board[row][col].Value);
                            }

                            Moved = true;
                        }
                        break;
                    }
                }
                // Shift cell to the right
                if (index != col) {
                    Board[row][index].Value = Board[row][col].Value;
                    Board[row][index].ModelID = Board[row][col].ModelID;
                    Board[row][col].Value = 0;
                    Board[row][col].ModelID = 0;
                    Moved = true;
                }
                index--;
            }
        }
    }

    return Moved;
}

// Function to move cells up
bool AGameBoard::MoveUp()
{
    bool Moved = false;

    for (int col = 0; col < BoardSize; ++col) {
        int index = 0;
        for (int row = 0; row < BoardSize; ++row) {
            if (Board[row][col].Value != 0) {
                // Find a matching cell to merge with
                for (int mergeRow = row + 1; mergeRow < BoardSize; ++mergeRow) {
                    if (Board[mergeRow][col].Value != 0) {
                        if (Board[row][col].Value == Board[mergeRow][col].Value) {
                            // Merge cells
                            Board[row][col].Value += 1;
                            Board[row][col].ModelID = Board[mergeRow][col].ModelID;
                            Board[mergeRow][col].Value = 0;
                            Board[mergeRow][col].ModelID = 0;

                            if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
                            {
                                PlayerController->AddScores(Board[row][col].Value);
                            }

                            Moved = true;
                        }
                        break;
                    }
                }
                // Shift cell up
                if (index != row) {
                    Board[index][col].Value = Board[row][col].Value;
                    Board[index][col].ModelID = Board[row][col].ModelID;
                    Board[row][col].Value = 0;
                    Board[row][col].ModelID = 0;
                    Moved = true;
                }
                index++;
            }
        }
    }

    return Moved;
}

// Function to move cells down
bool AGameBoard::MoveDown()
{
    bool Moved = false;

    for (int col = 0; col < BoardSize; ++col) {
        int index = BoardSize - 1;
        for (int row = BoardSize - 1; row >= 0; --row) {
            if (Board[row][col].Value != 0) {
                // Find a matching cell to merge with
                for (int mergeRow = row - 1; mergeRow >= 0; --mergeRow) {
                    if (Board[mergeRow][col].Value != 0) {
                        if (Board[row][col].Value == Board[mergeRow][col].Value) {
                            // Merge cells
                            Board[row][col].Value += 1;
                            Board[row][col].ModelID = Board[mergeRow][col].ModelID;
                            Board[mergeRow][col].Value = 0;
                            Board[mergeRow][col].ModelID = 0;

                            if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
                            {
                                PlayerController->AddScores(Board[row][col].Value);
                            }

                            Moved = true;
                        }
                        break;
                    }
                }
                // Shift cell down
                if (index != row) {
                    Board[index][col].Value = Board[row][col].Value;
                    Board[index][col].ModelID = Board[row][col].ModelID;
                    Board[row][col].Value = 0;
                    Board[row][col].ModelID = 0;
                    Moved = true;
                }
                index--;
            }
        }
    }

    return Moved;
}

AABoardElement* AGameBoard::SpawnBoardElement(int row, int col, int value, int ID)
{
    if (!BoardElementClass) // Ensure we have a reference set to the BoardElement class
    {
        return nullptr;
    }

    // Calculate the location based on the row, column, and CellSize
    FVector SpawnLocation = FVector(CellSize * col, CellSize * row, 0);

    // Instantiate the BoardElement
    AABoardElement* NewBoardElement = GetWorld()->SpawnActor<AABoardElement>(BoardElementClass, SpawnLocation, FRotator::ZeroRotator);

    if (NewBoardElement)
    {
        // Assign properties
        NewBoardElement->GameBoard = this;
        NewBoardElement->ID = ID;
        NewBoardElement->Value = value;
        NewBoardElement->CellSize = CellSize;

        if (AMergeTownPlayerController* PlayerController = Cast<AMergeTownPlayerController>(GetWorld()->GetFirstPlayerController()))
        {
            PlayerController->AddScores(value);
        }

        return NewBoardElement;
    }

    return nullptr;
}