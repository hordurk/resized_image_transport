#include "resized_image_transport/resized_publisher.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <dynamic_reconfigure/server.h>
#include <cv.h>
#include <highgui.h>
#include <boost/make_shared.hpp>

#include <vector>
#include <sstream>

using namespace cv;
using namespace std;

namespace enc = sensor_msgs::image_encodings;

namespace resized_image_transport
{

void ResizedPublisher::advertiseImpl(ros::NodeHandle &nh, const std::string &base_topic, uint32_t queue_size,
                                        const image_transport::SubscriberStatusCallback &user_connect_cb,
                                        const image_transport::SubscriberStatusCallback &user_disconnect_cb,
                                        const ros::VoidPtr &tracked_object, bool latch)
{
  typedef image_transport::SimplePublisherPlugin<sensor_msgs::Image> Base;
  Base::advertiseImpl(nh, base_topic, queue_size, user_connect_cb, user_disconnect_cb, tracked_object, latch);

  //img_init = 0;

  // Set up reconfigure server for this topic
  reconfigure_server_ = boost::make_shared<ReconfigureServer>(this->nh());
  ReconfigureServer::CallbackType f = boost::bind(&ResizedPublisher::configCb, this, _1, _2);
  reconfigure_server_->setCallback(f);
}

void ResizedPublisher::configCb(Config& config, uint32_t level)
{
  config_ = config;
  //img_init = 0;
}

void ResizedPublisher::publish(const sensor_msgs::Image& message, const PublishFn& publish_fn) const
{
  // Compressed image message
  //sensor_msgs::Image resized;
  //resized.header = message.header;
  //resized.format = message.encoding;

  // Bit depth of image encoding
  //int bitDepth = enc::bitDepth(message.encoding);
  //int numChannels = enc::numChannels(message.encoding);
  cv_bridge::CvImage img;
  cv_bridge::CvImageConstPtr cv_ptr;
  try
  {
          cv_ptr = cv_bridge::toCvShare(message, boost::shared_ptr<const void>(), "");
  }
  catch(cv_bridge::Exception& e)
  {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
  }

  if(img.image.cols != config_.width || img.image.rows != config_.height) {
          img.image.create(config_.height, config_.width, cv_ptr->image.type() );
          img.encoding = cv_ptr->encoding;
          //img_init = 1;
  }

  img.header = message.header;
  cv::resize(cv_ptr->image, img.image, img.image.size(), 0, 0, CV_INTER_AREA);
  //pub.publish(img.toImageMsg());


  publish_fn(*img.toImageMsg());

}

} //namespace resized_image_transport
