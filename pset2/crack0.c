#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

const string kALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const size_t kALPH_LENGTH = strlen(kALPHABET);

bool hash_match(string hash, string attempt);

int main(int argc, string argv[])
{
    // Password = "BcADx", salted with "j3", resulting hash = j3U4hc7dPG9Gg
    char final_pass[] = "aaaaa";
    const string user_hash = "j3U4hc7dPG9Gg";
    const size_t passlength = strlen(final_pass);
    const string salt = "j3";

    for (size_t char1 = 0; char1 < kALPH_LENGTH; ++char1)
    {
        final_pass[1] = kALPHABET[0];
        final_pass[0] = kALPHABET[char1];
        for (size_t char2 = 0; char2 < kALPH_LENGTH; ++char2)
        {
            printf("Attemping %s\n", final_pass);
            final_pass[2] = kALPHABET[0];
            final_pass[1] = kALPHABET[char2];
            for (size_t char3 = 0; char3 < kALPH_LENGTH; ++char3)
            {
                final_pass[3] = kALPHABET[0];
                final_pass[2] = kALPHABET[char3];
                for (size_t char4 = 0; char4 < kALPH_LENGTH; ++char4)
                {
                    final_pass[4] = kALPHABET[0];
                    final_pass[3] = kALPHABET[char4];
                    for (size_t char5 = 0; char5 < kALPH_LENGTH; ++char5)
                    {
                        final_pass[4] = kALPHABET[char5];
                        string attempt = crypt(final_pass, salt);

                        if (hash_match(user_hash, attempt))
                        {
                            printf("\n\nSUCCESS: %s\n", final_pass);
                            return 0;
                        }
                    }
                }
            }
        }
    }

}

bool hash_match(string hash, string attempt)
{
    if (strcmp(hash, attempt) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
