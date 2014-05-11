"""
2,1,-1,8,-3,-1,2,-11,-2,1,2,-3
"""
matrix = ""
matrixSize = ""
fixedMatrix = []

def getMatrixSize():
    global matrixSize
    matrixSize = input("Enter Matrix Size: ")
    
def getMatrixCSV():
    global matrixSize, matrix
    
    matrix = input("Enter CSV of the Matrix: ")
    if len(matrix.split(',')) != int(matrixSize.split(',')[0]) * int(matrixSize.split(',')[1]):
        print("Matrix CSV does not match matrix size")
        getMatrixCSV()

def makeMatrix():
    global matrix, matrixSize, fixedMatrix
    
    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1])
    fixedMatrix = [[] for i in range(sizeY)]
    
    for iy in range(0,sizeY):
        for ix in range(0,sizeX):
            fixedMatrix[iy].append(matrix.split(',')[(iy * sizeX)    + ix])

def getLeadingCoefficients():
    global fixedMatrix, matrixSize

    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1]) - 1
    leadCo = []

    for iy in range(sizeY):
        for ix in range(sizeX):
            if fixedMatrix[iy][ix] != 0:
                leadCo.append(ix)
                break
            elif ix == sizeX:
                leadCo.append(ix)
                break

    return leadCo
    
def checkForEchelon():
    sizeY = int(matrixSize.split(',')[0])
    leadCo = getLeadingCoefficients()
    for it in range(sizeY -1):
        if not leadCo[it]+1 == leadCo[it+1]:
            return False
    return True

def checkForReducedEchelon():
    global fixedMatrix, matrixSize

    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1]) - 1
    if(checkForEchelon()):
        for iy in range(sizeY):
            for ix in range(sizeX):
                if int(fixedMatrix[iy][ix]) < 0 or int(fixedMatrix[iy][ix]) > 1:
                    return False

        return True
    return False

def swapRows(first, second):
    global fixedMatrix, matrixSize
    sizeX = int(matrixSize.split(',')[1]) - 1

    fixedMatrix[first-1], fixedMatrix[second-1] = fixedMatrix[second-1], fixedMatrix[first-1]

def multiplyRow(mut, row):
    global fixedMatrix, matrixSize

    sizeX = int(matrixSize.split(',')[1])
    for addX in range(sizeX):
        fixedMatrix[row-1][addX] = (float(fixedMatrix[row-1][addX]) * float(mut))
    
def scalarRow(mut, row1, row2):
    global fixedMatrix, matrixSize

    sizeX = int(matrixSize.split(',')[1])
    for it in range(sizeX):
        fixedMatrix[row1-1][it] = float(fixedMatrix[row1-1][it]) + (float(mut) * float(fixedMatrix[row2-1][it]))

def printMatrix():
    for it in range(int(matrixSize.split(',')[0])):
        print(str(fixedMatrix[it]))
    print(" ")

def scalingReduction(ix, iy, it):
    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1]) - 1

    if ix >= (sizeX - 1) and iy >= (sizeY - 1) and it > 2:
        print("Reduction Complete")
        return
    else:

        print("iy: " + str(iy+1))
        print("ix: " + str(ix))
        print("it: " + str(it))
        ix = ix+1
        iy = iy+1
        it = it+1
    
    scalingReduction(ix, iy, it)
    


getMatrixSize()
getMatrixCSV()
makeMatrix()
printMatrix()

if checkForEchelon():
    print("Echelon")
else:
    print("Not Echelon")

if checkForReducedEchelon():
    print("Reduced Echelon\n")
else:
    print("Not Reduced Echelon\n")
    
scalingReduction(0, 0, 0)
printMatrix()

