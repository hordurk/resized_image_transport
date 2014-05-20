#include "image_transport/simple_publisher_plugin.h"
#include <sensor_msgs/Image.h>
#include <dynamic_reconfigure/server.h>
#include <resized_image_transport/ResizedPublisherConfig.h>
#include <cv_bridge/cv_bridge.h>

namespace resized_image_transport {

class ResizedPublisher : public image_transport::SimplePublisherPlugin<sensor_msgs::Image>
{
public:
  virtual ~ResizedPublisher() {}

  virtual std::string getTransportName() const
  {
    return "resized";
  }

protected:
  // Overridden to set up reconfigure server
  virtual void advertiseImpl(ros::NodeHandle &nh, const std::string &base_topic, uint32_t queue_size,
                             const image_transport::SubscriberStatusCallback  &user_connect_cb,
                             const image_transport::SubscriberStatusCallback  &user_disconnect_cb,
                             const ros::VoidPtr &tracked_object, bool latch);

  virtual void publish(const sensor_msgs::Image& message,
                       const PublishFn& publish_fn) const;

  typedef resized_image_transport::ResizedPublisherConfig Config;
  typedef dynamic_reconfigure::Server<Config> ReconfigureServer;
  boost::shared_ptr<ReconfigureServer> reconfigure_server_;
  Config config_;

  void configCb(Config& config, uint32_t level);
};

} //namespace resized_image_transport
