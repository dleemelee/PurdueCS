#! /usr/bin/python

def insertDB(newline):
  print("insert");
  f = open("student.csv", "a+");
  f.write(newline);
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
    if newline+"\n" != line:
      newarray.append(line);
    else:
      newarray.append(newrow+"\n");
  file.close();
  with open("student.csv", 'w') as file:
    file.writelines(newarray);
  file.close();



command = raw_input("Enter a Command(Insert, Delete, Update): \n");
newline = raw_input("Enter line to " + command + ":\n");


print("command: " + command);
print("newline: " + newline);

options = {"insert" : insertDB,
           "delete" : deleteDB,
           "update" : updateDB
}

options[command](newline);

f = open("student.csv", "r");
if f.mode == "r":
  contents = f.read();
  print contents;
f.close();

f = open("log.txt", "a+");
f.write("command: " + command + ", line changed: " + newline);
f.close();
