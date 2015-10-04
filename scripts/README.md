Ziroba Robot
============


systemd-services:
----------------
    * Status LED
       * this service turns on a LED when a network interface is UP
       * copy systemd-services/status-led.service file to /etc/systemd/system
       * copy status_led script to /sbin
       * chose a GPIO and connect a led (default 60 beaglebone black)
       * systemctl enable status-led.service
       * reboot the system

