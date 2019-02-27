class State():
  def __init__(self, nodeID):
    # Unique ID of node that indicates the state in the state space diagram
    self.nodeID = nodeID

class GraphEdge:
  def __init__(self, node1, node2):
    # Node goes from node 1 to node 2 
    self.fromNodeID = node1
    self.toNodeID = node2

class StateSpaceGraph:
  def __init__(self):
    #dictionary consisting of astar info of nodes
    self.nodeInfo = {}
    #the adjacency list that indicates graph of state space diagram
    self.adjacencyList = {}
    #list with all unique node IDs
    self.nodes = []

  def addNode(self, nodeID):
    #create a new state node
    newNode = State(nodeID)
    #add the node to astar dictionary
    self.nodeInfo[nodeID] = {"parent":"","f":float('inf'),"g":float('inf'),"h":float('inf')}
    #add the new nodeID to list of all nodeIDs
    self.nodes.append(nodeID)

  def addEdge(self, fromNodeID, toNodeID):
    #if edge already exists, return
    if fromNodeID in self.adjacencyList:
      for nodeID in self.adjacencyList[fromNodeID]:#
        if toNodeID == nodeID:
          return
    #if didnt return, add new edge to the graph
    if fromNodeID in self.adjacencyList:
      self.adjacencyList[fromNodeID].append(toNodeID)
    else:
      self.adjacencyList[fromNodeID] = [toNodeID]

#returns the count of dogs in the starting end of the river
def startDog(nodeID):
  return 3-int(nodeID[0])

#returns the count of cats in the starting end of the river
def startCat(nodeID):
  return 3-int(nodeID[1])
  
#returns the count of dogs in the goal end of the river
def goalDog(nodeID):
  return nodeID[0]

#returns the count of cats in the goal end of the river
def goalCat(nodeID):
  return nodeID[1]

#returns where the boat is at the current state space
def boatLocation(nodeID):
  if nodeID[2] == '0':
    return "start"
  return "goal"

#tells if current move from node1 to node2 is valid
def validMove(node1, node2):
  if node1[2] == node2[2]:
    return False
  if node1[2] == '1':
    if goalDog(node1) < goalDog(node2):
      return False
    if goalCat(node1) < goalCat(node2):
      return False
  if node1[2] == '0':
    if goalDog(node1) > goalDog(node2):
      return False
    if goalCat(node1) > goalCat(node2):
      return False
  if (abs(startDog(node1)-startDog(node2)) + abs(startCat(node1)-startCat(node2))) > 2:
    return False
  return True

#calculates the h value for astar
def calcH(node1, node2): 
  return abs(int(node1[0])-int(node2[0]))+abs(int(node1[1])-int(node2[1]))

#calculates the path after astar values are calculated, and goal is reached
def tracePath(info, goal):
  path = []
  curr = goal
  #for node in info:
    #print node,info[node]
  while curr is not "000":
    path.insert(0,curr)
    curr = info[curr]["parent"]
  path.insert(0,curr)
  return path
  

#Used reference
#https://www.geeksforgeeks.org/a-search-algorithm/
def astar(nodeInfo, start, goal):
  closed = []
  opened = []
  graph = ssg.adjacencyList
  info = ssg.nodeInfo
  info[start]["f"] = 0.0
  info[start]["g"] = 0.0
  info[start]["h"] = 0.0
  info[start]["parent"] = start
  opened.insert(0,start)
  while opened:
    node = opened.pop(0)
    closed.append(node)

    for succ in graph[node]:
      #print succ
      if succ in goal:
        info[succ]["parent"] = node
        return tracePath(info, succ)
      elif succ not in closed:
        gNew = info[node]["g"] + 1
        hNew = calcH(node1, goal)
        fNew = gNew + hNew
        if info[succ]["f"] == float("inf") or info[succ]["f"] > fNew:
          opened.insert(0,succ)
          info[succ]["f"] = fNew
          info[succ]["g"] = gNew
          info[succ]["h"] = hNew
          info[succ]["parent"] = node

def printState(node):
  print "There are",startCat(node),"cats and",startDog(node),"dogs at the starting end of the river"
  print "There are",goalCat(node),"cats and",goalDog(node),"dogs at the goal end of the river"
  print "The boat is currenty at the",boatLocation(node)


def printAction(nodeFrom, node):
  bloc = "start"
  bdest = "goal"
  catsMoved = 0
  dogsMoved = 0
  if boatLocation(nodeFrom) == "goal":
    bloc = "goal"
    bdest = "start"
    catsMoved = abs(int(goalCat(nodeFrom)) - int(goalCat(node)))
    dogsMoved = abs(int(goalDog(nodeFrom)) - int(goalDog(node)))
  else:
    catsMoved = abs(int(startCat(nodeFrom)) - int(startCat(node)))
    dogsMoved = abs(int(startDog(nodeFrom)) - int(startDog(node)))
  print "Boat moved",catsMoved,"cats and",dogsMoved,"dogs from",bloc,"to",bdest+"."


def narrate(path):
  count = 0
  nodeFrom = "000"
  for node in path[1:]:
    if count == 0:
      print "initial state"
    else:
      print "state",count
    printState(nodeFrom)
    print "action",count
    printAction(nodeFrom, node)
    count+=1
    nodeFrom = node
  print "goal"
  printState(nodeFrom)

if __name__ == "__main__":
  ssg = StateSpaceGraph()
  #add all possible nodes to state space graph with nodeID
  ssg.addNode("000")
  ssg.addNode("100")
  ssg.addNode("200")
  ssg.addNode("300")
  ssg.addNode("110")
  ssg.addNode("220")
  ssg.addNode("330")
  ssg.addNode("230")
  ssg.addNode("130")
  ssg.addNode("030")
  ssg.addNode("001")
  ssg.addNode("101")
  ssg.addNode("201")
  ssg.addNode("301")
  ssg.addNode("111")
  ssg.addNode("221")
  ssg.addNode("331")
  ssg.addNode("231")
  ssg.addNode("131")
  ssg.addNode("031")

  #add all possible edges to state space graph
  for node1 in ssg.nodes:
    for node2 in ssg.nodes:
      if node1 != node2 and validMove(node1,node2):
        ssg.addEdge(node1, node2)
  """ 
  for l in ssg.adjacencyList:
    print l+":",
    for edge in ssg.adjacencyList[l]:
      print(edge),
    print
  """
  
  path =astar(ssg, "000", ["331","330"])
  narrate(path)
  print "The final path is: "
  print(path)
  
        

