#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

/* #define TEST 1 */

main ()
{
    char *popauthdir = "/var/spool/popauth/";
    char filename[1024];
    DIR *Popdir;
    struct dirent *entry;
    struct stat fileinfo;
    time_t age;

    if((Popdir=opendir(popauthdir)) == NULL)
    {
        printf("Could not open %s", popauthdir);
        exit(1);
    }

    while((entry=readdir(Popdir)) != NULL)
    {
        if(strncmp(entry->d_name,".",1) != 0)
        {
            bzero(filename,1024);
            strncpy(filename,popauthdir,256);
            strncat(filename,entry->d_name,256);
            if(stat(filename,&fileinfo) == 0);
            {
                age = time(NULL) - fileinfo.st_mtime;
#ifdef TEST
                printf("%s\tmodified\t%ld\tSeconds ago.\n", filename, age);
#endif
                if(age > 1800)
                    unlink(filename);
            }
        }
    }
    closedir(Popdir);
}
