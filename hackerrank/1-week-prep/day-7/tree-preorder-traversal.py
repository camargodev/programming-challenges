def pre_order(root):
    values = []
    pre_order_rec(root, values)
    print(" ".join(values))
    
def pre_order_rec(root, values):
    if root is None:
        return
    values.append(str(root.info))
    pre_order_rec(root.left, values)
    pre_order_rec(root.right, values)