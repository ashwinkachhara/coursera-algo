import re
from operator import itemgetter

class Graph:

    def __init__(self, adjList = {}):
        self.adjList = adjList

    def shortestPath(self, source):
        global visited, processed, distance
        visited = [False for i in range(len(self.adjList)+1)]
        visited[source] = True
        visited[0] = None
        distance = [1000000 for i in range(len(self.adjList)+1)]
        distance[source] = 0
        processed = [source]

        newVert = source
        for edge in adjList[newVert]:
            distance[edge[0]] = edge[1]
        while len(processed) < len(self.adjList):
            minDist = 1000000
            v = source
            w = source
            nexthop = {a:distance[a] for a in adjList.keys()}
            for vert in processed:
                nexthop.pop(vert)
            w = min(nexthop,key=nexthop.get)
            print(w)
            processed.append(w)
            visited[w] = True
            for edge in adjList[w]:
                distance[edge[0]] = min(distance[edge[0]], distance[w]+edge[1])

def readData(filename):
    global adjList
    f = open(filename, 'r')

    for line in f:
        vert = re.split('\t|\r',line)
        vertex = int(vert[0])
        #print(vert)
        adjList[vertex] = []
        for edge in vert[1:-1]:
            if edge:
                dest, weight = edge.split(',')
                adjList[vertex].append((int(dest), int(weight)))


if __name__ == "__main__":
    adjList = {}
    readData('dijkstraData.txt')
    visited = []
    distance = []
    processed = []

    graph = Graph(adjList)
    graph.shortestPath(1)

    print str(distance[7])+","+str(distance[37])+","+str(distance[59])+","+str(distance[82])+","+str(distance[99])+","+str(distance[115])+","+str(distance[133])+","+str(distance[165])+","+str(distance[188])+","+str(distance[197])
