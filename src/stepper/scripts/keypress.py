import rospy

from std_msgs.msg import String

msg = """
Choose the direction of stepper motor
---------------------------
Clockwise: c
Counter-Clockwise: cc
"""

def stepper():
  # initialize node and set it as a publisher
  rospy.init_node('stepper_keypub')
  pub = rospy.Publisher('/stepper_controller', String, queue_size=10)
  rate = rospy.Rate(10)

  print(msg)
  
  # run code while connection is not down
  while not rospy.is_shutdown():
    dir = input("Enter direction: ")

    # if the input passes, then its published to the topic
    if dir == 'c' or dir == 'cc':
      rospy.loginfo('Chosen %s' % str(dir))
      pub.publish(str(dir))
    else:
      print("Please choose from given options")

    rate.sleep()

if __name__ == '__main__':
  try:
    stepper()
  except rospy.ROSInterruptException:
    pass
