Ziroba Robot
============

Ziroba is a low cost car robot built from cheap parts

Our main goal is easy replication and modification
 
Features:
---------

   * Communication over Wifi or bluetooth
   * Control from PC / Android
   * Cross Platform
      * Beaglebone-black / Raspberry Pi / Intel Galileo g1,g2 / esp8266
   * Camera Vision


Install:
--------
    On target platform:
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=/path/to/installdir ../

Runing:
------
    * setting up environment
       * source scripts/sysenv

    * stand-alone 
       * ssh to ziroba (ssh root@ziroba.local)
       * ./ziroba_pad

    * android 
       * ssh to ziroba
       * start the robot service: ./ziroba
       * on android start the ziroba app, connect to ziroba and start using the app

Ziroba-Robot
------------
![alt tag](https://github.com/ismaia/ziroba/raw/master/docs/ziroba.jpg)


