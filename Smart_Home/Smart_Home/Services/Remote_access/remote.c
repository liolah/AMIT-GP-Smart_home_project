/*
 * remote.c
 *
 * Created: 4/9/2023 4:21:11 PM
 *  Author: Hesham Hany
 */

#include "remote.h"

s8 msg_buffer[15];
s8 msg_length;
s8 msg_buffer_pointer;
void (*requesting_function)(void);
bool invalid_user_input;
bool dump_invalid_data;
s8 udr_temp;
s8 option[3];
u8 device_number;

ST_User_t remote_user;
ST_User_t new_user;
ST_User_t temp_user;

void add_user_prompt(void);
void initial_options_menu(void);
void print_initial_options_menu(void);
void remote_control(void);

void Remote_init(u32 baudRate) {
  BT_init(baudRate);
  }

void callFunWhenBufferReady(void) {
  requesting_function();
  }

void println_msg(s8* msg) {
  // Send the msg
  BT_sendString(msg);
  // Send CRLF - carriage return + new line
  BT_sendString("\r\n");
  }

void print_msg(s8* msg) {
  // Send the msg
  BT_sendString(msg);
  }

void request_user_input(void (*requestingFunction)(void), u8 msgLength) {
  requesting_function = requestingFunction;
  msg_length = msgLength;
  }

void delete_user_prompt(void) {
  if (invalid_user_input) {
    println_msg("\r\nInvalid user name!\t");
    //! The system should ask the user wether he want s to continue or not, and continue to validate his input. 
    //! But due to close deadline, the user will be returned to the initial menu.
    print_initial_options_menu();
    request_user_input(initial_options_menu, 2);
    }
  else {
    EN_UserStatusCode_t userExists = getUserByName(msg_buffer, &temp_user);
    if (userExists == USER_NOT_FOUND) {
      println_msg("\rError! User not found. Returning to the main menu...");
      print_initial_options_menu();
      request_user_input(initial_options_menu, 2);
      }
    else {
      // Delete the user
      delete_user(&temp_user);
      println_msg("The user has been deleted successfully!\t");
      //! Return to the main menu
      print_initial_options_menu();
      request_user_input(initial_options_menu, 2);
      }
    }
  }

void print_remote_control_menu(void) {
  println_msg("Select one of the following devices to control:\t");
  println_msg("[1] Lamp 1");
  println_msg("[2] Lamp 2");
  println_msg("[3] Lamp 3");
  println_msg("[4] Lamp 4");
  println_msg("[5] Lamp 5");
  println_msg("[6] Lamp 6");
  if (remote_user.isAdmin) {
    println_msg("[7] The Door");
    }
  }

// TODO: Send the status of each device to the user instead of just asking him to switch the device on or off.

void control_device(void) {
  u8 option = msg_buffer[0];
  if (invalid_user_input || option < '0' || option > '9') {
    println_msg("\r\nInvalid input!!\t");
    print_remote_control_menu();
    request_user_input(remote_control, 2);
    }
  else {
    if (device_number < 6) {
      if (option == '1') {
        Lamp_on(device_number);
        println_msg("The device has been turned on!");
        }
      else {
        Lamp_off(device_number);
        println_msg("The device has been turned off!");
        }
      }
    else if (device_number == 6) { // Dimmable led
      Lamp_dimmable_set_brightness(((double)(option - 48) / 9.0));
      println_msg("The brightness has been adjusted!");
      }
    else {
      if (option == '1') {
        Door_open();
        println_msg("The Door is open now.");
        }
      else {
        Door_close();
        println_msg("The Door is closed now.");
        }
      }
    print_remote_control_menu();
    request_user_input(remote_control, 2);
    }
  }

void remote_control(void) {
  u8 option = msg_buffer[0];
  if (remote_user.isAdmin) {
    if (invalid_user_input || option < '1' || option > '7') {
      println_msg("Invalid option!\t");
      print_remote_control_menu();
      request_user_input(remote_control, 2);
      }
    else {
      println_msg("Do you want to switch the device on or off? (Enter 1 to turn it on. 0 to turn it off)");
      println_msg("For dimmable lamp the brightness levels are from 0 to 9.");
      println_msg("If you slected the door, entr 1 to open and 0 to close.");
      request_user_input(control_device, 2);
      device_number = option - 48;
      }
    }
  else {
    if (invalid_user_input || option < '1' || option > '6') {
      println_msg("Invalid option!\t");
      print_remote_control_menu();
      request_user_input(remote_control, 2);
      }
    else {
      println_msg("Do you want to switch the device on or off? (Enter 1 to turn it on. 0 to turn it off)");
      println_msg("For dimmable lamp the brightness levels are from 0 to 9.");
      println_msg("If you slected the door, entr 1 to open and 0 to close.");
      request_user_input(control_device, 2);
      device_number = option - 48;
      }
    }
  }

void print_initial_options_menu(void) {
  if (remote_user.isAdmin) {
    println_msg("Select one of the following options(by entering its number):\t");
    println_msg("[1] Add user\t");
    println_msg("[2] Delete user\t");
    println_msg("[3] Control a device\t");
    println_msg("[4] Log out\t");
    }
  else {
    println_msg("Select one of the following options(by entering its number):\t");
    println_msg("[1] Control a device\t");
    println_msg("[2] Log out\t");
    }
  }

void initial_options_menu() {
  if (remote_user.isAdmin) {
    u8 option = msg_buffer[0];
    if (invalid_user_input || option < '1' || option > '4') {
      println_msg("Invalid option!\t");
      print_initial_options_menu();
      request_user_input(initial_options_menu, 2);
      }
    else {
      switch (option) {
          case '1':
            print_msg("Enter the user name: ");
            request_user_input(add_user_prompt, 13);
            break;
          case '2':
            print_msg("Enter the user name: ");
            request_user_input(delete_user_prompt, 13);
            break;
          case '3':
            print_remote_control_menu();
            request_user_input(remote_control, 2);
            break;
          case '4':
            remote_user_loggedin = true;
            println_msg("To login again you have to disconnect and reconnect to the BT module...");
            println_msg("You have successfully logged out...");
            msg_length = 0;
            break;
        }
      }
    }
  else {
    u8 option = msg_buffer[0];
    if (invalid_user_input || option < '1' || option > '2') {
      println_msg("Invalid option!\t");
      print_initial_options_menu();
      request_user_input(initial_options_menu, 2);
      }
    else {
      switch (option) {
          case '1':
            print_remote_control_menu();
            request_user_input(remote_control, 2);
            break;
          case '2':
            remote_user_loggedin = true;
            println_msg("To login again you have to disconnect and reconnect to the BT module...");
            println_msg("You have successfully logged out...");
            msg_length = 0;
            break;
        }
      }
    }
  }

void add_user_isAdmin_prompt(void) {
  if (invalid_user_input) {
    println_msg("\r\nInvalid input!!\t");
    //! The system should ask the user wether he wants to continue or not, and continue to validate his input. 
    //! But due to close deadline, the user will be returned to the initial menu.
    print_initial_options_menu();
    request_user_input(initial_options_menu, 2);
    }
  else {
    new_user.isAdmin = (msg_buffer[0] == 'y' || msg_buffer[0] == 'Y');
    add_user(&new_user);
    println_msg("User has been added successfully!");
    //! Return to the main menu
    print_initial_options_menu();
    request_user_input(initial_options_menu, 2);
    }
  }

void add_user_password_prompt(void) {
  if (invalid_user_input) {
    println_msg("\r\nPassword too long!!\t");
    //! The system should ask the user wether he want s to continue or not, and continue to validate his input. 
    //! But due to close deadline, the user will be returned to the initial menu.
    print_initial_options_menu();
    request_user_input(initial_options_menu, 2);
    }
  else {
    strcpy(new_user.password, msg_buffer);
    print_msg("Do you want to make the new user an admin? (y/n) ");
    request_user_input(add_user_isAdmin_prompt, 2);
    }
  }

void add_user_code_prompt(void) {
  if (invalid_user_input) {
    println_msg("\r\nInvalid user code!\t");
    //! The system should ask the user wether he want s to continue or not, and continue to validate his input. 
    //! But due to close deadline, the user will be returned to the initial menu.
    print_initial_options_menu();
    request_user_input(initial_options_menu, 2);
    }
  else {
    EN_UserStatusCode_t userExists = getUserByCode(msg_buffer, &temp_user);
    if (userExists == USER_NOT_FOUND) {
      strcpy(new_user.code, msg_buffer);
      print_msg("Enter the new user's password: ");
      request_user_input(add_user_password_prompt, 11);
      }
    else {
      // Prompt the user to enter the password
      println_msg("\rThe user code already exists!\t");
      //! Return to the main menu
      print_initial_options_menu();
      request_user_input(initial_options_menu, 2);
      }
    }
  }

void add_user_prompt(void) {
  if (invalid_user_input) {
    println_msg("\r\nInvalid user name!\t");
    //! The system should ask the user wether he want s to continue or not, and continue to validate his input. 
    //! But due to close deadline, the user will be returned to the initial menu.
    print_initial_options_menu();
    request_user_input(initial_options_menu, 2);
    }
  else {
    EN_UserStatusCode_t userExists = getUserByName(msg_buffer, &temp_user);
    if (userExists == USER_NOT_FOUND) {
      strcpy(new_user.name, msg_buffer);
      print_msg("Enter the new user's code(must be a unique six digit code): ");
      request_user_input(add_user_code_prompt, 7);
      }
    else {
      // Prompt the user to enter the user code
      println_msg("\rThe user already exists!\t");
      //! Return to the main menu
      print_initial_options_menu();
      request_user_input(initial_options_menu, 2);
      }
    }
  }

void invalid_remote_login_attempt(void) {
  invalid_trails++;
  if (invalid_trails < 3) {
    s8 msg[50];
    sprintf(msg, "\r\nInvalid login attempt! \r\n%d attempts remaining.", 3 - invalid_trails);
    println_msg(msg);
    return;
    }
  set_alarm();
  run_system = false;
  }

void userPassword_prompt_handler(void) {
  // Validate the given username (length and syntax)
  if (invalid_user_input) {
    invalid_remote_login_attempt();
    print_msg("Enter your password:\t");
    request_user_input(userPassword_prompt_handler, 11);
    }
  else {
    if (strcmp(remote_user.password, msg_buffer)) { // Wrong password
      print_msg("Wrong password!");
      invalid_remote_login_attempt();
      print_msg("Enter your password:\t");
      request_user_input(userPassword_prompt_handler, 11);
      }
    else {
      remote_user_loggedin = true;
      print_msg("Welcome ");
      print_msg(remote_user.name);
      println_msg("!");
      // Show the options menu
      print_initial_options_menu();
      request_user_input(initial_options_menu, 2);
      }
    }
  }

void userName_prompt_handler(void) {
  // Validate the given username (length and syntax)
  if (invalid_user_input) {
    invalid_remote_login_attempt();
    print_msg("Enter your user name:\t");
    request_user_input(userName_prompt_handler, 13);
    }
  else {
    EN_UserStatusCode_t userExists = getUserByName(msg_buffer, &remote_user);
    if (userExists == USER_NOT_FOUND) {
      print_msg("User doesn't exist!");
      invalid_remote_login_attempt();
      print_msg("Enter your user name:\t");
      request_user_input(userName_prompt_handler, 13);
      }
    else {
      // Prompt the user to enter the password
      print_msg("Enter your password:\t");
      request_user_input(userPassword_prompt_handler, 11);
      }
    }
  }

void remote_login_prompt(void) {
  println_msg("Welcome to the Smart Home System!");
  println_msg("To proceed, please login.");
  print_msg("Enter your user name:\t");
  request_user_input(userName_prompt_handler, 13);
  }

// Handles the user input asynchronously.
ISR(USART_RXC_vect) {
#if UART_COMMUNICATION_INTERFACE ==  PROTEUS_VIRTUAL_TERMINAL
  // Read the UDR to clear the RXC bit
  udr_temp = UDR;

  // If no input requested, ignore the input. No input requested is indicated by msg length of zero
  if (msg_length == 0) return;

  // Handling backspaces
  if (udr_temp == '\b') {
    if (msg_buffer_pointer > 0) {
      msg_buffer_pointer--;
      BT_sendChar(udr_temp);
      }
    return;
    }

  msg_buffer[msg_buffer_pointer] = udr_temp;
  msg_buffer_pointer++;

  // Msg is empty
  // Ignore null msgs
  if (msg_buffer_pointer == 1) {
    if (msg_buffer[0] == PROTEUS_VIRTUAL_TERMINAL_STRING_DELIMITER) {
      msg_buffer_pointer = 0;
      return;
      }
    }

  // Echo the sent char on the terminal
  //! Proteus virtual terminal doesn't send a line feed char (ASCII code: 10). Instead it sends a carriage return (ASCII code: 13).
  if (udr_temp != PROTEUS_VIRTUAL_TERMINAL_STRING_DELIMITER)
    BT_sendChar(udr_temp);

  // Msg is longer than required
  if (msg_buffer_pointer == msg_length) {
    if (msg_buffer[msg_buffer_pointer - 1] != PROTEUS_VIRTUAL_TERMINAL_STRING_DELIMITER) {
      invalid_user_input = true;
      dump_invalid_data = true;
      msg_buffer_pointer = 0;
      BT_sendChar('\r');
      callFunWhenBufferReady();
      }
    }

  // Msg has ended and is within the required length
  if (udr_temp == PROTEUS_VIRTUAL_TERMINAL_STRING_DELIMITER) {
    if (msg_buffer_pointer <= msg_length) {
      // Replace the carriage return with null to terminate the string correctly
      msg_buffer[msg_buffer_pointer - 1] = '\0';
      BT_sendChar('\r');
      callFunWhenBufferReady();
      msg_buffer_pointer = 0;
      }
    }
#elif UART_COMMUNICATION_INTERFACE ==  HC_05_BLUETOOTH_MODULE
  // Read the UDR to clear the RXC pin
  udr_temp = UDR;
  // If no input requested, ignore the input. No input requested is indicated by msg length of zero
  if (msg_length == 0) return;

  // If the msg length is reached without the input being terminated by null, then it's wrong input
  // If the input is invalid, reset the buffer pointer, set the invalid input flag, call the function responsible for handling the input, and keep ignoring the incoming data till null is reached
  if (dump_invalid_data) {
    if (udr_temp == HC_05_BLUETOOTH_MODULE_STRING_DELIMITER) {
      dump_invalid_data = false;
      invalid_user_input = false;
      msg_buffer_pointer = 0;
      }
    return;
    }

  msg_buffer[msg_buffer_pointer] = udr_temp;
  msg_buffer_pointer++;

  // Msg is empty
  // Ignore null msgs
  if (msg_buffer_pointer == 1) {
    if (msg_buffer[0] == HC_05_BLUETOOTH_MODULE_STRING_DELIMITER) {
      msg_buffer_pointer = 0;
      return;
      }
    }

  // Msg is longer than required
  if (msg_buffer_pointer == msg_length) {
    if (msg_buffer[msg_buffer_pointer - 1] != HC_05_BLUETOOTH_MODULE_STRING_DELIMITER) {
      invalid_user_input = true;
      dump_invalid_data = true;
      msg_buffer_pointer = 0;
      callFunWhenBufferReady();
      }
    }

  // Msg has ended and is within the required length
  if (udr_temp == HC_05_BLUETOOTH_MODULE_STRING_DELIMITER) {
    if (msg_buffer_pointer <= msg_length) {
      callFunWhenBufferReady();
      msg_buffer_pointer = 0;
      }
    }
#endif
  }

ISR(INT0_vect) {
  // Initialize communication with the user
  // Request user login credentials
  remote_login_prompt();
  }
