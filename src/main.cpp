#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

namespace boost_uuid = boost::uuids;
int main() {

    const std :: string uuid_str = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
    std::cout << uuid_str << std::endl;
    return 0;
}
