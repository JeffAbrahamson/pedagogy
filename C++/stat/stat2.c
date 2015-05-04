#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


void touch(const char *fn, const char *contents)
{
        FILE *fp;
        assert(fp = fopen(fn, "w"));
        fprintf(fp, contents);
        fclose(fp);
}


int main( int argc, char *argv[] )
{
        struct stat st;
        char path[] = "/tmp/foo";
        time_t m1, m2;
        unsigned int t;
        
        touch(path, "hello\n");
        assert(!stat(path, &st));
        m1 = st.st_mtime;

        t = sleep(2);
        touch(path, "hello, world!\n");
        assert(!stat(path, &st));
        m2 = st.st_mtime;

        printf("Sleep remaining: %lu\n", t);
        printf("Elapsed modtime=%lu\n", m2 - m1);
}
