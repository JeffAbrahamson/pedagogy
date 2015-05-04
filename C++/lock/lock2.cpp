
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <time.h>
#include <unistd.h>


using namespace boost::interprocess;
using namespace boost::posix_time;
using namespace std;


boost::interprocess::file_lock *m_lock;


void do_lock(const char *lock_file)
{
        if(!m_lock)
                m_lock = new file_lock(lock_file);
        m_lock->lock();
        return;

        ptime timeout = from_time_t(time(0) + 1); // one second in the future
        while(!m_lock->timed_lock(timeout)) {
                cout << "Waiting on file lock..." << endl;
                timeout = from_time_t(time(0) + 1);
        }
}
        


/*
  Unlock the file.
*/
void do_unlock(const char *lock_file)
{
        if(!m_lock)
                m_lock = new file_lock(lock_file);
        m_lock->unlock();
}



int main( int argc, char *argv[] )
{
        // Make sure we have a lock file
        string lock_file("lock.lck");
        ofstream fs(lock_file.c_str(), ios::out);
        assert(fs.is_open());
        fs.write("", 0);
        fs.close();

        do_lock(lock_file.c_str());
        int ret = unlink(lock_file.c_str());
        if(ret)
                cerr << strerror(errno) << endl;
        // Does unlock succeed even though we've removed the file?
        // Answer: yes.
        // (Note that we're not checking if the file has lost all links.)
        do_unlock(lock_file.c_str());
}
