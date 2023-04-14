/*
 * remote.c
 *
 * Created: 4/9/2023 4:21:11 PM
 *  Author: hesha
 */

#include "remote.h"

s8 msg_buffer[15];
u8 msg_length;
u8 msg_buffer_pointer;
void (*requesting_function)(void);
bool invalid_user_input;
bool dump_invalid_data;

s8 option[3];

ST_User_t remote_user;

void remote_init(u32 baudRate) {
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

void invalid_remote_login_attempt(void) {
  invalid_trails++;
  if (invalid_trails < 3) {
    s8 msg[50];
    sprintf(msg, "Invalid login attempt! %d attempts remaining.", 3 - invalid_trails);
    println_msg(msg);
    return;
    }
  set_alarm();
  run_system = false;
  }

void request_user_input(void (*requestingFunction)(void), u8 msgLength) {
  requesting_function = requestingFunction;
  msg_length = msgLength;
  }

void userPassword_prompt_handler(void) {
  // Validate the given username (length and syntax)
  if (invalid_user_input) {
    invalid_remote_login_attempt();
    print_msg("\r\nEnter your password:\t");
    request_user_input(userPassword_prompt_handler, 11);
    }
  else {
    if (strcmp(remote_user.password, msg_buffer)) { // Wrong password
      println_msg("\r\nWrong password!");
      invalid_remote_login_attempt();
      print_msg("\r\nEnter your password:\t");
      request_user_input(userPassword_prompt_handler, 11);
      }
    else {
      remote_user_loggedin = true;
      }
    }
  }

void userName_prompt_handler(void) {
  // Validate the given username (length and syntax)
  if (invalid_user_input) {
    invalid_remote_login_attempt();
    print_msg("\r\nEnter your user name:\t");
    request_user_input(userName_prompt_handler, 13);
    }
  else {
    EN_UserStatusCode_t userExists = getUserByName(msg_buffer, &remote_user);
    if (userExists == USER_NOT_FOUND) {
      println_msg("\r\nUser doesn't exist!");
      invalid_remote_login_attempt();
      print_msg("\r\nEnter your user name:\t");
      request_user_input(userName_prompt_handler, 13);
      }
    else {
      // Prompt the user to enter the password
      print_msg("\r\nEnter your password:\t");
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

ISR(USART_RXC_vect) {
  // // If no input requested, ignore the input. No input requested is indicated by msg length of zero
  // if (msg_length == 0) return;

  // // If the msg length is reached without the input being terminated by null, then it's wrong input
  // // If the input is invalid, reset the buffer pointer, set the invalid input flag, call the function responsible for handling the input, and keep ignoring the incoming data till null is reached
  // if (dump_invalid_data) {
  //   if (UDR == 0) {
  //     dump_invalid_data = false;
  //     invalid_user_input = false;
  //     msg_buffer_pointer = 0;
  //     }
  //   return;
  //   }

  // msg_buffer[msg_buffer_pointer] = UDR;
  // msg_buffer_pointer++;

  // // Msg is empty
  // // Ignore null msgs
  // if (msg_buffer_pointer == 1) {
  //   if (msg_buffer[0] == 0) {
  //     msg_buffer_pointer = 0;
  //     return;
  //     }
  //   }

  // // Msg is longer than required
  // if (msg_buffer_pointer == msg_length) {
  //   if (msg_buffer[msg_buffer_pointer - 1] != 0) {
  //     invalid_user_input = true;
  //     dump_invalid_data = true;
  //     msg_buffer_pointer = 0;
  //     callFunWhenBufferReady();
  //     }
  //   }

  // // Msg has ended and is within the required length
  // if (UDR == 0) {
  //   if (msg_buffer_pointer <= msg_length) {
  //     callFunWhenBufferReady();
  //     msg_buffer_pointer = 0;
  //     }
  //   }
  }

// ISR(INT0_vect) {
//   // Initialize communication with the user
//   // Request user login credentials
//   // remote_login_prompt();
//   DIO_toggle(3, PORT_D);
//   }
