from datetime import date

#Class creator function
#   name: class name
def class_creator(name):
    #Initialization
    today = date.today()
    class_h = open("include/" + name + ".h","w+")
    class_s = open("src/"+ name + ".cpp", "w+")

    #Header
    class_h.write("/**\n")
    class_h.write("* @file " + name + ".h\n")
    class_h.write("* @brief Description\n")
    class_h.write("* @author Dennis Porras Barrantes\n")
    class_h.write("* @date " + today.strftime("%d/%m/%y\n"))
    class_h.write("**/\n\n")

    class_s.write("/**\n")
    class_s.write("* @file " + name + ".cpp\n")
    class_s.write("* @brief Description\n")
    class_s.write("* @author Dennis Porras Barrantes\n")
    class_s.write("* @date " + today.strftime("%d/%m/%y\n"))
    class_s.write("**/\n\n")

    #Declaration
    class_h.write("#ifndef INCLUDE_" + name.upper() + "_H_\n")
    class_h.write("#define INCLUDE_" + name.upper() + "_H_\n\n")
    class_h.write("#include \"Debug.h\"")
    class_h.write("\n\n")
    class_h.write("class " + name + " {\n")
    class_h.write("public: \n")
    class_h.write("\t" + name + "();\n\n")
    class_h.write("private:\n\n")
    class_h.write("};\n\n")
    class_h.write("#endif")

    class_s.write("#include \"../include/" + name + ".h\"\n\n")
    class_s.write("/**\n")
    class_s.write("* @brief Constructor\n")
    class_s.write("**/\n")
    class_s.write(name + "::" + name + "(){\n\n")
    class_s.write("}")
    
    #Close files
    class_h.close()
    class_s.close()

#Get class name
class_n = input("Class name: ")

#Create class
class_creator(class_n)