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
                print(leadCo)
                break
            elif ix == sizeX:
                leadCo.append(ix)
                print(leadCo)
                break

    return leadCo
    
def checkForEchelon():
    sizeY = int(matrixSize.split(',')[0])
    leadCo = getLeadingCoefficients()
    for it in range(sizeY):
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

def solveForEchelon():
    global matrixSize

    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1]) - 1

    if sizeX == sizeY:
        if sizeX == 2:
            eliminateOne()
            return
        elif sizeX == 3:
            eliminateTwo()
            printMatrix()
            if checkForEchelon():
                print("Matrix is now in Echelon form\n")
            else:
                print("Matrix is not in Echelon form\n")
                solveForEchelon()
            return
        elif sizeX == 4:
            eliminateThree()
            return
    else:
        print("nothanks\n")

def solveForReducedEchelon():
    global matrixSize

    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1]) - 1

    if sizeX == sizeY:
        if sizeX == 2:
            eliminateOneReduced()
            return
        elif sizeX == 3:
            eliminateTwoReduced()
            if checkForReducedEchelon():
                print("Matrix is now in Reduced Echelon form\n")
            else:
                print("Matrix is not in Reduced Echelon form\n")
                solveForReducedEchelon()
            return
        elif sizeX == 4:
            eliminateThree()
            return
    else:
        print("nothanks")
    
def eliminateOne():
    global fixedMatrix

    scalarRow(-(float(fixedMatrix[1][0]) / float(fixedMatrix[0][0])),2,1)
    
def eliminateOneReduced():
    global fixedMatrix

    scalarRow(-(float(fixedMatrix[0][1]) / float(fixedMatrix[1][1])),1,2)
    multiplyRow(1 / float(fixedMatrix[0][0]),1)
    multiplyRow(1 / float(fixedMatrix[1][1]),2)
    
def eliminateTwo():
    global fixedMatrix
    
    scalarRow(-(float(fixedMatrix[1][0]) / float(fixedMatrix[0][0])),2,1)
    scalarRow(-(float(fixedMatrix[2][0]) / float(fixedMatrix[0][0])),3,1)

    scalarRow(-(float(fixedMatrix[2][1]) / float(fixedMatrix[1][1])),3,2)

def eliminateTwoReduced():
    global fixedMatrix
    
    scalarRow(-(float(fixedMatrix[1][2]) / float(fixedMatrix[2][2])),2,3)
    scalarRow(-(float(fixedMatrix[0][2]) / float(fixedMatrix[2][2])),1,3)

    multiplyRow(1 / float(fixedMatrix[1][1]),2)
    multiplyRow(1 / float(fixedMatrix[2][2]),3)

    scalarRow(-(float(fixedMatrix[0][1]) / float(fixedMatrix[1][1])),1,2)
    multiplyRow(1 / float(fixedMatrix[0][0]),1)
    
def eliminateThree():
    global fixedMatrix

    scalarRow(-(float(fixedMatrix[1][0]) / float(fixedMatrix[0][0])),2,1)
    scalarRow(-(float(fixedMatrix[2][0]) / float(fixedMatrix[0][0])),3,1)
    scalarRow(-(float(fixedMatrix[3][0]) / float(fixedMatrix[0][0])),4,1)
    printMatrix()
    scalarRow(-(float(fixedMatrix[2][1]) / float(fixedMatrix[1][1])),3,2)
    scalarRow(-(float(fixedMatrix[3][1]) / float(fixedMatrix[1][1])),4,2)
    printMatrix()
    scalarRow(-(float(fixedMatrix[3][2]) / float(fixedMatrix[2][2])),4,3)
    
"""
def eliminateThreeReduced():
"""


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
    
printMatrix()
solveForEchelon()

printMatrix()
solveForReducedEchelon()
