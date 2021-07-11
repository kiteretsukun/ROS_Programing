#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/msg/int32_stamped.hpp>

/*** 名前空間を省略して利用できるように宣言 ***/
using tutorial_interfaces::msg::Int32Stamped;

int main(int argc, char **argv){
    /*** プロセスの初期化 ***/
    rclcpp::init(argc, argv);
    /*** ノードの初期化 ***/
    auto node = rclcpp::Node::make_shared("publisher");
    /*** パブリッシャの初期化 ***/
    auto pub = node->create_publisher<Int32Stamped>("number", 10);
    /*** ループ周期の設定 ***/
    rclcpp::WallRate loop(1);
    /*** パブリッシュするメッセージの宣言 ***/
    Int32Stamped msg;
    /*** CTRL+C で中断されるまで無限ループ ***/
    while(rclcpp::ok()){
        /*** メッセージのカウントをインクリメント ***/
        msg.data++;
        /*** メッセージに現在時刻を代入 ***/
        msg.header.stamp = node->now();
        /*** メッセージのカウント、現在時刻を表示 ***/
        int sec = msg.header.stamp.sec, nanosec = msg.header.stamp.nanosec;
        RCLCPP_INFO(node->get_logger(), "I publish : %d @ %d.%09d", msg.data, sec, nanosec);
        /*** メッセージのパブリッシュ ***/
        pub->publish(msg);
        loop.sleep();
    }
    
    /*** プロセスの終了 ***/
    rclcpp::shutdown();
    return 0;

}