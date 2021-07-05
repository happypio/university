import random

def straight_flush(hand):
    cards = hand[0]
    suits = hand[1]
    cards.sort()
    for i in range(1,5):
        if cards[i -1] != cards[i] + 1:
            return False
        if suits[i-1] != suits[i]:
            return False
    return True
def four_of_a_kind(hand):
    cards = hand[0]
    cards.sort()
    count = 0
    for i in range(1,5):
        if cards[i -1] != cards[i]:
            count = count + 1
    if count > 1:
        return False
    return True

def full_house(hand):
    cards = hand[0]
    cards.sort()
    count  = 0
    for i in range(1,5):
        if cards[i -1] != cards[i]:
            count = count + 1
    if count > 1:
        return False
    return True

def flush(hand):
    suits = hand[1]
    for i in range(1,5):
        if suits[i -1] != suits[i]:
            return False
    return True

def straight(hand):
    cards = hand[0]
    cards.sort()
    for i in range(1,5):
        if cards[i -1] != cards[i] + 1:
            return False
    return True

def three_of_a_kind(hand):
    cards = hand[0]
    cards.sort()
    count = 0
    for i in range(1, 5):
        if cards[i - 1] != cards[i]:
            count = count + 1
    if count > 2:
        return False
    return True

def two_pair(hand):
    cards = hand[0]
    cards.sort()
    count = 0
    for i in range(1, 5):
        if cards[i - 1] != cards[i]:
            count = count + 1
    if count > 2:
        return False
    return True

def pair(hand):
    cards = hand[0]
    cards.sort()
    for i in range(1, 5):
        if cards[i - 1] == cards[i]:
            return True
    return False

Figurant = [141, 142, 143, 144,
            131, 132, 133, 134,
            121, 122, 123, 124,
            111, 112, 113, 114]
Blotkarz = [21, 22, 23, 24,
            31, 32, 33, 34,
            41, 42, 43, 44,
            51, 52, 53, 54,
            61, 62, 63, 64,
            71, 72, 73, 74,
            81, 82, 83, 84,
            91, 92, 93, 94,
            101, 102, 103, 104]

Blotkarz_victory = [21, 31, 41, 51, 61, 71, 81, 91, 101]
def gen_figurant():
    count = 0
    first = 0
    i = 0
    cards = [0 for i in range(5)]
    while i < 5:
        is_good = random.choice(Figurant)
        if i == 0:
            first = is_good
        if is_good == first:
            count = count + 1
        if is_good in cards or count > 4:
            count = count - 1
            i = i - 1
        else:
            cards[i] = is_good
        i = i + 1
    suits = [card % 10 for card in cards]
    cards = [card // 10 for card in cards]

    return (cards, suits)

def gen_blotkarz():
    cards = [0 for i in range(5)]
    count = 0
    i = 0
    while i < 5:
        is_good = random.choice(Blotkarz)
        if i == 0:
            first = is_good
        if is_good == first:
            count = count + 1
        if is_good in cards or count > 4:
            count = count -1
            i = i - 1
        else:
            cards[i] = is_good
        i = i + 1
    suits = [card % 10 for card in cards]
    cards = [card // 10 for card in cards]

    return (cards, suits)
def game():
    Figurant_hand = gen_figurant()
    Blotkarz_hand = gen_blotkarz()
    Rankings = [straight_flush, four_of_a_kind, full_house, flush, straight, three_of_a_kind, two_pair, pair]
    #Rankings.reverse()
    for ranking in Rankings:
        fig = ranking(Figurant_hand)
        blo = ranking(Blotkarz_hand)
        if fig and not blo :
            return (1,0)
        if not fig and blo :
            return (0,1)
        if fig and blo:
            return(1,0)

number_of_games = 10000
fig_wins = 0
blo_wins = 0

for i in range(number_of_games):
    result = game()
    fig_wins = fig_wins + result[0]
    blo_wins = blo_wins + result[1]

print(f'Games : {number_of_games} , Figurant_wins : {fig_wins} , Blotkarz_wins : {blo_wins}')
print(f'The probability of Blotkarz\'s victory is {blo_wins/number_of_games * 100}%')