#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"
#include <wiringPi.h>

using namespace std::chrono_literals;


class GpioPublisher : public rclcpp::Node
{
public:
    GpioPublisher()
    : Node("GPIO_publisher"), toggle_(false)
    {

    }

private:
    void publish_gpio_msg()
    {
        auto msg = std_msgs::msg::Bool();
        msg.data = toggle_;
    }

    bool toggle_;
};

