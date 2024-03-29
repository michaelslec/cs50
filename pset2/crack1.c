#include <crypt.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: crack <hash>\n");
        return 1;
    }

    // TODO: how can i compute the length of the string below?

    // 26 lowercase + 26 uppercase + \0 counts as 1 character = 53
    const int letters_count = 53;

    // TODO: possible improvement =>
    // https://en.wikipedia.org/wiki/Letter_frequency
    string letters = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string hash = argv[1];

    char salt[3];
    memcpy(salt, hash, 2);
    salt[2] = '\0';

    char key_candidate[6] = "\0\0\0\0\0\0";

    // The outermost loop advances least frequently compared to its descendants,
    // therefore according to the scheme above, it maps to the last (fifth)
    // letter.
    for (int fifth = 0; fifth < letters_count; fifth++) {
        for (int fourth = 0; fourth < letters_count; fourth++) {
            for (int third = 0; third < letters_count; third++) {
                for (int second = 0; second < letters_count; second++) {
                    // The innermost loop advances most frequently compared to its
                    // ascendants, therefore according to the scheme above, it maps to the
                    // first letter.  We could initialize it to 0 but that would be an
                    // empty string (i.e. no password) which is not allowed (should not
                    // be!)
                    for (int first = 1; first < letters_count; first++) {
                        key_candidate[0] = letters[first]; // 1)
                        key_candidate[1] = letters[second]; // 2)
                        key_candidate[2] = letters[third]; // 3)
                        key_candidate[3] = letters[fourth]; // 4)
                        key_candidate[4] = letters[fifth]; // 5)
                        printf("Attempting %s\n", key_candidate);

                        // It's important to realize that most string manipulation functions
                        // in C stop looping over the characters once they encounter a null
                        // character.  That's essentially what this algorithm leverages when
                        // it initializes the key_candidate full of null characters and
                        // progresses from 1-letter all the way through 5-letter strings.
                        if (strcmp(crypt(key_candidate, salt), hash) == 0) {
                            printf("%s\n", key_candidate);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    printf("Password couldn't be cracked!");

    // This may be out of scope of the task but we signal failure w/ a different
    // exit status than 1 (wrong arguments) or 0 (success) which have been
    // reserved.
    return 2;
}
