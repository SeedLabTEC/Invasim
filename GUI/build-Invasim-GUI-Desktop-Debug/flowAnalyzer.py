
from tkinter import filedialog
from tkinter import *
import os
from xml.etree import ElementTree as ET
import xml.dom.minidom
import numpy as np

cutBlockValues = ["beq", "bnez", "bge", "blt", "ble", "j", "jr",
                  "jal", "jalr", "call"]  # BNEZ-J-JR-JAL-JALR-EBREAK


def findRegOnList(reg1, listIn):  # check the use of the register on the other subprocess
    indexList = []
    index = -1

    for listInDep in listIn:  # check in every list
        index = index+1
        for elInst in listInDep:  # check every instuction
            # check if isn't a intersection
            if(not elInst.split()[0] in cutBlockValues):
                if(reg1 in elInst):  # check if is in instruction
                    indexList.append(index)
                    break

    return indexList


def dependenciesSearchDeep(listIn):
    restW = True
    control = 0
    joinList = []
    #print("Here deep")
    #print(listIn)

    while(restW):
        joinList = []
        posRev = 0
        for subList in listIn:
            tempJoin = []
            for inst in subList:
                reg = inst.split()[1].split(",")
                if(len(reg) >= 2):
                        # anything that could change register
                    if(("addi" in inst) or ("li" in inst) or ("mv" in inst) or ("lw" in inst) or ("mul" in inst) or ("slli" in inst) or ("srli" in inst)):
                            # go to search other blocks

                        res = findRegOnList(reg[0], listIn)
                        if(posRev in res):
                            res.remove(posRev)
                        tempJoin = tempJoin + res

            posRev = posRev+1
            joinList.append(sorted(list(set(tempJoin))))

        posJ = 0
        # print(joinList)
        for eleJoin in joinList:
            restW = False
            if(posJ+1 < len(joinList)):
                if((posJ-1) in eleJoin):
                    # unir y break y volver a revisar
                    listIn[posJ-1] = listIn[posJ-1] + listIn[posJ]
                    listIn.pop(posJ)
                    restW = True
                    break
                if((posJ+1) in eleJoin):
                    # unir y break y volver a revisar
                    listIn[posJ] = listIn[posJ] + listIn[posJ+1]

                    listIn.pop(posJ+1)
                    restW = True
                    break
                if(posJ in joinList[posJ+1]):
                    # unir y break y volver a revisar
                    listIn[posJ] = listIn[posJ] + listIn[posJ+1]
                    listIn.pop(posJ+1)
                    restW = True
                    break
                if(eleJoin != []):
                    # revisar q tiene
                    restW = True
                    print("CHECK THIS")
            else:
                restW = False
            posJ = posJ + 1

        if(control > 100):
            print("OUT OF CONTROL")
            restW = False

        control = control + 1

    for eleJoin in joinList:
        if(eleJoin != []):
            print("CHECK")

    return listIn


def dependenciesSearchDeep2(listIn):  # sorted(list(set()))
    restartW = True
    while(restartW):
        restartF = False
        posRev = 0
        for subList in listIn:

            for inst in subList:
                reg = inst.split()[1].split(",")
                if(len(reg) >= 2):
                    # anything that could change register
                    if(("addi" in inst) or ("li" in inst) or ("mv" in inst) or ("lw" in inst) or ("mul" in inst)):
                        # go to search other blocks
                        #print("Found "+inst)
                        res = findRegOnList(reg[0], listIn)

                        if(posRev in res):
                            res.remove(posRev)

                        for union in res:
                            restartF = True
                            #print("UNIR EL "+str(posRev) + " CON "+str(union))
                            if(posRev > union):
                                listIn[union] = listIn[union] + listIn[posRev]
                                listIn.pop(posRev)
                            else:
                                listIn[posRev] = listIn[posRev] + listIn[union]
                                listIn.pop(union)

                            break

            if(restartF):
                break

            posRev = posRev + 1

        if(posRev == len(listIn)):
            restartW = False

    return listIn


def dependenciesSearch(instructionList):
    posInst = 0
    returnListDivided = []
    tempList = []
    for val in instructionList:    
        if(val == "nop"):
            val = "addi	zero,zero,0"

        temp = val.split()
        if(posInst+1 < len(instructionList)):
            nextVal = instructionList[posInst+1].split()[1]
            nextVal = nextVal.replace("(", ",").replace(")", "")
            nextVal = nextVal.split(',')
            temp[1] = temp[1].replace("(", ",").replace(")", "")
            tempList.append(val)

            checkReg = temp[1].split(",")
            if((temp[0] == 'sw') and (temp[0] == instructionList[posInst+1].split()[0])):
                returnListDivided.append(tempList)
                tempList = []
            elif((temp[0] == 'lw') and (temp[0] == instructionList[posInst+1].split()[0])):
                returnListDivided.append(tempList)
                tempList = []
            else:
                if((temp[0] == 'sw') and (instructionList[posInst+1].split()[0] == 'lw') and (checkReg[0] != nextVal[0])):
                    # print('gggg')
                    # print(tempList)
                    returnListDivided.append(tempList)
                    tempList = []

                elif(len(checkReg) == 2):

                    if(len(nextVal) == 3):
                        if((checkReg[0] != nextVal[0]) and (checkReg[0] != nextVal[1]) and (checkReg[0] != nextVal[2])):
                            returnListDivided.append(tempList)
                            tempList = []

                    elif(len(nextVal) == 2):
                        if((checkReg[0] != nextVal[0]) and (checkReg[0] != nextVal[1])):
                            returnListDivided.append(tempList)
                            tempList = []

                elif(len(checkReg) == 3):
                    if(len(nextVal) == 3):

                        if((checkReg[0] != nextVal[0]) and (checkReg[0] != nextVal[1]) and (checkReg[0] != nextVal[2])):
                            returnListDivided.append(tempList)
                            tempList = []

                    elif(len(nextVal) == 2):

                        if((checkReg[0] != nextVal[0]) and (checkReg[0] != nextVal[1])):
                            returnListDivided.append(tempList)
                            tempList = []
                    else:
                        tempList.append(instructionList[posInst+1])
                        returnListDivided.append(tempList)
                        tempList = []
        else:
            tempList.append(val)

        posInst = posInst + 1

    if(len(tempList) != 0):
        returnListDivided.append(tempList)
        tempList = []

    if((len(returnListDivided[-1]) == 1) and (returnListDivided[-1][0].split()[0] in cutBlockValues) and (len(returnListDivided) !=1) ):
        returnListDivided.pop()

    return dependenciesSearchDeep(returnListDivided)


def blocksCreation(blocksRootFirstAnalisis, instructionListIn, idBlock, actualLine):
    subprocess = dependenciesSearch(instructionListIn)

    block = ET.SubElement(blocksRootFirstAnalisis, "block")
    block.set("id", idBlock)
    indexSub = 0

    for instructionList in subprocess:

        subIlet = ET.SubElement(block, "subp")
        subIlet.set("id", str(indexSub))
        posInst = 0

        for val in instructionList:  
            if((posInst == len(instructionList)-1) and (val.split()[0] in cutBlockValues)):
                instDo = val.split()
                # create xml objects
                intersection = ET.SubElement(subIlet, "intersection")
                instruction = ET.SubElement(intersection, "instruction")
                condition1 = ET.SubElement(intersection, "condition1")
                condition2 = ET.SubElement(intersection, "condition2")
                probability = ET.SubElement(intersection, "probability")

                instruction.text = val  # set instruction

                if(instDo[0] == "call"):
                    condition1.text = instDo[1]
                    condition2.text = str(actualLine)
                    probability.text = str(1)
                    # jr	ra
                elif(instDo[0] == "jr"):
                    condition1.text = "N/A"
                    condition2.text = str(actualLine)
                    probability.text = str(1)
                elif((instDo[0] == "beq") or (instDo[0] == "bnez") or (instDo[0] == "bge") or (instDo[0] == "blt") or (instDo[0] == "ble")):
                    condition1.text = instDo[-1].split(",")[-1]
                    condition2.text = str(actualLine)
                    probability.text = str(np.random.binomial(1, 0.5, 1)[0])
                else:
                    # condition1.text = "N/A"
                    condition1.text = instDo[1]
                    condition2.text = str(actualLine)
                    probability.text = str(1)
            else:
                instDo = val.split()
                instruction = ET.SubElement(subIlet, "instruction")

                instruction.text = instDo[0]+","+instDo[1]
            posInst = posInst + 1

        indexSub = indexSub + 1


def crateBlocks(readFile, writeFile):
    blocksRootFirstAnalisis = ET.Element('Blocks')  # root of blocks flow

    readLine = 0
    f = open(readFile, "r+")
    line = f.readline()
    blockLines = 0  # keep lines of respective block
    blocksID = ""
    temporalBlock = []

    while line:
        if(line.startswith('	.') == False):   # if isn't an annotation
            if(any(s in line for s in cutBlockValues)):  # if is an intersection instruction

                # delete before and after spaces
                temporalBlock.append(line.rstrip().lstrip())

                # Logic of block ID to save on flow
                if(blocksID != ""):
                    blocksCreation(blocksRootFirstAnalisis,
                                   temporalBlock, blocksID, readLine)
                else:
                    blocksCreation(blocksRootFirstAnalisis, temporalBlock, "Line" +
                                   str(readLine-blockLines+1), readLine)

                # clear variables
                blockLines = 0
                temporalBlock = []
                blocksID = ""

            elif(line.startswith('	') == False):   # if is a tag an isn't an instruction

                if(temporalBlock != []):
                    if(blocksID != ""):
                        blocksCreation(blocksRootFirstAnalisis,
                                       temporalBlock, blocksID, readLine)
                    else:
                        blocksCreation(blocksRootFirstAnalisis, temporalBlock, "Line" +
                                       str(readLine-blockLines+1), readLine)

                blocksID = line.replace(":", "").rstrip()
                # clear variables
                blockLines = 0
                temporalBlock = []

            else:  # different instruction
                blockLines = blockLines + 1
                temporalBlock.append(line.rstrip().lstrip())

            readLine = readLine + 1

        line = f.readline()  # next line

    if(temporalBlock != []):
        blocksCreation(blocksRootFirstAnalisis,
                       temporalBlock, "EndBlock", readLine)
        # clear variables
        blockLines = 0
        temporalBlock = []

    fw = open(writeFile, "w+")
    show = xml.dom.minidom.parseString(
        ET.tostring(blocksRootFirstAnalisis)).toprettyxml()
    fw.write(show)

    fw.close()
    f.close()

# Get position of name tag on xml


def findIdOnXml(xml, name):
    index = 0
    for child in xml:
        if(child.get("id") == name):
            return index
        index = index + 1

# Get position of name tag on xml and variable of visited to known and parse flow


def listBlocks(xml):
    indexList = []
    for child in xml:
        indexList.append([child.get("id"), 0])
    return indexList


def checkPendingBlocks(blocks):
    index = 0
    for ele in blocks:
        if(ele[1] != 1):
            return index
        index = index + 1
    return -1
# create the logic flow


def createLogicFlow(readFile, writeFile):
    # print(readFile)
    # print(writeFile)
    tree = ET.parse(readFile)  # get xml from file
    root = tree.getroot()  # create the object

    orderFlowBlocks = []  # keep order blocks
    onFlowListBlocks = listBlocks(root)  # get list of blocks to process

    tempBlock = root[findIdOnXml(root, "main")]  # get xml of block main

    breakAt = len(onFlowListBlocks)+3  # to prevent infinite while

    breakCount = 0
    while(breakCount < breakAt):  # search on all blocks
        if(checkPendingBlocks(onFlowListBlocks) == -1):
            break
        if(onFlowListBlocks[findIdOnXml(root, tempBlock.get("id"))][1] != 1):
            # read block on list and check if was done
            onFlowListBlocks[findIdOnXml(root, tempBlock.get("id"))][1] = 1
            # main is the firts block that we read
            orderFlowBlocks.append(tempBlock)
            # print(tempBlock.get("id"))
            # search last instruction of block to break the while
            
            if(tempBlock[-1][-1].tag != "intersection"):
                # check if finished all or there are something pending
                if(checkPendingBlocks(onFlowListBlocks) != -1):
                    # print("Pending")
                    tempBlock = root[checkPendingBlocks(onFlowListBlocks)]
                else:
                    # print("Break flow")
                    break
            else:
                # if is necessary return to next block of called block
                if(tempBlock[-1][-1][1].text == "N/A"):
                    # print(tempBlock.get("id"))
                    # get the next block of which where was called

                    if((tempBlock.get("id") != "main")):
                        # finish
                        if((findIdOnXml(root, orderFlowBlocks[-2].get("id"))+1) >= len(root)):
                            break
                        else:
                            # print(tempBlock.get("id"))
                            # print(orderFlowBlocks[-2].get("id"))
                            tempBlock = root[findIdOnXml(
                                root, orderFlowBlocks[-2].get("id"))+1]
                            # print(tempBlock.get("id"))
                    else:
                        tempBlock = root[findIdOnXml(
                            root, tempBlock[-1][-1][0].text.split()[-1])]
                else:
                    instDo = tempBlock[-1][-1][0].text.split()
                    if((instDo[0] == "beq") or (instDo[0] == "bnez") or (instDo[0] == "bge") or (instDo[0] == "blt") or (instDo[0] == "ble")):
                        # change intersection value to known
                        orderFlowBlocks[-1][-1][-1][2].text = root[findIdOnXml(
                            root, orderFlowBlocks[-1].get("id"))+1].get("id")

                        if(tempBlock[-1][-1][-1].text == "1"):  # if the branch is taken
                            tempBlock = root[findIdOnXml(
                                root, tempBlock[-1][-1][1].text)]  # next block
                        else:
                            # get the next block of which where was called
                            # change to check the block didn't take
                            onFlowListBlocks[findIdOnXml(
                                root, tempBlock[-1][-1][1].text)][1] = 1
                            tempBlock = root[findIdOnXml(
                                root, tempBlock[-1][-1][2].text)]

                    else:
                        tempBlock = root[findIdOnXml(
                            root, tempBlock[-1][-1][1].text)]  # next block
        else:
            tempBlock = root[checkPendingBlocks(onFlowListBlocks)]

        breakCount = breakCount + 1

    stringReadyKeep = ""
    for bl in orderFlowBlocks:
        stringReadyKeep = stringReadyKeep + ET.tostring(bl, encoding='unicode')

    readyToProcess = open(writeFile, "w+")
    stringReadyKeep = "<?xml version='1.0' ?>\n<Blocks>\n"+stringReadyKeep+"\n</Blocks>"
    readyToProcess.write(stringReadyKeep)
    readyToProcess.close()


def main():
    os.makedirs("./bin/analyzerResults/blocks", exist_ok=True)
    os.makedirs("./bin/analyzerResults/flow", exist_ok=True)

    # root = Tk()
    # filenames =  filedialog.askopenfilenames(initialdir = filedialog.askdirectory(),title = "Select files with ctrl",filetypes = (("Assembler files","*.s"),("all files","*.*")), multiple=True)

    index = 0
    files = [
        "/home/gabriel/Documents/Proyectos/codes/test0.s",
        # "/home/gabriel/Documents/Proyectos/codes/test1.s",
        # "/home/gabriel/Documents/Proyectos/codes/test2.s"
    ]

    readyToProcess = open("./bin/analyzerResults/files.txt", "w+")
    for ele in files:
        readyToProcess.write(
            "./bin/analyzerResults/flow/flow"+str(index)+".xml"+"\n")
        crateBlocks(ele, "./bin/analyzerResults/blocks/blocks" +
                    str(index)+".xml")
        createLogicFlow("./bin/analyzerResults/blocks/blocks"+str(index) +
                        ".xml", "./bin/analyzerResults/flow/flow"+str(index)+".xml")
        index = index+1

    readyToProcess.close()


main()
