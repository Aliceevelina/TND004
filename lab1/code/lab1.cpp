// lab1.cpp : stable partition
// Two algorithms: iterative and divide-and-conquer

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <functional>
#include <cassert>

/****************************************
 * Declarations                          *
 *****************************************/

// generic class to write an item to a stream
template <typename T>
class Formatter {
public:
    Formatter(std::ostream& os, int width, int per_line)
        : os_{os}, per_line_{per_line}, width_{width} {
    }

    void operator()(const T& t) {
        os_ << std::setw(width_) << t;
        if (++outputted_ % per_line_ == 0)
            os_ << "\n";
    }

private:
    std::ostream& os_;    // output stream
    const int per_line_;  // number of columns per line
    const int width_;     // column width
    int outputted_{0};    // counter of number of items written to os_
};

/* *************************************** */

namespace TND004 {
// Iterative algorithm
void stable_partition_iterative(std::vector<int>& V, std::function<bool(int)> p);


// Auxiliary function that performs the stable partition recursively
std::vector<int>::iterator stable_partition(std::vector<int>::iterator first,
                                            std::vector<int>::iterator last,
                                            std::function<bool(int)> p);

// Divide-and-conquer algorithm
void stable_partition(std::vector<int>& V, std::function<bool(int)> p) {
    TND004::stable_partition(std::begin(V), std::end(V), p);  // call auxiliary function
}
}  // namespace TND004

void execute(std::vector<int>& V, const std::vector<int>& res);

bool even(int i);

/****************************************
 * Main:test code                        *
 *****************************************/

int main() {
    /*****************************************************
     * TEST PHASE 1                                       *
     ******************************************************/
    {
        std::cout << "TEST PHASE 1\n\n";

        std::vector<int> seq{1, 2};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>{std::cout, " "});

        execute(seq, std::vector<int>{2, 1});
		
		std::cout << "\nEmpty sequence: ";
        std::vector<int> empty;

        execute(empty, std::vector<int>{});
    }

    /*****************************************************
     * TEST PHASE 2                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 2\n\n";

        std::vector<int> seq{2};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>{std::cout, " "});

        execute(seq, std::vector<int>{2});
    }

    /*****************************************************
     * TEST PHASE 3                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 3\n\n";

        std::vector<int> seq{3};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>{std::cout, " "});

        execute(seq, std::vector<int>{3});
    }

    /*****************************************************
     * TEST PHASE 4                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 4\n\n";

        std::vector<int> seq{3, 3};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>(std::cout, " "));

        execute(seq, std::vector<int>{3, 3});
    }

    /*****************************************************
     * TEST PHASE 5                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 5\n\n";

        std::vector<int> seq{1, 2, 3, 4, 5, 6, 7, 8, 9};

        std::cout << "Sequence: ";
        std::copy(std::begin(seq), std::end(seq), std::ostream_iterator<int>(std::cout, " "));

        execute(seq, std::vector<int>{2, 4, 6, 8, 1, 3, 5, 7, 9});
    }

    /*****************************************************
     * TEST PHASE 6                                       *
     ******************************************************/
    {
        std::cout << "\n\nTEST PHASE 6: test with long sequence loaded from a file\n\n";

        std::ifstream file("/Users/Alice/Desktop/SKOLA/TND004 - Datastrukturer/lab1/code/test_data.txt");

        if (!file) {
            std::cout << "Could not open test test_data.txt!!\n";
            return 0;
        }

        // read the input sequence from file
        std::vector<int> seq{std::istream_iterator<int>{file}, std::istream_iterator<int>()};
        file.close();

        std::cout << "Number of items in the sequence: " << seq.size() << '\n';

        // display sequence
        // std::for_each(std::begin(seq), std::end(seq), Formatter<int>(std::cout, 8, 5));

        // read the result sequence from file
        file.open("/Users/Alice/Desktop/SKOLA/TND004 - Datastrukturer/lab1/code/test_result.txt");

        if (!file) {
            std::cout << "Could not open test_result.txt!!\n";
            return 0;
        }

        std::vector<int> res{std::istream_iterator<int>{file}, std::istream_iterator<int>()};

        std::cout << "Number of items in the result sequence: " << res.size() << '\n';

        // display sequence
        // std::for_each(std::begin(res), std::end(res), Formatter<int>(std::cout, 8, 5));

        assert(seq.size() == res.size());

        execute(seq, res);
    }
}

/****************************************
 * Functions definitions                 *
 *****************************************/

bool even(int i) {
    return i % 2 == 0;
}

// Used for testing
void execute(std::vector<int>& V, const std::vector<int>& res) {
    std::vector<int> _copy{V};

    std::cout << "\n\nIterative stable partition: ";
    TND004::stable_partition_iterative(V, even);
    assert(V == res);  // compare with the expected result
    
    //Display for testing iterative
    std::copy(std::begin(V), std::end(V), std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\nDivide-and-conquer stable partition: ";
    TND004::stable_partition(_copy, even);
    assert(_copy == res);  // compare with the expected result
    
    //Display for testing divide-and-conquer
    std::copy(std::begin(_copy), std::end(_copy), std::ostream_iterator<int>(std::cout, " "));
}

//Iterative algorithm T(n) = O(n)
void TND004::stable_partition_iterative(std::vector<int>& V, std::function<bool(int)> p) {
    // IMPLEMENT before Lab1 HA
    
    std::vector<int> e; e.reserve(V.size()); //O(n), O(1) //Create vectors a and b and reserve the same size as V
    std::vector<int> o; o.reserve(V.size()); //O(n), O(1) //These will store the even and the odd integers in two separate vectors
    
    for(unsigned long i=0; i < V.size(); i++) { //O(n)
        
        if (p(V[i])) { //O(1)
            e.push_back(V[i]); //O(1) //If the bool p returns true, insert the value at the end of the even-vector
        }
        
        else {
            o.push_back(V[i]); //O(1) //If the bool p returns false, insert the value at the end of the odd-vector
        }
    }
    
    e.insert(e.end(), o.begin(), o.end()); //O(n) //When all integers are sorted and tested, insert the odd-vector at the end of the even
    V = e; //O(1)
}

//Best case: V.size = 0; 2 + 1 + 1 = 4
//Worst case: a big vector; 2 + n(3 + 1 + 1) + 1 + 1 = 5n + 4

// Auxiliary function that performs the stable partition recursively
// Divide-and-conquer algorithm: stable-partition the sub-sequence starting at first and ending at
// last-1.
// If there are items with property p then return an iterator to the end of the block
// containing the items with property p. If there are no items with property p then return first.

// Auxiliary function that performs the stable partition recursively T(n) = O(n*log(n))
//function that calls on itself as a form of loop
std::vector<int>::iterator TND004::stable_partition(std::vector<int>::iterator first,
                                                    std::vector<int>::iterator last,
                                                    std::function<bool(int)> p) {

    if (first==last) { //O(n)
        return first;
    }
    
    else if ((first + 1 == last) && !p(*first)){ //O(n), O(1)
        return first;
    }
    
    else if ((first + 1 == last) && p(*first)){ //O(n), O(1)
        return first+1;
    }
    
    else
    {
        std::vector<int>::iterator mid = first + (last - first) / 2;
        
        std::vector<int>::iterator ll = stable_partition(first, mid, p); //O(log(n))
        std::vector<int>::iterator rr = stable_partition(mid, last, p); //O(log(n))
        return std::rotate(ll, mid, rr); //O(n)
    }
}
//Best case: first == last, 1
//Worst case: a big sequence, n(1 + 1 + 1 + T(n/2) + T(n/2)) = n(T(n/2) + 3) = O(n*log(n))
