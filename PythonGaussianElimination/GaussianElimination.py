"""
MatrixSize: 3,3
MatrixCSV:  2,1,-1,-3,-1,2,-2,1,2
SupMatrix:  8,-11,-3
"""

matrix = "0"
matrixSize = "0,0"
supMatrix = "0"
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

def getMatrixSup():
    global matrixSize, supMatrix
    supMatrix = input("Enter 1 by " + matrixSize.split(',')[1] + " Matrix: ")

def makeMatrix():
    global matrix, matrixSize, fixedMatrix
    
    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1])
    fixedMatrix = [[] for i in range(sizeY)]
    
    for iy in range(0,sizeY):
        for ix in range(0,sizeX):
            fixedMatrix[iy].append(matrix.split(',')[(iy * sizeX)    + ix])
            if ix == sizeX-1:
                fixedMatrix[iy].append("|")
                fixedMatrix[iy].append(supMatrix.split(',')[iy])


def getLeadingCoefficients():
    global fixedMatrix, matrixSize

    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1])
    leadCo = []

    for iy in range(sizeY):
        for ix in range(sizeX):
            if not int(fixedMatrix[iy][ix]) == 0:
                leadCo.append(ix)
                break

    return leadCo
    
def checkForEchelon():
    sizeY = int(matrixSize.split(',')[0])
    leadCo = getLeadingCoefficients()
    for it in range(sizeY-1):
        if not leadCo[it]+1 == leadCo[it+1]:
            return False
    return True


def checkForReducedEchelon():
    global fixedMatrix, matrixSize

    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1])
    if(checkForEchelon()):
        for iy in range(sizeY):
            for ix in range(sizeX):
                if int(fixedMatrix[iy][ix]) < 0 or int(fixedMatrix[iy][ix]) > 1:
                    return False

        return True
    return False

def swapRows(first, second):
    global fixedMatrix, matrixSize
    sizeX = int(matrixSize.split(',')[1])

    fixedMatrix[first-1], fixedMatrix[second-1] = fixedMatrix[second-1], fixedMatrix[first-1]

def multiplyRow(mut, row):
    global fixedMatrix, matrixSize

    sizeX = int(matrixSize.split(',')[1])
    for addX in range(sizeX):
        fixedMatrix[row-1][addX] = (float(fixedMatrix[row-1][addX]) * float(mut))
    fixedMatrix[row-1][4] = (float(fixedMatrix[row-1][4]) * float(mut))
    

def scalarRow(mut, row1, row2):
    global fixedMatrix, matrixSize

    sizeX = int(matrixSize.split(',')[1])
    for it in range(sizeX):
        fixedMatrix[row1-1][it] = float(fixedMatrix[row1-1][it]) + (float(mut) * float(fixedMatrix[row2-1][it]))
    fixedMatrix[row1-1][4] = float(fixedMatrix[row1-1][4]) + (float(mut) * float(fixedMatrix[row2-1][4]))

def printMatrix():
    for it in range(int(matrixSize.split(',')[1])):
        print(str(fixedMatrix[it]))
    print(" ")
    
        

getMatrixSize()
getMatrixCSV()
getMatrixSup()
makeMatrix()
printMatrix()
if checkForEchelon():
    print("Echelon")
else:
    print("Not Echelon")

if checkForReducedEchelon():
    print("Reduced Echelon")
else:
    print("Not Reduced Echelon")

scalarRow(1.5,2,1)
scalarRow(1,3,1)

printMatrix()

scalarRow(-4,3,2)

printMatrix()

scalarRow(.5,2,3)
scalarRow(-1,1,3)

printMatrix()

multiplyRow(2,2)
multiplyRow(-1,3)

printMatrix()

scalarRow(-1,1,2)
multiplyRow(.5,1)

printMatrix()

if checkForEchelon():
    print("Echelon")
else:
    print("Not Echelon")

if checkForReducedEchelon():
    print("Reduced Echelon")
else:
    print("Not Reduced Echelon")
