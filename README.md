
- Write a ros node that writes in a text format the 2D location of the laser (x,y,theta) when laser messages arrive, and the timestamp
- FORMAT:
  1. One line per message
  2. LASER <timestamp.sec>.<timestamp.usec> <laser pose w.r.t. odom frame (x,y,theta)>
