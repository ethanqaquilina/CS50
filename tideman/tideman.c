#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if name equals a candidate
        if (strcmp(name, candidates[i]) == 0)
        {
            // Set rank pref
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Add votes to first place preference
    for (int i = 0; i < candidate_count - 1; i++)
    {

        for (int j = i; j < candidate_count - 1;)
        {
            preferences[ranks[i]][ranks[j + 1]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count - 1; j++)
        {
            if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            else if (preferences[j][i] < preferences[i][j])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int largestWin = 0;
    int largestPair;

    // Get the int difference of each victory of pairs
    for (int j = 0; j < pair_count - 1; j++)
    {
        for (int i = j; i < pair_count - 1; i++)
        {

            int winDif = preferences[pairs[i].winner][pairs[i].loser] -
                         preferences[pairs[i].winner][pairs[i].loser];
            if (winDif > largestWin)
            {
                largestPair = i;
            }
        }

        // Swap largest pair to top
        pair temp = pairs[j];
        pairs[j] = pairs[largestPair];
        pairs[largestPair] = temp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        // Check if creates loop
        int truesPerRow = 0;
        for (int j = 0; j < candidate_count - 1; j++)
        {
            for (int k = 0; k < candidate_count - 1; k++ )
            {
                if(locked[j][k] == true)
                {
                    truesPerRow++;
                    // Breaks out of loop to go to next row
                    k += candidate_count;
                }
            }
        }

        // Undo True if creates a loop
        if (truesPerRow == candidate_count)
        {
             locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Scan each array row
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int numOfTrues = 0;
        for (int j = 0; j < candidate_count - 1; j++)
        {
            if(locked[i][j] == true)
            {
                numOfTrues++;
            }
        }

        if(numOfTrues == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }


    return;
}
