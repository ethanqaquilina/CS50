import cs50

height = 0

while height < 1 or height > 8:
    height = cs50.get_int("Height: ")

spaces = height
bricks = 0

for x in range(height):
    bricks += 1
    spaces -= 1

    for y in range(spaces):
        print(" ", end="")

    for z in range(bricks):
        print("#", end="")
    print()
