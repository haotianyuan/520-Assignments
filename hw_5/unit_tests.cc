#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <numeric>      // std::accumulate
#include "examples.h"
#include "db.h"

namespace {

  using namespace std;

  class Imag {
      public: 
      Imag(double a, double b) : x(a), y(b) {}
      double x, y;
  };

  TEST(Vector,Vector) {

      vector<Imag> r;
      r.emplace(r.begin(),2.0,3.0);
      Imag h(1,2);
      r.push_back(h);

    vector<double> v;
    for (int i=0; i< 50; i++) {
      v.push_back(i);
    }
    v.pop_back();

    for (double &i : v)
      i *= i;
    for (double &i : v)        
      std::cout << i << " "; 

    std::cout << "\n";

    std::cout << v.capacity() << "\n";

    v.shrink_to_fit();

    std::cout << v.capacity() << "\n";
    v.push_back(1);
    std::cout << v.capacity() << "\n";     

    vector<int> w = { 1, 2, 3 };  // vector of three ints
    vector<double> x(10,3.14);    // vector of 10 3.14s
    vector<double> y = x;         // copy constructor with assignment operator       

    string s;
    string t = "hello";
    string u = t;

    t.pop_back();
    cout << t << ", "  << "\n";

    std::cout << u.capacity() << "\n";
    u.shrink_to_fit();    

  }

  TEST(VectorString,Common) {

      vector<double> v = { 1, 2, 3 };
      v.push_back(4);

      cout << v.empty() << v.size() << v[0] << (v==v) << (v!=v) << (v>v) << "\n";

      string s = "abc";
      s.push_back('d');

      cout << s << s.empty() << s.size() << s[0] << (s==s) << (s!=s) << (s>s) << "\n";

      vector<double> u;

      for ( double x : v ) {
          u.push_back(x);
      }

      string t;

      for ( char c : s ) {
          cout << c << "\n";
      }

      cout << t << "\n";    

        vector<string> V = { "i", "am", "on", "a", "bumpy", "flight" };
        for (string s : V ) {
            cout << s << "!\n";
        }      

        string q = "I know my ABC's and 123's.";


      for ( char &c : q ) {
          c = toupper(c);
      }

      for ( string::iterator i = q.begin(); i != q.end(); i++ ) {
          *i = tolower(*i);
      }      

      cout << q << "\n";

    auto i = v.begin();
    auto j = i + v.size() / 2;
    i < j; // true      

    q.insert(q.begin()+1, 'x');
    cout << q << "\n";
    q.erase(5,2);
    cout << q << "\n";


  }

  TEST(Find,Find) {
      vector<string> v = { "The", "quick", "brown", "fox" };
      string s = "this is a string";
      int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};      

      auto f1 = find(v.begin(), v.end(), "not quick");
      if ( f1 != v.end() ) {
        cout << *f1 << "\n";
      } else {
          cout << "not found \n";
      }

      auto f2 = find(s.begin(), s.end(), 'i');
      cout << *f2 << "\n"; 

      auto f3 = find(begin(a), end(a), 6);
      cout << *f3 << "\n";       

  }

  TEST(ALG,ALG) {
    vector<int> v = { 1, 2, 3, 4, 5 }, w = { 2,3,4,5,6,6,7,8 };
    cout << accumulate(v.begin(), v.end(), 0) << "\n"; // sum of the elements in v  
    cout << count(v.begin(), v.end(), 3) << "\n";
    cout << (equal(v.begin(), v.end(), w.begin()) ? "true" : "false") << "\n";
    sort(v.begin(), v.end());
    fill(v.begin(), v.end(), 1);
    fill_n(v.begin(), 3, 1);
    copy(v.begin(), v.end(), w.begin() + 3);
    replace(v.begin(), v.end(), 3,-1);
  }

  void add_to(vector<int> &v, int x) {
      transform(v.begin(), v.end(), v.begin(), [x](int y) { return x+y; });
  }


  TEST(LAMBDA,LAMBDA) {
   auto f = [](double x) { return x*x; };
   f(3);

    vector<int> v = { 1, 2, 3, 4, 5 };
    transform(
        v.begin(), 
        v.end(), 
        v.begin(),
        [](int x) { return x*x; }
    );

    for(auto x : v) {
        cout << x << "\n";
    }

  }

  TEST(Map,Map) {

    map<string,string> person;
    person["First"] = "Alan";
    person["Last"] = "Turing";
    person["Job"] = "Code breaker";

    map<string, vector<int>> sequence;
    sequence["fib"] = { 1, 1, 2, 3, 5, 8, 13 };
    sequence["ints"] = { 1, 2, 3, 4, 5, 6 };
    sequence ["squares"] = { 1, 4, 9, 16, 25, 36 };

    map<unsigned int, double> a;
    a[0] = 123;
    a[5] = 34;
    cout << "a[3] = " << a[3] << "\n";

  }

  TEST(examples,sort_by_magnitude) {
    examples a;

    vector<double> v={-10.0,5.0,-19.1,1,0,23};
    vector<double> sorted=a.sort_by_magnitude(v);
    
    cout << "sorted[0] = " << sorted[0] << ", " << sorted[1] << ", "<< sorted[2]<< ", "<< sorted[3]<<", "<<sorted[4]<< ", "<<sorted[5]<<"\n";

  }

  TEST(examples,primes) {
    examples a;
    vector<int> sorted=a.primes(30);
    
    cout << "sorted[0] = " << sorted[0] << ", " << sorted[1] << ", "<< sorted[2]<< ", "<< sorted[3]<<", "<<sorted[4]<< ", "<<sorted[5] << ", "<<sorted[6] << ", " << sorted[7] << ", "<< sorted[8]<< ", "<< sorted[9]<<"\n";
  }

  TEST(examples,twins) {
    examples a;
    vector<int> temp=a.primes(1000);
    vector<tuple<int,int>> res=a.twins(temp);
    
    for(int i=0;i<res.size();i++){
      cout << get<0>(res[i]) << ", "<< get<1>(res[i]) <<"\n";
    }
  }

  TEST(DB,Basics) {

        DB db;
        try{
          db.insert("earth", 1, 1)            
            .insert("mars", 0.11, 1.524)
            .insert("moon", 0.012, 1)
            .insert("exoplanet one", 1, 1054.4)
            .insert("jupiter", 318, 5.2)
            .insert("jupiter", 318, 5.2);
          ASSERT_EQ(NAME(db.find(0)), "earth");
        }catch(runtime_error e){
          ASSERT_STREQ(e.what(), "Name already exists");
        }

        

        auto rows = db.where([](DB::Row row) { return  MASS(row) < 1; }); 

        ASSERT_EQ(rows.size(), 2);

        try {
            db.drop(2)                        
              .find(2);  
            FAIL();
        } catch ( runtime_error e ) {
            ASSERT_STREQ(e.what(), "Could not find an entry with the given key");
        }     

  }

  TEST(DB,find_by_name) {

        DB db;
        try{
          db.insert("earth", 1, 1)            
            .insert("mars", 0.11, 1.524)
            .insert("moon", 0.012, 1)
            .insert("exoplanet one", 1, 1054.4)
            .insert("jupiter", 318, 5.2);
            
          ASSERT_EQ(NAME(db.find_by_name("moon")), "moon");
          ASSERT_EQ(KEY(db.find_by_name("moon")), 2);
          ASSERT_EQ(MASS(db.find_by_name("moon")), 0.012);
          ASSERT_EQ(DISTANCE(db.find_by_name("moon")), 1);
        }catch(runtime_error e){
          ASSERT_STREQ(e.what(), "Name already exists");
        }
  }

  TEST(DB,find_by_name2) {

        DB db;
        try{
          db.insert("earth", 1, 1)            
            .insert("mars", 0.11, 1.524)
            .insert("moon", 0.012, 1)
            .insert("exoplanet one", 1, 1054.4)
            .insert("jupiter", 318, 5.2);
            db.find_by_name("234");
            
        }catch(runtime_error e){
          ASSERT_STREQ(e.what(), "Could not find row by name");
        }
  }

  TEST(DB,create_test_data) {

        DB db;
        db.create_test_data(10);
        for(int i=0;i<10;i++){
          cout << NAME(db.find(i)) << ", " << MASS(db.find(i)) << ", "<< DISTANCE(db.find(i)) <<"\n";
        }
  }

  TEST(DB,size) {
        DB db;
        db.insert("earth", 1, 1)            
          .insert("mars", 0.11, 1.524)
          .insert("moon", 0.012, 1)
          .insert("exoplanet one", 1, 1054.4)
          .insert("jupiter", 318, 5.2);
        ASSERT_EQ(db.size(), 5);
  }

  TEST(DB,aaccumulate) {
        DB db;
        db.insert("earth", 1, 1)            
          .insert("mars", 2, 2)
          .insert("moon", 3, 3)
          .insert("exoplanet one", 4, 4)
          .insert("jupiter", 5, 5);

        double total_mass = db.accumulate([](DB::Row row) { return MASS(row); });
        ASSERT_EQ(total_mass, 15);
  }

  TEST(DB,average_mass) {
        DB db;
        db.insert("earth", 1, 1)            
          .insert("mars", 2, 1.524)
          .insert("moon", 3, 1)
          .insert("exoplanet one", 4, 1054.4)
          .insert("jupiter", 5, 5.2);
        ASSERT_EQ(db.average_mass(), 3);
  }

  TEST(DB,average_distance) {
        DB db;
        db.insert("earth", 1, 1)            
          .insert("mars", 2, 2)
          .insert("moon", 3, 3)
          .insert("exoplanet one", 4, 4)
          .insert("jupiter", 5, 5);
        ASSERT_EQ(db.average_distance(), 3);
  }


}






