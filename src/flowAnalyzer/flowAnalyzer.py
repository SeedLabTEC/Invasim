
from tkinter import filedialog
from tkinter import *
import os
from shutil import copyfile
from xml.etree import ElementTree as ET
import xml.dom.minidom
import numpy as np

cutBlockValues = ["beq", "bne", "bnez", "bge", "blt", "ble", "j", "jr",
                  "jal", "jalr", "call"]  # instructions used to divide blocks

"""!
    Function used to find an register of one instruction on other instrucctions on list, check the use of the register on the other subprocess.

    @param reg String: name of the register to search
    @param listIn list: List where we need to search

    @return Return List with the positions where was found the register
"""
def findRegOnList(reg, listIn):  # 
    indexList = []
    index = -1

    for listInDep in listIn:  # check in every list
        index = index+1
        for elInst in listInDep:  # check every instuction
            # check if isn't a intersection
            if(not elInst.split()[0] in cutBlockValues): # check if is on the list of instructions to 
                if(reg in elInst):  # check if is in instruction to divide blocks
                    indexList.append(index) # to return the positions where was founded
                    break

    return indexList

"""!
    Function used to find dependencies between lists of instructions

    @param listIn list: Contains the lists where we need to search dependencies

    @return Return Ordered list with the groups of instructions
"""
def dependenciesSearchDeep(listIn):
    controlWhile = True # control the principal loop of search dependencies on the groups
    control = 0 # variable used to know when is on a loop on the logic
    joinList = [] # list created by logic with positions with dependencies

    while(controlWhile):
        joinList = [] # restart to empty the list
        posRev = 0 # variable to know the position of group that is checking
        for subList in listIn: # start to search on the sub groups
            tempJoin = [] # restart to empty the list
            for inst in subList: # start to search on the instructions 
                reg = inst.split()[1].split(",") # extract the register where the instruction could write
                if(len(reg) >= 2): # check if the instruction has more of 2 registers
                        # anything that could change register is necessary to search dependencies
                    if(("addi" in inst) or ("li" in inst) or ("mv" in inst) or ("lw" in inst) or ("mul" in inst) or ("slli" in inst) or ("srli" in inst)):
                        res = findRegOnList(reg[0], listIn) # go to search other blocks
                        if(posRev in res): # if there is on the same group remove
                            res.remove(posRev)
                        tempJoin = tempJoin + res # add to the list with positions to merge groups

            posRev = posRev+1
            joinList.append(sorted(list(set(tempJoin)))) # order the list with positions

        posJ = 0 # variable to control position on principal list of groups of instructions
        
        for eleJoin in joinList: # start to run over the list of blocks with dependencies
            controlWhile = False 
            if(posJ+1 < len(joinList)): # check that posJ is less than lenght of joinList to avoid out of range 
                if((posJ-1) in eleJoin): # check if is on the list related with dependent groups
                    # merge blocks with dependencies and break to re-check
                    listIn[posJ-1] = listIn[posJ-1] + listIn[posJ] # join with the group
                    listIn.pop(posJ) # delete from the group
                    controlWhile = True
                    break
                if((posJ+1) in eleJoin):
                    # merge blocks with dependencies and break to re-check
                    listIn[posJ] = listIn[posJ] + listIn[posJ+1] # join with the group
                    listIn.pop(posJ+1) # delete from the group
                    controlWhile = True
                    break
                if(posJ in joinList[posJ+1]):
                    # merge blocks with dependencies and break to re-check
                    listIn[posJ] = listIn[posJ] + listIn[posJ+1] # join with the group
                    listIn.pop(posJ+1) # delete from the group
                    controlWhile = True
                    break
                if(eleJoin != []):
                    # control if there 
                    controlWhile = True
                    print("CHECK THIS GROUP")
            else:
                controlWhile = False
            posJ = posJ + 1 #other case append to the actual grouphere
            print("OUT OF CONTROL")
            controlWhile = False

        control = control + 1

    for eleJoin in joinList: # only check if there are some group empty
        if(eleJoin != []):
            print("CHECK")

    return listIn

"""!
    Function used to find direct dependencies, like registers on next instructions

    @param instructionList list: Contains the lists where we need to search dependencies

    @return Return Ordered list separated on groups with the division and passed for the function called dependenciesSearchDeep
"""
def dependenciesSearch(instructionList):
    posInst = 0
    returnListDivided = []
    tempList = []
    for val in instructionList: # check all the instructions on the incoming list
        if(val == "nop"): # check if is a nop instruction and change if true
            val = "addi	zero,zero,0"

        temp = val.split() # split the instruction 
        if(posInst+1 < len(instructionList)): # check if you have not exceeded the total amount of instructions
            nextVal = instructionList[posInst+1] # get the next instruction
            if(nextVal == "nop"): # if the next instruction is an nop remplace with add 0
                nextVal = "addi	zero,zero,0"
            else: # else set next instruction 
                nextVal = instructionList[posInst+1].split()[1] 
            # delete the characters "(" and ")", after that split by ","  
            nextVal = nextVal.replace("(", ",").replace(")", "")
            nextVal = nextVal.split(',')
            temp[1] = temp[1].replace("(", ",").replace(")", "")
            tempList.append(val)
            # split the instruction and check the type, if it is sw or lw and the next instruction is also, we can divide on a group
            checkReg = temp[1].split(",")
            if(((temp[0] == 'sw') or (temp[0] == 'lw') ) and (temp[0] == instructionList[posInst+1].split()[0])):
                returnListDivided.append(tempList)
                tempList = []
            #elif( (temp[0] == 'lw') and (temp[0] == instructionList[posInst+1].split()[0])):
            #    returnListDivided.append(tempList)
            #    tempList = []
            else:
                if((temp[0] == 'sw') and (instructionList[posInst+1].split()[0] == 'lw') and (checkReg[0] != nextVal[0])): # check if next val dont have the register where we could read or write
                    returnListDivided.append(tempList)
                    tempList = []

                elif(len(checkReg) == 2): # check on the sublist of the string the quantity of values, case where actual instruction has 2 registers
                    if(len(nextVal) == 3): # if the next instruction could be divided on 3, we need to check these 3 to search dependencies
                        if((checkReg[0] != nextVal[0]) and (checkReg[0] != nextVal[1]) and (checkReg[0] != nextVal[2])): # no dependencies, create new group
                            returnListDivided.append(tempList)
                            tempList = []

                    elif(len(nextVal) == 2): # if the next instruction could be divided on 2, we need to check these 2 to search dependencies
                        if((checkReg[0] != nextVal[0]) and (checkReg[0] != nextVal[1])): # no dependencies, create new group
                            returnListDivided.append(tempList)
                            tempList = []

                elif(len(checkReg) == 3): # check on the sublist of the string the quantity of values, case where actual instruction has 2 registers
                    if(len(nextVal) == 3): # if the next instruction could be divided on 3, we need to check these 3 to search dependencies
                        if((checkReg[0] != nextVal[0]) and (checkReg[0] != nextVal[1]) and (checkReg[0] != nextVal[2])):
                            returnListDivided.append(tempList)
                            tempList = []

                    elif(len(nextVal) == 2): # if the next instruction could be divided on 2, we need to check these 2 to search dependencies
                        if((checkReg[0] != nextVal[0]) and (checkReg[0] != nextVal[1])): # no dependencies, create new group
                            returnListDivided.append(tempList)
                            tempList = []
                    else: # other case only create new group
                        tempList.append(instructionList[posInst+1])
                        returnListDivided.append(tempList)
                        tempList = []
        else: # other case append to the actual group
            tempList.append(val)

        posInst = posInst + 1

    if(len(tempList) != 0): # check if the last group is on the temporal list, if it is create new group
        returnListDivided.append(tempList)
        tempList = []

    if((len(returnListDivided[-1]) == 1) and (returnListDivided[-1][0].split()[0] in cutBlockValues) and (len(returnListDivided) !=1) ): # if last group only have one instruction of type intersection, pop that
        returnListDivided.pop()

    return dependenciesSearchDeep(returnListDivided)

"""!
    Function used to create the direction of instructions on decimal

    @param val number: Value on decimal to change
    @param nbits number: Quantity of bits of the base (64 or 32)

    @return Return decimal number of address
"""
def toDir(val, nbits):
    if(val<0):
        a = ((val + (1 << nbits)) % (1 << nbits)) # desplace to extract sign
        b = (bin(a)[22:]) # extract the number on decimal with 12 bits
        return int(b, 2) # return the decimal
    else:
        return int(bin((val + (1 << nbits)) % (1 << nbits)),2)


"""!
    Function used to create the direction of instructions on decimal

    @param blocksRootFirstAnalisis object: XML object root where put 
    @param instructionListIn list: The list of instructions to use on the block
    @param idBlock string: The name of the block
    @param actualLine number: Line where the block finished

    @return Return Void
"""
def blocksCreation(blocksRootFirstAnalisis, instructionListIn, idBlock, actualLine):
    subprocess = dependenciesSearch(instructionListIn) # call to create the sub groups of instructions

    block = ET.SubElement(blocksRootFirstAnalisis, "block") # block child of root
    block.set("id", idBlock) # set id of block
    indexSub = 0 # number of subprocess

    for instructionList in subprocess: # iterate by groups of instructions to create the structure on the xml 

        subIlet = ET.SubElement(block, "subp") # subprocess tag where put instructions
        subIlet.set("id", str(indexSub)) # id with the number of subprocess
        posInst = 0 # number of instruction on subprocess

        for val in instructionList:  
            if((posInst == len(instructionList)-1) and (val.split()[0] in cutBlockValues)): # if is an intersection instruction, there are a special structure
                instDo = val.split()
                # create xml objects
                intersection = ET.SubElement(subIlet, "intersection")
                instruction = ET.SubElement(intersection, "instruction")
                condition1 = ET.SubElement(intersection, "condition1")
                condition2 = ET.SubElement(intersection, "condition2")
                probability = ET.SubElement(intersection, "probability")

                instruction.text = val  # set instruction

                if(instDo[0] == "call"): # always take calls
                    condition1.text = instDo[1]
                    condition2.text = str(actualLine)
                    probability.text = str(1)
                    # jr	ra
                elif(instDo[0] == "jr"): # always take jr but keep line where the block finish
                    condition1.text = "N/A"
                    condition2.text = str(actualLine)
                    probability.text = str(1)
                
                # if is an branch we need to calculate the probability of take
                elif((instDo[0] == "beq") or (instDo[0] == "bnez") or (instDo[0] == "bge") or (instDo[0] == "blt") or (instDo[0] == "ble") or (instDo[0] == "bne")):
                    condition1.text = instDo[-1].split(",")[-1]
                    condition2.text = str(actualLine)
                    probability.text = str(np.random.binomial(1, 0.5, 1)[0])
                else: # other case only take
                    condition1.text = instDo[1]
                    condition2.text = str(actualLine)
                    probability.text = str(1)
            else: # normal instruction
                if( "-" in val): # check the address number to calculate decimal direction of offset 
                    fv = val.find("-")
                    offsetDir = toDir(int(val[fv:fv+3]), 32)-4064
                    tempVal = val[0:fv] + str(offsetDir) + val[fv+3:]
                    val = tempVal

                instDo = val.split()
                instruction = ET.SubElement(subIlet, "instruction")

                instruction.text = instDo[0]+","+instDo[1]
            posInst = posInst + 1

        indexSub = indexSub + 1


"""!
    Function used to create the direction of instructions on decimal

    @param readFile string: Path to read the file to create the flow
    @param writeFile string: Path to write the file with only blocks

    @return Return void
"""
def crateBlocks(readFile, writeFile):
    blocksRootFirstAnalisis = ET.Element('Blocks')  # root of blocks flow

    readLine = 0 # position of line read
    f = open(readFile, "r+") # open file to read
    line = f.readline() # get firts line
    blockLines = 0  # keep lines of respective block
    blocksID = "" # keep id of block if exist
    temporalBlock = [] # list where put the instructions of fundamental group

    while line: # iterate by lines
        if(line.startswith('	.') == False):   # if isn't an annotation
            if(any(s in line for s in cutBlockValues)):  # if is an intersection instruction we need to create the block of instructions

                # delete before and after spaces
                temporalBlock.append(line.rstrip().lstrip())

                # Logic of block ID to save on flow
                if(blocksID != ""): # if there are an tag taken
                    blocksCreation(blocksRootFirstAnalisis,
                                   temporalBlock, blocksID, readLine)
                else: # if the id es empty keep tag with line where finish
                    blocksCreation(blocksRootFirstAnalisis, temporalBlock, "Line" +
                                   str(readLine-blockLines+1), readLine)

                # clear variables
                blockLines = 0
                temporalBlock = [] # clean temp list
                blocksID = "" 

            elif(line.startswith('	') == False):   # if is a tag an isn't an instruction
                if(temporalBlock != []): # if the actual block isn't empty we need to create a block
                    if(blocksID != ""): # check if there are some tag of block
                        blocksCreation(blocksRootFirstAnalisis,
                                               temporalBlock, blocksID, readLine)
                    else: # keep id tag of block with line number
                        blocksCreation(blocksRootFirstAnalisis, temporalBlock, "Line" +
                                               str(readLine-blockLines+1), readLine)
        
                blocksID = line.        replace(":", "").rstrip()
                # clear variables
                blockLines = 0
                temporalBlock = []

            else:  # different instruction only keep on temporal list 
                blockLines = blockLines + 1
                temporalBlock.append(line.rstrip().lstrip())

            readLine = readLine + 1

        line = f.readline()  # next line

    if(temporalBlock != []): # when finished, check if there are a block on list
        blocksCreation(blocksRootFirstAnalisis,
                       temporalBlock, "EndBlock", readLine)
        # clear variables
        blockLines = 0
        temporalBlock = []

    fw = open(writeFile, "w+") # open file to keep the blocks
    show = xml.dom.minidom.parseString(
        ET.tostring(blocksRootFirstAnalisis)).toprettyxml() # pretty XML
    fw.write(show)

    fw.close()
    f.close()

# Get position of name tag on xml

"""!
    Function used to find a ID name of node on xml

    @param xml xml: XML to search the name 
    @param name string: Name of if to search

    @return Return Position of the found tag
"""
def findIdOnXml(xml, name):
    index = 0
    for child in xml: # go over the xml
        if(child.get("id") == name):
            return index
        index = index + 1


"""!
    Function used to get position of name tag on xml and create a flag to known if is used

    @param xml xml: XML to search the XML tags

    @return Return List of tags and positions
"""
def listBlocks(xml):
    indexList = []
    for child in xml:
        indexList.append([child.get("id"), 0])
    return indexList

"""!
    Function used to search a block that is not used 

    @param blocks list: All the blocks that we need check

    @return Return Number of position 
"""
def checkPendingBlocks(blocks):
    index = 0
    for ele in blocks: # run over blocks
        if(ele[1] != 1): # check if the item has not been used
            return index
        index = index + 1
    return -1
# create the logic flow


"""!
    Function used to create the logic of flow

    @param readFile string: Path to read the file to create the flow
    @param writeFile string: Path to write the file with only blocks

    @return Return void
"""
def createLogicFlow(readFile, writeFile):
    tree = ET.parse(readFile)  # get xml from file
    root = tree.getroot()  # create the object

    orderFlowBlocks = []  # keep order blocks
    onFlowListBlocks = listBlocks(root)  # get list of blocks to process

    tempBlock = root[findIdOnXml(root, "main")]  # get xml of block main

    breakAt = len(onFlowListBlocks)+3  # to prevent infinite while

    breakCount = 0
    while(breakCount < breakAt):  # search on all blocks
        if(checkPendingBlocks(onFlowListBlocks) == -1): # if are not pending block 
            break
        if(onFlowListBlocks[findIdOnXml(root, tempBlock.get("id"))][1] != 1):
            # read block on list and check if was done
            onFlowListBlocks[findIdOnXml(root, tempBlock.get("id"))][1] = 1
            # main is the firts block that we read
            orderFlowBlocks.append(tempBlock)

            # search last instruction of block to break the while            
            if(tempBlock[-1][-1].tag != "intersection"):
                # check if finished all or there are something pending
                if(checkPendingBlocks(onFlowListBlocks) != -1):
                    tempBlock = root[checkPendingBlocks(onFlowListBlocks)]
                else:
                    break
            else:
                # if is necessary return to next block of called block
                if(tempBlock[-1][-1][1].text == "N/A"):
                    # get the next block of which where was called
                    if((tempBlock.get("id") != "main")): # if different of main block
                        if((findIdOnXml(root, orderFlowBlocks[-2].get("id"))+1) >= len(root)): # finish if there are not more blocks and is on the last
                            break
                        else:
                            tempBlock = root[findIdOnXml(
                                root, orderFlowBlocks[-2].get("id"))+1] # call the next block of the ordered list before the actual
                    else: # if is main block search the next
                        tempBlock = root[findIdOnXml(
                            root, tempBlock[-1][-1][0].text.split()[-1])] # else search the next block of actual
                else: # if is a normal instruction 
                    instDo = tempBlock[-1][-1][0].text.split() 
                    # check if is an branch instruction
                    if((instDo[0] == "beq") or (instDo[0] == "bnez") or (instDo[0] == "bge") or (instDo[0] == "blt") or (instDo[0] == "ble") or (instDo[0] == "bne")):
                        # change intersection value to known
                        orderFlowBlocks[-1][-1][-1][2].text = root[findIdOnXml(
                            root, orderFlowBlocks[-1].get("id"))+1].get("id")

                        if(tempBlock[-1][-1][-1].text == "1"):  # if the branch is taken
                            tempBlock = root[findIdOnXml(
                                root, tempBlock[-1][-1][1].text)]  # call next block
                        else:
                            # get the next block of which where was called
                            # change to check the block didn't taken
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
        stringReadyKeep = stringReadyKeep + ET.tostring(bl, encoding='unicode') # create a string of xml

    readyToProcess = open(writeFile, "w+")
    stringReadyKeep = "<?xml version='1.0' ?>\n<Blocks>\n"+stringReadyKeep+"\n</Blocks>" # create xml header
    readyToProcess.write(stringReadyKeep) # write to flow file
    readyToProcess.close()


"""!
    Main function with files selection 

    @return Return 
"""
def main():
    # create the dirs
    os.makedirs("./bin/analyzerResults/blocks", exist_ok=True)
    os.makedirs("./bin/analyzerResults/flow", exist_ok=True)

    root = Tk() 
    # call the window to use on selection of files
    filenames =  filedialog.askopenfilenames(initialdir = filedialog.askdirectory(),title = "Select files with ctrl",filetypes = (("Assembler files","*.s"), ("C files","*.c"), ("XML files","*.xml"), ("all files","*.*")), multiple=True)
    index = 0

    readyToProcess = open("./bin/analyzerResults/files.txt", "w+") # create the file where put paths to created files of flow
    for ele in filenames: # run over the files selected
        if(ele.endswith('.c')): # if is an c file
            os.environ["PATH"] = "/opt/riscv32/bin/:$PATH" # call the compiler on environment 
            eleo = ele[:-1] 
            eleo = eleo + "s"
            os.system("riscv32-unknown-elf-gcc -O0 -S "+ele +" -o "+eleo ) # compile the file to generate assembler files
            ele = eleo

            # call the logic of generate flow
            crateBlocks(ele, "./bin/analyzerResults/blocks/blocks" + str(index)+".xml")
            createLogicFlow("./bin/analyzerResults/blocks/blocks"+str(index) +".xml", "./bin/analyzerResults/flow/flow"+str(index)+".xml")
            readyToProcess.write("./bin/analyzerResults/flow/flow"+str(index)+".xml"+"\n")
    
        elif(ele.endswith('.s')): # if is an s file
            # call the logic of generate flow
            crateBlocks(ele, "./bin/analyzerResults/blocks/blocks" + str(index)+".xml")
            createLogicFlow("./bin/analyzerResults/blocks/blocks"+str(index) +".xml", "./bin/analyzerResults/flow/flow"+str(index)+".xml")
            readyToProcess.write("./bin/analyzerResults/flow/flow"+str(index)+".xml"+"\n")
        
        elif(ele.endswith('.xml')): # if is an xml file
            # only copy the file and change the name
            copyfile(ele, "./bin/analyzerResults/flow/flow"+str(index)+".xml")
            readyToProcess.write("./bin/analyzerResults/flow/flow"+str(index)+".xml"+"\n")
        
        else:
            print("Can't load this type of file: "+ele)
            index = index-1    

        index = index+1 # next file

    readyToProcess.close()

main()
