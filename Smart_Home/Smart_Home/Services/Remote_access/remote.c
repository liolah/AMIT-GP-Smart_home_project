/*
 * remote.c
 *
 * Created: 4/9/2023 4:21:11 PM
 *  Author: Hesham Hany
 */

#include "remote.h"

 // A buffer used to store the user input before sending it to the right function
s8 msg_buffer[15];

// Requested input maximum length
s8 msg_length;

// least available index in the buffer
s8 msg_buffer_pointer;

// The UDR must be read to reset the RXC interrupt. This UDR wil be stored in this variable
s8 udr_temp;
u8 device_number;

// Stores the data of the logged in user
ST_User_t remote_user;

// Used to store the new user data temporarily
ST_User_t new_user;

// Used in deleting a user
ST_User_t temp_user;

// When this flag is set, only digits and backspaces will be accepted as input. 
// (the password and the usercode must be both digits only for them to be used in the local control system as it only can input digits)
bool numerical_input_mode;

// Points to the function responsible for handling the input
void (*requesting_function)(void);

// Used to check if the user input has been requested for a function at least once
bool user_input_accepted;

//* For BT mode(unused) 
// bool invalid_user_input;
// bool dump_invalid_data;

// ***************************************************************************
//^ Private functions declarations 
// ***************************************************************************
void println_msg(s8* msg);

void print_msg(s8* msg);

void callFunWhenBufferReady(void);

void request_user_input(void (*requestingFunction)(void), u8 msgLength, bool numericalInputOnly);

void get_lamp_state(u8 lamp, u8* state);

void remote_login_prompt(void);

void userName_prompt_handler(void);

void userPassword_prompt_handler(void);

void invalid_remote_login_attempt(void);

void logout(void);

void grant_local_control_permission(void);

void print_initial_options_menu(void);

void initial_options_menu(void);

void print_remote_control_menu(void);

void remote_control(void);

void control_device(void);

void add_user_prompt(void);

void add_user_code_prompt(void);

void add_user_password_prompt(void);

void add_user_isAdmin_prompt(void);

void delete_user_prompt(void);

// ***************************************************************************

void Remote_init(u32 baudRate) {
  User_DB_init();
  BT_init(baudRate);
  INT0_init(RISING_EDGE_INTERRUPT_REQUEST);
  UART_RXC_INT_init();
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

void callFunWhenBufferReady(void) {
  requesting_function();
  }

void request_user_input(void (*requestingFunction)(void), u8 msgLength, bool numericalInputOnly) {
  requesting_function = requestingFunction;
  msg_length = msgLength;
  numerical_input_mode = numericalInputOnly;
  }

void get_lamp_state(u8 lamp, u8* state) {
  DIO_Read(lamp + 2, PORT_C, state);
  }

void delete_user_prompt(void) {
  if (!user_input_accepted) {
    print_msg("Enter the user name of the user you want to delete: ");
    request_user_input(delete_user_prompt, 13, false);
    user_input_accepted = true;
    }
  else {
    user_input_accepted = false;
    EN_UserStatusCode_t userExists = getUserByName(msg_buffer, &temp_user);
    if (userExists == USER_NOT_FOUND) {
      println_msg("\rError! User not found. Returning to the main menu...");
      }
    else {
      // Delete the user
      delete_user(&temp_user);
      println_msg("The user has been deleted successfully!\t");
      }
    initial_options_menu();
    }
  }

void print_remote_control_menu(void) {
  println_msg("Select one of the following devices to control:\t");
  println_msg("[1] Lamp 1");
  println_msg("[2] Lamp 2");
  println_msg("[3] Lamp 3");
  println_msg("[4] Lamp 4");
  println_msg("[5] Lamp 5");
  println_msg("[6] Lamp 6 (dimmable)");
  if (remote_user.isAdmin) {
    println_msg("[7] The Door");
    println_msg("[8] Go back to main menu");
    }
  else {
    println_msg("[7] Go back to main menu");
    }
  }

void control_device(void) {
  u8 option = msg_buffer[0];
  switch (device_number) {
      case 6:
        if (option < '0' || option > '9') {
          println_msg("\r\nInvalid input!!\t");
          }
        else {
          option -= 48; // Convert to int
          Lamp_dimmable_set_brightness((double)option / 9.0);
          println_msg("The brightness has been adjusted!");
          }
        break;
      case 7:
        if (option != '0' && option != '1') {
          println_msg("\r\nInvalid input!!\t");
          }
        else {
          if (option == '0') {
            Door_close();
            println_msg("The Door is closed now.");
            }
          else {
            Door_open();
            println_msg("The Door is open now.");
            }
          }
        break;
      default:
        if (option != 'Y' && option != 'y' && option != 'n' && option != 'N') {
          println_msg("\r\nInvalid input!!\t");
          }
        else {
          //! Disabled because the program used more than 99.5% of the data memory and can't be extended further.
          // u8 state;
          // get_lamp_state(option - 48, state);
          // Lamp_toggle(device_number);
          // if (state) {
          //   println_msg("The Lamp is now on!");
          //   }
          // else {
          //   println_msg("The Lamp is now off!");
          //   }
          }
        break;
    }
  remote_control();
  }

// Prints the state of the device and prompts the user if he wants to change it.
void remote_control(void) {
  if (!user_input_accepted) {
    print_remote_control_menu();
    request_user_input(remote_control, 2, true);
    user_input_accepted = true;
    }
  else {
    user_input_accepted = false;
    u8 option = msg_buffer[0];
    if ((!remote_user.isAdmin && option > '7') || option < '1' || option > '8') {
      println_msg("Invalid option!\t");
      remote_control();
      }
    else {
      u8 state;
      get_lamp_state(option - 48, &state);
      device_number = option - 48;
      switch (option) {
          case '6':
            print_msg("Enter the brightness level for the lamp(from 0(off) to 9(max)): ");
            request_user_input(control_device, 2, true);
            break;
          case '7':
            if (remote_user.isAdmin) {
              println_msg("Enter 1 to open the door and 0 to close it: ");
              request_user_input(control_device, 2, true);
              }
            else {
              initial_options_menu();
              }
            break;
          case '8':
            initial_options_menu();
            break;
          default:
            // if (state) {
            //   print_msg("Lamp ");
            //   BT_sendChar(device_number);
            //   println_msg(" is on. Turn it off? (Y/N)");
            //   }
            // else {
            //   print_msg("Lamp ");
            //   // BT_sendChar(device_number);
            //   println_msg(" is off. Turn it on? (Y/N)");
            //   }
            request_user_input(control_device, 2, false);
            break;
        }
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
    if (local_user_loggedin) {
      println_msg("[5] Allow local user control\t");
      }
    }
  else {
    println_msg("Select one of the following options(by entering its number):\t");
    println_msg("[1] Control a device\t");
    println_msg("[2] Log out\t");
    }
  }

void grant_local_control_permission(void) {
  local_control_permission_granted = true;
  }

void initial_options_menu(void) {
  if (!user_input_accepted) {
    print_initial_options_menu();
    request_user_input(initial_options_menu, 2, true);
    user_input_accepted = true;
    }
  else {
    user_input_accepted = false;
    if (remote_user.isAdmin) {
      u8 option = msg_buffer[0];
      if (option < '1' || option > '5') {
        println_msg("Invalid option!\t");
        initial_options_menu();
        }
      else {
        switch (option) {
            case '1':
              add_user_prompt();
              break;
            case '2':
              delete_user_prompt();
              break;
            case '3':
              remote_control();
              break;
            case '4':
              logout();
              break;
            case '5':
              grant_local_control_permission();
              break;
          }
        }
      }
    else {
      u8 option = msg_buffer[0];
      if (option < '1' || option > '2') {
        println_msg("Invalid option!\t");
        initial_options_menu();
        }
      else {
        switch (option) {
            case '1':
              remote_control();
              break;
            case '2':
              logout();
              break;
          }
        }
      }
    }
  }

void logout(void) {
  remote_user_loggedin = false;
  println_msg("To login again you have to disconnect and reconnect to the BT module...");
  println_msg("You have successfully logged out...");
  msg_length = 0;
  }

void add_user_isAdmin_prompt(void) {
  if (!user_input_accepted) {
    println_msg("Do you want to make the new user an admin? (y/n) ");
    request_user_input(add_user_isAdmin_prompt, 2, false);
    user_input_accepted = true;
    }
  else {
    user_input_accepted = false;
    new_user.isAdmin = (msg_buffer[0] == 'y' || msg_buffer[0] == 'Y');
    add_user(&new_user);
    println_msg("User has been added successfully!");
    // Return to the main menu
    initial_options_menu();
    }
  }

void add_user_password_prompt(void) {
  if (!user_input_accepted) {
    println_msg("Enter the new user's password(The password can only consist of numbers and 4 digits at least, 10 at max): ");
    request_user_input(add_user_password_prompt, 11, true);
    user_input_accepted = true;
    }
  else {
    user_input_accepted = false;
    if (strlen(msg_buffer) < 4) {
      println_msg("Password too short!!\t");
      add_user_password_prompt();
      }
    else {
      strcpy(new_user.password, msg_buffer);
      add_user_isAdmin_prompt();
      }
    }
  }

void add_user_code_prompt(void) {
  if (!user_input_accepted) {
    print_msg("Enter the new user's code(must be a unique six digit code): ");
    request_user_input(add_user_code_prompt, 7, true);
    user_input_accepted = true;
    }
  else {// Validating the length of the user code. It can't be more than 6 digits by the input limitations. But the input can be smaller
    user_input_accepted = false;
    if (strlen(msg_buffer) != 6) {
      println_msg("User code too short!");
      add_user_code_prompt();
      }
    else {
      EN_UserStatusCode_t userExists = getUserByCode(msg_buffer, &temp_user);
      if (userExists == USER_NOT_FOUND) {
        strcpy(new_user.code, msg_buffer);
        add_user_password_prompt();
        }
      else {
        println_msg("\rThe user code already exists!\t");
        add_user_code_prompt();
        }
      }
    }
  }

void add_user_prompt(void) {
  if (!user_input_accepted) {
    print_msg("Enter the new user's name: ");
    request_user_input(add_user_prompt, 13, false);
    user_input_accepted = true;
    }
  else {
    user_input_accepted = false;
    EN_UserStatusCode_t userExists = getUserByName(msg_buffer, &temp_user);
    if (userExists == USER_NOT_FOUND) {
      strcpy(new_user.name, msg_buffer);
      add_user_code_prompt();
      }
    else {
      // Prompt the user to enter the user code
      println_msg("\rThe user already exists!\t");
      //! Return to the main menu
      initial_options_menu();
      }
    }
  }

void userPassword_prompt_handler(void) {
  if (!user_input_accepted) {
    print_msg("Enter your password:\t");
    request_user_input(userPassword_prompt_handler, 11, true);
    user_input_accepted = true;
    }
  else {
    user_input_accepted = false;
    if (strcmp(remote_user.password, msg_buffer)) { // Wrong password
      println_msg("Wrong password!");
      invalid_remote_login_attempt();
      userPassword_prompt_handler();
      }
    else {
      remote_user_loggedin = true;
      print_msg("Welcome ");
      print_msg(remote_user.name);
      println_msg("!");
      // Show the options menu
      initial_options_menu();
      }
    }
  }

void userName_prompt_handler(void) {
  // Request user input for the first time and in case of wrong input
  if (!user_input_accepted) {
    print_msg("Enter your user name:\t");
    request_user_input(userName_prompt_handler, 13, false);
    user_input_accepted = true;
    }
  else {
    EN_UserStatusCode_t userExists = getUserByName(msg_buffer, &remote_user);
    user_input_accepted = false;
    if (userExists == USER_NOT_FOUND) {
      println_msg("User doesn't exist!");
      invalid_remote_login_attempt();
      userName_prompt_handler();
      }
    else {
      // Prompt the user to enter the password
      userPassword_prompt_handler();
      }
    }
  }

void remote_login_prompt(void) {
  //! for some reason this part causes a compilation error related to .bss section in memory!!!! 
  // if (!remote_user_loggedin) {
  println_msg("Welcome!");
  // println_msg("Welcome to the Smart Home System!");
  // println_msg("To proceed, please login.");
  userName_prompt_handler();
  //   }
  // else {
  // print_msg("Welcome ");
  // print_msg(remote_user.name);
  // println_msg("!");
  // // Show the options menu
  // initial_options_menu();
  // }
  }

void invalid_remote_login_attempt(void) {
  invalid_trails++;
  s8 msg[50];
  if (invalid_trails < 3) {
    sprintf(msg, "Invalid login attempt! \r\n%d attempts remaining.", 3 - invalid_trails);
    println_msg(msg);
    return;
    }
  strcpy(msg, "Too many login attempts! \r--- System Suspended! ---");
  println_msg(msg);
  Alarm_set();
  run_system = false;
  }

// Handles the user input asynchronously.
ISR(USART_RXC_vect) {
#if UART_COMMUNICATION_INTERFACE ==  PROTEUS_VIRTUAL_TERMINAL
  // Read the UDR to clear the RXC bit
  udr_temp = UDR;

  // If no input requested, ignore the input. No input requested is indicated by msg length of zero
  if (msg_length == 0) return;

  // Accept numbers only in the numerical input mode
  if (numerical_input_mode) {
    if (!((udr_temp >= '0' && udr_temp <= '9') || udr_temp == '\b' || udr_temp == PROTEUS_VIRTUAL_TERMINAL_STRING_DELIMITER || udr_temp == '\n')) {
      return;
      }
    }

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
  // Delete the last input char. Don't allow the user to enter longer input than the maximum required
  if (msg_buffer_pointer == msg_length) {
    if (msg_buffer[msg_buffer_pointer - 1] != PROTEUS_VIRTUAL_TERMINAL_STRING_DELIMITER) {
      msg_buffer_pointer--;
      BT_sendChar('\b');
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
  //! DISCLAIMER: this piece of code wasn't tested and isn't guaranteed to work!
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
