#include "ros/ros.h"
#include "std_srvs/Trigger.h"
#include "jetsonGPIO/jetsonGPIO.c"

bool hl_value = true; //default value for the headlights.
const jetsonTX2GPIONumber HL_PIN = jetsonTX2GPIONumber::gpio298; //GPIO pin for the pin 25 on the J1 GPIO header

/**
 * Call back function for to toggle the Headlight pin. This will change the electric output on the pin and enable or disable
 * the headlights.
 */
bool toggleHL(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res) {
    hl_value = !hl_value;

    if (hl_value) {
        res.message = "successfully toggle headlights to on";
        gpioSetValue(HL_PIN, 1);
    } else {
        res.message = "successfully toggle headlights to off";
        gpioSetValue(HL_PIN, 0);
    }
    res.success = static_cast<unsigned char>(true);
    return true;
}

/**
 * Initialize the configuration to control the GPIO pin.
 */
void initializeGPIO() {
    gpioExport(HL_PIN);
    gpioSetDirection(HL_PIN, 1);
    gpioSetValue(HL_PIN, 0);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "headlights");
    ros::NodeHandle nh;

    initializeGPIO();

    ros::ServiceServer service = nh.advertiseService("headlights", toggleHL);
    ros::spin();

    return 0;
}


