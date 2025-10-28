#include <chrono>
#include <memory>
#include <string>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "chatting/msg/nachricht.hpp"

using namespace std::chrono_literals;

class SchreibClient : public rclcpp::Node
{
public:
    SchreibClient(std::string userName)
        : Node("chat_publisher"), userName_(userName)
    {
        publisher_ = this->create_publisher<chatting::msg::Nachricht>("chatmessage", 10);

        // Create a timer that checks for input and publishes
        auto timer_callback = [this]() -> void {
            std::string text;
            
            // Prompt for message
            std::cout << "Nachricht eingeben: ";
            std::getline(std::cin, text);
            
            if (!text.empty()) {
                auto message = chatting::msg::Nachricht();
                message.user = this->userName_;
                message.text = text;
                
                RCLCPP_INFO(this->get_logger(), "Nachricht gesendet: [%s] | %s", 
                    message.user.c_str(), message.text.c_str());
                publisher_->publish(message);
            }
        };
        
        // Check for input every 100ms
        timer_ = this->create_wall_timer(100ms, timer_callback);
    }

private:
    rclcpp::Publisher<chatting::msg::Nachricht>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::string userName_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // Get username
    std::string userName;
    std::cout << "Enter your username: ";
    std::getline(std::cin, userName);
    
    if (userName.empty()) {
        userName = "Anonymous";
    }
    
    // Create and spin the node
    auto node = std::make_shared<SchreibClient>(userName);
    rclcpp::spin(node);
    rclcpp::shutdown();
    
    return 0;
}