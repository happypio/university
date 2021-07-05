ans = 0

def getHeight(node):
    if node.left is None and node.right is None:
        return 0

    height_left, height_right = 0, 0

    if node.left:
        height_left = getHeight(node.left)

    if node.right:
        height_right = getHeight(node.right)

    ans = max(ans, height_left + height_right + 2)

    return max(height_left + 1, height_right + 1)

getHeight(root)