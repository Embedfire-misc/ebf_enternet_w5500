/**
******************************************************************************
* @file    			main.c
* @author  			WIZnet Software Team
* @version 			V1.0
* @date    			2015-02-14
* @brief   			用3.5.0版本库建的工程模板
* @attention  	实验平台：野火 iSO-MINI STM32 开发板 + 野火W5500网络适配板
*
*               默认使用野火开发板的SPI1接口，请断开“J10”A4与cs间的短接帽
*							
*               内网测试，请讲野火网络适配版与路由器相接。并确认路由器的
*               DHCP功能处于打开的状态。
*
* 实验平台:野火 iSO-MINI STM32 开发板 
* 论坛    :http://www.firebbs.cn
* 淘宝    :http://fire-stm32.taobao.com
*
******************************************************************************
*/ 
#include <stdio.h>
#include <string.h>

#include "stm32f10x.h"

#include "bsp_usart1.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"
#include "bsp_led.h"

#include "w5500.h"
#include "W5500_conf.h"
#include "socket.h"
#include "utility.h"
/*app函数头文件*/
#include "dhcp.h"

int main(void)
{
	systick_init(72);				            /*初始化Systick工作时钟*/
	USART1_Config(); 				            /*初始化串口通信:115200@8-n-1*/
	i2c_CfgGpio();				    	        /*初始化eeprom*/
	
	printf("  野火网络适配版 DHCP Demo V1.0 \r\n");		
	
	gpio_for_w5500_config();	         	/*初始化MCU相关引脚*/
	reset_w5500();					            /*硬复位W5500*/
	set_w5500_mac();                    /*配置MAC地址*/
	
  socket_buf_init(txsize, rxsize);    /*初始化8个Socket的发送接收缓存大小*/

	printf(" 野火网络适配板作为DHCP客户端，尝试从DHCP服务器获取IP地址 \r\n");
	 
	while(1)                            /*循环执行的函数*/ 
	{
		do_dhcp();                        /*DHCP测试程序*/
	}
} 


