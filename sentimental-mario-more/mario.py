import cs50

height = 0

while height < 1 or height > 8:
    height = cs50.get_int("Height: ")

firSpaces = height
gap = 2
firBricks = 0
secBricks = 0

for x in range(height):
    firBricks += 1
    firSpaces -= 1
    secBricks += 1

    for y in range(firSpaces):
        print(" ", end="")

    for z in range(firBricks):
        print("#", end="")

    for x in range(gap):
        print(" ", end="")

    for z in range(secBricks):
        print("#", end="")

    print()
