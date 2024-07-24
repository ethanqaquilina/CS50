import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) < 3:
        print("Improper Usage")

    # TODO: Read database file into a variable

    # Reads the data base into a list as a dict
    persons = []
    with open(sys.argv[1]) as dataBase:
        reader = csv.DictReader(dataBase)
        for row in reader:
            persons.append(row)

        # Creates a list of STRs in the database and removes name
        STRs = reader.fieldnames
        del STRs[0]

    dataBase.close()

    # TODO: Read DNA sequence file into a variable

    # Opens sequence file
    with open(sys.argv[2]) as sequence:
        reader = sequence.read()

    # TODO: Find longest match of each STR in DNA sequence

    # Count the str in the sequence
    strCount = {}
    for subsequence in STRs:
        strCount[subsequence] = longest_match(reader, subsequence)

    # TODO: Check database for matching profiles

    # Goes through data to count number of matches per person
    numMatches = {}
    for person in persons:
        numMatches[person["name"]] = 0
        for subsequence in STRs:
            if int(person[subsequence]) == int(strCount[subsequence]):
                numMatches[person["name"]] += 1

    # Count how many patterns are in STR
    STRcount = 0
    for pat in STRs:
        STRcount += 1

    # Calculate most matches
    mostMatch = 0
    for person in persons:
        if int(numMatches[person["name"]]) > mostMatch:
            mostMatch = numMatches[person["name"]]
            match = person["name"]
    if mostMatch != STRcount:
        print("No match")
    else:
        print(f"{match}")

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
