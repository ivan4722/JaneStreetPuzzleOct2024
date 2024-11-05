#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cstdint>
#include <fstream>

using namespace std;

int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

char grid[6][6];
unordered_map<char, int> valueMap;

string getCellLabel(int x, int y)
{
    char file = 'a' + x;
    int rank = 6 - y;
    return string(1, file) + to_string(rank);
}

struct State
{
    int x, y;
    int score;
    uint64_t visited;
    vector<pair<int, int>> path;
};

bool bfs(int startX, int startY, int targetX, int targetY, int startScore, vector<pair<int, int>>& resultPath)
{
    queue<State> q;
    State initialState;
    initialState.x = startX;
    initialState.y = startY;
    initialState.score = startScore;
    initialState.visited = 0;
    initialState.path.push_back({ startX, startY });
    int pos = startY * 6 + startX;
    initialState.visited |= (1ULL << pos);
    q.push(initialState);

    while (!q.empty())
    {
        State current = q.front();
        q.pop();

        if (current.x == targetX && current.y == targetY && current.score == 2024)
        {
            resultPath = current.path;
            return true;
        }

        if (current.score > 2024) continue;

        for (int i = 0; i < 8; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx < 0 || nx >= 6 || ny < 0 || ny >= 6) continue;

            int newPos = ny * 6 + nx;
            if (current.visited & (1ULL << newPos)) continue;

            char currentCell = grid[current.y][current.x];
            char nextCell = grid[ny][nx];
            int currentValue = valueMap[currentCell];
            int nextValue = valueMap[nextCell];

            int newScore;
            if (currentCell == nextCell)
            {
                newScore = current.score + nextValue;
            }
            else
            {
                newScore = current.score * nextValue;
            }

            if (newScore > 2024) continue;

            State newState;
            newState.x = nx;
            newState.y = ny;
            newState.score = newScore;
            newState.visited = current.visited | (1ULL << newPos);
            newState.path = current.path;
            newState.path.push_back({ nx, ny });

            q.push(newState);
        }
    }
    return false;
}

int main()
{
    string gridPattern[6] = 
    {
        "ABBCCC",
        "ABBCCC",
        "AABBCC",
        "AABBCC",
        "AAABBC",
        "AAABBC"
    };

    for (int y = 0; y < 6; y++)
    {
        string row = gridPattern[y];
        for (int x = 0; x < 6; x++)
        {
            grid[y][x] = row[x];
        }
    }

    int minSumABC = 51;
    int bestA = -1, bestB = -1, bestC = -1;
    vector<pair<int, int>> bestPath1, bestPath2;

    ofstream outFile("output.txt", ofstream::app); // Open file in append mode

    for (int A = 20; A >= 1; A--)
    {
        for (int B = 20; B >= 1; B--)
        {
            if (B == A) continue;
            for (int C = 20; C >= 1; C--)
            {
                if (C == A || C == B) continue;

                if (A + B + C >= minSumABC) continue;

                valueMap['A'] = A;
                valueMap['B'] = B;
                valueMap['C'] = C;

                vector<pair<int, int>> path1;
                if (!bfs(0, 5, 5, 0, A, path1)) continue;

                vector<pair<int, int>> path2;
                if (!bfs(0, 0, 5, 5, A, path2)) continue;

                minSumABC = A + B + C;
                bestA = A;
                bestB = B;
                bestC = C;
                bestPath1 = path1;
                bestPath2 = path2;

                outFile << bestA << "," << bestB << "," << bestC << ",";
                for (size_t i = 0; i < bestPath1.size(); i++)
                {
                    outFile << getCellLabel(bestPath1[i].first, bestPath1[i].second);
                    if (i != bestPath1.size() - 1) outFile << ",";
                }
                outFile << ",";
                for (size_t i = 0; i < bestPath2.size(); i++)
                {
                    outFile << getCellLabel(bestPath2[i].first, bestPath2[i].second);
                    if (i != bestPath2.size() - 1) outFile << ",";
                }
                outFile << endl;
            }
        }
    }

    outFile.close(); // Close file after writing all results

    cout << "Finished searching for solutions." << endl;
    return 0;
}
