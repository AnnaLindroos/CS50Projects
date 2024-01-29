import csv
import sys


def main():

    # TODO: Check for command-line usage
    if not len(sys.argv) == 3:
        print("Incorrect usage of command-line arguments")

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dna_file:
        content = dna_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Save STR counts in a list called results
    if sys.argv[1] == "databases/small.csv":
        results_small = []
        first = longest_match(content, "AGATC")
        results_small.append(first)

        second = longest_match(content, "AATG")
        results_small.append(second)

        third = longest_match(content, "TATC")
        results_small.append(third)
    else:
        results_large = []
        first = longest_match(content, "AGATC")
        results_large.append(first)

        second = longest_match(content, "TTTTTTCT")
        results_large.append(second)

        third = longest_match(content, "AATG")
        results_large.append(third)

        fourth = longest_match(content, "TCTAG")
        results_large.append(fourth)

        fifth = longest_match(content, "GATA")
        results_large.append(fifth)

        sixth = longest_match(content, "TATC")
        results_large.append(sixth)

        seventh = longest_match(content, "GAAA")
        results_large.append(seventh)

        eighth = longest_match(content, "TCTG")
        results_large.append(eighth)

    # TODO: Check database for matching profiles
    # For each row in the database reader, check if each STR matches. If so, print out the name of that person
    # TODO: Read database file into a variable
    if sys.argv[1] == "databases/small.csv":
        with open(sys.argv[1], "r") as data_file:
            database_readerSmall = csv.DictReader(data_file)
            for row in database_readerSmall:
                name = row["name"]
                AGATC = row["AGATC"]
                AATG = row["AATG"]
                TATC = row["TATC"]

                if first == int(AGATC) and second == int(AATG) and third == int(TATC):
                    print(name)
                    return
            print("No match")
            return

    else:
        with open(sys.argv[1], "r") as data_file:
            database_readerLarge = csv.DictReader(data_file)
            for row in database_readerLarge:
                name = row["name"]
                AGATC = row["AGATC"]
                TTTTTTCT = row["TTTTTTCT"]
                AATG = row["AATG"]
                TCTAG = row["TCTAG"]
                GATA = row["GATA"]
                TATC = row["TATC"]
                GAAA = row["GAAA"]
                TCTG = row["TCTG"]

                if first == int(AGATC) and second == int(TTTTTTCT) and third == int(AATG) and fourth == int(TCTAG) and fifth == int(GATA) and sixth == int(TATC) and seventh == int(GAAA) and eighth == int(TCTG):
                    print(name)
                    return
            print("No match")
            return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
