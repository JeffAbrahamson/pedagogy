#include <cassert>
#include <functional>
#include <iostream>
#include <sys/time.h>


using namespace std;


namespace {

        const unsigned int N = 1000 * 1000;

        
        void fn_and()
        {
                unsigned int acc = 1;
                for(unsigned int i = 1; i < N; i++)
                        acc &= i;
                cout << " [" << acc << "]  ";
        }
        
        
        void fn_or()
        {
                unsigned int acc = 1;
                for(unsigned int i = 1; i < N; i++)
                        acc |= i;
                cout << " [" << acc << "]  ";
        }
        

        unsigned int f_and(unsigned int m, unsigned int n) { return m & n; };
        unsigned int f_or(unsigned int m, unsigned int n) { return m | n; };

        void fn_fn_and()
        {
                unsigned int acc = 1;
                for(unsigned int i = 1; i < N; i++)
                        acc = f_and(acc, i);
                cout << " [" << acc << "]  ";
        }
        
        
        void fn_fn_or()
        {
                unsigned int acc = 1;
                for(unsigned int i = 1; i < N; i++)
                        acc = f_or(acc, i);
                cout << " [" << acc << "]  ";
        }
        
        
        void fn_if(bool val)
        {
                unsigned int acc = 1;
                for(unsigned int i = 1; i < N; i++)
                if(val)
                        acc |= i;
                else
                        acc &= i;
                cout << " [" << acc << "]  ";
        }
        
        
        
        void fn_lambda(bool val)
        {
                function<unsigned int(unsigned int, unsigned int)> fn;
                unsigned int acc = 1;
                if(val)
                        fn = [](unsigned int m, unsigned int n){ return m | n; };
                else
                        fn = [](unsigned int m, unsigned int n){ return m & n; };
                for(unsigned int i = 1; i < N; i++)
                        acc = fn(acc, i);
                cout << " [" << acc << "]  ";
        }
        

        void fn_lambda_ref(bool val)
        {
                function<void(unsigned int)> fn;
                unsigned int acc = 1;
                if(val)
                        fn = [&acc](unsigned int n){ acc |= n; };
                else
                        fn = [&acc](unsigned int n){ acc &= n; };
                for(unsigned int i = 1; i < N; i++)
                        fn(i);
                cout << " [" << acc << "]  ";
        }
        

        struct obj {
                virtual ~obj() {};
                virtual unsigned int operator()(unsigned int m, unsigned int n) { assert(0); };
        };
        struct obj_and : public obj
        { virtual unsigned int operator()(unsigned int m, unsigned int n) { return m & n; }; };
        struct obj_or : public obj
        { virtual unsigned int operator()(unsigned int m, unsigned int n) { return m | n; }; };
        void fn_obj(bool val)
        {
                obj *o;
                if(val)
                        o = new obj_or();
                else
                        o = new obj_and();
                unsigned int acc = 1;
                for(unsigned int i = 1; i < N; i++)
                        acc = (*o)(acc, i);
                delete o;
                cout << " [" << acc << "]  ";
        }
        
        
        
        typedef void (*func0)();
        typedef void (*func1)(bool);
        
        void time_it(func0 fn)
        {
                struct timeval tv1, tv2;
                assert(!gettimeofday(&tv1, 0));
                fn();
                assert(!gettimeofday(&tv2, 0));
                // elapsed time in milliseconds
                double elapsed = 1000.0 * (tv2.tv_sec - tv1.tv_sec)
                        + (double)(tv2.tv_usec - tv1.tv_usec) / 1000.0;
                cout << "Elapsed=" << elapsed << endl;
        }


        void time_it1(func1 fn, bool val)
        {
                struct timeval tv1, tv2;
                assert(!gettimeofday(&tv1, 0));
                fn(val);
                assert(!gettimeofday(&tv2, 0));
                // elapsed time in milliseconds
                double elapsed = 1000.0 * (tv2.tv_sec - tv1.tv_sec)
                        + (double)(tv2.tv_usec - tv1.tv_usec) / 1000.0;
                cout << "Elapsed=" << elapsed << endl;
        }
}


int main( int argc, char *argv[] )
{
        cout << "N=" << N << endl;
        
        cout << "fn_and:    ";
        time_it(fn_and);
        
        cout << "fn_or:     ";
        time_it(fn_or);

        cout << "fn_fn_and:    ";
        time_it(fn_fn_and);
        
        cout << "fn_fn_or:     ";
        time_it(fn_fn_or);

        cout << "fn_if:     ";
        time_it1(fn_if, false);

        cout << "fn_if:     ";
        time_it1(fn_if, true);

        cout << "fn_lambda:  ";
        time_it1(fn_lambda, false);

        cout << "fn_lambda:  ";
        time_it1(fn_lambda, true);

        cout << "fn_lamref:  ";
        time_it1(fn_lambda_ref, false);

        cout << "fn_lamref:  ";
        time_it1(fn_lambda_ref, true);

        cout << "fn_obj:  ";
        time_it1(fn_obj, false);

        cout << "fn_obj:  ";
        time_it1(fn_obj, true);
}
