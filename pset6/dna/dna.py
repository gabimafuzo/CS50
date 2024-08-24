import sys
import csv

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py databases.csv sequences.txt")
        sys.exit(1)

    # Read database file into a variable
    database = []
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        sequence = file.read().strip()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    strs = list(database[0].keys())
    strs.remove('name')  # Remove the 'name' column from STRs

    for str in strs:
        str_counts[str] = longest_match(sequence, str)

    # Check database for matching profiles
    matched_person = None
    for person in database:
        match = True
        for str in strs:
            if (int(person[str]) != str_counts[str]):
                match = False
                break  # Not a match, so exit the inner loop
        if match:
            matched_person = person['name']
            break  # Exit the outer loop

    if matched_person:
        print(matched_person)
    else:
        print("No match")


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
