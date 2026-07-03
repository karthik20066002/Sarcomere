#include "joint.hpp"
#include "skeleton.hpp"

Joint Skeleton::createNewJoint(const std::string& name, int index, LocalTransform localOffset, std::vector<Channel> channelList, int parentIndex) {
    return Joint(name, index, localOffset, channelList, parentIndex);
}


