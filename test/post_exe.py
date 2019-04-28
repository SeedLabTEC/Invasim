import json

ilet_data = None
path_json = input("Insert path to ilets.json: ")

with open(path_json, "r") as file_data:
    ilet_data = json.load(file_data)

test_as01 = False
test_as02 = False
test_as03 = False


for ilet in ilet_data:
    for operation in ilet["Operations"]:
        if operation["Operation"] == "Invade":
            test_as01 = True
        if operation["Operation"] == "Infect":
            test_as01 = True
            test_as03 = operation["Parameter"] > 0
        if operation["Operation"] == "Retreat":
            test_as01 = True
            test_as02 = True


print("Test[AS-01]:", ("PASS" if test_as01 else "FAIL"))
print("Test[AS-02]:", ("PASS" if test_as02 else "FAIL"))
print("Test[AS-03]:", ("PASS" if test_as03 else "FAIL"))
        