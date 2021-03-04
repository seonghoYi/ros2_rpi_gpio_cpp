#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/string.hpp"

#include <wiringPi.h>

using std::placeholders::_1;

const int LED1 = 8;


class GpioSubscriber : public rclcpp::Node
{
public:
    GpioSubscriber()
    : Node("GPIO_subscriber")
    {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        gpio_subscriber_ = this->create_subscription<std_msgs::msg::Bool>(
            "GpioState",
            qos_profile,
            std::bind(&GpioSubscriber::subscribe_topic_message, this, _1));
    }



private:
    void subscribe_topic_message(const std_msgs::msg::Bool::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "received gpio state: '%d'", msg->data);
        digitalWrite(LED1, msg->data);
    }

    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr gpio_subscriber_;
};


int main(int argc, char *argv[])
{
    
    wiringPiSetup();
    pinMode(LED1, OUTPUT);


    rclcpp::init(argc, argv);
    auto node = std::make_shared<GpioSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}