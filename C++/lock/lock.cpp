
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <iostream>
#include <time.h>
#include <unistd.h>


using namespace boost::interprocess;
using namespace boost::posix_time;
using namespace std;


boost::interprocess::file_lock *m_lock;


void do_lock()
{
        if(!m_lock)
                m_lock = new file_lock("lock.cpp");
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
void do_unlock()
{
        if(!m_lock)
                m_lock = new file_lock("lock.cpp");
        m_lock->unlock();
}



int main( int argc, char *argv[] )
{
        cout << "Start." << endl;

        do_lock();              // Expect this call to wait until on other proc
        cout << "Lock 1." << endl;
        do_lock();
        cout << "Lock 2." << endl;

        sleep(3);
        do_unlock();
        cout << "Unlock 2." << endl;

        // The question, and the reason for this example, is to verify
        // if locks are cumulative, or if the first unlock unlocks.
        //
        // Answer: first unlock unlocks.  They don't nest.
        sleep(3);
        do_unlock();
        cout << "Unlock 1." << endl;
}
