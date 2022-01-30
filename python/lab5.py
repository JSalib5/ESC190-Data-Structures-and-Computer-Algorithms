import numpy as np

class Node:
    def __init__(self, name):
        self.name = name
        self.connections = []
        self.visited = False


def connect(node1, node2, weight):
    node1.connections.append({"node": node2, "weight": weight})
    node2.connections.append({"node": node1, "weight": weight})


def BFS(node):
    q = [node]
    node.visited = True
    while len(q) > 0:
        cur = q.pop(0) 
        print(cur.name)
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                con["node"].visited = True


################################################################################

def get_all_nodes(node):
    '''Return a list of the nodes in the graph of nodes connected to node
    (N.B., the nodes can be indirectly connected as well)'''
    nodes_list = []
    q = [node]
    node.visited = True
    while len(q) > 0:
        cur = q.pop(0)
        nodes_list.append(cur)
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                con["node"].visited = True
    unvisit_all(node)
    return nodes_list

    
################################################################################

def unvisit_all(node):
    '''Change all n.visited to False in all the nodes in the graph of nodes
    connected to node. Use BFS to find all the nodes'''
    q = [node]
    node.visited = False
    while len(q) > 0:
        cur = q.pop(0)
        for con in cur.connections:
            if con["node"].visited:
                q.append(con["node"])
                con["node"].visited = False


###############################################################################

def DFS_rec(node):
    '''Print out the names of all nodes connected to node using a
    recursive version of DFS'''
    node.visited = True
    print(node.name)
    for next_node in node.connections:
        if not next_node["node"].visited:
            DFS_rec(next_node["node"])


################################################################################

def DFS_nonrec(node):
    '''Print out the names of all nodes connected to node using a non-recursive
    version of DFS. Make it so that the nodes are printed in the same order
    as in DFS_rec'''
    #Vertices = get_all_nodes(node)
    #while cur_node in not Vertices["node"].visited:
    stack = []
    stack.append(node)
    node.visited = True
    while len(stack) > 0:
        cur = stack.pop()
        print(cur.name)
        cur.visited = True
        for con in cur.connections[::-1]:
            if not con["node"].visited:
                stack.append(con["node"])
                

################################################################################
#
# OPTIONAL
#

def min_distance(node, S):
    name = []
    dist = []
    for con in node.connections:
        if con["node"] in S:
            name.append(con["node"])
            dist.append(con["weight"])
    min_dist = min(dist)
    min_node = name[dist.index(min_dist)]
    return min_node, min_dist


def dijsktra_slowish(node):
    '''Implement Dijkstra's algorithm as discussed in class (i.e., you don't
    need to use a priority queue'''
    S = [node]
    d = {node.name: 0}
    unexplored = get_all_nodes(node)
    unexplored.remove(node)
    while len(unexplored) > 0:
        for u in unexplored:
            v, dist_v = min_distance(u, S)
            S.append(u)
            d[u.name] = d.get(v.name)+dist_v
            unexplored.remove(u)
    return d




if __name__ == '__main__':
    '''
    TO = Node("TO")
    NYC = Node("NYC")
    DC = Node("DC")
    CDMX = Node("CDMX")
    SF = Node("SF")
    '''

    #Making graph nodes
    Zero = Node("0")
    One = Node("1")
    Two = Node("2")
    Three = Node("3")
    Four = Node("4")
    Five = Node("5")
    Six = Node("6")
    Seven = Node("7")
    Eight = Node("8")
    Nine = Node("9")
    Ten = Node("10")


    #Connecting our graph
    connect(One, Two, 8)
    connect(Two, Three, 2)   
    connect(Three, Four, 6) 
    connect(One, Five, 3)
    connect(Five, Six, 1)
    connect(Five, Eight, 5)
    connect(Six, Seven, 4)
    connect(One, Nine, 4)
    connect(Nine, Ten, 3)
    '''
    #print(get_all_nodes(Five)) #true
    print("\nRecursive\n")
    DFS_rec(One)
    unvisit_all(One)
    print("\nNon-Recursive\n")
    DFS_nonrec(One)
    unvisit_all(One)
    print("\nBreadth\n")
    BFS(One)
    '''
    #print(get_all_nodes(One))
    print(dijsktra_slowish(Six))