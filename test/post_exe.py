import json

ilet_data = None
path_json = input("Insert path to ilets.json: ")

with open(path_json, "r") as file_data:
    ilet_data = json.load(file_data)

test_as01 = True
test_as02 = True
test_as03 = True


for ilet in ilet_data:
    op_invade = False
    op_infect = False
    op_retreat = False
    is_infected = False
    
    for operation in ilet["Operations"]:
        if operation["Operation"] == "Invade":
            op_invade = True
        if operation["Operation"] == "Infect":
            op_infect = True
            is_infected = operation["Parameter"] > 0
        if operation["Operation"] == "Retreat":
            op_retreat = True

    test_as01 = test_as01 and (op_invade and op_infect and op_retreat)
    test_as02 = test_as02 and op_retreat
    test_as03 = test_as03 and is_infected


print("Test[AS-01]:", ("PASS" if test_as01 else "FAIL"))
print("Test[AS-02]:", ("PASS" if test_as02 else "FAIL"))
print("Test[AS-03]:", ("PASS" if test_as03 else "FAIL"))
        