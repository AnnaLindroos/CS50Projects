# Prompt user for height of pyramid
while True:
    try:
        height = int(input("Height: "))
        if (height > 0) and (height <= 8):
            break
    except ValueError:
        print("That's not an integer!")

# print pyramid
for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i)