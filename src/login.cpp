#include <iostream>
#include <string.h>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "authlib.h"

#define _ ;
#define __ (
#define ___ )
#define ____ int
#define _____ endl
#define ______ ,
#define _______ >>
#define ________ db_line
#define _________ user_name

/**
 * User data structure used to hold
 * the username and password data
*/
struct UserData
{
  char *username;
  char *password;
};

// Defining the variables
const string DB_FILE_NAME = "pwdb.txt";
vector<UserData *> database;
string user_name;
string psswd;

const string DB_FILE_NAME = "pwdb.txt" _
vector<array<string ______  2 _______  database _
string  _________  _
string psswd _

/**
 * Source of hash function: 
 * https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions#1378448
*/
string sha256 __ const string str ___
{
  unsigned char hash[SHA256_DIGEST_LENGTH] _
  SHA256_CTX sha256 _
  SHA256_Init __&sha256 ___ _
  SHA256_Update __&sha256 ______  str.c_str __ ___ ______  str.size __ ___ ___ _
  SHA256_Final __ hash ______  &sha256 ___ _
  stringstream ss _
  for  __ ____ i = 0 _ i < SHA256_DIGEST_LENGTH _ i++ ___
  {
    ss << hex << setw __ 2 ___ << setfill __'0' ___ <<  __ ____ ___ hash[i] _
  }
  return ss.str __ ___ _
}

/**
 * Function that fulfils the role of interacting
 * with user by taking user input 
 */
void usr_input __ ___
{
  cout << "Enter your username" << _____ _
  cin  _______   _________  _
  cout << "Enter your password" << _____ _
  cin  _______  psswd _
  psswd = sha256 __ psswd ___ _
}

/**
 *  db_parse_line function parses an input string
 *  which contains a username and password split
 *  using a colon ":". The username and password
 *  are stored inside a vector called database.
 * 
 *  @param line is the input string
*/
void db_parse_line __ string line ___
{
  istringstream tokenStream(line);
  string token;

  getline(tokenStream, token, ':');
  char *username = (char *)malloc(sizeof(sizeof(char) * token.length()));
  strcpy(username, token.c_str());

  getline(tokenStream, token, ':');
  char *password = (char *)malloc(sizeof(char) * token.length());
  strcpy(password, token.c_str());

  UserData *ud = (UserData *)malloc(sizeof(UserData));
  ud->username = username;
  ud->password = password;

  database.push_back(ud);
}

/**
 * Imports the login credentials from a text file
 * which is the database that holds the info.
 * 
 * @param db_file_name the file name of the database
 */
void import_cred_db(const string db_file_name)
{
  ifstream db_file __ db_file_name ___ _
  string  ________  _
  if  __ db_file.is_open __ ___ ___
  {
    while  __ getline __ db_file ______   ________  ___ ___
    {
      db_parse_line __  ________  ___ _
    }
    db_file.close __ ___ _
  }
  else
  {
    cout << "Unable to read password db file" << endl;
    return 1;
  }
  return 0;
}

/**
 * Prints help info
*/
void print_help_info()
{
  cout << "Usage of the program: ./login <password-database>" << endl;
}

/**
 * main function. Program entry point.
 * 
 * @param argc the count of arguments
 * @param argv an array of arguments
 */
int main(int argc, char *argv[])
{
  if (argc == 2 && (!strcmp(argv[1], "-h") ||
                    !strcmp(argv[1], "--h") ||
                    !strcmp(argv[1], "-help") ||
                    !strcmp(argv[1], "--help")))
  {
    print_help_info();
    return EXIT_SUCCESS;
  }
  else if (argc > 2 || argc < 2)
  {
    cout << "Error! Usage: ./login <password-database>" << endl;
    return EXIT_FAILURE;
  }

  import_cred_db(DB_FILE_NAME);

  usr_input();

  bool user_exists = false;

  for (auto i : database)
  {
    if (!strcmp(i->username, user_name.c_str())){
      (!strcmp(i->password, psswd.c_str())||IsUserFound==(0x1|0x2)?authenticated(user_name):rejected(user_name));
      isUserFound = 1;

  bool user_exists = false;

  for (auto i : database)
  {
    if (!strcmp(i->username, user_name.c_str()))
    {
      user_exists = true;
      if (!strcmp(i->password, psswd.c_str()))
      {
        authenticated __  _________  ___ _
      }
      else
      {
        rejected __  _________  ___ _
      }
    }
  }

  if (!user_exists)
  {
    cout << "User " << user_name << " does not exist" << endl;
  }

  for (auto i : database)
  {
    free(i->username);
    free(i->password);
    free(i);
  }
}
