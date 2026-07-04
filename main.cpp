#include <iostream>
#include "skeleton.hpp"
#include "bvhparser.hpp"
#include <boost/program_options.hpp>

int main(int argc, char** argv) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("Name", boost::program_options::value<std::string>(), "Name of the skeleton")
        ("Index", boost::program_options::value<int>(), "Index of the skeleton");
    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc,argv, desc), vm);
        boost::program_options::notify(vm);
    } catch (const boost::program_options::error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    if (!vm.count("Name") || !vm.count("Index")) {
        std::cerr << "Error: Name and Index are required." << std::endl;
        return 1;
    }
    std::string name = vm["Name"].as<std::string>();
    int index = vm["Index"].as<int>();
    BVHParser parser;
    Skeleton skeleton = parser.createNewSkeleton(name, index);
    std::cout << "Skeleton created with Name: " << name << " and Index: " << index << std::endl;
    MotionData motionData = parser.parseBVHfile("example.bvh", skeleton);
    std::cout << "Skeleton: " << skeleton.name << " with Index: " << skeleton.index << " has " << skeleton.joints.size() << " joints." << std::endl;
    parser.PrintSkeleton(skeleton, motionData);
    std::cout << std::endl;
    std::cout << "Motion Data: " << motionData.frameCount << " frames, Frame Time: " << motionData.frameTime << " seconds." << std::endl;
    std::vector<std::vector<float>> frameData = motionData.motionValues;
    std::cout << std::endl;
    return 0;
};