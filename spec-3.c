#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <time.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_PATH_BUF 200
#define MAX_COMMAND 200

void fPermissions(char *temp)
{
    struct stat fileStat;
    int check = stat(temp, &fileStat);

    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t%ld", fileStat.st_nlink);
    char user_name[200];
    userName(user_name);
    printf("\t%s", user_name);
    int gid = fileStat.st_gid;
    struct group *g = getgrgid(gid);
    printf("\t");
    if (g != NULL)
    {
        printf("%s", (g->gr_name));
    }
    printf("\t%ld", fileStat.st_size);
    char *mTime = ctime(&fileStat.st_mtime);
    (mTime) = &(mTime[4]);
    char temp_2[14];
    for (int i = 0; i < 12; i++)
    {
        temp_2[i] = mTime[i];
    }
    temp_2[12] = '\0';
    strcpy(mTime, temp_2);
    printf("\t%s", mTime);
    printf("\t%s\n", temp);
}

void lsColumn_basic_a(char string[MAX_PATH_BUF])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(string);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}
void lsColumn_basic(char string[MAX_PATH_BUF])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(string);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && (dir->d_name)[0] != '.')
            {
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    }
}
void lsColumn_la(char string[MAX_PATH_BUF])
{
    char* curr_dir = malloc(sizeof(char)*MAX_PATH_BUF);
    getcwd(curr_dir, MAX_PATH_BUF);
    chdir(string);
    DIR *d = opendir(string);
    struct dirent *dir;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            fPermissions(dir->d_name);
        }
        closedir(d);
    }
    chdir(curr_dir);
}
void lsColumn_basic_l(char string[MAX_PATH_BUF])
{
    DIR *d;
    struct dirent *dir;
    char* curr_dir = malloc(sizeof(char)*MAX_PATH_BUF);
    getcwd(curr_dir, MAX_PATH_BUF);
    chdir(string);
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {

            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                fPermissions(dir->d_name);
            }
        }
        closedir(d);
    }
    chdir(curr_dir);
}

// This page is dedicated for the listing files in a directory command.

/*Splitting the strings with the delimiter function*/
char **str_split(char *a_str, const char a_delim)
{
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_delim = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    // Calculating the number of elements
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_delim = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_delim < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);

    if (result)
    {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int numberOfsplits(char *a_str, const char a_delim)
{
    int count = 0;
    char *tmp = a_str;
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count++;
    return count;
}

void processLsCommand(char string[MAX_COMMAND])
{
    if (strlen(string) == 3 || strlen(string) == 4)
    {
        lsColumn_basic(".");
        return;
    } // base case handled
    (string) = &(string[3]);
    //printf("%s\n", string);// Here the string has the rest of the command except ls.
    int number_of_splits = numberOfsplits(string, ' ');
    // Number of splits work.
    char **dir_and_flags = str_split(string, ' ');
    int a_flag = 0;
    int l_flag = 0;
    char directories[10][MAX_PATH_BUF];
    int dir_count = 0; // on default they do not exist
    for (int i = 0; i < number_of_splits; i++)
    {
        if (dir_and_flags[i][0] == '-')
        {
            for (int j = 0; dir_and_flags[i][j]; j++)
            {
                if (dir_and_flags[i][j] == 'a')
                {
                    a_flag = 1;
                    //printf("flag a\n");
                }
                else if (dir_and_flags[i][j] == 'l')
                {
                    l_flag = 1;
                    //printf("flag l\n");
                }
            } // This is the flag setter.
        }
        else
        {
            strcpy(directories[dir_count], dir_and_flags[i]);
            dir_count++;
            //printf("%d %s\n", dir_count, directories[dir_count - 1]);
        }
    }

    for (int i = 0; i < dir_count; i++)
    {
        directories[i][strlen(directories[i]) - 1] = '\0';
    }

    // Now we have obtained all the flags and dirs.
    if (a_flag == 1)
    {
        if (l_flag == 0)
        {
            if (dir_count == 0)
            {
                lsColumn_basic_a(".");
            }
            else if (dir_count > 0)
            {
                for (int i = 0; i < dir_count; i++)
                {
                    printf("./%s\n", directories[i]);
                    lsColumn_basic_a(directories[i]);
                    printf("\n\n");
                }
            }
        }
        else if (l_flag == 1)
        {
            if (dir_count == 0)
            {
                lsColumn_la(".");
            }
            else if (dir_count > 0)
            {
                for (int i = 0; i < dir_count; i++)
                {
                    printf("./%s\n", directories[i]);
                    lsColumn_la(directories[i]);
                    printf("\n\n");
                }
            }
        }
    }
    else if (a_flag == 0)
    {
        if (l_flag == 0)
        {
            if (dir_count == 0)
            {
                lsColumn_basic(".");
            }
            else if (dir_count > 0)
            {
                for (int i = 0; i < dir_count; i++)
                {
                    printf("./%s\n", directories[i]);
                    lsColumn_basic(directories[i]);
                    printf("\n\n");
                }
            }
        }
        else if (l_flag == 1)
        {
            if (dir_count == 0)
            {
                lsColumn_basic_l(".");
            }
            else if (dir_count > 0)
            {
                for (int i = 0; i < dir_count; i++)
                {
                    printf("./%s\n", directories[i]);
                    lsColumn_basic_l(directories[i]);
                    printf("\n\n");
                }
            }
        }
    }
}