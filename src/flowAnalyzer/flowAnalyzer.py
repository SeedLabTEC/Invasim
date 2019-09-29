#from xml.etree.ElementTree import Element, SubElement, Comment, tostring
from xml.etree import ElementTree as ET
import xml.dom.minidom
import numpy as np

blocksRootFirstAnalisis = ET.Element('Blocks')  # root of blocks flow
cutBlockValues = ["beq", "bnez", "bge", "blt", "j", "jr",
                  "jal", "jalr", "call"]  # BNEZ-J-JR-JAL-JALR-EBREAK


def blockIletsSearch():
    print("Deps")


def blocksCreation(instructionList, idBlock, actualLine):
    block = ET.SubElement(blocksRootFirstAnalisis, "block")
    block.set("id", idBlock)

    posInst = 0
    for val in instructionList:
        if((posInst == len(instructionList)-1) and (val.split()[0] in cutBlockValues)):
            instDo = val.split()
            # create xml objects
            intersection = ET.SubElement(block, "intersection")
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
            elif((instDo[0] == "beq") or (instDo[0] == "bnez") or (instDo[0] == "bge")):
                condition1.text = instDo[-1].split(",")[-1]
                condition2.text = str(actualLine)
                probability.text = str(np.random.binomial(1, 0.5, 1)[0])
            else:
                condition1.text = "N/A"
                condition2.text = str(actualLine)
                probability.text = str(1)
        else:
            instruction = ET.SubElement(block, "instruction")
            instruction.text = val
        posInst = posInst + 1


def crateBlocks(readFile, writeFile):

    readLine = 0

    f = open(readFile, "r+")
    line = f.readline()

    blockLines = 0  # keep lines of respective block

    blocksID = ""
    temporalBlock = []

    while line:
        if(line.startswith('	.') == False):   # if isn't an annotation

            if(any(s in line for s in cutBlockValues)):  # if is an intersection instruction
                lineList = line.split()

                # delete before and after spaces
                temporalBlock.append(line.rstrip().lstrip())

                # Logic of block ID to save on flow
                if(blocksID != ""):
                    blocksCreation(temporalBlock, blocksID, readLine)
                else:
                    blocksCreation(temporalBlock, "Line" +
                                   str(readLine-blockLines+1), readLine)

                # clear variables
                blockLines = 0
                temporalBlock = []
                blocksID = ""

            elif(line.startswith('	') == False):   # if is a tag an isn't an instruction
                if(temporalBlock != []):
                    blocksCreation(temporalBlock, "Line" +
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
        blocksCreation(temporalBlock, "EndBlock", readLine)
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

# create the logic flow


def createLogicFlow(readFile, writeFile):
    tree = ET.parse(readFile)  # get xml from file
    root = tree.getroot()  # create the object

    orderFlowBlocks = []  # keep order blocks
    onFlowListBlocks = listBlocks(root)  # get list of blocks to process

    tempBlock = root[findIdOnXml(root, "main")]  # get xml of block main

    breakAt = len(onFlowListBlocks)+3  # to prevent infinite while

    breakCount = 0
    while(breakCount < breakAt):  # search on all blocks

        # read block on list and check if was done
        onFlowListBlocks[findIdOnXml(root, tempBlock.get("id"))][1] = 1
        # main is the firts block that we read
        orderFlowBlocks.append(tempBlock)

        # search last instruction of block to break the while
        if(tempBlock[-1].tag != "intersection"):
            print("Flow finished")
            break
        else:
            # if is necessary return to next block of called block
            if(tempBlock[-1][1].text == "N/A"):
                # get the next block of which where was called
                tempBlock = root[findIdOnXml(
                    root, orderFlowBlocks[-2].get("id"))+1]
                # change intersection value to known
                orderFlowBlocks[-1][-1][1].text = tempBlock.get("id")
                # print(orderFlowBlocks[-1][-1][1].text)
            else:
                instDo = tempBlock[-1][0].text.split()
                if((instDo[0] == "beq") or (instDo[0] == "bnez") or (instDo[0] == "bge")):
                    # change intersection value to known
                    orderFlowBlocks[-1][-1][2].text = root[findIdOnXml(
                        root, orderFlowBlocks[-1].get("id"))+1].get("id")

                    if(tempBlock[-1][-1].text == "1"):  # if the branch is taken
                        # print("take branch")
                        tempBlock = root[findIdOnXml(
                            root, tempBlock[-1][1].text)]  # next block
                    else:
                        # get the next block of which where was called
                        tempBlock = root[findIdOnXml(
                            root, tempBlock[-1][2].text)]

                else:
                    tempBlock = root[findIdOnXml(
                        root, tempBlock[-1][1].text)]  # next block

        breakCount = breakCount + 1

    stringReadyKeep = ""
    for bl in orderFlowBlocks:
        stringReadyKeep = stringReadyKeep + ET.tostring(bl, encoding='unicode')

    readyToProcess = open(writeFile, "w+")
    stringReadyKeep = "<?xml version='1.0' ?>\n<Blocks>\n"+stringReadyKeep+"\n</Blocks>"
    readyToProcess.write(stringReadyKeep)
    readyToProcess.close()


crateBlocks("./codes/test.s", "./analyzerResults/blocks.xml")
createLogicFlow("./analyzerResults/blocks.xml", "./analyzerResults/flow.xml")
