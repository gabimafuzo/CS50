def get_int(prompt):
    while True:
        try:
            value = int(input(prompt))
            if 1 <= value <= 8:
                return value
            else:
                pass
        except:
            pass


def main():
    height = get_int("Height: ")

    for i in range(height):
        for j in range(height - 1 - i):
            print(" ", end="")
        for k in range(i + 1):
            print("#", end="")

        print()


main()
