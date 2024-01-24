import sys

def is_valid(s):
    if s[1] > s[0] or s[0] not in range(0, 4) or s[1] not in range(0, 4):
        return False
    return True

def perform_action(state, action, signum):
    if signum == '+':
        return (state[0]+action[0], state[1]+action[1], state[2]+action[2])
    else:
        return (state[0]-action[0], state[1]-action[1], state[2]-action[2])
    
def check_goal(state):
    return (state == (0, 0, 0))

action_set = [(1, 0, 1), (2, 0, 1), (0, 1, 1), (0, 2, 1), (1, 1, 1)]

def BFS(init):
    if check_goal(init):
        print("Found goal!")
        return
    frontier = [init]
    explored = []
    curr_sign = '-'
    while(True):
        if not frontier:
            print("Failure!")
            return
        curr = frontier.pop()
        explored.append(curr)
        for i in action_set:
            child = perform_action(curr, i, curr_sign)
            if not is_valid(child):
                continue
            print(f"Exploring {child}\n")
            if child not in explored and child not in frontier:
                if check_goal(child):
                    print("Found goal!")
                    return
                frontier.append(child)
        curr_sign = '+' if curr_sign == '-' else '-'


def main():
    BFS((3, 3, 1))

main()