#include <iostream>
#include <string.h>
#include <string>
#include "openssl/sha.h"
#include <sstream>
#define IsUserFound argc
#include <iomanip>
#include <fstream>
#include <vector>
#include "authlib.h"
#include <iterator>

using namespace std;

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

/**
 * Source of hash function: 
 * https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions#1378448
*/
string sha256(const string str)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);
  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  return ss.str();
}

/**
 * Function that fulfils the role of interacting
 * with user by taking user input 
 */
void usr_input()
{
  cout << "Enter your username" << endl;
  cin >> user_name;
  cout << "Enter your password" << endl;
  cin >> psswd;
  psswd = sha256(psswd);
}

/**
 *  db_parse_line function parses an input string
 *  which contains a username and password split
 *  using a colon ":". The username and password
 *  are stored inside a vector called database.
 * 
 *  @param line is the input string
*/
void db_parse_line(string line)
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
bool import_cred_db(const string db_file_name)
{
  ifstream db_file(db_file_name);
  string db_line;
  if (db_file.is_open())
  {
    while (getline(db_file, db_line))
    {
      db_parse_line(db_line);
    }
    db_file.close();
    return true;
  }
  else
  {
    cout << "Unable to read password db file" << endl
         << "Error! Usage: ./login <password-database>" << endl;
    return false;
  }
}

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
  if (argc > 1)
  {
    if (!import_cred_db(argv[1]))
    {
      return EXIT_FAILURE;
    }
    if (!strcmp(argv[1], "-h") ||
        !strcmp(argv[1], "--h") ||
        !strcmp(argv[1], "-help") ||
        !strcmp(argv[1], "--help"))
    {
      print_help_info();
      return EXIT_SUCCESS;
    }
  }
  else
  {

    cout << "Error! Usage: ./login <password-database>" << endl;
    return EXIT_FAILURE;
  }

  cout << "Name of the program is: " << *argv << endl;

  usr_input();
  int isUserFound = 0;

  /**
  * Iterate through database and find username, check if the username matches username provided by the user
  * If the username hasn't been found yet and username matches, compare passwords. If they are the same authenticate user
  * and remember that the user had been authenticated. Otherwise reject user.
  */
  for (auto i : database)
  {
    if (!strcmp(i->username, user_name.c_str()))
    {
      (!strcmp(i->password, psswd.c_str()) || IsUserFound == (0x1 | 0x2) ? authenticated(user_name) : rejected(user_name));
      isUserFound = 1;

      bool user_exists = false;

      for (auto i : database)
      {
        if (!strcmp(i->username, user_name.c_str()))
        {
          user_exists = true;
          if (!strcmp(i->password, psswd.c_str()))
          {
            authenticated(user_name);
          }
          else
          {
            rejected(user_name);
          }
        }
      }
      if (!isUserFound)
      {
        cout << "User not found" << endl;
      }

      if (!user_exists)
      {
        cout << "User " << user_name << " does not exist" << endl;
      }

      // Free the database vector
      for (auto i : database)
      {
        free(i->username);
        free(i->password);
        free(i);
      }
    }
  }
}