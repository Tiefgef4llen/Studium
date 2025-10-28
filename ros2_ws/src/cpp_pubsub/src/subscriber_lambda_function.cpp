// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    auto topic_callback =
      [this](std_msgs::msg::Int32::UniquePtr msg) -> void {
        // RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg->data);
        if (msg->data != 0)
        {
          sum_ += msg->data;
          count_++;
        } else 
        {
          RCLCPP_INFO(this->get_logger(), "Received zero, avg: %f", static_cast<double>(sum_) / count_);
          sum_ = 0;
          count_ = 0;
        }
      };
    subscription_ =
      this->create_subscription<std_msgs::msg::Int32>("topic", 10, topic_callback);
  }

private:
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
  size_t count_;
  uint32_t sum_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
