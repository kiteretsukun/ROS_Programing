#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/msg/int32_stamped.hpp>

/*** 名前空間を省略して利用できるように宣言 ***/
using tutorial_interfaces::msg::Int32Stamped;
/*** グローバル変数の宣言 ***/
rclcpp::Node::SharedPtr g_node = nullptr;

/*** Int32Stamped型をサブスクライブするコールバック関数 ***/
void onNumberSubscribed(const Int32Stamped::SharedPtr msg){
    RCLCPP_INFO(g_node->get_logger(), "I heard : %d @ %d.%09d",
     msg->data, msg->header.stamp.sec, msg->header.stamp.nanosec);
}

int main(int argc, char **argv){
    /*** プロセスの初期化 ***/
    rclcpp::init(argc, argv);
    /*** ノードの初期化 ***/
    g_node = rclcpp::Node::make_shared("subscriber");
    /*** サブスクライバの初期化 ***/
    auto sub = g_node->create_subscription<Int32Stamped>("number", 10, onNumberSubscribed);
    /*** コールバックの発生を待機 ***/
    rclcpp::spin(g_node);
    /*** プロセスの終了 ***/
    g_node = nullptr;
    rclcpp::shutdown();
    return 0;
}