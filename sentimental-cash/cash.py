# TODO
import cs50

coins = 0

# Prompt user for amount of change owed
while True:
    change = cs50.get_float("Change owed: ")
    if change > 0:
        break
# Transform change from dollars into cents
cents = round(change * 100)

# Calculate amount of quarters
while cents >= 25:
    cents = cents - 25
    coins = coins + 1

# Calculate amount of dimes
while cents >= 10:
    cents = cents - 10
    coins = coins + 1

# Calculate amount of nickles
while cents >= 5:
    cents = cents - 5
    coins = coins + 1

# Calculate amount of pennies
while cents >= 1:
    cents = cents - 1
    coins = coins + 1

print(f"{coins}")
