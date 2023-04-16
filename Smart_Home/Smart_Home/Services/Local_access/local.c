/*
 * local.c
 *
 * Created: 4/12/2023 7:26:01 AM
 *  Author: Hesham Hany
 */

#include "local.h"

bool running_devices[7];
u8 running_devices_screen;
u8 control_devices_screen;

void Local_access_init(void) {
  LCD_init();
  Keypad_init();
  }

void Get_running_devices(void) {
  // Check the on/off lamps
  u8 lamp;
  for (lamp = 0; lamp < 5; lamp++) {
    DIO_Read(lamp + 2, PORT_C, &running_devices[lamp]);
    }
  // Check the dimmable lamp
  running_devices[5] = read_bit(TCCR2, COM21); // To see if the OC pins are connected
  // Check the AC
  DIO_Read(7, PORT_D, &running_devices[6]);
  }

void next_running_device_screen(void) {
  running_devices_screen++;
  }

void Show_bottom_options_menu(u8 menu) {
  switch (menu) {
      case 1:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_1);
        break;
      case 2:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_2);
        break;
      case 3:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_3);
        break;
      case 4:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_4);
        break;
      case 5:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_5);
        break;
      case 6:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_6);
        break;
      case 7:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_7);
        break;
      case 8:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_8);
        break;
      case 9:
        LCD_writeString_xy(0, 1, OPTIONS_MENU_9);
        break;
    }
  }

void Show_side_options_menu(u8 menu) {
  LCD_writeString_xy(12, 0, BACKSPACE_OPTION);
  LCD_writeString_xy(12, 1, ENTER_OPTION);
  }

void Show_running_devices(u8 screen) {
  LCD_clear_screen();
  // Write device name
  switch (screen) {
      case 7:
        LCD_writeString_xy(0, 0, "AC: ");
        break;
      default:
        LCD_writeString_xy(0, 0, "Lamp");
        LCD_sendData(screen + 48);
        LCD_sendString(": ");
        break;
    }
  // Write the device state
  if (running_devices[screen - 1])
    LCD_sendString("On");
  else
    LCD_sendString("Off");
  // Show the options menu
  switch (screen) {
      case 1:
        Show_bottom_options_menu(3);
        break;
      case 7:
        Show_bottom_options_menu(2);
        break;
      default:
        Show_bottom_options_menu(1);
        break;
    }
  }

/*void LCD_menu*/
