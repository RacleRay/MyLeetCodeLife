
WIN = 10
INF = 1000

MAGIC_SQUARE = [4, 9, 2, 
                3, 5, 7, 
                8, 1, 6]

def win(seq):
    n = len(seq)
    if (n < 3):
        return False
    
    seq = sorted(seq)
    for i in range(n - 2):
        l = i + 1
        r = n - 1
        while l < r:
            total = seq[i] + seq[l] + seq[r]
            if total == 15:
                return True
            elif total < 15:
                l += 1
            else:
                r -= 1
        
    return False


def eval(tick_seq, tack_seq):
    """
    tick -- WIN is 10
    tack -- WIN is -10
    draw -- 0
    """
    if win(tick_seq):
        return WIN
    if win(tack_seq):
        return -WIN
    return 0


def finished(tick_seq, tack_seq):
    return len(tick_seq) + len(tack_seq) >= 9


def minmax(tick_seq, tack_seq, depth, for_maximum):
    score = eval(tick_seq, tack_seq)
    if score == WIN:
        return score - depth
    if score == -WIN:
        return score + depth
    if finished(tick_seq, tack_seq):
        return 0  # draw
    
    bestscore = -INF if for_maximum else INF
    for i in MAGIC_SQUARE:
        if (i not in tick_seq) and (i not in tack_seq):
            if for_maximum:
                # swtich for_maximum to false, turn to the opponent's round
                bestscore = max(bestscore, minmax(tick_seq + [i], tack_seq, depth + 1, not for_maximum))
            else:
                bestscore = min(bestscore, minmax(tick_seq, tack_seq + [i], depth + 1, not for_maximum))

    return bestscore


def find_best_move(tick_seq, tack_seq, for_maximum):
    bestscore = -INF if for_maximum else INF
    bestmove = 0
    for i in MAGIC_SQUARE:
        if (i not in tick_seq) and (i not in tack_seq):
            if (for_maximum):
                val = minmax(tick_seq + [i], tack_seq, 0, not for_maximum)
                if val > bestscore:
                    bestscore = val
                    bestmove = i
            else:
                val = minmax(tick_seq, tack_seq + [i], 0, not for_maximum)
                if val < bestscore:
                    bestscore = val
                    bestmove = i

    return bestmove


def borad(tick_seq, tack_seq):
    for r in range(3):
        print("-" * 11)
        for c in range(3):
            p = MAGIC_SQUARE[r * 3 + c]
            if p in tick_seq:
                print(" | X", end="")
            elif p in tack_seq:
                print(" | O", end="")
            else:
                print(" | ", end="")
        print(" | ")
    print("-" * 11)


def play():
    tick_seq = []
    tack_seq = []
    while not( win(tick_seq) or win(tack_seq) or finished(tick_seq, tack_seq) ):
        borad(tick_seq, tack_seq)
        while True:
            i = int(input(" [1 ... 9] ==> "))
            if i not in MAGIC_SQUARE or MAGIC_SQUARE[i - 1] in tick_seq or MAGIC_SQUARE[i - 1] in tack_seq:
                print("Invalid move!")
            else:
                tick_seq = [MAGIC_SQUARE[i - 1]] + tick_seq
                break
        
        move = find_best_move(tick_seq, tack_seq, False)
        print(">>> ", move)
        tack_seq = [move] + tack_seq
    borad(tick_seq, tack_seq)


if __name__ == "__main__":
    play()