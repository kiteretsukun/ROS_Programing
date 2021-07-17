#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>
#include <thread>
#include <mutex>

/*** 名前を省略して利用できるように宣言 ***/
using std_msgs::msg::Int32;

/*** グローバル変数の宣言 ***/
rclcpp::Node::SharedPtr g_node = nullptr;
std::mutex g_mutex;
int g_number1 = 0, g_number2 = 0;

/*** Int 32型をサブスクライブするコールバック関数(1) ***/
void onNumber1Subscribed(const Int32::SharedPtr msg){
    std::lock_guard<std::mutex> lock(g_mutex);
    g_number1 = msg->data;
}

/*** Int 32型をサブスクライブするコールバック関数(2) ***/
void onNumber2Subscribed(const Int32::SharedPtr msg){
    std::lock_guard<std::mutex> lock(g_mutex);
    g_number2 = msg->data;
}

int main(int argc, char **argv){
    /*** プロセスの初期化 ***/
    rclcpp::init(argc, argv);
    /*** ノードの初期化 ***/
    g_node = rclcpp::Node::make_shared("subscriber");
    /*** サブスクライバの初期化 ***/
    auto sub1 = g_node->create_subscription<Int32>("number1", 10, onNumber1Subscribed);
    auto sub2 = g_node->create_subscription<Int32>("number2", 10, onNumber2Subscribed);

    /*** ループ周期の設定 ***/
    rclcpp::WallRate loop(1);

    /*** 新規スレッドでコールバックを監視 ***/
    std::thread([]{rclcpp::spin(g_node);}).detach();

    /*** CTRC+Cで中断されるまで無限ループ ***/
    while(rclcpp::ok()){
        g_mutex.lock();
            int sum = g_number1 + g_number2;
        g_mutex.unlock();
        RCLCPP_INFO(g_node->get_logger(), "Sum : %d", sum);
        loop.sleep();
    }

    /*** プロセスの終了 ***/
    g_node = nullptr;
    rclcpp::shutdown();
    return 0;
}