#include <assert.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


using namespace std;


void touch(const char *fn)
{
        ofstream f(fn);
        f << "hello" << endl;
        f.close();
}


int main( int argc, char *argv[] )
{
        struct stat st;
        char path[] = "/tmp/foo";

        touch(path);
        assert(!stat(path, &st));
        time_t m1 = st.st_mtime;

        cout << "Sleep remaining: " << sleep(2) << endl;
        touch(path);
        assert(!stat(path, &st));
        time_t m2 = st.st_mtime;

        cout << "Elapsed modtime=" << m2 - m1 << endl;
}
