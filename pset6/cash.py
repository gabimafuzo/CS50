def main():
    change = get_float("Change: ")
    change = round(change * 100)
    coins = countChangeCoins(change)
    print(coins)


def get_float(prompt):
    while True:
        try:
            value = float(input(prompt))
            if value > 0:
                return value
            else:
                pass
        except:
            pass


def countChangeCoins(value):
    coins = 0
    while value > 0:
        if value >= 25:
            value = value - 25
            coins += 1
        elif value >= 10:
            value = value - 10
            coins += 1
        elif value >= 5:
            value = value - 5
            coins += 1
        elif value >= 1:
            value = value - 1
            coins += 1
    return coins


main()
