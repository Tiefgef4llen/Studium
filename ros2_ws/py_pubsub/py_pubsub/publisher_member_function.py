# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node

from std_msgs.msg import String, Int32
import json

USER_NAME = ""

class MinimalPublisher(Node):

    def __init__(self, user_name: str = ""):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(String, 'chatmessage', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0
        self.user_name = user_name

    def timer_callback(self):
        # struct for user and text
        payload = {
            "user": self.user_name or "anonymous",
            "text": 'Hello World: %d' % self.i,
        }
        msg = String()
        # Serialize the struct as JSON so it can be sent over a String topic
        msg.data = json.dumps(payload)
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1


def main(args=None):
    try:
        # Prompt for user name first and pass it into the node so it appears in the struct
        user_name = input("Enter your user name: ")
        with rclpy.init(args=args):
            minimal_publisher = MinimalPublisher(user_name=user_name)

            rclpy.spin(minimal_publisher)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass


if __name__ == '__main__':
    main()
