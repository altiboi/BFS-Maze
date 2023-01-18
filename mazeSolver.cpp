#include <iostream>
#include <queue>
#include <vector>
#include <array>


using namespace std;

vector< vector<char> > grid(int row, int col)
{
    vector<vector<char> > maze;
    string s;

    for(int i = 0; i < row; i++)
    {
        vector<char> r;
        getline(cin, s);
        for(int j = 0; j < col; j++) 
        {
            r.push_back(s[j]);
        }
        maze.push_back(r);
        cout << endl;
    }

    return maze;
}

vector< vector<pair<int,int> > > make_parent(int row, int col)
{
    vector<vector<pair<int,int> > > parent;

    for(int i = 0; i < row; i++)
    {
        vector<pair<int,int> > r;
        for(int j = 0; j < col; j++)
        {
            r.push_back(make_pair(-1,-1));
        }
        parent.push_back(r);
    }

    return parent;
}

pair<int,int> search_maze(vector<vector<char> > maze, char value, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
           if(maze[i][j] == value)
           {
               return make_pair(i,j);
           }
        }
    }
}

vector<vector<bool> > been(int row, int col)
{
    vector<vector<bool> > v;

    for(int i = 0; i < row; i++)
    {
        vector<bool> r;
        for(int j = 0; j < col; j++)
        {
            r.push_back(false);
        }
        v.push_back(r);
    }
    return v;
}

vector<vector<char> > solve(vector<vector<char> > maze, pair<int,int> source, pair<int,int> goal, int row, int col)
{
    queue<pair<int,int> > next;
    next.push(source);
    vector<vector<bool> > visited = been(row, col);
    visited[source.first][source.second] = true;
    vector< vector<pair<int,int> > > parent = make_parent(row,col);
    pair<int,int> curr;
    int move_col[] = {0, -1, 0, 1};
    int move_row[] = {1, 0, -1, 0};

    while(curr != goal && next.empty() == false)
    {
        curr = next.front();
        next.pop();

        for(int a = 0; a < 4; a++)
        {
            int x = curr.first + move_row[a];
            int y = curr.second + move_col[a];

            if(x >= row || x < 0 || y >= col || y < 0 || maze[x][y] == 'x')
            {
                continue;
            }

            pair<int,int> neighbour = make_pair(x,y);

            if(visited[x][y] != true)
            {
                visited[x][y] = true;
                parent[x][y] = curr;
                next.push(neighbour);
            }
        }
    }

    if(curr != goal)
    {
        cout << "No Path" << endl;
        exit(0);
    }
    else
    {
        curr = parent[curr.first][curr.second];
        while(curr != source)
        {
            maze[curr.first][curr.second] = '*';
            curr = parent[curr.first][curr.second];
        }
    }

    return maze;
}

void print(vector<vector<char> > maze, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
    
}

int main()
{
    int row, col;
    cin >> row >> col;
    cin.ignore();

    vector<vector<char> > maze = grid(row,col);
    pair<int,int> start = search_maze(maze, 'S', row, col);
    pair<int,int> end = search_maze(maze, 'G', row, col);

    print(solve(maze, start, end, row, col), row, col);
    
    return 0;
}