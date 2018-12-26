/**
 * @file accel_gyro.h
 *
 * @author spencer jackson
 * @date Initial: 19 Mar 2018
 * @version 1
 * @date Released: 19 Mar 2018
 * @brief generalized interface for an accelerometer/gryo IC, this is not a standalone feature, but is used by other features
 * @detail these functions may be implemented by different source files
 */

#include<stdbool.h>
#include<stdint.h>

typedef struct accel_gyro_data
{
    float x; //!< acceleration in m/s^2 (metres per sec per sec)
    float y; //!< acceleration in m/s^2 (metres per sec per sec)
    float z; //!< acceleration in m/s^2 (metres per sec per sec)
    float pitch; //!< rotational velocity about x axis in radians per second
    float roll;  //!< rotational velocity about y axis in radians per second
    float yaw;   //!< rotational velocity about z axis in radians per second
} accel_gyro_data_s; //!< struct passed to the callback when new data arrives

//the callback will be handed an accel_gyro_data_s;
bool accel_gyro_init(ml_sched_cb_f cb);
