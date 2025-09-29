#include "ActorGenerator.h"
#include "PatrolActor.h"
#include "RotationActor.h"

AActorGenerator::AActorGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AActorGenerator::BeginPlay()
{
    Super::BeginPlay();
    GenerateActor();
}

void AActorGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AActorGenerator::GenerateActor()
{
    TArray<TArray<TPair<EDirection, int>>> Grid;
    InitializeGrid(Grid);

    TMap<TPair<int, int>, TArray<TPair<int, int>>> Graph;
    SetupGraph(Grid, Graph);

    TArray<TPair<int, int>> Path;
    if (FindPath(Graph, Path))
    {
        SpawnActorsAlongPath(Path, Grid);
    }
    else
    {
        GenerateActor(); // ��θ� ��ã���� ���
    }
}

void AActorGenerator::InitializeGrid(TArray<TArray<TPair<EDirection, int>>>& Grid)
{
    FMath::RandInit(FDateTime::Now().GetTicks());
    TArray<TArray<int>> Offset = { {1, 0}, {0, -1}, {0, 1}, {-1, 0} };
    for (int i = 0; i < Height; i++) {
        TArray<TPair<EDirection, int>> Row;
        for (int j = 0; j < Width; j++) {
            switch (int Rand = FMath::RandRange(0, 3))
            {
            case 0: Row.Add({ EForward, FMath::RandRange(0, FMath::Min(Height - i - 1, MinPatrolRange)) }); break;
            case 1: Row.Add({ EBackward, FMath::RandRange(0, FMath::Min(i, MinPatrolRange)) }); break;
            case 2: Row.Add({ ERight, FMath::RandRange(0, FMath::Min(Width - j - 1, MinPatrolRange)) }); break;
            case 3: Row.Add({ ELeft, FMath::RandRange(0, FMath::Min(j, MinPatrolRange)) }); break;
            }
        }
        Grid.Add(Row);
    }
}

void AActorGenerator::SetupGraph(TArray<TArray<TPair<EDirection, int>>>& Grid, TMap<TPair<int, int>, TArray<TPair<int, int>>>& Graph)
{
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            TPair<EDirection, int> Node = Grid[y][x];
            TArray<TPair<int, int>> Neighbors;

            auto AddNeighbor = [&](int NewY, int NewX, EDirection OppositeDirection) {
                if (NewY >= 0 && NewY < Height && NewX >= 0 && NewX < Width) {
                    TPair<EDirection, int> NeighborNode = Grid[NewY][NewX];
                    if (NeighborNode.Key != OppositeDirection || NeighborNode.Value == 0) {
                        Neighbors.Add({ NewY, NewX });
                    }
                }
                };

            switch (Node.Key) {
            case EDirection::EForward:
                AddNeighbor(y + Node.Value + 1, x, EBackward);
                AddNeighbor(y + Node.Value, x + 1, ELeft);
                AddNeighbor(y + Node.Value, x - 1, ERight);
                break;
            case EDirection::EBackward:
                AddNeighbor(y - Node.Value - 1, x, EForward);
                AddNeighbor(y - Node.Value, x + 1, ELeft);
                AddNeighbor(y - Node.Value, x - 1, ERight);
                break;
            case EDirection::ERight:
                AddNeighbor(y, x + Node.Value + 1, ELeft);
                AddNeighbor(y + 1, x + Node.Value, EBackward);
                AddNeighbor(y - 1, x + Node.Value, EForward);
                break;
            case EDirection::ELeft:
                AddNeighbor(y, x - Node.Value - 1, ERight);
                AddNeighbor(y + 1, x - Node.Value, EBackward);
                AddNeighbor(y - 1, x - Node.Value, EForward);
                break;
            }

            Graph.Add({ y, x }, Neighbors);
        }
    }
}

bool AActorGenerator::FindPath(const TMap<TPair<int, int>, TArray<TPair<int, int>>>& Graph, TArray<TPair<int, int>>& Path)
{
    TPair<int, int> Start = { 0, Width / 2 };
    TPair<int, int> End = { Height - 1, Width / 2 };

    TMap<TPair<int, int>, TPair<int, int>> CameFrom;
    TArray<TArray<bool>> Visited;
    Visited.SetNum(Height);
    for (int i = 0; i < Height; i++) {
        Visited[i].SetNum(Width);
    }

    TQueue<TPair<int, int>> Frontier;
    Frontier.Enqueue(Start);
    Visited[Start.Key][Start.Value] = true;
    CameFrom.Add(Start, Start);
    bool bPathFound = false;
    while (!Frontier.IsEmpty()) {
        TPair<int, int> Current;
        Frontier.Dequeue(Current);

        if (Current == End) {
            bPathFound = true;
            break;
        }

        for (const TPair<int, int>& Next : Graph[Current]) {
            if (!Visited[Next.Key][Next.Value]) {
                Frontier.Enqueue(Next);
                Visited[Next.Key][Next.Value] = true;
                CameFrom.Add(Next, Current);
            }
        }
    }

    if (!bPathFound) {
        return false;
    }

    TPair<int, int> Current = End;
    while (Current != Start) {
        Path.Add(Current);
        Current = CameFrom[Current];
    }
    Path.Add(Start);
    Algo::Reverse(Path);

    return true;
}

void AActorGenerator::SpawnActorsAlongPath(const TArray<TPair<int, int>>& Path, const TArray<TArray<TPair<EDirection, int>>>& Grid)
{
    int Scale = 1000;
    FVector ForwardVector = GetActorForwardVector();
    FVector RightVector = GetActorRightVector();
    FVector StartLocation = GetActorLocation();

    float PrevSpeed = 0;
    for (const TPair<int, int>& Node : Path) {
        int Y = Node.Key;
        int X = Node.Value;

        float Range = Grid[Y][X].Value * Scale;
        float Speed = FMath::RandRange(100, Scale);

        ADynamicActor* Actor = nullptr;

        if (FMath::IsNearlyZero(Range)) {
            ARotationActor* RotationActor = GetWorld()->SpawnActor<ARotationActor>(ARotationActor::StaticClass());
            RotationActor->Init(static_cast<bool>(FMath::RandRange(0, 1)), Speed);
            Actor = RotationActor;
            Speed = 0;
        }
        else {
            APatrolActor* PatrolActor = GetWorld()->SpawnActor<APatrolActor>(APatrolActor::StaticClass());
            while (FMath::Abs(Speed - PrevSpeed) < 50) Speed = FMath::RandRange(100, Scale);
            PatrolActor->Init(Grid[Y][X].Key, Speed, Range);
            Actor = PatrolActor;
        }

        X -= Width / 2;
        FVector Location = StartLocation + ForwardVector * Y * Scale + RightVector * X * Scale;
        Actor->SetActorLocation(Location);

        PrevSpeed = Speed;
    }
}

/*
void AActorGenerator::GenerateActor()
{
	TArray<TArray<float>> Grid;
	for (int i = 0; i < Height; i++) {
		TArray<float> Temp;
		for (int j = 0; j < Width; j++) {
			Temp.Push(0);
		}
		Grid.Push(Temp);
	}
	for (int i = 0; i < Width; i++) {
		Grid[Height - 1][i] = 1;
	}

	Grid[0][Width >> 1] = 1;

	FMath::RandInit(FDateTime::Now().GetTicks());
    TArray<TArray<int>> Offset = { {1,0},{0,-1},{0,1}, {-1,0}};
    TArray<TPair<int, int>> Stack;
    Stack.Push({ 0, Width >> 1 });

    while (!Stack.IsEmpty()) {
        TPair<int, int> Current = Stack.Pop();
        int X = Current.Value;
        int Y = Current.Key;
        Grid[Y][X] = 1;
        if (Y == Height - 2)break;

        TArray<TPair<int, int>> Neighbors;
        for (int i = 0; i < 3; i++) {
            int XX = X + Offset[i][1];
            int YY = Y + Offset[i][0];
            if (XX < 0 || XX >= Width || YY >= Height || Grid[YY][XX] == 1) continue;
            Neighbors.Push({ YY, XX });
        }

        bool bGenerated = false; // ���� ���� ���� Ȯ��
        TPair<int, int> BestNeighbor;
        float MaxProba = -1.0f;

        // Ȯ�� ���
        for (TPair<int, int>& Neighbor : Neighbors) {
            float Proba = 0;
            for (int i = 0; i < 4; i++) {
                int XX = Neighbor.Value + Offset[i][1];
                int YY = Neighbor.Key + Offset[i][0];
                if (XX < 0 || XX >= Width || YY < 0 || YY >= Height) continue;
                Proba += Grid[YY][XX];
            }
            Proba *= 0.25;
            Grid[Neighbor.Key][Neighbor.Value] = Proba;
        }
        
        for (TPair<int, int>& Neighbor : Neighbors) {
            float Rand = FMath::FRand();
            if (Rand < Grid[Neighbor.Key][Neighbor.Value] * Density * Density) { // Ȯ�� ��
                Stack.Push(Neighbor);
                bGenerated = true;
            }

            // ���� ���� Proba�� ���� �̿� ����
            if (Grid[Neighbor.Key][Neighbor.Value] > MaxProba) {
                MaxProba = Grid[Neighbor.Key][Neighbor.Value];
                BestNeighbor = Neighbor;
            }
        }

        // ���� ���� ���� �� ���� ���� Proba �̿� �߰�
        if (!bGenerated && MaxProba > 0) {
            Grid[BestNeighbor.Key][BestNeighbor.Value] = 1;
            Stack.Push(BestNeighbor);
        }
    }


    PrintGrid(Grid);
}
*/

