import sys, copy, heapq

class DirectedGraph:

    def __init__(self, adjList = {}):
        self.adjList = adjList
        #print adjList

    def addEdge(self, fromV, toV):
        try:
            self.adjList[fromV].append(toV)
        except KeyError:
            self.adjList[fromV] = [toV]
        #print self.adjList

    def getNeighbors(self, vertex):
        return self.adjList.get(vertex)

    def getNumVerts(self):
        return len(self.adjList)

    def DFSLoop(self):
        visited = [False for i in range(myGraph.getNumVerts()+1)]
        ordering = {}
        for i in range(len(self.adjList),0,-1):
            if not visited[i]:
                self.DFS(i, visited, ordering)#, index)
        return ordering

    def DFS(self, vertex, visited, ordering):#, index):
        global index
        visited[vertex] = True

        for neighbor in self.adjList[vertex]:
            if not visited[neighbor]:
                self.DFS(neighbor, visited, ordering)#, index)

        ordering[index] = vertex
        index = index+1

    def DFSLoop2(self):
        global src
        visited = [False for i in range(len(DFS1ordering)+1)]

        for i in range(len(DFS1ordering),0,-1):
            if not visited[DFS1ordering.get(i)]:
                src = DFS1ordering.get(i)
                self.DFS2(DFS1ordering.get(i), visited)#, index)

    def DFS2(self, vertex, visited):
        global src
        visited[vertex] = True
        leaders[vertex] = src
        unvisitedNeighbors =  [x for x in self.adjList[vertex] if not visited[x]]
        if unvisitedNeighbors:
            for neighbor in unvisitedNeighbors:
                self.DFS2(neighbor, visited)

def findSCC(myGraph, myRevGraph):
    sys.setrecursionlimit(max(sys.getrecursionlimit(), myGraph.getNumVerts()))
    global DFS1ordering, leaders
    DFS1ordering = myRevGraph.DFSLoop()
    #print(DFS1ordering.get(875714))
    #print(len(DFS1ordering))
    print("DFS Loop 1 Executed")
    myGraph.DFSLoop2()
    print("DFS Loop 2 Executed")
    sLeaders = sorted(leaders.values())
    sccSizes = []
    strt = 0
    for i in range(0,N-1):
        if sLeaders[i]!=sLeaders[i+1]:
            sccSizes.append(i+1-strt)
            strt = i+1
    sccSizes.append(N-strt)
    print(sorted(sccSizes)[-5:])


f = open('SCC.txt', 'r')
N=875714

myGraph = DirectedGraph({k: [] for k in range(1,N+1)})#15+1)})#875714+1)})
myRevGraph = DirectedGraph({k: [] for k in range(1,N+1)})#15+1)})#875714+1)})

for line in f:
    edge = line.split(' ')
    myGraph.addEdge(int(edge[0]), int(edge[1]))
    myRevGraph.addEdge(int(edge[1]), int(edge[0]))
print ("Read Input")

index = 1
DFS1ordering = {}
leaders = {}

findSCC(myGraph, myRevGraph)
