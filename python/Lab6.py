
import random
import matplotlib.pyplot as plt

class BST:
    def __init__(self, value):
        self.value = value
        self.left = None 
        self.right = None

    def insert(self, value):
        '''
        node.insert(5) is the same as BST.insert(node, 5)
        We use this when recursively calling, e.g. self.left.insert
        '''
        if value < self.value:
            if self.left == None:
                self.left = BST(value)
            else:
                self.left.insert(value)
        else:
            if self.right == None:
                self.right = BST(value)
            else:
                self.right.insert(value)

    def __repr__(self):
        '''The string representation of a node.
        Here, we convert the value of the node to a string and make that
        the representation.
        We can now use
        a = Node(4)
        print(a) # prints 4
        '''
        return str(self.value)

# Problem 1
# Draw (manually) the binary tree rooted in a.

'''
                        4
                     /     \ 
                   2        5
                  / \      / \ 
                     3       10
                            /  \ 
                                15

'''
                


# Problem 2
# Write code to find the height of a Binary Search Tree

def tree_height(node):
    if node is None:
        return -1
    else:
        left_height = tree_height(node.left)
        right_height = tree_height(node.right)
        if left_height > right_height:
            return left_height + 1
        else:
            return right_height + 1
    


# Problem 3

# Write code to print out the nodes of the BST using
# Breadth-First Search. How would you get the Breadth-First Traversal
# from the tree you've drawn?
# (Modify the BFS function from lecture for this problem)

def BFS_tree(node):
    q = [node]
    while len(q) > 0:
        cur = q.pop(0)
        print(cur.value)    
        if cur.left != None:
            q.append(cur.left)
        if cur.right != None:
            q.append(cur.right)


# Problem 4

# Empirically investigate the relationship between the number of nodes in the
# tree and the height of the tree when inserting nodes with values generated
# using random.random()

def make_random_tree(n_nodes):
    '''Make a tree with n_nodes nodes by inserting nodes with values
    drawn using random.random()
    '''
    root = BST(random.random())
    array = []
    for i in range(n_nodes - 1):
        n = random.random()
        if n not in array:
            root.insert(n)
            array.append(n)
        else:
            i -= 1
    return root

def height_random_tree(n_nodes):
    '''Generate a random tree with n_nodes nodes, and return its height'''
    tree = make_random_tree(n_nodes)
    return tree_height(tree)

def make_data(max_nodes):
    '''Make two lists representing the empirical relationship between
    the number of nodes in a random tree and the height of the tree.
    Generate N_TREES = 40 trees with each of
    n_nodes = 5 , int(1.2*5), int(1.2^2*5).....

    return n (a list of values of n_nodes) and h (a list of heights)
    '''
    N_TREES = 40
    n_nodes = 5
    count = 0
    n = []
    h = []
    avg = 0
    while n_nodes < max_nodes:
        count += 1
        for i in range(N_TREES):
            avg += height_random_tree(n_nodes)
        avg = avg/N_TREES 
        h.append(avg)
        n.append(n_nodes)
        n_nodes = int(1.2**count * 5)
    return n, h

if __name__ == '__main__':
    a = BST(4)
    a.insert(2)
    a.insert(5)
    a.insert(10)
    a.insert(3)
    a.insert(15)

    #Problem 2
    tree_height(a)

    #Problem 3
    BFS_tree(a)

    #Problem 4
    b = make_random_tree(6)
    #BFS_tree(b)
    print(height_random_tree(5))
    n, h = make_data(10000)
    plt.scatter(n, h)
    plt.show()
    # plt.savefig("trees.png") can save the data to disk