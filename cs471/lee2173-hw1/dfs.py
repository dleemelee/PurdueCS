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
"""
Used reference
https://eddmann.com/posts/depth-first-search-and-breadth-first-search-in-python/
Returns the path from start to goal recursively
"""
def dfs(graph, node, end, visited):
  if node in end:
    return [node]
  if node in graph:
    for adj in graph[node]:
      if adj not in visited:
        visited.append(adj)
        path = dfs(graph, adj, end, visited)
        if path is not None:
          path.insert(0,node)
          return path

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
  path=dfs(ssg.adjacencyList, "000", ["331","330"], ["000"]) 
  narrate(path)
  print "The final path is: "
  print(path)
  
        

