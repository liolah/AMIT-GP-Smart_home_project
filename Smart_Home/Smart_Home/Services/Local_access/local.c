/*
 * local.c
 *
 * Created: 4/12/2023 7:26:01 AM
 *  Author: Hesham Hany
 */

#include "local.h"

 // Used to store the state of the lamps and the AC
bool running_devices[7];

// Used to store the state of the lamps, including the brightness of lam6
s8 devices_status[6];

// The last screen shown on the LCD in show running devices task
u8 running_devices_screen;

// The last screen shown on the LCD in devices control task
u8 control_devices_screen;

// 0 = The user's in the progress of entering the user code
// 1 = The user is entering the password
u8 login_stage;

// When cleared the LCD gets initialized to show the appropriate login screen
bool login_stage_started;

// When both an admin remote user and a local user are connected to the system, the local user has to get a permission from the admin to be able to control the system at the same time.
bool control_permission_granted;

// Used to determine how the keypad input will be used.
// 0 = The user is logged out - Showing running devices
// 1 = Login in progress. The user is attempting to login.
// 2 = Devices control. The user's logged in and is controlling the devices. 
u8 local_control_running_task;

s8 input_buffer[11];
u8 input_buffer_pointer;

ST_User_t local_user;

// Initialize the local control system
void Local_access_init(void) {
  LCD_init();
  Keypad_init();
  User_DB_init();
  }

// Updates the logical states (in/off) of the running devices' array
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

// Shows the bottom line options on the LCD
void Show_bottom_options_menu(u8 menu) {
  switch (menu) {
      case 1:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_1);
        break;
      case 2:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_2);
        break;
      case 3:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_3);
        break;
      case 4:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_4);
        break;
      case 5:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_5);
        break;
      case 6:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_6);
        break;
      case 7:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_7);
        break;
      case 8:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_8);
        break;
      case 9:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_9);
        break;
    }
  }

// Shows the side options list on the LCD
void Show_side_options_menu(void) {
  LCD_write_string_xy(12, 0, BACKSPACE_OPTION);
  LCD_write_string_xy(12, 1, ENTER_OPTION);
  }

// Updates the device status array, which has lamp 6 brightness level 
void Get_devices_status(void) {
  // Check the on/off lamps
  u8 lamp;
  for (lamp = 0; lamp < 5; lamp++) {
    DIO_Read(lamp + 2, PORT_C, &devices_status[lamp]);
    }
  devices_status[5] = (u8)(OCR1A / 200);
  }

// Shows the currently running devices with the appropriate control menu appended (Screen controls and login- no device controls)
void Show_running_devices(u8 screen) {
  // Do nothing if the correct screen is shown.
  // if (screen == running_devices_screen) return;
  LCD_clear_screen();
  // Write device name
  switch (screen) {
      case 7:
        LCD_write_string_xy(0, 0, "AC: ");
        break;
      default:
        LCD_write_string_xy(0, 0, "Lamp");
        LCD_sendData(screen + 48);
        LCD_write_string(": ");
        break;
    }
  // Write the device state
  if (running_devices[screen - 1])
    LCD_write_string("On");
  else
    LCD_write_string("Off");
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

// Shows the currently running devices with the appropriate control menu appended (Devices' controls)
void Show_devices_controls(u8 screen) {
  // Do nothing if the correct screen is shown.
  // if (screen == control_devices_screen) return;
  LCD_clear_screen();
  LCD_write_string_xy(0, 0, "Lamp");
  LCD_sendData(screen + 48);
  LCD_write_string(":  ");

  if (screen < 6) {
    // Write the device state
    if (devices_status[screen - 1])
      LCD_write_string("On");
    else
      LCD_write_string("Off");
    }
  else {
    s8 brightness[4];
    sprintf(brightness, "%d%%", devices_status[5]);
    }
  // Show the options menu
  switch (screen) {
      case 1:
        if (devices_status[0])
          Show_bottom_options_menu(8);
        else
          Show_bottom_options_menu(7);
        break;
      case 6:
        Show_bottom_options_menu(9);
        break;
      default:
        if (devices_status[screen - 1])
          Show_bottom_options_menu(6);
        else
          Show_bottom_options_menu(5);
        break;
    }
  }

// Handles setting the alarm and halting the system when the user enters invalid credentials during login
void invalid_local_login_attempt(void) {
  invalid_trails++;
  if (invalid_trails < 3) {
    LCD_clear_screen();
    LCD_move_cursor_xy(0, 0);
    LCD_sendData((3 - invalid_trails) + 48);
    LCD_write_string(" attempts");
    LCD_write_string_xy(0, 1, "remaining !");
    return;
    }
  Alarm_set();
  run_system = false;
  }

// Used in the super loop for getting the user input and handling it.
void Local_control_input_handler(void) {
  u8 pressed_key;
  EN_KeypadStatusCode_t keypad_stat = Keypad_getPressedKey(&pressed_key);
  switch (local_control_running_task) {
    // Show running devices
      case 0:
        Get_running_devices();
        if (running_devices_screen == 0) {  // First run
          Show_running_devices(1);
          running_devices_screen++;
          }
        if (keypad_stat == NO_KEY_PRESSED) return;
        switch (pressed_key) {
            case '1':
              if (running_devices_screen > 1) running_devices_screen--;
              break;
            case '2':
              local_control_running_task = 1;
              break;
            case '3':
              if (running_devices_screen < 7) running_devices_screen++;
              break;
          }
        Show_running_devices(running_devices_screen);
        break;
        // Logging in
      case 1:
        if (keypad_stat == NO_KEY_PRESSED) return;
        switch (login_stage) {
          // Entering the user code
            case 0:
              if (!login_stage_started) {
                LCD_clear_screen();
                Show_side_options_menu();
                LCD_write_string_xy(0, 0, "User Code:");
                LCD_move_cursor_xy(0, 1);
                login_stage_started = true;
                input_buffer_pointer = 0;
                }
              if (pressed_key == '-') { // Delete last input number
                if (input_buffer_pointer > 0) input_buffer_pointer--;
                LCD_write_string_xy(input_buffer_pointer, 1, " ");
                LCD_move_cursor_xy(input_buffer_pointer, 1);
                }
              else if (pressed_key == '=') {
                input_buffer[input_buffer_pointer] = 0;
                // Validate user code
                EN_UserStatusCode_t codeExists = getUserByCode(input_buffer, &local_user);
                if (codeExists == USER_FOUND) {
                  login_stage_started = false;
                  login_stage = 1;
                  }
                else {
                  LCD_clear_screen();
                  LCD_write_string_xy(5, 0, "Wrong");
                  LCD_write_string_xy(2, 1, "User Code !");
                  invalid_local_login_attempt();
                  }
                }
              else if (pressed_key >= '0' && pressed_key <= '9') { // Ignoring invalid options
                if (input_buffer_pointer < 6) {
                  input_buffer[input_buffer_pointer] = pressed_key;
                  input_buffer_pointer++;
                  }
                }
              break;
              //  Entering the password
            case 1:
              if (!login_stage_started) {
                LCD_clear_screen();
                Show_side_options_menu();
                LCD_write_string_xy(0, 0, "Password:");
                LCD_move_cursor_xy(0, 1);
                login_stage_started = true;
                input_buffer_pointer = 0;
                }
              if (pressed_key == '-') { // Delete last input number
                if (input_buffer_pointer > 0) input_buffer_pointer--;
                LCD_write_string_xy(input_buffer_pointer, 1, " ");
                LCD_move_cursor_xy(input_buffer_pointer, 1);
                }
              else if (pressed_key == '=') {
                input_buffer[input_buffer_pointer] = 0;
                // Validate user password
                if (strcmp(input_buffer, local_user.password) == 0) { // Password is correct
                  login_stage_started = false;
                  login_stage = 0;
                  local_control_running_task = 2;
                  LCD_clear_screen();
                  LCD_write_string_xy(4, 0, "Welcome");
                  LCD_write_string_xy((16 - strlen(local_user.name)) / 2 - 1, 1, local_user.name);
                  LCD_sendData('!');
                  }
                else {
                  LCD_clear_screen();
                  LCD_write_string_xy(5, 0, "Wrong");
                  LCD_write_string_xy(3, 1, "Password !");
                  invalid_local_login_attempt();
                  }
                }
              else if (pressed_key >= '0' && pressed_key <= '9') { // Ignoring invalid options
                if (input_buffer_pointer < 10) {
                  input_buffer[input_buffer_pointer] = pressed_key;
                  input_buffer_pointer++;
                  }
                }
              break;
          }
        break;
        // Devices control
      case 2:
        if (remote_user_loggedin && !control_permission_granted) {
          LCD_clear_screen();
          LCD_write_string_xy(0, 0, "Admin Permission");
          LCD_write_string_xy(3, 1, "Required !");
          //~ Controls can be added to allow the user to go back and view the running devices if needed.
          }
        else {
          Get_devices_status();
          if (control_devices_screen == 0) {  // First run
            Show_running_devices(1);
            control_devices_screen++;
            }
          if (keypad_stat == NO_KEY_PRESSED) return;
          switch (pressed_key) {
              case '1':
                if (control_devices_screen > 1) control_devices_screen--;
                break;
              case '2':
                switch (control_devices_screen) {
                    case 6:
                      // Increment the brightness
                      // Floor the brightness
                      devices_status[5] = devices_status[5] - (devices_status[5] % LAMP_6_BRIGHTNESS_PERCENTAGE_STEP);
                      devices_status[5] += LAMP_6_BRIGHTNESS_PERCENTAGE_STEP;
                      if (devices_status[5] > 100) devices_status[5] = 100;
                      Lamp_dimmable_set_brightness((double)devices_status[5] / 100.0);
                      break;
                    default:
                      Lamp_toggle(control_devices_screen);
                      devices_status[control_devices_screen - 1] = !devices_status[control_devices_screen - 1];
                      break;
                  }
                break;
              case '3':
                switch (control_devices_screen) {
                    case 6:
                      // Decrement the brightness
                      // Ceil the brightness
                      devices_status[5] = devices_status[5] - (devices_status[5] % LAMP_6_BRIGHTNESS_PERCENTAGE_STEP) + LAMP_6_BRIGHTNESS_PERCENTAGE_STEP;
                      devices_status[5] -= LAMP_6_BRIGHTNESS_PERCENTAGE_STEP;
                      if (devices_status[5] < 0) devices_status[5] = 0;
                      Lamp_dimmable_set_brightness((double)devices_status[5] / 100.0);
                      break;
                    default:
                      if (control_devices_screen < 6) control_devices_screen++;
                      break;
                  }
                break;
            }
          Show_devices_controls(control_devices_screen);
          }
        break;
        break;
    }
  }

