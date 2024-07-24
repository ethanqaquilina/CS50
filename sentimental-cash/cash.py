import cs50


amount = -1

while amount < 0:
    amount = cs50.get_float("Change: ")

totalCoins = 0

# Divide by quarters
while amount >= 0.25:
    totalCoins += 1
    amount -= 0.25
    amount = round(amount, 2)

# Divide by dimes
while amount >= 0.10:
    totalCoins += 1
    amount -= 0.10
    amount = round(amount, 2)

# Divide by nickels
while amount >= 0.05:
    totalCoins += 1
    amount -= 0.05
    amount = round(amount, 2)

# Divide by pennies
while amount >= 0.01:
    totalCoins += 1
    amount -= 0.01
    amount = round(amount, 2)

print(f"{int(totalCoins)}")
