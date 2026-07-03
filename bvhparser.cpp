#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "skeleton.hpp"
#include "bvhparser.hpp"
#include <stack>
auto BVHParser::createNewSkeleton(const std::string& name, const int index) -> Skeleton
{
    Skeleton skeleton(name, index);
    return skeleton;
    }
int BVHParser::addJointToSkeleton(Skeleton& skeleton, const Joint& joint) {
    skeleton.addJoint(joint);
    return 0;
}
void BVHParser::parseBVHfile(const std::string& filename, Skeleton& skeleton, int parentIndex)
{
    std::cout << "Parsing BVH file: " << filename << std::endl;
    std::ifstream stream(filename, std::ios::in);
    if (!stream.is_open()) {
        std::cerr << "Error opening BVH file: " << filename << std::endl;
        return;
    }
    int totalFrames = 0;
    double frameTime = 0;
    int currentFrame = 0;
    int numChannels = 0;
    int jointIndex = 0;
    std::string line;
    std::string name;
    std::string token, rootName;
    bool endSite = false;
    std::stack<int> parentStack;

    while (std::getline(stream, line)) {
        std::cout << line << std::endl;
        if (line.find("HIERARCHY") != std::string::npos) {
            std::cout << "Found HIERARCHY section." << std::endl;
        }
        else if (line.find("ROOT") != std::string::npos) {
            std::istringstream iss(line);
            iss >> token >> rootName;
            std::cout << "Found ROOT joint: " << rootName << std::endl;
            Joint rootJoint = skeleton.createNewJoint(rootName, 0, LocalTransform{}, {}, -1);
            addJointToSkeleton(skeleton, rootJoint);
            parentStack.push(0); // Push the root joint index onto the stack
        }
        else if (line.find("JOINT") != std::string::npos) {
            std::istringstream iss(line);
            iss >> token >> name;
            std::cout << "Found JOINT: " << name << std::endl;
            // Create a new joint and add it to the skeleton
            addJointToSkeleton(skeleton, skeleton.createNewJoint(name, ++jointIndex, LocalTransform{}, {}, skeleton.joints[parentStack.top()].index));
            parentStack.push(jointIndex); // Push the current joint index onto the stack
        }
        else if (line.find("OFFSET") != std::string::npos) {
            if (1)
            {
                std::istringstream iss(line);
                iss >> token >> skeleton.joints[jointIndex].offset.x >> skeleton.joints[jointIndex].offset.y >> skeleton.joints[jointIndex].offset.z;
                std::cout << "Found OFFSET: " << skeleton.joints[jointIndex].offset.x << ", " << skeleton.joints[jointIndex].offset.y << ", " << skeleton.joints[jointIndex].offset.z << std::endl;
            }



        }
        else if (line.find("CHANNELS") != std::string::npos) {
            std::istringstream iss(line);
            iss >> token >> numChannels; // Read the number of channels
            std::cout << "Found CHANNELS: " << numChannels << std::endl;
            while (iss >> token) {
                if (token == "Xposition") {skeleton.joints[jointIndex].channels.push_back(Channel::PosX);}
                else if (token == "Yposition") {skeleton.joints[jointIndex].channels.push_back(Channel::PosY);}
                else if (token == "Zposition") {skeleton.joints[jointIndex].channels.push_back(Channel::PosZ);}
                else if (token == "Xrotation") {skeleton.joints[jointIndex].channels.push_back(Channel::RotX);}
                else if (token == "Yrotation") {skeleton.joints[jointIndex].channels.push_back(Channel::RotY);}
                else if (token == "Zrotation") {skeleton.joints[jointIndex].channels.push_back(Channel::RotZ);}
                else if (token == "CHANNELS") {continue; } // Skip the "CHANNELS" token
                else { std::cerr << "Unknown channel type: " << token << std::endl; }

            }
        }
        else if (line.find("End Site") != std::string::npos)
        {
            addJointToSkeleton(skeleton, skeleton.createNewJoint("End Site", ++jointIndex, LocalTransform{}, {}, skeleton.joints[parentStack.top()].index));
            endSite = true;
            std::cout << "End Site" << std::endl;
        }
        else if (line.find('}') != std::string::npos) {
            if (!endSite)
            {   
                parentStack.pop();
                continue;
            }
             // Pop the current joint index from the stack
            endSite = false;
        }
        else if (line.find("MOTION") != std::string::npos) {
            std::cout << "Found MOTION section." << std::endl;
        }
        else if (line.find("Frames:") != std::string::npos) {
            std::istringstream iss(line);
            iss >> token >> totalFrames;
            std::cout << "Found Frames: " << totalFrames << std::endl;
        }
        else if (line.find("Frame Time:") != std::string::npos) {
            std::istringstream iss(line);
            iss >> token >> token >> frameTime;
            std::cout << "Found Frame Time: " << frameTime << std::endl;
        }
        else if (line.find_first_of("0123456789-") != std::string::npos) {
            std::cout << "Found Frame Data: " << line << std::endl;
            std::istringstream iss(line);
            std::vector<float> frameData;
            float value;
            while (iss >> value) {
                frameData.push_back(value);
            }
            std::cout << "Frameline:";
            for (size_t i = 0; i < frameData.size(); ++i) {
                std::cout << frameData[i] << " ";
            }
            std::vector<std::vector<float>> jointFrameData(skeleton.joints.size());
            std::cout << std::endl;
        }
    };
}
void BVHParser::PrintSkeleton(const Skeleton& skeleton)
{
    std::cout << "Skeleton Name: " << skeleton.name << std::endl;
    std::cout << "Skeleton Index: " << skeleton.index << std::endl;
    std::cout << "Number of Joints: " << skeleton.joints.size() << std::endl;
    for (const auto& joint : skeleton.joints) {
        std::cout << "Joint Name: " << joint.name << ", parentIndex: " << joint.parentIndex << ", Index: " << joint.index
                  << ", Offset: (" << joint.offset.x << ", "
                  << joint.offset.y << ", "
                  << joint.offset.z << ")"
                  << ", Channels: ";
        for (const auto& channel : joint.channels) {
            switch (channel) {
            case Channel::PosX: std::cout << "PosX "; break;
            case Channel::PosY: std::cout << "PosY "; break;
            case Channel::PosZ: std::cout << "PosZ "; break;
            case Channel::RotX: std::cout << "RotX "; break;
            case Channel::RotY: std::cout << "RotY "; break;
            case Channel::RotZ: std::cout << "RotZ "; break;
            }
        }
        
        std::cout << std::endl;
    }
}