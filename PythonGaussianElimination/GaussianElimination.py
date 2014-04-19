
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



def checkForEchelon():
    global fixedMatrix, matrixSize
    leadCo = []
    sizeY = int(matrixSize.split(',')[0])
    sizeX = int(matrixSize.split(',')[1])

    for iy in range(0,sizeY):
        for ix in range(0,sizeX):
            if not 0 == fixedMatrix[0][0]:
                leadCo.append(iy)
                leadCo.append(ix)
                print(iy)
                print(ix)
                iy+1
        
        
            

    
"""    
def checkForReducedEchelon():
    
def getLeadingCoefficients():
    
def swapRows():
    
def multiplyRow():
    
def scalarRow():

"""
def printMatrix():
    print(fixedMatrix)
    
        

getMatrixSize()
getMatrixCSV()
getMatrixSup()
makeMatrix()
printMatrix()
checkForEchelon()
