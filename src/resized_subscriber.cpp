#include "resized_image_transport/resized_subscriber.h"
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv/cvwimage.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>


#include <limits>
#include <vector>

using namespace cv;

namespace enc = sensor_msgs::image_encodings;

namespace resized_image_transport
{

void ResizedSubscriber::internalCallback(const sensor_msgs::ImageConstPtr& message,
                                            const Callback& user_cb)

{
  user_cb(message);
}

} //namespace resized_image_transport
