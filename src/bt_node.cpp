#include <behaviortree_cpp/bt_factory.h>
#include <rclcpp/rclcpp.hpp>


class SayHello : public BT::SyncActionNode {

public:

  SayHello(const std::string& name, const BT::NodeConfig& config)
    : BT::SyncActionNode(name, config) {}

  static BT::PortsList providedPorts() {
    return { };
  }

  BT::NodeStatus tick() override {
    RCLCPP_INFO(rclcpp::get_logger("SayHello"), "Hello, World!");
    return BT::NodeStatus::SUCCESS;
  }

};


int main(int argc, char** argv) {

  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("bt_node");

  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<SayHello>("SayHello");

  auto tree = factory.createTreeFromText(R"(
    <root main_tree_to_execute="MainTree">
      <BehaviorTree ID="MainTree">
        <SayHello/>
      </BehaviorTree>
    </root>
  )");

  while (rclcpp::ok()) {
    BT::NodeStatus status = tree.tickExactlyOnce();
    rclcpp::spin_some(node);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  rclcpp::shutdown();
  return 0;
}
