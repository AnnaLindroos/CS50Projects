void tabulate(void)
{
    int voters_preference = preferences[i];

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if a candidate is eliminated. If so, break out early.
            if (candidates[j].eliminated == true)
            {
                break;
            }
            // Give the voter's preferred candidate (non-eliminated) a score in their vote field and then break out.
            else if (strcmp(voters_preference[0], candidates[j].name) == 0)
            {
                candidates[j].votes += 1;
                break;
            }
        }
    }
    return;
    
    

    
    
    
    