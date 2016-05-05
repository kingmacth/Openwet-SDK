#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define CHIP			"/dev/i2c-0"
#define CHIP_ADDR		0x23

 

int main()

{

         printf("hello,this is i2c tester \n");

         int fd =open(CHIP, O_RDWR);

         if (fd< 0) {

                   printf("open"CHIP"failed \n");

                   goto exit;

         }

 

         if (ioctl(fd,I2C_SLAVE_FORCE, CHIP_ADDR) < 0) {           /*设置芯片地址                                   */

                   printf("oictl:setslave address failed\n");

                   goto close;

         }

 

         struct		i2c_msg msg;

         unsigned char      rddata[2];
         unsigned char      rdaddr[2] = {0x10, 0};                                            /* 将要读取的数据在芯片中的偏移量          */
         unsigned char      wrbuf[3] = {0x10, 0, 0x3c};                                   /* 要写的数据，头两字节为偏移量    */

         /*printf("inputa char you want to write to E2PROM\n");
         wrbuf[2]= getchar();
         printf("writereturn:%d, write data:%x\n", write(fd, wrbuf, 1), wrbuf[2]);
         sleep(5);*/
         printf("writeaddress return: %d\n",write(fd, rdaddr, 1));      /* 写入0X10开启数据采集    */
	 sleep(1);
         printf("readdata return:%d\n", read(fd, &rddata, 2));		//读取两字节光照数据
         printf("rddata:%x%02x\n", rddata[0], rddata[1]);


close:

         close(fd);

exit:

         return 0;

}
