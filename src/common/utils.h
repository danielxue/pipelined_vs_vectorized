#ifndef PIPELINED_VS_VECTORIZED_UTILS_H
#define PIPELINED_VS_VECTORIZED_UTILS_H

#include <iostream>
#include <fcntl.h>
//#include <boost/program_options.hpp>

void parseArgs(int argc, char* argv[], int& ctl_fd, bool& time) {
    ctl_fd = -1;
    time = true;

//    boost::program_options::options_description desc("Allowed options");
//    desc.add_options()
//        ("help", "produce help message")
//        ("control", boost::program_options::value<int>(), "set control fd for perf")
//        ("disable-time", "disable timing")
//    ;
//    boost::program_options::variables_map vm;
//    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
//    boost::program_options::notify(vm);
//
//    if (vm.count("help")) {
//        std::cout << desc << std::endl;
//        exit(1);
//    }
//
//    if (vm.count("control")) {
//        ctl_fd = vm["control"].as<int>();
//        if (fcntl(ctl_fd, F_GETFD) == -1) ctl_fd = -1;
//    }
//
//    if (vm.count("disable-time")) {
//        time = false;
//    }
}

#endif
