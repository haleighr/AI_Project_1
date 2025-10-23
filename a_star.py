# A Star Implementation in Python
import matplotlib.pyplot as plt
import heapq
import math

class Node:
    def __init__(self, position, parent=None):
        self.position = position
        self.parent = parent
        self.g = 0  # Cost from start to current node
        self.h = 0  # Heuristic cost to goal
        self.f = 0  # Total cost

    def __eq__(self, other):
        return self.position == other.position

    def __lt__(self, other):
        return self.f < other.f
    
def a_star(start, goal, grid):
    open_list = []
    closed_list = set()

    start_node = Node(start)
    goal_node = Node(goal)

    heapq.heappush(open_list, start_node)

    while open_list:
        current_node = heapq.heappop(open_list)
        closed_list.add(current_node.position)

        if current_node == goal_node:
            path = []
            while current_node:
                path.append(current_node.position)
                current_node = current_node.parent
            return path[::-1]  # Return reversed path

        neighbors = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # 4 possible directions
        for new_position in neighbors:
            node_position = (current_node.position[0] + new_position[0], 
                             current_node.position[1] + new_position[1])

            if (node_position[0] > (len(grid) - 1) or 
                node_position[0] < 0 or 
                node_position[1] > (len(grid[len(grid)-1]) - 1) or 
                node_position[1] < 0):
                continue

            if grid[node_position[0]][node_position[1]] != 0:
                continue

            neighbor_node = Node(node_position, current_node)

            if neighbor_node.position in closed_list:
                continue

            neighbor_node.g = current_node.g + 1
            neighbor_node.h = ((neighbor_node.position[0] - goal_node.position[0]) ** 2) + \
                              ((neighbor_node.position[1] - goal_node.position[1]) ** 2)
            neighbor_node.f = neighbor_node.g + neighbor_node.h
            if add_to_open(open_list, neighbor_node):
                heapq.heappush(open_list, neighbor_node)
    return None  # No path found

def add_to_open(open_list, neighbor_node):
    for open_node in open_list:
        if neighbor_node == open_node and neighbor_node.g >= open_node.g:
            return False
    return True

# Example usage
if __name__ == "__main__":
    grid = [
        [0, 0, 0, 0, 0],
        [0, 1, 1, 1, 0],
        [0, 0, 0, 1, 0],
        [0, 1, 0, 0, 0],
        [0, 0, 0, 1, 0]
    ]
    start = (0, 0)
    goal = (4, 4)
    path = a_star(start, goal, grid)
    print("Path from start to goal:", path)
    
    