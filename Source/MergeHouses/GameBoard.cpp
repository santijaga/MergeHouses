// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoard.h"

// Sets default values
AGameBoard::AGameBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitializeBoard();
}

// Called when the game starts or when spawned
void AGameBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Function to print the board to the screen
void AGameBoard::PrintBoardToScreen()
{
    // Create a string to store the board representation
    FString BoardString = "2048 Board:\n";

    for (int32 Row = 0; Row < BOARD_SIZE; ++Row)
    {
        for (int32 Col = 0; Col < BOARD_SIZE; ++Col)
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

// Called every frame
void AGameBoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Call the printBoardToScreen function each frame
    PrintBoardToScreen();
}

bool AGameBoard::MakeMove(float x, float y)
{
    bool success = false;

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
    }

    return success;
}

// Function to initialize the game board with zeros
void AGameBoard::InitializeBoard()
{
    Board.Empty();
    Board.SetNum(BOARD_SIZE);

    for (int32 Row = 0; Row < BOARD_SIZE; ++Row)
    {
        Board[Row].Init(FBoardCell(), BOARD_SIZE);  // Use FBoardCell() as the default value
    }

    for (int32 times = 0; times < 2; ++times)
    {
        AddRandomCell();
    }
}

// Function to generate a random position (row, col) for a new cell
FVector2D AGameBoard::GenerateRandomPosition()
{
    TArray<FVector2D> EmptyCells;

    for (int32 Row = 0; Row < BOARD_SIZE; ++Row)
    {
        for (int32 Col = 0; Col < BOARD_SIZE; ++Col)
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
        int32 Value = FMath::RandBool() ? 1 : 2; // Randomly choose 1 or 2
        Board[Position.X][Position.Y].Value = Value;

        addedSuccessfully = true;
    }

    return addedSuccessfully;
}

// Function to move cells to the left
bool AGameBoard::MoveLeft()
{
    bool Moved = false;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        int index = 0;
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (Board[row][col].Value != 0) {
                // Find a matching cell to merge with
                for (int mergeCol = col + 1; mergeCol < BOARD_SIZE; ++mergeCol) {
                    if (Board[row][mergeCol].Value != 0) {
                        if (Board[row][col].Value == Board[row][mergeCol].Value) {
                            // Merge cells
                            Board[row][col].Value += 1;
                            Board[row][mergeCol].Value = 0;
                            Moved = true;
                        }
                        break;
                    }
                }
                // Shift cell to the left
                if (index != col) {
                    Board[row][index].Value = Board[row][col].Value;
                    Board[row][col].Value = 0;
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

    for (int row = 0; row < BOARD_SIZE; ++row) {
        int index = BOARD_SIZE - 1;
        for (int col = BOARD_SIZE - 1; col >= 0; --col) {
            if (Board[row][col].Value != 0) {
                // Find a matching cell to merge with
                for (int mergeCol = col - 1; mergeCol >= 0; --mergeCol) {
                    if (Board[row][mergeCol].Value != 0) {
                        if (Board[row][col].Value == Board[row][mergeCol].Value) {
                            // Merge cells
                            Board[row][col].Value += 1;
                            Board[row][mergeCol].Value = 0;
                            Moved = true;
                        }
                        break;
                    }
                }
                // Shift cell to the right
                if (index != col) {
                    Board[row][index].Value = Board[row][col].Value;
                    Board[row][col].Value = 0;
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

    for (int col = 0; col < BOARD_SIZE; ++col) {
        int index = 0;
        for (int row = 0; row < BOARD_SIZE; ++row) {
            if (Board[row][col].Value != 0) {
                // Find a matching cell to merge with
                for (int mergeRow = row + 1; mergeRow < BOARD_SIZE; ++mergeRow) {
                    if (Board[mergeRow][col].Value != 0) {
                        if (Board[row][col].Value == Board[mergeRow][col].Value) {
                            // Merge cells
                            Board[row][col].Value += 1;
                            Board[mergeRow][col].Value = 0;
                            Moved = true;
                        }
                        break;
                    }
                }
                // Shift cell up
                if (index != row) {
                    Board[index][col].Value = Board[row][col].Value;
                    Board[row][col].Value = 0;
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

    for (int col = 0; col < BOARD_SIZE; ++col) {
        int index = BOARD_SIZE - 1;
        for (int row = BOARD_SIZE - 1; row >= 0; --row) {
            if (Board[row][col].Value != 0) {
                // Find a matching cell to merge with
                for (int mergeRow = row - 1; mergeRow >= 0; --mergeRow) {
                    if (Board[mergeRow][col].Value != 0) {
                        if (Board[row][col].Value == Board[mergeRow][col].Value) {
                            // Merge cells
                            Board[row][col].Value += 1;
                            Board[mergeRow][col].Value = 0;
                            Moved = true;
                        }
                        break;
                    }
                }
                // Shift cell down
                if (index != row) {
                    Board[index][col].Value = Board[row][col].Value;
                    Board[row][col].Value = 0;
                    Moved = true;
                }
                index--;
            }
        }
    }

    return Moved;
}
