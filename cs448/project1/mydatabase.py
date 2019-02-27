#! /usr/bin/python

def insertDB(newline):
  print("insert");
  f = open("student.csv", "a+");
  f.write(newline+"\n");
  f.close()

def deleteDB(newline):
  with open("student.csv", "r") as file:
    db = file.readlines();
  newarray = [];
  for line in db:
    if newline != line:
      newarray.append(line);
      #print("line: " + line + "\nnewline: " + newline + "\n");
      #print(line==newline);
    #else:
      #print("TRUE------------------------");
  file.close();
  with open("student.csv", 'w') as file:
    file.writelines(newarray);
  file.close();

def updateDB(newline):
  newrow = raw_input("Enter updated row: \n");
  print("update");
  with open("student.csv", "r") as file:
    db = file.readlines();
  newarray = [];
  for line in db:
    if newline != line:
      newarray.append(line);
    else:
      newarray.append(newrow + "\n");
  file.close();
  with open("student.csv", 'w') as file:
    file.writelines(newarray);
  file.close();


def deleteEmpty():
  with open("student.csv", "r") as file:
    db = file.readlines();
  newarray = [];
  for line in db:
    if line != "\n":
      newarray.append(line);
  file.close();
  with open("student.csv", 'w') as file:
    file.writelines(newarray);
  file.close();


command = raw_input("Enter a Command(Insert, Delete, Update): \n");
newline = raw_input("Enter line to " + command + ":\n");

print("command: " + command);
print("newline: " + newline);
newline = newline+"\n";

options = {"insert" : insertDB,
           "delete" : deleteDB,
           "update" : updateDB
}

options[command](newline);

deleteEmpty();

f = open("student.csv", "r");
if f.mode == "r":
  contents = f.read();
  print contents;
f.close();

f = open("log.txt", "a+");
f.write("command: " + command + ", edited line: " + newline);
f.close();

