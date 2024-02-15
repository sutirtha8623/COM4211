from search import Problem, hill_climbing
import random

class nQueens(Problem):

    def __init__(self, n, initial, goal=None):
        self.n = n
        self.initial = initial

    def actions(self, state):
        result = []
        queens = []
        for i in range(0, len(state)):
            queens.append((i, state[i]))
        for i in range(0, self.n):
            for j in range(0, self.n):
                if (i, j) not in queens:
                    result.append((i, j))

        return result
    
    def result(self, state, action):
        temp = [i for i in state]
        temp[action[0]] = action[1]
        return temp
    
    def goal_test(self, state):
        return (self.n * (self.n -1))//2 == self.value(state)
    
    def value(self, state):
        temp_board = [state[0]]
        attack_count = 0
        for i in range(0, len(state)-1):
            curr_col = len(temp_board)
            curr_row = state[curr_col]
            for j in temp_board:
                if j == curr_row:
                    attack_count = attack_count + 1
                
            for j in range(len(temp_board)):
                if temp_board[j] + (curr_col - j) == curr_row or temp_board[j] + (curr_col - j) == curr_row:
                    attack_count = attack_count + 1
                
            temp_board.append(curr_row)
        return (self.n * (self.n -1))//2 - attack_count


if __name__ == "__main__":
    
    n = int(input("Enter size of board: "))
    choices = [i for i in range(n)]
    init = []
    for i in range(len(choices)):
        init.append(random.choice(choices))

    nqueens = nQueens(n, init)
    hill_climbing(nqueens)
