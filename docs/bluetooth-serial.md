Firstly:
pair devices


**client side**
    rfcomm connect /dev/rfcomm0 00:15:83:3D:0A:57 3
    screen /dev/rfcomm0 115200


**server side**
    mknod -m 666 /dev/rfcomm0 c 216 0
    rfcomm watch /dev/rfcomm0 3 /sbin/agetty rfcomm0 115200 linux

