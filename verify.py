def create_grid(A, B, C):
    return [
        [A, B, B, C, C, C],   # 6
        [A, B, B, C, C, C],   # 5
        [A, A, B, B, C, C],   # 4
        [A, A, B, B, C, C],   # 3
        [A, A, A, B, B, C],   # 2
        [A, A, A, B, B, C]    # 1
    ]

A = 20
B = 2
C = 1
grid = create_grid(A, B, C)

def chessToMatrix(chessNotation):
    colChar = chessNotation[0]
    col = ord(colChar) - ord('a')
    row = 5-(int(chessNotation[1])-1)
    return row,col

input = 'a1,b3,c1,e2,c3,d1,e3,f5,d4,b5,d6,c4,e5,f3,d2,e4,f2,d3,f4,d5,f6,a6,b4,c2,e1,d3,c5,e6,d4,b5,d6,f5,e3,c4,b6,d5,c3,e4,d2,f1'
inputArr = input.split(',')

moves = []
for i in inputArr:
    moves.append(chessToMatrix(i))
mid = moves.index((0,0))
path1 = moves[:mid]
path2 = moves[mid:]
print(path1)
print(path2)

def path1sum(path):
    currsum = grid[5][0]
    currx = 5
    curry = 0 
    for x,y in path[1:]:
        if grid[x][y] != grid[currx][curry]:
            currsum *= grid[x][y]
            currx = x
            curry = y
        else:
            currsum+=grid[x][y]
        currx = x
        curry = y
    return currsum

def path2sum(path):
    currsum = grid[0][0]
    currx = 0 
    curry = 0 
    for x,y in path[1:]:
        if grid[x][y] != grid[currx][curry]:
            currsum *= grid[x][y]
            currx = x
            curry = y
        else:
            currsum+=grid[x][y]
        currx = x
        curry = y
    return currsum

print(path1sum(path1))
print(path2sum(path2))