#include <ng_imploder/imploder/Imploder.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << extras::start(argv[0]) << std::endl;
        ng::Imploder imploder(argv[1]);
        imploder.implode();
        std::cout << extras::end(argv[0]) << std::endl << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << extras::fail(ex.what()) << std::endl << std::endl;
        return -1;
    }
}
