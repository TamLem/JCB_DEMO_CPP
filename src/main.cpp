#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

using std::cout;
using std::endl;
using std::string;
using namespace boost::uuids;

string generate_random_uuid()
{
    string uuid_str = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
    return uuid_str;
}

//generate random char [0-9a-f]
char generate_random_char()
{
    char c = rand() % 16;
    if (c < 10)
        c += '0';
    else
        c += 'a' - 10;
    return c;
}

namespace boost_uuid = boost::uuids;
int main() 
{
    srand(time(NULL));
    std::cout << generate_random_uuid() << std::endl;
    for (int i = 0; i < 10; i++)
    {
        cout << generate_random_char();
    }
    cout << endl;
    return 0;
}
