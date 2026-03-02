#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISTINCT_NAMES 100
#define MAX_NAME_LENGTH 30
#define BUF_SIZE 512

int main(int argc, char *argv[])
{
    // open files
    pid_t pid = getpid();
    char err_name[64], out_name[64];
    snprintf(err_name, sizeof(err_name), "%d.err", pid);
    snprintf(out_name, sizeof(out_name), "%d.out", pid);

    FILE *ef = fopen(err_name, "w");
    FILE *of = fopen(out_name, "w");
    if (!ef || !of)
    {
        fprintf(stderr, "error: cannot open output/error file for pid %d\n", pid);
        if (ef)
            fclose(ef);
        if (of)
            fclose(of);
        exit(1);
    }

    FILE *in = stdin;
    const char *input_name = "stdin";
    if (argc >= 2)
    {
        input_name = argv[1];
        in = fopen(input_name, "r");
        if (!in)
        {
            // print to stderr and exit 1
            fprintf(stderr, "error: cannot open file %s\n", input_name);
            fclose(ef);
            fclose(of);
            exit(1);
        }
    }

    // init name list and counter
    int distinct = 0;
    int name_counter[MAX_DISTINCT_NAMES];
    char name_list[MAX_DISTINCT_NAMES][MAX_NAME_LENGTH + 1];
    for (int i = 0; i < MAX_DISTINCT_NAMES; i++)
    {
        name_counter[i] = 0;
        name_list[i][0] = '\0';
    }

    char buf[BUF_SIZE];
    int line_number = 0;
    while (fgets(buf, sizeof(buf), in) != NULL)
    {
        line_number++;

        // check for empty line && fix the last char
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n')
        {
            buf[len - 1] = '\0';
        }
        if (buf[0] == '\0')
        {
            fprintf(ef, "Warning - file %s line %d is empty.\n", input_name, line_number);
            continue;
        }

        // counting
        int name_found_idx = -1;
        for (int i = 0; i < distinct; i++)
        {
            if (strcmp(buf, name_list[i]) == 0)
            { // found name
                name_found_idx = i;
                break;
            }
        }

        if (name_found_idx >= 0)
        { // name founded: increase counter
            name_counter[name_found_idx]++;
        }
        else
        { // new name: add to the list, update distinct
            if (distinct < MAX_DISTINCT_NAMES)
            {
                strncpy(name_list[distinct], buf, MAX_NAME_LENGTH);
                name_list[distinct][MAX_NAME_LENGTH] = '\0';
                name_counter[distinct] = 1;
                distinct++;
            }
            else
            { // over limit
                fprintf(ef, "Warning - too many distinct names.\n");
            }
        }
    }

    for (int i = 0; i < distinct; i++)
    {
        fprintf(of, "%d %s\n", name_counter[i], name_list[i]);
    }
    if (in != stdin)
    {
        fclose(in);
    }
    fclose(ef);
    fclose(of);
    return 0;
}
