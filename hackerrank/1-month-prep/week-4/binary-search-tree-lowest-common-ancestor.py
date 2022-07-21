class Node:
    def __init__(self, info): 
        self.info = info  
        self.left = None  
        self.right = None 
        self.level = None 

    def __str__(self):
        return str(self.info) 

class BinarySearchTree:
    def __init__(self): 
        self.root = None

    def create(self, val):  
        if self.root == None:
            self.root = Node(val)
        else:
            current = self.root
         
            while True:
                if val < current.info:
                    if current.left:
                        current = current.left
                    else:
                        current.left = Node(val)
                        break
                elif val > current.info:
                    if current.right:
                        current = current.right
                    else:
                        current.right = Node(val)
                        break
                else:
                    break

from collections import deque

def find_path(root, target):
    if root is None:
        return []
    if root.info == target:
        return [root]
    left = find_path(root.left, target)
    if target in [node.info for node in left]:
        return [root] + left
    right = find_path(root.right, target)
    if target in [node.info for node in right]:
        return [root] + right
    return []
    
    
def lca(root, v1, v2):
    path1 = find_path(root, v1)
    path2 = find_path(root, v2)
    index = 0
    while (index < len(path1) and index < len(path2)) and (path1[index].info == path2[index].info):
        index += 1
    return path1[index-1]

tree = BinarySearchTree()