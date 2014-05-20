#include <pluginlib/class_list_macros.h>
#include "resized_image_transport/resized_publisher.h"
#include "resized_image_transport/resized_subscriber.h"

PLUGINLIB_DECLARE_CLASS(image_transport, resized_pub, resized_image_transport::ResizedPublisher, image_transport::PublisherPlugin);

PLUGINLIB_DECLARE_CLASS(image_transport, resized_sub, resized_image_transport::ResizedSubscriber, image_transport::SubscriberPlugin);
