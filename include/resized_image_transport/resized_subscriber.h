#include "image_transport/simple_subscriber_plugin.h"
#include <sensor_msgs/Image.h>

namespace resized_image_transport {

class ResizedSubscriber : public image_transport::SimpleSubscriberPlugin<sensor_msgs::Image>
{
public:
  virtual ~ResizedSubscriber() {}

  virtual std::string getTransportName() const
  {
    return "resized";
  }

protected:
  virtual void internalCallback(const sensor_msgs::ImageConstPtr& message,
                                const Callback& user_cb);
};

} //namespace resized_image_transport
