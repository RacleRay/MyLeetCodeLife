from typing import NewType, List
from enum import Enum
from abc import ABC, abstractmethod

Move = NewType('Move', int)

class Piece: ...
class Board(ABC): ...

class Piece:
    @property
    def opposite(self) -> Piece:
        raise NotImplementedError("Should be implemented by subclasses.")


class Board(ABC):
    @property
    @abstractmethod
    def turn(self) -> Piece:
        ...

    @abstractmethod
    def move(self, location: Move) -> Board:
        ...

    @property
    @abstractmethod
    def legal_moves(self) -> List[Move]:
        ...

    @property
    @abstractmethod
    def is_win(self) -> bool:
        ...

    @property
    def is_draw(self) -> bool:
        return (not self.is_win) and (len(self.legal_moves) == 0)

    @abstractmethod
    def evaluate(self, player: Piece) -> float:
        ...


"""Minimax"""
# Find the best possible outcome for original player
def minimax(board: Board, maximizing: bool, original_player: Piece, max_depth: int = 8) -> float:
    # Base case – terminal position or maximum depth reached
    if board.is_win or board.is_draw or max_depth == 0:
        return board.evaluate(original_player)

    # Recursive case - maximize your gains or minimize the opponent's gains
    if maximizing:
        best_eval: float = float("-inf") # arbitrarily low starting point
        for move in board.legal_moves:
            result: float = minimax(board.move(move), False, original_player, max_depth - 1)
            best_eval = max(result, best_eval) # we want the move with the highest evaluation
        return best_eval
    else: # minimizing
        worst_eval: float = float("inf")
        for move in board.legal_moves:
            result = minimax(board.move(move), True, original_player, max_depth - 1)
            worst_eval = min(result, worst_eval) # we want the move with the lowest evaluation
        return worst_eval


def alphabeta(board: Board, maximizing: bool, original_player: Piece, max_depth: int = 8, alpha: float = float("-inf"), beta: float = float("inf")) -> float:
    # Base case – terminal position or maximum depth reached
    if board.is_win or board.is_draw or max_depth == 0:
        return board.evaluate(original_player)

    # Recursive case - maximize your gains or minimize the opponent's gains
    if maximizing:
        for move in board.legal_moves:
            result: float = alphabeta(board.move(move), False, original_player, max_depth - 1, alpha, beta)
            alpha = max(result, alpha)
            if beta <= alpha:
                break
        return alpha
    else:  # minimizing
        for move in board.legal_moves:
            result = alphabeta(board.move(move), True, original_player, max_depth - 1, alpha, beta)
            beta = min(result, beta)
            if beta <= alpha:
                break
        return beta


# Find the best possible move in the current position
# looking up to max_depth ahead
def find_best_move(board: Board, max_depth: int = 8) -> Move:
    best_eval: float = float("-inf")
    best_move: Move = Move(-1)
    for move in board.legal_moves:
        result: float = alphabeta(board.move(move), False, board.turn, max_depth)
        if result > best_eval:
            best_eval = result
            best_move = move
    return best_move


"""井字棋类"""
class TTTPiece(Piece, Enum): ...

class TTTPiece(Piece, Enum):
    X = "X"
    O = "O"
    E = " " # stand-in for empty

    @property
    def opposite(self) -> TTTPiece:
        if self == TTTPiece.X:
            return TTTPiece.O
        elif self == TTTPiece.O:
            return TTTPiece.X
        else:
            return TTTPiece.E

    def __str__(self) -> str:
        return self.value


class TTTBoard(Board):
    def __init__(self, position: List[TTTPiece] = [TTTPiece.E] * 9, turn: TTTPiece = TTTPiece.X) -> None:
        self.position: List[TTTPiece] = position
        self._turn: TTTPiece = turn

    @property
    def turn(self) -> Piece:
        return self._turn

    def move(self, location: Move) -> Board:
        temp_position: List[TTTPiece] = self.position.copy()
        temp_position[location] = self._turn
        return TTTBoard(temp_position, self._turn.opposite)

    @property
    def legal_moves(self) -> List[Move]:
        return [Move(l) for l in range(len(self.position)) if self.position[l] == TTTPiece.E]

    @property
    def is_win(self) -> bool:
        # three row, three column, and then two diagonal checks
        return self.position[0] == self.position[1] and self.position[0] == self.position[2] and self.position[0] != TTTPiece.E or \
        self.position[3] == self.position[4] and self.position[3] == self.position[5] and self.position[3] != TTTPiece.E or \
        self.position[6] == self.position[7] and self.position[6] == self.position[8] and self.position[6] != TTTPiece.E or \
        self.position[0] == self.position[3] and self.position[0] == self.position[6] and self.position[0] != TTTPiece.E or \
        self.position[1] == self.position[4] and self.position[1] == self.position[7] and self.position[1] != TTTPiece.E or \
        self.position[2] == self.position[5] and self.position[2] == self.position[8] and self.position[2] != TTTPiece.E or \
        self.position[0] == self.position[4] and self.position[0] == self.position[8] and self.position[0] != TTTPiece.E or \
        self.position[2] == self.position[4] and self.position[2] == self.position[6] and self.position[2] != TTTPiece.E

    def evaluate(self, player: Piece) -> float:
        if self.is_win and self.turn == player:
            return -1
        elif self.is_win and self.turn != player:
            return 1
        else:
            return 0

    def __repr__(self) -> str:
        return f"""{self.position[0]}|{self.position[1]}|{self.position[2]}
-----
{self.position[3]}|{self.position[4]}|{self.position[5]}
-----
{self.position[6]}|{self.position[7]}|{self.position[8]}"""


"""unittest"""
import unittest

class TTTMinimaxTestCase(unittest.TestCase):
    def test_easy_position(self):
        # win in 1 move
        to_win_easy_position: List[TTTPiece] = [TTTPiece.X, TTTPiece.O, TTTPiece.X,
                                                TTTPiece.X, TTTPiece.E, TTTPiece.O,
                                                TTTPiece.E, TTTPiece.E, TTTPiece.O]
        test_board1: TTTBoard = TTTBoard(to_win_easy_position, TTTPiece.X)
        answer1: Move = find_best_move(test_board1)
        self.assertEqual(answer1, 6)

    def test_block_position(self):
        # must block O's win
        to_block_position: List[TTTPiece] = [TTTPiece.X, TTTPiece.E, TTTPiece.E,
                                             TTTPiece.E, TTTPiece.E, TTTPiece.O,
                                             TTTPiece.E, TTTPiece.X, TTTPiece.O]
        test_board2: TTTBoard = TTTBoard(to_block_position, TTTPiece.X)
        answer2: Move = find_best_move(test_board2)
        self.assertEqual(answer2, 2)

    def test_hard_position(self):
        # find the best move to win 2 moves
        to_win_hard_position: List[TTTPiece] = [TTTPiece.X, TTTPiece.E, TTTPiece.E,
                                                TTTPiece.E, TTTPiece.E, TTTPiece.O,
                                                TTTPiece.O, TTTPiece.X, TTTPiece.E]
        test_board3: TTTBoard = TTTBoard(to_win_hard_position, TTTPiece.X)
        answer3: Move = find_best_move(test_board3)
        self.assertEqual(answer3, 1)


if __name__ == "__main__":
    board: Board = TTTBoard()

    def get_player_move() -> Move:
        player_move: Move = Move(-1)
        while player_move not in board.legal_moves:
            play: int = int(input("Enter a legal square (0-8):"))
            player_move = Move(play)
        return player_move


    # main game loop
    while True:
        human_move: Move = get_player_move()
        board = board.move(human_move)
        if board.is_win:
            print("Human wins!")
            break
        elif board.is_draw:
            print("Draw!")
            break
        computer_move: Move = find_best_move(board)
        print(f"Computer move is {computer_move}")
        board = board.move(computer_move)
        print(board)
        if board.is_win:
            print("Computer wins!")
            break
        elif board.is_draw:
            print("Draw!")
            break


    # unittest.main()