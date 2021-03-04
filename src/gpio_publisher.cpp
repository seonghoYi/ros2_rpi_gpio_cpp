#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"


using namespace std::chrono_literals;


class GpioPublisher : public rclcpp::Node
{
public:
    GpioPublisher()
    : Node("GPIO_publisher"), toggle_(false)
    {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        gpio_publisher_ = this->create_publisher<std_msgs::msg::Bool>(
            "GpioState", qos_profile);

        timer_ = this->create_wall_timer(
            1s, std::bind(&GpioPublisher::publish_gpio_msg, this));
    }

private:
    void publish_gpio_msg()
    {
        auto msg = std_msgs::msg::Bool();
        msg.data = toggle_;
        RCLCPP_INFO(this->get_logger(), "GPIO state: '%d'", msg.data);
        gpio_publisher_->publish(msg);
        
        toggle_ ^= true;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    bool toggle_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr gpio_publisher_;
};



int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GpioPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}