/*
 * local.c
 *
 * Created: 4/12/2023 7:26:01 AM
 *  Author: Hesham Hany
 */

#include "local.h"

 // Used to store the state of the lamps and the AC
bool running_devices[7];

// Used to store the brightness of lamp6
s16 dimmer_brightness;

// The last screen shown on the LCD in show running devices task
u8 running_devices_screen;

// The last screen shown on the LCD in devices control task
u8 control_devices_screen;

// 0 = The user's in the progress of entering the user code
// 1 = The user is entering the password
u8 login_stage;

// When cleared the LCD gets initialized to show the appropriate login screen
bool login_stage_started;

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
  // The value in OCR2 determine the brightness of the led
  dimmer_brightness = OCR2;
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
      case 10:
        LCD_write_string_xy(0, 1, OPTIONS_MENU_10);
        break;
    }
  }

// Shows the side options list on the LCD
void Show_side_options_menu(void) {
  LCD_write_string_xy(12, 0, BACKSPACE_OPTION);
  LCD_write_string_xy(12, 1, ENTER_OPTION);
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
        LCD_write_string(":  ");
        break;
    }
  if (screen == 6) {
    s8 brightness[4];
    sprintf(brightness, "%d%%", (u8)((double)dimmer_brightness / 2.55));
    LCD_write_string(brightness);
    }
  else {// Write the device state
    if (running_devices[screen - 1])
      LCD_write_string("On");
    else
      LCD_write_string("Off");
    }
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
    if (running_devices[screen - 1])
      LCD_write_string("On");
    else
      LCD_write_string("Off");
    }
  else if (screen == 6) { // Dimmer
    s8 brightness[4];
    sprintf(brightness, "%d%%", (u8)((double)dimmer_brightness / 2.55));
    LCD_write_string(brightness);
    }
  else {  // Logout screen
    LCD_clear_screen();
    LCD_write_string_xy(4, 0, "Log out?");
    }
  // Show the options menu
  switch (screen) {
      case 1:
        if (running_devices[0])
          Show_bottom_options_menu(8);
        else
          Show_bottom_options_menu(7);
        break;
      case 6:
        Show_bottom_options_menu(9);
        break;
      case 7:
        Show_bottom_options_menu(10);
        break;
      default:
        if (running_devices[screen - 1])
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
    LCD_move_cursor_xy(3, 0);
    LCD_sendData((3 - invalid_trails) + 48);
    LCD_write_string(" attempts");
    LCD_write_string_xy(3, 1, "remaining !");
    _delay_ms(1000);
    return;
    }
  LCD_clear_screen();
  LCD_write_string_xy(4, 0, "Too many");
  LCD_write_string_xy(0, 1, "wrong attempts!");
  _delay_ms(1000);
  LCD_clear_screen();
  LCD_write_string_xy(3, 0, "- System -");
  LCD_write_string_xy(2, 1, "- Suspended -");
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
              if (keypad_stat == NO_KEY_PRESSED) return;
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
                  login_stage_started = false;
                  }
                }
              else if (pressed_key >= '0' && pressed_key <= '9') { // Ignoring invalid options
                if (input_buffer_pointer < 6) {
                  // Echo the input on the LCD
                  LCD_sendData(pressed_key);
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
                  local_user_loggedin = true;
                  LCD_clear_screen();
                  LCD_write_string_xy(4, 0, "Welcome");
                  LCD_write_string_xy((16 - strlen(local_user.name)) / 2 - 1, 1, local_user.name);
                  LCD_sendData('!');
                  _delay_ms(1000);
                  }
                else {
                  LCD_clear_screen();
                  LCD_write_string_xy(5, 0, "Wrong");
                  LCD_write_string_xy(3, 1, "Password !");
                  login_stage_started = false;
                  invalid_local_login_attempt();
                  }
                }
              else if (pressed_key >= '0' && pressed_key <= '9') { // Ignoring invalid options
                // Limit the input length
                if (input_buffer_pointer < 10) {
                  // Echo the input on the LCD
                  LCD_sendData(pressed_key);
                  input_buffer[input_buffer_pointer] = pressed_key;
                  input_buffer_pointer++;
                  }
                }
              break;
          }
        break;
        // Devices control
      case 2:
        if (remote_user_loggedin && !local_control_permission_granted) {
          LCD_clear_screen();
          LCD_write_string_xy(0, 0, "Admin Permission");
          LCD_write_string_xy(3, 1, "Required !");
          //~ Controls can be added to allow the user to go back and view the running devices if needed.
          }
        else {
          Get_running_devices();
          if (control_devices_screen == 0) {  // First run
            Show_devices_controls(1);
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
                      dimmer_brightness += ((double)LAMP_6_BRIGHTNESS_PERCENTAGE_STEP * 2.55);
                      if (dimmer_brightness > 255) dimmer_brightness = 255;
                      Lamp_dimmable_set_brightness(((double)dimmer_brightness / 255.0));
                      break;
                    case 7:
                      // Logout
                      local_user_loggedin = false;
                      control_devices_screen = 0;
                      running_devices_screen = 0;
                      local_control_running_task = 0;
                      LCD_clear_screen();
                      LCD_write_string_xy(1, 0, "logging out...");
                      LCD_write_string_xy(4, 1, "Good Bye!");
                      _delay_ms(1000);
                      break;
                    default:
                      Lamp_toggle(control_devices_screen);
                      running_devices[control_devices_screen - 1] = !running_devices[control_devices_screen - 1];
                      break;
                  }
                break;
              case '3':
                switch (control_devices_screen) {
                    case 6:
                      // Decrement the brightness
                      // Ceil the brightness
                      dimmer_brightness -= ((double)LAMP_6_BRIGHTNESS_PERCENTAGE_STEP * 2.55);
                      if (dimmer_brightness < 0) dimmer_brightness = 0;
                      Lamp_dimmable_set_brightness(((double)dimmer_brightness / 255.0));
                      break;
                    default:
                      if (control_devices_screen < 7) control_devices_screen++;
                      break;
                  }
                break;
              case '4':
                // Moving to logout screen
                if (control_devices_screen == 6) control_devices_screen++;
                break;
            }
          Show_devices_controls(control_devices_screen);
          }
        break;
    }
  }